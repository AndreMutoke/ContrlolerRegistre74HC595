#include "74HC595Ctrl.h"

ShiftRegister_74HC595::ShiftRegister_74HC595(int DS, 
                                             int SH_CP, 
                                             int ST_CP)
{
    this->m_dataPin = DS;
    this->m_shiftAllowerPin = SH_CP;
    this->m_writtingAllowerPin = ST_CP;
}

void ShiftRegister_74HC595::begin()
{
    pinMode(this->m_dataPin, OUTPUT);
    pinMode(this->m_shiftAllowerPin, OUTPUT);
    pinMode(this->m_writtingAllowerPin, OUTPUT);
}

int ShiftRegister_74HC595::returnBit(uint8_t data, int pos)
{
    uint8_t dataCtrl = 0x00; 
    switch(pos)
    {
        case 0:
        dataCtrl = 0x01; // 0b00000001; 
        break;
    case 1:
        dataCtrl = 0x02; // 0b00000010;
        break;
    case 2:
        dataCtrl = 0x04; // 0b00000100;
        break;
    case 3:
        dataCtrl = 0x08; // 0b00001000;
        break;
    case 4:
        dataCtrl = 0x10; // 0b00010000;
        break;
    case 5:
        dataCtrl = 0x20; // 0b00100000;
        break;
    case 6:
        dataCtrl = 0x40; // 0b01000000;
        break;
    case 7:
        dataCtrl = 0x80; // 0b10000000;
        break;
    default :
        break;
    }
    return data &= dataCtrl;
}

void ShiftRegister_74HC595::WrittingBitByBit(uint8_t data)
{
    digitalWrite(this->m_writtingAllowerPin, LOW);
    for(int i=0; i<8; ++i){
        digitalWrite(this->m_shiftAllowerPin, LOW);
        digitalWrite(this->m_dataPin, returnBit(data, i));
        digitalWrite(this->m_shiftAllowerPin, HIGH);
    }
    digitalWrite(this->m_writtingAllowerPin, HIGH);
}