/// @author André MUTOKE
/// @details Ce bout de code permet de gerer le registre à décalage tout en permettant sa comprehension
/// @date 13 Avril 2025
/// @file main.cpp

#include <Arduino.h>
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


#define DATA_INPUT       5//  The 14th pin on the 74HC595 
#define SHIFT_ALLOWER    6 // The 11th pin on the 74HC595 
#define WRITTING_ALLOWER 7 // The 12th pin on the 74HC595 

uint8_t data[3] = {0xAA, 0x04, 0x30};

void setup(){
  pinMode(DATA_INPUT, OUTPUT);
  pinMode(SHIFT_ALLOWER, OUTPUT);
  pinMode(WRITTING_ALLOWER, OUTPUT);
}

void loop(){
  for(int i=0; i<3; ++i){
    EcrireBitParBit(data[i]);
    delay(2000);
  }
  delay(2500);
}

int returnBit(uint8_t data, int pos)
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

void EcrireBitParBit(uint8_t data){
  digitalWrite(WRITTING_ALLOWER, LOW);
  for(int i=0; i<8; ++i){
      digitalWrite(SHIFT_ALLOWER, LOW);
      digitalWrite(DATA_INPUT, returnBit(data, i));
      digitalWrite(SHIFT_ALLOWER, HIGH);
  }
  digitalWrite(WRITTING_ALLOWER, HIGH);
}
