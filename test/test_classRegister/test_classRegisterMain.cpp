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
ShiftRegister_74HC595 myRegister(5, 6, 7);
void setup()
{
  myRegister.begin();
}

void loop()
{
  for(int i=0; i<3; ++i){
    myRegister.WrittingBitByBit(data[i]);
    delay(2000);
  }
  delay(2500);
}