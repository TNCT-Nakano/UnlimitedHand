#include <string.h>

//ここではデバック用の文字列を生成する。
extern const char newline;
static const char space ='*';//デバックの余白に表示するもの
void dprint(const char *s){
  size_t block=30;//[Byte]
  char msg[block+1];
  int idx;
  const char *p=s;
  //領域を作成する。
  msg[0]='!';//コメント行であることを宣言
  for (idx =1;idx<block-1&&*p!='\0';idx++){
    msg[idx]=*p;
    p++;
  }
  for (;idx<block-1;idx++){
    msg[idx]=space;
  }
  msg[block-1]=newline;
  msg[block]='\0';
  Serial.print(msg);

  
}

