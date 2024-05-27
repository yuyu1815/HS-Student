  #define PIN 13
  unsigned char spk=0;//スピーカー初期化
  unsigned char spk1=0;//スピーカー初期化
  void sw_spk(void);//割り込み用関数
  void sw_spk1(void);//割り込み用関数
  
  int Life=3,Count=0,Kill=0,Count2=0,PinNanber=5,ab=0;;
  bool StartGame=false,Game1=false,Act=false,Flag=false;
  void setup() {
    randomSeed(analogRead(0));
  pinMode(2,INPUT);//イライラ棒の当たった時の判定
  pinMode(3,INPUT);//モーター信号受け取り
  pinMode(4,INPUT);//開始用ピン
  pinMode(5,OUTPUT);//LED1
  pinMode(8,OUTPUT);//LED2
  pinMode(9,OUTPUT);//LED3
  pinMode(11,OUTPUT);//モーター
  pinMode(12,OUTPUT);//モーター
  
  pinMode(13,OUTPUT);//スピーカー
  pinMode(17, INPUT);//ゴールのスイッチ感知用
    
  pinMode(15,OUTPUT);//スタート合図
  pinMode(16,OUTPUT);//ゴール合図
  pinMode(18,OUTPUT);//死んだことを送る用
  pinMode(19, INPUT);//タイムアップ
  attachInterrupt(digitalPinToInterrupt(2),sw_spk,RISING);//  割り込みのピン２
  attachInterrupt(digitalPinToInterrupt(3),sw_spk1,RISING);// 割り込みのピン３
 //    digitalWrite(18,HIGH);//resetpin
}
void loop() {
  
  if(StartGame==false && digitalRead(4)==HIGH){//スタート
  delay(50);//チャタリングするため
 // digitalWrite(18,HIGH);//resetpin
  digitalWrite(15,HIGH);
  delay(1000);
  digitalWrite(15,LOW);
  Life=8,Count=0,Kill=0,Count2=0,ab=0;;
  Game1=false,Act=false,Flag=false;
  StartGame=true;
  }else if(StartGame==true){
    BGM();
 }
}

int BGM(void){//BGM
  Kill=0;
  //Act=false;
  int BGM[][78]={{/*1*/523,523,523,0,392,494,440,392,349,330,349,392,392,131,131,0,/*1*/523,523,523,0,392,494,440,392,349,330,349,392,392,131,131,0,/*2*/523,523,523,587,659,587,523,659,587,523,659,587,523,/*1*/523,523,523,0,392,494,440,392,349,330,349,392,392,0,/*3*/415,494,677,659,587,0,500,0,523,659,587,523,392,494,440,392,440,392,0},{466,0,392,0,440,0,349,0,392,0,311,0,349,0,294,0,262,311,262,0}};
  int T1[][78]={{/*1*/300,50,20,30,200,200,200,200,200,300,100,200,400,200,200,200,/*1*/300,50,20,30,200,200,200,200,200,300,100,200,400,200,200,200,/*2*/300,50,200,200,200,200,400,100,100,300,200,200,400,/*1*/300,50,20,30,200,200,200,200,200,300,100,200,400,200,/*3*/1000,200,200,300,200,100,400,200,800,200,200,200,200,200,200,200,200,200,400},{200,50,50,100,200,50,50,100,200,50,50,100,200,50,50,100,400,400,400,10}};
  for(Count=0;Count<=77 &&  StartGame==true;Count++){

    if(Act==true || digitalRead(18)==HIGH || digitalRead(19)==HIGH){
      Damage();
    }
      tone(PIN,BGM[Kill][Count],T1[Kill][Count]);
      delay(T1[Kill][Count]);
      Serial.println(Count);
      Count2++;
   if((Kill==1 && Count>=21)|| StartGame==false){
      Count=100;
    }
  }
  //tone(PIN,0,20);
  //delay(20);
}

int Damage(void){//LED処理
  
  if(Kill==1 || Life>0){//Lifeが残っている場合
    PinNanber++;
    Life--;
    Count=0;
    Act=false;
    delay(200);
  }
  if(digitalRead(16)==HIGH){
    StartGame=false;
    Goal();

  }
  if(Life==0 || digitalRead(19)==HIGH){//死んだとき
    Flag=true;
    if(Flag==true){//死んだとき
    Flag=false;
    StartGame=false;
    Life=0;
    Kill=1;
    digitalWrite(16,LOW);
     
    digitalWrite(5,LOW);
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);
   digitalWrite(18,HIGH);
   delay(5000);
   digitalWrite(18,LOW);
    }
  }
}

int Goal(void){
  
}
void sw_spk1(void){//スタート
  if(StartGame==true){
    Morter();
  }
}
  
void sw_spk(void){//当たったと起動
  if(StartGame==true && Kill==0){
    Kill=1;//1変更
    Act=true;
    Count=0;//リセット
    
    if(ab==0){
     digitalWrite(5,HIGH);  
    ab=1;
    }else if(ab==1){
      digitalWrite(8,HIGH);  
    ab=2;
    }else if(ab==2){
      digitalWrite(9,HIGH);  
    ab=3;
    }else{
      digitalWrite(5,LOW);  
      digitalWrite(8,LOW);  
      digitalWrite(9,LOW);  
    ab=0;
      }
  }
}
int Morter(void){
  int PIN_01,PIN_02,a=0;
  PIN_01=11;
  PIN_02=12;
  if(Count2>=2){
    switch (random(3000)%2){
    case 0:
      digitalWrite(PIN_01,LOW);
      digitalWrite(PIN_02,LOW);
      delay(100);
      digitalWrite(PIN_01,HIGH);
      digitalWrite(PIN_02,LOW);
    break;

    case 1:
      digitalWrite(PIN_01,LOW);
      digitalWrite(PIN_02,LOW);
      delay(100);
      digitalWrite(PIN_01,LOW);
      digitalWrite(PIN_02,HIGH);  
    break;

    case 2:
      digitalWrite(PIN_01,LOW);
      digitalWrite(PIN_02,LOW);
      delay(100);
      digitalWrite(PIN_01,LOW);
      digitalWrite(PIN_02,HIGH);  
    break;
    }
  }
}
