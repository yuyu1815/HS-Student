int Sab_Bingo_Check[8];
  int OutPut_Pin_Nunber[]={2,4,7,8,/**/10,11,12,13};
  int InPut_Pin_Nunber[]={3,5,6,9,/**/14,15,16,17};
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

    for(int i=0;i<=7;i++){//要調整
    if(analogRead(InPut_Pin_Nunber[i])<=900){
     // Sab_Bingo_Check[i]=true;
     Serial.write(i);
    }
  }

}
