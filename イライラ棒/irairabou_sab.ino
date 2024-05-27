  #define PIN 13
  unsigned char spk=0;
  unsigned char spk1=0;//スピーカー初期化
  void sw_spk(void);
  void sw_spk1(void);
  int hu=0,stop1=0,start=0,a=0,KILL1=0;
void setup() {
  //イライラ棒制御
  pinMode(2,INPUT);//イライラ棒の当たった時の判定
  pinMode(3,INPUT);//開始用スイッチ
  pinMode(9,OUTPUT);//予備
  //BGM
  pinMode(5,OUTPUT);//LED1
  pinMode(6,OUTPUT);//LED2
  pinMode(7,OUTPUT);//LED3
  attachInterrupt(digitalPinToInterrupt(2),sw_spk,RISING);
  attachInterrupt(digitalPinToInterrupt(3),sw_spk1,RISING);
  
}

void loop() {
     int l,y;
     int BGM1[]={/*1*/523,523,523,0,392,494,440,392,349,330,349,392,392,131,131,0,/*1*/523,523,523,0,392,494,440,392,349,330,349,392,392,131,131,0,/*2*/523,523,523,587,659,587,523,659,587,523,659,587,523,/*1*/523,523,523,0,392,494,440,392,349,330,349,392,392,0,/*3*/415,494,677,659,587,0,500,0,523,659,587,523,392,494,440,392,440,392,0};
     int T[]={/*1*/300,50,20,30,200,200,200,200,200,300,100,200,400,200,200,200,/*1*/300,50,20,30,200,200,200,200,200,300,100,200,400,200,200,200,/*2*/300,50,200,200,200,200,400,100,100,300,200,200,400,/*1*/300,50,20,30,200,200,200,200,200,300,100,200,400,200,/*3*/1000,200,200,300,200,100,400,200,800,200,200,200,200,200,200,200,200,200,400};
     int BGM2[]={466,0,392,0,440,0,349,0,392,0,311,0,349,0,294,0,262,311,262,0};
     int T1[]={200,50,50,100,200,50,50,100,200,50,50,100,200,50,50,100,400,400,400,10};
     int test[]={77,19};
  if(start==1)
  {
     while(a<=test[hu])
     {
      if(hu==0){//通常
      tone(PIN,BGM1[a],T[a]);
      delay(T[a]);
      
      }else{//死んだ
      tone(PIN,BGM2[a],T1[a]);
      delay(T1[a]);
      }
      a++;
    }
    if(hu==1)
    {
      digitalWrite(5+KILL1,HIGH);
      delay(100);    
      a=0;
      KILL1++;
      stop1=0;
      hu=0;
    }
  if(KILL1>=3)
  {
      start=0;
    //点滅5回
    for(l=0;l<=5;l++){
      for(y=0;y<=2;y++){
        digitalWrite(5+y,HIGH);
        delay(100);
        digitalWrite(5+y,LOW);
        delay(100);
       }
     }
    a=0;start=0;hu=1;KILL1=0;stop1==0;
   }
  }
}
    


void sw_spk(void){
  if(stop1==0 && start==1){
  hu=1;
  stop1=1;
  a=0;
  }
}
void sw_spk1(void){
  if(stop1==0){
  start=1;
  a=0;
  KILL1=0;
  }  
}
