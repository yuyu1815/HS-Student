#include "CytronMakerSumo.h"
/**
わからない人は触らないでね
**/
/*bool buzzerState = false;
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
int Now_time=0,Time_Count=0;
int melodyPitch[] = {100,0,20,10};
int melodyDuration[] = {100, 10, 10, 10, 10, 10, 10, 10, 10};
int arrayNumber = sizeof(melodyPitch) / sizeof(melodyPitch[0]);*/
void setup() {
  // Initialize the Maker Sumo
  MakerSumo.begin();
  Serial.begin(9800);


  MakerSumo.setMotorSpeed(MOTOR_L, -255); 
  MakerSumo.setMotorSpeed(MOTOR_R, -255);
  delay(1*1000);
  MakerSumo.setMotorSpeed(MOTOR_L, 0); 
  MakerSumo.setMotorSpeed(MOTOR_R, 0);

  /*currentMillis = millis();
  previousMillis =millis();*/
}

void loop() {
  MoveMotor();
  //Music();
}

void Music(){
  //没になりました
  /*  currentMillis = millis(); 
  // 半周期ごとにブザーの状態を切り替える
  if(Time_Count<=melodyDuration[Now_time]){
    if(arrayNumber>=Now_time){
      Now_time++;
    }else{
      Now_time=0;
    }
    Time_Count++;
  }else{
    Time_Count=0;
  }
  if (millis() - previousMillis >= melodyPitch[Now_time]) {
    previousMillis = millis(); // 前回の時間を更新
    buzzerState = !buzzerState; // ブザーの状態を反転
    digitalWrite(8, buzzerState ? HIGH : LOW);
  }*/
}

void MoveMotor(){
  int ReftSpeed, LeftSpeed; // ローカル変数として宣言

  MoveSpeed(digitalRead(OPP_L) ,digitalRead(OPP_FL) ,digitalRead(OPP_FC) ,digitalRead(OPP_FR),digitalRead(OPP_R), &ReftSpeed, &LeftSpeed); // ポインターを引数として渡す
  setSpeed(ReftSpeed,LeftSpeed);//スピード(0~100の%で入力してください)
  //Serial.print(ReftSpeed);Serial.print(" ");Serial.println(LeftSpeed);

}

void MoveSpeed(int LeftMove,int FrontLeftMove,int FrontMove,int FrontRightMove,int RightMove, int *ReftSpeed, int *LeftSpeed){//方向
  // デフォルトのスピードを設定（前進）
  //Serial.print(LeftMove);Serial.print(" ");Serial.print(FrontLeftMove);Serial.print(" ");Serial.print(FrontMove);Serial.print(" ");Serial.print(FrontRightMove);Serial.print(" ");Serial.println(RightMove);Serial.println(" ");
  // センサーの組み合わせに応じてスピードを変更
  switch (LeftMove << 4 | FrontLeftMove << 3 | FrontMove << 2 | FrontRightMove << 1 | RightMove) {
    case 0b11111: // センサーが反応しない場合はデフォルトのまま
      *ReftSpeed = 0/*-255*/;
      *LeftSpeed = 0/*255*/;
      break;
    case 0b11110: // 右端センサーが反応した場合は右モーターを加速
    case 0b11100:
    case 0b11000:
      *ReftSpeed = -255;
      *LeftSpeed = 255;
      break;
    case 0b11101: // 右前センサーが反応した場合は右回転
    case 0b11001:
      *ReftSpeed = -255;
      *LeftSpeed = 255;
      break;
    case 0b10001:
    case 0b10101:
    case 0b11011: // 中央前センサーが反応した場合は後退
      *ReftSpeed = -255;
      *LeftSpeed = -255;
      break;
    case 0b10011:
    case 0b10111: // 左前センサーが反応した場合は左回転
      *ReftSpeed = 255;
      *LeftSpeed = -255;
      break;
    case 0b01111: // 左端センサーが反応した場合は左モーターを加速
    case 0b00111:
    case 0b00011:
      *ReftSpeed = 255;
      *LeftSpeed = -255;
      break;
    case 0b01110://普通は反応しないのも
    case 0b01101:
    case 0b10110:
      *ReftSpeed = 0;
      *LeftSpeed = 0;
  
  }
}

void setSpeed(int leftSpeed, int rightSpeed) {//モータースピード(0~100の%で入力してください)

  MakerSumo.setMotorSpeed(MOTOR_L, leftSpeed); 
  MakerSumo.setMotorSpeed(MOTOR_R, rightSpeed);
}
