#include "main_window.h"
#include <QApplication>
#include <QFontDialog>

#include <iostream>

#include "CANDatabase.h"

void test()
{
    BYTE data[8] = {0b00000010, 0b00000100, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000};
    uint8_t start_bit_in_byte = 10 % 8;
    uint8_t cur_bit = start_bit_in_byte;
    uint8_t start_byte = 10 / 8;
    uint8_t cur_byte = start_byte;
    int64_t value = 0;  // 读取出来的数据存放单元
    uint8_t bits = 0;  // 已经读取了多少个位
    if (false)    // Intel
    {
        while (bits < 8)
        {
            if (cur_bit > 7)
            {
                cur_bit = 0;
                ++cur_byte;
            }

            uint8_t bit_val = 0x01<<cur_bit;
            uint64_t tmp = (0 != (data[cur_byte]&bit_val))?1:0;    // 取出当前位的值 0/1
            value |= tmp<<bits;   // tmp<<bits相当于给第bits个位取值，然后让value按位或上tmp，让value的第bits位取值
            ++bits;
            ++cur_bit;
        }
    }
    else  // Motorola_LSB
    {
        while (bits < 8)
        {
            if (cur_bit > 7)
            {
                cur_bit = 0;
                --cur_byte;
            }

            uint8_t bit_val = 0x01<<cur_bit;
            uint64_t tmp = (0 != (data[cur_byte]&bit_val))?1:0;    // 取出当前位的值 0/1
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
            uint64_t tmp = (0 != (data[cur_byte]&bit_val))?1:0;    // 取出当前位的值 0/1
            value += tmp;
            --cur_bit;
        }
    }
#endif

    if (true)
    {
        uint64_t tmp = 0x01;
        tmp = tmp<<(8-1);
        if (0 != (tmp & value))   // 负数
        {
            value &= ~tmp;
            value = ~value + 1;
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // test();

    QFont font;
    bool ok = false;
    font = QFontDialog::getFont(&ok, font, 0, "", QFontDialog::DontUseNativeDialog);
    a.setFont(font);

    MainWindow w;
    w.show();

    return a.exec();
}
