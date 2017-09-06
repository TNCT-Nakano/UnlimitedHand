#include <SPI.h>
 
#define SSPin 51
 
void setup() {
  Serial.begin (115200); 
  Serial.println("Master");
 
  pinMode(MOSI,OUTPUT); //SSピンを出力設定
 
  SPI.setBitOrder(MSBFIRST);  //最上位ビット(MSB)から送信
  SPI.setClockDivider(SPI_CLOCK_DIV4);  //通信速度をデフォルト
  SPI.setDataMode(SPI_MODE2);   //アイドル5Vで0V→5Vの変化で送信する
  
  SPI.begin();  //開始
}
 
void loop() {
  char snd = 'a';
  char rcv;
 
  //UARTから読み込み
  //snd = Serial.read();
 
  //データがあれば送信
  //if(snd != -1){
 
    //このSlaveをセレクトする
    //（マスタ通信は有効です）
    SetSSPin(LOW);
 
    //送信
    SPI.transfer(snd);
    delay(100);
 
    //受信
    //rcv = SPI.transfer('a');
 
    //データ確認
    //Serial.println(rcv);
  //}
}
 
/*
 * SSピンの設定
 * Lowでマスタからの通信が有効（セレクト）
 * (Highではマスタから通信出来ない(無視される）セレクト解除の状態)
 */
void SetSSPin(int val)
{ 
    digitalWrite(SSPin, val); 
}
