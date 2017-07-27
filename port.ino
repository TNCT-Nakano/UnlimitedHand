/* Objects for Serial Connection   */
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "port.h"
#include "task.h"

const char newline='\n';//改行文字をここで設定する
#define CMD_MAX 16
void decoder(char*);


command_t cmd[CMD_MAX]={0};
static int cmd_cnt;




void cmd_setup(){
  memset(cmd,0,sizeof(cmd));
  cmd_cnt=0;
  cmd_insert("help",help);
  cmd_insert("dummy",dummy);
  cmd_insert("vbr",vibration);
  cmd_insert("vbr_on",vibration_on);
  cmd_insert("vbr_off",vibration_off);
  cmd_insert("ack",ack);
  cmd_insert("ems",ems);
}

void cmd_insert(const char* cc,void (*fn)(int,char**)){
  command_ptr ptr=&cmd[cmd_cnt++];
  ptr->cmd=cc;
  ptr->func=fn;
}

//依存:buffer,pos
void serialEvent() {
  //条件付きFIFOを実装する。
  static  const uint8_t line_max=64;
  static  char buf[line_max]={0};//バッファ
  static  uint8_t pos=0;//FIFO用の位置
  char c;
  while (Serial.available()>0){
     c=Serial.read();
     if (c==newline){
       buf[pos]='\0';
       decoder(buf);
       pos=0;
     }else{
       buf[pos]=c;
       pos=pos+1;
     }
  }
}

void decoder(char* line){
  static const uint8_t arg_max=6;
  static const char split[]=" ,";
  command_ptr ptr;
  char *argv[arg_max+1];
  char *it;

  uint8_t argc=1,idx;
  argv[0]=it=strtok(line,split);
  while(it!=NULL&&argc<arg_max){
    argv[argc++]=it=strtok(NULL,split);
  }
  argc--;
  //Serial.println(argv[0]);
  for (idx=0;idx<cmd_cnt;idx++){
    ptr=&cmd[idx];
    if (!strcmp(argv[0],ptr->cmd)){
      ptr->func(argc,argv);
      return ;
    }
  }
  return ;
}
