/* Objects for Serial Connection   */
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
extern UH uh;
const char newline='\n';//改行文字をここで設定する

void decoder(char*);

//引数なし関数
typedef struct{
  void (*func)();
  const char *command;
}pair1_t;
void help();

const static pair1_t pair1[]={{help,"help"},{dummy_ninja,"dummy"}};
const static size_t pair1_cnt=sizeof(pair1)/sizeof(pair1[0]);
//引数1の関数
typedef struct {
  void (*func)(char*);
  const char *command;
}pair2_t;
void vibration(char*);

const static pair2_t pair2[]={{vibration,"vbr"}};
const static size_t pair2_cnt=sizeof(pair2)/sizeof(pair2[0]);




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
  static const uint8_t arg_max=4;
  static const char split[]=" ,";
  char *argv[arg_max+1];
  int argn[arg_max+1];
  char *it;
  uint8_t argc=1,idx;
  argv[0]=it=strtok(line,split);
  while(it!=NULL&&argc<arg_max){
    argv[argc++]=it=strtok(NULL,split);
  }
  //Serial.println(argv[0]);
  switch (argc){
    case 2:
      //引数なし
      for (idx=0;idx<pair1_cnt;idx++){
        const pair1_t *p=&pair1[idx];
        if (!strcmp(argv[0],p->command)){
          (*p->func)();
          return;
        }
      }
    return;
    case 3:
      for (idx=0;idx<pair2_cnt;idx++){
        const pair2_t *p=&pair2[idx];
        if (!strcmp(argv[0],p->command)){
          (*p->func)(argv[1]);
          return;
        }
      }
    return ;

    case 4:

    return;
    default:
    return;
  }
}

void help(){
  Serial.println("help");
}

void vibration(char* arg){
  int x = atoi(arg);
  dprint("vbr");
  uh.moveVibrationMotor(x);

}

