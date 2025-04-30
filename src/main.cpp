#include <Arduino.h>
/// @author André MUTOKE
/// @details Ce bout de code permet de gerer le registre à décalage tout en permettant sa comprehension
/// @date 13 Avril 2025
/// @file main.cpp
/**
 * 
 *  
 *         
 *                    74HC595
 *                   __________
 *         Q1 1 ----|          |---- 16 Vcc(5v)
 *         Q2 2 ----|          |---- 15 Q0
 *         Q3 3 ----|          |---- 14 DS (Data Serial input)
 *         Q4 4 ----|          |---- 13 /OE (Output Enable) To put an 1 we must give it a O(GND)
 *         Q5 5 ----|          |---- 12 ST_CP (STore Clock Pin) or Latch Pin : Allow to write state on output PIN
 *         Q6 6 ----|          |---- 11 SH_CP (SHift Clock Pin) allow to shift data
 *         Q7 7 ----|          |---- 10 /MR(To reset input register) To put it in 0 state we must give it a 1(Vcc)
 *        GND 8 ----|__________|---- 9 Q7'
 * 
 */

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

uint8_t data[8] = {
  0x80,
  0x40,
  0x20,
  0x10,
  0x08,
  0x04,
  0x02,
  0x01,  
};

static uint8_t RIBAMBELLE[13][8] = {
    {0x80, 0x80,0x80, 0x80, 0x80, 0x80, 0xFE, 0x00}, // L ok
    {0x7C, 0x82,0x82, 0x82, 0xFE, 0x82, 0x82, 0x00}, // A ok
    {0xFC, 0x82,0x82, 0xFC, 0x82, 0x82, 0x82, 0x00}, // R ok
    {0xFE, 0x20,0x10, 0x10, 0x10, 0x10, 0xFE, 0x00}, // I ok
    {0xFC, 0x82,0x82, 0xFC, 0x82, 0x82, 0xFC, 0x00}, // B ok
    {0x7C, 0x82,0x82, 0x82, 0xFE, 0x82, 0x82, 0x00}, // A ok
    {0x82, 0xC6,0xAA, 0x92, 0x82, 0x82, 0x82, 0x00}, // M ok
    {0xFC, 0x82,0x82, 0xFC, 0x82, 0x82, 0xFC, 0x00}, // B ok

    {0xFE, 0x80,0x80, 0xF0, 0x80, 0x80, 0xFE, 0x00}, // E OK
    {0x80, 0x80,0x80, 0x80, 0x80, 0x80, 0xFE, 0x00}, // L ok
    {0x80, 0x80,0x80, 0x80, 0x80, 0x80, 0xFE, 0x00}, // L ok
    {0xFE, 0x80,0x80, 0xF0, 0x80, 0x80, 0xFE, 0x00}, // E OK

};

void writeOneLed(int xposData, int yposData, uint8_t *dataLine, uint8_t *dataCol1, ShiftRegister_74HC595 *registerLine, ShiftRegister_74HC595 *registerCol1, ShiftRegister_74HC595 *registerCol2, int j)
{
  if(j%2 == 0)
  {
    registerCol1->WrittingBitByBit(*(dataCol1+xposData));
  }
  else
  {
    registerCol2->WrittingBitByBit(*(dataCol1+xposData));
  }
  //registerCol1->WrittingBitByBit(*(dataCol1+xposData));
  registerLine->WrittingBitByBit(~*(dataLine+yposData));
}


ShiftRegister_74HC595 myRegisterLine(8, 9, 10);
ShiftRegister_74HC595 myRegisterCol1(2, 3, 4);
ShiftRegister_74HC595 myRegisterCol2(5, 6, 7);

void setup()
{
  myRegisterLine.begin();
  myRegisterCol1.begin();
  myRegisterCol2.begin();
}

void loop()
{
 for(int j=0; j<13; ++j){
    // int t = msg[j];
     for(int i=0; i<8; ++i){
      writeOneLed(i, i, data, (RIBAMBELLE[j]+0), &myRegisterLine, &myRegisterCol1, &myRegisterCol2, j);
      //dataCol >>= 1;
      delay(5);    
    }
  }
  delay(1000);
}