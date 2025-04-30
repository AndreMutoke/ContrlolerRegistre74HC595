/// @author André MUTOKE
/// @details Ce bout de code permet de gerer le registre à décalage tout en permettant sa comprehension
/// @date 13 Avril 2025
/// @file main.cpp

#include <Arduino.h>
#include <74HC595Ctrl.h>
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

uint8_t data[3] = {0xAA, 0x04, 0x30};
// 10101010       00000100      00110000
uint8_t dataLine[]= {
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF 
};
uint8_t dataCol[]= {
  0x00,
  0x00,
  0x00,
  0x00,
  0xFF 
};



ShiftRegister_74HC595 myRegister(5, 6, 7);
ShiftRegister_74HC595 myRegister2(8, 9, 10);


void drawChar(char c, uint8_t *dataLine, uint8_t *dataCol)
{
  /*
  00000000  ------>   ~00000000
  01110000  ------>   ~01110000
  10001000  ------>   ~10001000
  10001000  ------>   ~10001000
  11111000  ------>   ~11111000
  10001000  ------>   ~10001000
  10001000  ------>   ~10001000
  10001000  ------>   ~10001000
  |     ||
        ||________>    00000000
  |     |_________>    00000000
         _________>    00000000
         _________>    00111111
         _________>    01001000
         _________>    01001000
         _________>    01001000
         _________>    00111111

  
  
  */
  switch (c)
  {
  case 'A':
    *(dataLine+0) = ~0b00000000;
    *(dataLine+1) = ~0b01110000;
    *(dataLine+2) = ~0b10001000;
    *(dataLine+3) = ~0b10001000;
    *(dataLine+4) = ~0b11111000;
    *(dataLine+5) = ~0b10001000;
    *(dataLine+6) = ~0b10001000;
    *(dataLine+7) = ~0b10001000;

    *(dataCol+0) = 0b00111111;
    *(dataCol+1) = 0b01001000;
    *(dataCol+2) = 0b01001000;
    *(dataCol+3) = 0b01001000;
    *(dataCol+4) = 0b00111111;
    *(dataCol+5) = 0b00000000;
    *(dataCol+6) = 0b00000000;
    *(dataCol+7) = 0b00000000;
    break;
  
  default:
    break;
  }
}


void print(uint8_t *dataLine, uint8_t *dataCol)
{
  drawChar('A', dataLine, dataCol);

}

void showScreen(uint8_t *dataLine, uint8_t *dataCol)
{
  for(int i=0; i<8; ++i){
    for(int j=0; j<8; ++j){
      myRegister.WrittingBitByBit(*(dataLine+i));
      myRegister2.WrittingBitByBit(*(dataCol+j));
    }
  }
}
void setup()
{
  myRegister.begin();
  myRegister2.begin();
}

void loop()
{
  print(dataLine, dataCol);
  delay(2500);
}