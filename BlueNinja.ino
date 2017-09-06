#include <stdlib.h>
#include <stdio.h>
#include <SPI.h>
#include "BlueNinja.h"

void blueNinja(){
  pinMode(MISO, OUTPUT);//pinmode D12
  
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  SPI.setDataMode(SPI_MODE1);//立ち上がり,アイドルが0

  SPCR |= _BV(SPE);//よくわからん、おまじない
  SPI.attachInterrupt();//割り込み??
}

ISR (SPI_STC_vect){
  char ch = SPDR;  
  Serial.print(ch);
}

