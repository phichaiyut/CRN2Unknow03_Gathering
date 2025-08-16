void FD_time(int Speed, int Time) {
  BaseSpeed = Speed;
  InitialSpeed();
  Motor(LeftBaseSpeed,RightBaseSpeed);
  delay(Time);
}
void BK_time(int Speed, int Time) {
  BaseSpeed = Speed;
  InitialSpeed();
  Motor(-BackLeftBaseSpeed,-BackRightBaseSpeed);
  delay(Time);
}

void SR(int Speed, int Time){
MotorStop(50);
Motor(Speed,-Speed);
delay(Time);
MotorStop(50);

}

void SL(int Speed, int Time){
MotorStop(50);
Motor(-Speed,Speed);
delay(Time);
MotorStop(50);
}
void TL(int Speed, int Time){
MotorStop(50);
Motor(0,Speed);
delay(Time);
MotorStop(50);
}
void TR(int Speed, int Time){
MotorStop(50);
Motor(Speed,0);
delay(Time);
MotorStop(50);
}