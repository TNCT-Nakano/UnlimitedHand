#include <stdlib.h>
#include <stdio.h>

unsigned short xorshift(){
  static unsigned short y = 0x1234;
  y = y ^ (y << 13); y = y ^ (y >> 8);
  return y = y ^ (y << 5);
}

void dummy_ninja(){
  char buf[31];
  int rnd;
  
  sprintf(buf,"%x",xorshift());
  for (int i=1;i<6;i++){
    sprintf(buf,"%s,%x",buf,xorshift());
  }
  strcat(buf,"\n");
  Serial.print(buf);
}

