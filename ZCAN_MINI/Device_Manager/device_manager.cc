#include "device_manager.h"

/**
 * @brief DeviceManager::getInstance    局部静态的方式实现单例类
 * @return
 */
DeviceManager *DeviceManager::GetInstance()
{
    static DeviceManager deviceManager;
    return &deviceManager;
}

DeviceManager::DeviceManager(QObject *parent) : QObject(parent),
    device_type_index_(0),
    device_index_(0),
    channel_index_(0),
    work_mode_index_(0),
    resistance_enable_(true),
    baud_index_(0),
    abit_baud_index_(0),
    dbit_baud_index_(0),
    filter_mode_(1),
    acc_code_("00000000"),
    acc_mask_("FFFFFFFF"),
    id_("00000001"),
    frame_type_index_(0),
    protocol_index_(1),
    canfd_exp_index_(1),
    frm_delay_time(1000),
    frm_delay_flag(false),
    datas_("00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63"),
    send_type_index_(0),
    send_count_once_(10),
    auto_send_index_(0),
    auto_send_period_(1000)
{

}
