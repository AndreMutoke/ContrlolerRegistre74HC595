#ifndef REGISTER_74HC595_H_INCLUDED
#define REGISTER_74HC595_H_INCLUDED

#include <Arduino.h>

class ShiftRegister_74HC595
{
public :
    ShiftRegister_74HC595(int DS = 5, 
                          int SH_CP = 6, 
                          int ST_CP = 7);

    void begin();
    void WrittingBitByBit(uint8_t data);

private :
    uint8_t m_dataPin;
    uint8_t m_shiftAllowerPin;
    uint8_t m_writtingAllowerPin;

    int returnBit(uint8_t data, int pos);
};


#endif // REGISTER_74HC595_H_INCLUDED