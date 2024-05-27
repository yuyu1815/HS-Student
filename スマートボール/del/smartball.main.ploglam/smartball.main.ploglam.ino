int Bingo=0;
bool Bingo_Flag[10];
bool Main_Bingo_Check[16];
int InPut_Pin_Nunber[]={3,5,6,9,/**/14,15,16,17};
int OutPut_Pin_Nunber[]={2,4,7,8,/**/10,11,12,13};
void setup() {
  Serial.begin(9600);

  for(int i=0;i<=7;i++){
    pinMode(OutPut_Pin_Nunber[i], OUTPUT);
  }
  for(int i=0;i<=7;i++){
    pinMode(InPut_Pin_Nunber[i], INPUT); 
  }
}

void loop() {
  int Second_Arduino_uno_Pass;
      Second_Arduino_uno_Pass = Serial.read();
  if(Second_Arduino_uno_Pass<=9){
    Main_Bingo_Check[Second_Arduino_uno_Pass+8]=true;
  }
  for(int i=0;i<=7;i++){//要調整
    if(analogRead(InPut_Pin_Nunber[i])<=900){
      Main_Bingo_Check[i]=true;
    }
  }
    for(int i=0;i<=7;i++){//要調整
    int test;
    test=analogRead(InPut_Pin_Nunber[i]);
    if(test<1000){
      Serial.print("0");
    }
      Serial.print(test);
      Serial.print(" ");
    if(i==3)Serial.println("");
    }
    Serial.println("");
    Serial.println("");
    delay(200);
   /* for(int i=0;i<=15;i++){//要調整
      Serial.print(Main_Bingo_Check[i]);
    }
    Serial.println("");*/
/*-----------------ビンゴ場所-----------------*/
  if(Bingo_Check_Flag()){
    Bingo++;
  }
}

bool Bingo_Check_Flag(){
  for(int i=0;i<=3;i++){
    if(Bingo_Flag[i]=!true && (Main_Bingo_Check[i] && Main_Bingo_Check[i+1] && Main_Bingo_Check[i+2] && Main_Bingo_Check[i+3])){//縦
      Bingo_Flag[i]=true;
      return true;
    }
    if(Bingo_Flag[i+4]=!true && (Main_Bingo_Check[i] && Main_Bingo_Check[i+4] && Main_Bingo_Check[i+8] && Main_Bingo_Check[i+12])){//横
      Bingo_Flag[i+4]=true;
      return true;
    }
  }
  if(Bingo_Flag[8]=!true && (Main_Bingo_Check[0] && Main_Bingo_Check[6] && Main_Bingo_Check[11] && Main_Bingo_Check[16])){//斜め
    Bingo_Flag[8]=true;
    return true;
  }
  if(Bingo_Flag[9]=!true && (Main_Bingo_Check[3] && Main_Bingo_Check[6] && Main_Bingo_Check[9] && Main_Bingo_Check[12])){//斜め
    Bingo_Flag[9]=true;
    return true;
  }
  return false;
}

/*
4 8 12 16
3 7 11 15
2 6 10 14
1 5 9  13
*/