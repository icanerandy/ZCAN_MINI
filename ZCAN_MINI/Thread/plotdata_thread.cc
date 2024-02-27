#include "plotdata_thread.h"

PlotDataThread::PlotDataThread(QCustomPlot* const plot,const unsigned long long msg_id, const CppCAN::CANSignal& ref_speed, const CppCAN::CANSignal& rel_speed)
    : plot_(plot),
      msg_id_(msg_id),
      ref_speed_(ref_speed),
      rel_speed_(rel_speed)
{

}

void PlotDataThread::beginThread()
{
    m_pause = false;

    RecMsgThread* rec_msg_thread = RecMsgThread::getInstance();
    connect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_Receive_Data* const, const uint)>(&RecMsgThread::newMsg),
            this, static_cast<void (PlotDataThread::*)(const ZCAN_Receive_Data* const, const uint)>(&PlotDataThread::slot_newMsg));
    connect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_ReceiveFD_Data* const, const uint)>(&RecMsgThread::newMsg),
            this, static_cast<void (PlotDataThread::*)(const ZCAN_ReceiveFD_Data* const, const uint)>(&PlotDataThread::slot_newMsg));
}

void PlotDataThread::pauseThread()
{
    m_pause = true;

    RecMsgThread* rec_msg_thread = RecMsgThread::getInstance();
    disconnect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_Receive_Data* const, const uint)>(&RecMsgThread::newMsg),
            this, static_cast<void (PlotDataThread::*)(const ZCAN_Receive_Data* const, const uint)>(&PlotDataThread::slot_newMsg));
    disconnect(rec_msg_thread, static_cast<void (RecMsgThread::*)(const ZCAN_ReceiveFD_Data* const, const uint)>(&RecMsgThread::newMsg),
            this, static_cast<void (PlotDataThread::*)(const ZCAN_ReceiveFD_Data* const, const uint)>(&PlotDataThread::slot_newMsg));
}

void PlotDataThread::stopThread()
{
    m_stop = true;
}

double PlotDataThread::getValue(const BYTE * const data, const CppCAN::CANSignal& signal)
{
    const uint8_t start_bit_in_byte = signal.start_bit() % 8;
    uint8_t cur_bit = start_bit_in_byte;
    const uint8_t start_byte = signal.start_bit() / 8;
    uint8_t cur_byte = start_byte;
    int32_t value = 0;  // 读取出来的数据存放单元
    uint8_t bits = 0;  // 已经读取了多少个位
    if (CppCAN::CANSignal::LittleEndian == signal.endianness())    // Intel
    {
        while (bits < signal.length())
        {
            if (cur_bit > 7)
            {
                cur_bit = 0;
                ++cur_byte;
            }

            uint8_t bit_val = 0x01<<cur_bit;
            uint32_t tmp = (0 != (data[cur_byte]&bit_val))?1:0;    // 取出当前位的值 0/1
            value |= tmp<<bits;   // tmp<<bits相当于给第bits个位取值，然后让value按位或上tmp，让value的第bits位取值
            ++bits;
            ++cur_bit;
        }
    }
    else  // Motorola_LSB
    {
        while (bits < signal.length())
        {
            if (cur_bit > 7)
            {
                cur_bit = 0;
                --cur_byte;
            }

            uint8_t bit_val = 0x01<<cur_bit;
            uint32_t tmp = (0 != (data[cur_byte]&bit_val))?1:0;    // 取出当前位的值 0/1
            value |= tmp<<bits;   // tmp<<bits相当于给第bits个位取值，然后让value按位或上tmp，让value的第bits位取值
            ++bits;
            ++cur_bit;
        }
    }
//#define Motorola_MSB
#ifdef Motorola_MSB
    else    // Motorola_MSB
    {
        while (bits < sig.length())
        {
            if (cur_bit < 0)
            {
                cur_bit = 7;
                ++cur_byte;
            }

            value <<= 1;
            uint8_t bit_val = 0x01<<cur_bit;
            uint32_t tmp = (0 != (data[cur_byte]&bit_val))?1:0;    // 取出当前位的值 0/1
            value += tmp;
            --tmp;
        }
    }
#endif

    if (CppCAN::CANSignal::Signed == signal.signedness())
    {
        uint32_t tmp = 0x01;
        tmp <<= (signal.length()-1);
        if (0 != (tmp & value))   // 负数
        {
            value &= ~tmp;
            value = ~value + 1;
        }
    }

    return value * signal.scale() + signal.offset();
}

