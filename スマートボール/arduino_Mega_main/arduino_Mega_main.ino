int InPut_Pin_Number[16]={A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15};
int OutPut_Pin_Number[16]={22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37};
int Led_Pin_Number[3][4]={{2,3,4,5},{6,7,8,9},{10,11,12,13}};
bool Main_Bingo_Check[16]={false};
bool Bingo_Flag[16]={false};
int Bingo=0;
int InPut_Chenge[16];
int countsafe=1015;
void setup() {
  Serial.begin(9600);

  for(int i=0;i<sizeof(OutPut_Pin_Number)/sizeof(int);i++){
    pinMode(OutPut_Pin_Number[i], OUTPUT);
  }
  for(int i=0;i<3;i++){
    for(int a=0;a<4;a++){
      pinMode(Led_Pin_Number[i][a], OUTPUT);
    }
  }
  /*for(int i=0;i<sizeof(InPut_Pin_Number)/sizeof(int);i++){
    pinMode(InPut_Pin_Number[i], INPUT); 
  }*/
  delay(1000);
  for(int i=0;i<16;i++){
    InPut_Chenge[i]=countsafe-analogRead(InPut_Pin_Number[i]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int InPut_Chenge_Fine_Tuning[16];

  for(int i=0;i<16;i++){

    
    InPut_Chenge_Fine_Tuning[i] = analogRead(InPut_Pin_Number[i]) + InPut_Chenge[i];
    if(InPut_Chenge_Fine_Tuning[i]<=1000){//要調整部分
      Main_Bingo_Check[i]=true;
      digitalWrite(OutPut_Pin_Number[i],HIGH);
    }
  }
  for(int i=0;i<16;i++){
    Serial.print(InPut_Chenge_Fine_Tuning[i]);
    Serial.print(" ");
    if((i+1)%4==0){
      Serial.println("");
    }
  }
  Serial.println("");
  //delay(1000);
  if(Bingo_Check_Flag()){
    Bingo++;
    //Seven_segment_Display(Bingo);
  }
}

bool Bingo_Check_Flag(){
  for(int i=0;i<=3;i++){
    if(Bingo_Flag[i]==false && (Main_Bingo_Check[i] && Main_Bingo_Check[i+1] && Main_Bingo_Check[i+2] && Main_Bingo_Check[i+3])){//縦
      Bingo_Flag[i]=true;
      return true;
    }
    if(Bingo_Flag[i+4]==false && (Main_Bingo_Check[i] && Main_Bingo_Check[i+4] && Main_Bingo_Check[i+8] && Main_Bingo_Check[i+12])){//横
      Bingo_Flag[i+4]=true;
      return true;
    }
  }
  if(Bingo_Flag[8]==false && (Main_Bingo_Check[0] && Main_Bingo_Check[6] && Main_Bingo_Check[11] && Main_Bingo_Check[16])){//斜め
    Bingo_Flag[8]=true;
    return true;
  }
  if(Bingo_Flag[9]==false && (Main_Bingo_Check[3] && Main_Bingo_Check[6] && Main_Bingo_Check[9] && Main_Bingo_Check[12])){//斜め
    Bingo_Flag[9]=true;
    return true;
  }
  return false;
}

void Seven_segment_Display(int Number_remaining){//残りの個数計算
  int Timer[3];
  bool OnOff[10][4] {
    {LOW, LOW, LOW, LOW},     // 0
    {LOW, LOW, LOW, HIGH},    // 1
    {LOW, LOW, HIGH, LOW},    // 2
    {LOW, LOW, HIGH, HIGH},   // 3
    {LOW, HIGH, LOW, LOW},    // 4
    {LOW, HIGH, LOW, HIGH},   // 5
    {LOW, HIGH, HIGH, LOW},   // 6
    {LOW, HIGH, HIGH, HIGH},  // 7
    {HIGH, LOW, LOW, LOW},    // 8
    {HIGH, LOW, LOW, HIGH},   // 9
  };
  Timer[0]=Number_remaining/100;//100の位
  Timer[1]=Number_remaining/10-Timer[0]*10;//10の位
  Timer[2]=Number_remaining%10;//1の位
  for(int a=0;a<=2;a++){
    digitalWrite(Led_Pin_Number[a][0],OnOff[Timer[a]][0]);
    digitalWrite(Led_Pin_Number[a][1],OnOff[Timer[a]][1]);
    digitalWrite(Led_Pin_Number[a][2],OnOff[Timer[a]][2]);
    digitalWrite(Led_Pin_Number[a][3],OnOff[Timer[a]][3]);
  }          
}
