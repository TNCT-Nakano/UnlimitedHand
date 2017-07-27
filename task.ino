#include "task.h"
#include <UH.h>
#include <math.h>
extern UH uh;
static unsigned short xorshift(){
  static unsigned short y = 0x1234;
  y = y ^ (y << 13); y = y ^ (y >> 8);
  return y = y ^ (y << 5);
}

void help(int argc,char** argv){
  Serial.println("help");
}

void dummy(int argc,char** argv){
  char buf[31];
  int rnd;

  sprintf(buf,"%x",xorshift());
  for (int i=1;i<6;i++){
    sprintf(buf,"%s,%x",buf,xorshift());
  }
  strcat(buf,"\n");
  Serial.print(buf);
}

void vibration(int argc,char** argv){
  int x = atoi(argv[1]);
  dprint("vbr");
  uh.moveVibrationMotor(x);

}

void vibration_on(int argc,char** argv){
  uh.onVibrationMotor();
}

void vibration_off(int argc,char** argv){
  uh.offVibrationMotor();
}

void ack(int argc,char** argv){
  dprint("ack");
}

int limit(int v,int a,int b){//[b..a]に制約
  v=min(v,a);
  v=max(v,b);
  return v;
}


void ems(int argc,char** argv){
  int ch=atoi(argv[1]);
  int time=atoi(argv[2]);
  int vlot=atoi(argv[3]);
  int boot=atoi(argv[4]);
  int temp;
  // 制約をかける
  ch=limit(ch,7,0);
  time=limit(time,200,0);
  vlot=limit(vlot,12,0);
  boot=limit(boot,20,5);
  uh.setStimulationChannel(ch);
  uh.setStimulationTime(time);
  uh.setStimulationVoltage(vlot);
  for (temp=0;temp<boot;temp++){uh.keepVoltage(vlot);}
  /*
  Serial.print(argc);Serial.print(',');
  Serial.print(time);Serial.print(',');
  Serial.print(vlot);Serial.print(',');
  Serial.println(boot);
  */
}