void PlotDataThread::run()
{
    // 线程任务
    m_stop = false;

    last_time = std::chrono::high_resolution_clock::time_point(std::chrono::high_resolution_clock::now());

    double duration_time = 0.0;
    t1 = std::chrono::high_resolution_clock::time_point(std::chrono::microseconds::zero());
    t2 = std::chrono::high_resolution_clock::time_point(std::chrono::microseconds::zero());
    t1 = std::chrono::high_resolution_clock::now();

    while (!m_stop)
    {
        if (!m_pause)
        {
            t2 = std::chrono::high_resolution_clock::now();
            duration_time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1.0;  // 定时1us，其实是1ms，精度为1us
            if (duration_time - 1 > 0)
            {
                realTimeData();
                t1 = std::chrono::high_resolution_clock::now();
            }
        }
    }
    quit();
}

void PlotDataThread::slot_newMsg(const ZCAN_Receive_Data* const can_data, const uint len)
{
    QVector<QCPGraphData>* const ref_data = plot_->graph(0)->data()->coreData();
    QVector<QCPGraphData>* const rel_data = plot_->graph(1)->data()->coreData();

    static auto start_time = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point current_time;
    std::chrono::high_resolution_clock::duration duration_us;

    uint i = 0;
    while (i < len)
    {
        if (GET_ID(can_data[i].frame.can_id) != msg_id_)
            return;

        const BYTE* const data = can_data[i].frame.data;

        const double ref_speed = getValue(data, ref_speed_);
        const double rel_speed = getValue(data, rel_speed_);

        current_time = std::chrono::high_resolution_clock::now();
        duration_us = std::chrono::duration_cast<std::chrono::microseconds>(current_time - start_time);

        const double key = duration_us.count() / 1000000.0;

        ref_data->push_back(QCPGraphData(key, ref_speed));
        rel_data->push_back(QCPGraphData(key, rel_speed));

        ++i;
    }
}

void PlotDataThread::slot_newMsg(const ZCAN_ReceiveFD_Data* const canfd_data, const uint len)
{
    QVector<QCPGraphData>* ref_data = plot_->graph(0)->data()->coreData();
    QVector<QCPGraphData>* rel_data = plot_->graph(1)->data()->coreData();

    static auto start_time = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point current_time;
    std::chrono::high_resolution_clock::duration duration_us;

    uint i = 0;
    while (i < len)
    {
        if (GET_ID(canfd_data[i].frame.can_id) != msg_id_)
            return;

        const BYTE* const data = canfd_data[i].frame.data;

        const double ref_speed = getValue(data, ref_speed_);
        const double rel_speed = getValue(data, rel_speed_);

        current_time = std::chrono::high_resolution_clock::now();
        duration_us = std::chrono::duration_cast<std::chrono::microseconds>(current_time - start_time);

        const double key = duration_us.count() / 1000000.0;

        ref_data->push_back(QCPGraphData(key, ref_speed));
        rel_data->push_back(QCPGraphData(key, rel_speed));

        ++i;
    }
}

void PlotDataThread::realTimeData()
{
    // 定义车速范围和每次变化的最大步长
    const double minSpeed = 0.0;        // 最小车速（km/h）
    const double maxSpeed = 180.0;      // 最大车速（km/h）
    const double maxChange = 2.0;       // 每次变化的最大步长（km/h）

    // 创建随机数引擎和分布
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-maxChange, maxChange);

    // 更新当前车速
    static double currentSpeed = minSpeed + (maxSpeed - minSpeed) / 2.0;  // 初始车速为速度范围的中间值
    currentSpeed += dis(gen);
    if (currentSpeed < minSpeed) {
        currentSpeed = minSpeed;
    } else if (currentSpeed > maxSpeed) {
        currentSpeed = maxSpeed;
    }

    /*--------------------------------------------------------------------*/
    static auto start_time = std::chrono::high_resolution_clock::now();

    auto current_time = std::chrono::high_resolution_clock::now();

    auto duration_us = std::chrono::duration_cast<std::chrono::microseconds>(current_time - start_time);

    double key = duration_us.count() / 1000000.0;

    QVector<QCPGraphData>* const data = plot_->graph(0)->data()->coreData();
    data->push_back(QCPGraphData(key, currentSpeed));
    QVector<QCPGraphData>* const data1 = plot_->graph(1)->data()->coreData();
    data1->push_back(QCPGraphData(key, currentSpeed + (std::rand() % 10 - 5)));

//    auto last_duration = std::chrono::duration_cast<std::chrono::microseconds>(current_time - last_time);
//    if (last_duration.count()/1.0 > 1)
//        qDebug() << last_duration.count() / 1.0 << " us";
//    last_time = current_time;

    if (key > 10)
        pauseThread();
}
