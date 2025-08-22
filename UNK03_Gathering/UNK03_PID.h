#include <UNK03_Sensor.h>
#include <UNK03_Motor.h>
#include <UNK03_Initial.h>
#include <UNK03_Turn.h>
#include <UNK03_ForwardAndTurn.h>

int MaxSpeed = 100;
int MinSpeed = 0;
int ModePidStatus = 0;
int LastError;


void OK_STOP() {
  MotorStop(0);
  while (1) {
    if (analogRead(A7) < 700) {
      break;
    }
  }
  Beep(200);
}
void MODEPidStatusMaxMinSpeed(int Mod,int max, int min) {
  ModePidStatus = Mod;
  MaxSpeed = max;
  MinSpeed = min;
}


int readPosition(int Track, int noise) {
  unsigned char i, online = 0;
  unsigned long avg = 0;
  unsigned int sum = 0;
  static int last_value = 0;
  ReadCalibrate();
  for (i = 0; i < NUM_SENSORS; i++) {
    int values = F[i];
    if (values > Track) {
      online = 1;
    }
    if (values > noise) {
      avg += (long)(values) * (i * 1000);
      sum += values;
    }
  }
  if (!online) {
    if (last_value < (NUM_SENSORS - 1) * 1000 / 2) {
      return 0;
    } else {
      return (NUM_SENSORS - 1) * 1000;
    }
  }
    // if (sum == 0) {
    //     return last_value; // ใช้ค่าตำแหน่งล่าสุดเมื่อไม่มีเส้น
    // }
  last_value = avg / sum;
  return last_value;
}

void PID(int SpeedL,int SpeedR, float Kp, float Kd) {
  int Pos = readPosition(300, 50);
  int Error = Pos - ((NUM_SENSORS - 1) * 1000 / 2);
  int PID_Value = ((Kp/1000) * Error) + ((Kd/100) * (Error - LastError));
  LastError = Error;
 int LeftPower = SpeedL + PID_Value;
  int RightPower = SpeedR - PID_Value;
  if (ModePidStatus == 0) {
    if (LeftPower > MaxSpeed) LeftPower = MaxSpeed;
    if (LeftPower < 0) LeftPower = MinSpeed;
    if (RightPower > MaxSpeed) RightPower = MaxSpeed;
    if (RightPower < 0) RightPower = MinSpeed;
  } else if (ModePidStatus == 1) {
    if (LeftPower > MaxSpeed) LeftPower = MaxSpeed;
    if (LeftPower < MinSpeed) LeftPower = MinSpeed;
    if (RightPower > MaxSpeed) RightPower = MaxSpeed;
    if (RightPower < MinSpeed) RightPower = MinSpeed;
  } else if (ModePidStatus == 2) {
    if (LeftPower > SpeedL) LeftPower = SpeedL;
    if (LeftPower < -SpeedL) LeftPower = -SpeedL;
    if (RightPower > SpeedR) RightPower = SpeedR;
    if (RightPower < -SpeedR) RightPower = -SpeedR;
  }
  else {
    if (LeftPower > MaxSpeed) LeftPower = MaxSpeed;
    if (LeftPower < 0) LeftPower = 0;
    if (RightPower > MaxSpeed) RightPower = MaxSpeed;
    if (RightPower < 0) RightPower = 0;
  }
  Motor(LeftPower, RightPower);
}
void lineFollow_upSpeed_with_time(float Start_speed,float normally_speed,float Time_round , float Kp, float Kd) {  //เพิ่มความเร็วขึ้นเรื่อยๆ

  for(float round_for_run_with_timer = Start_speed;round_for_run_with_timer<normally_speed;round_for_run_with_timer+=Time_round){
    BaseSpeed = round_for_run_with_timer;
  PID(LeftBaseSpeed,RightBaseSpeed, Kp, Kd);
  }
}

void lineFollow_downSpeed_with_time(float Start_speed,float normally_speed,float Time_round , float Kp, float Kd) {  //เพิ่มความเร็วขึ้นเรื่อยๆ

  for(float round_for_run_with_timer = Start_speed;round_for_run_with_timer>normally_speed;round_for_run_with_timer-=Time_round){
  BaseSpeed = round_for_run_with_timer;
  PID(LeftBaseSpeed,RightBaseSpeed, Kp, Kd);
  }
}


void TrackSelect(int spd, char x) {
  if (x == 'S') {
    MotorStop();
  } 
  else if (x == 'p') {
    Motor(LeftBaseSpeed, RightBaseSpeed);
    Beep(30);
    while (1) {
      Motor(LeftBaseSpeed, RightBaseSpeed);
      ReadCalibrate();
      if (F[0] < 500 && F[7] < 500) {
        Motor(LeftBaseSpeed, RightBaseSpeed);
        while (1) {
      Motor(LeftBaseSpeed, RightBaseSpeed);
      ReadCalibrate();
      if (F[0] > 500 && F[7] > 500) {
        Motor(LeftBaseSpeed, RightBaseSpeed);
        delay(5);
        break;
      }
    }
    
      }
    }
  } 
  else if (x == 'l') {
    ToCenter();
    SpinL();
  } 
  else if (x == 'r') {
    ToCenter();
    SpinR();
  } 
  else if (x == 'f') {
    Motor(LeftBaseSpeed, RightBaseSpeed);
    Beep(20);
  } 
  else if (x == 'c') {
    ToCenter();
  } 
  else if (x == 'q') {
    while (1) {
      Motor(spd/2, spd/2);
      ReadCalibrate();
      if (F[0] < Ref) {
        break;
      }
    }
    SpinL(); // ใส่ไว้ถ้าต้องการ
  } 
  else if (x == 'e') {
    while (1) {
      Motor(spd/2, spd/2);
      ReadCalibrate();
      if (F[7] < Ref) {
        break;
      }
    }
    SpinR();
  }
else if (x == 'b') {
    Motor(-BackLeftBaseSpeed, -BackRightBaseSpeed);
    Beep(30);
    while (1) {
      Motor(-BackLeftBaseSpeed, -BackRightBaseSpeed);
      ReadCalibrateC();
      if (C[0] < 500 && C[1] < 500) {
        Motor(-BackLeftBaseSpeed, -BackRightBaseSpeed);
        while(1){
          ReadCalibrateC();
          if (C[0] > 500 && C[1] > 500){
          delay(5);
          break;
          }
        }
        
      }
    }
    
  } 
  else if (x == 'B') {
    Motor(-BackLeftBaseSpeed, -BackRightBaseSpeed);
    Beep(30);
  } 

}

    


void FF(int Speed, char select) {
  BaseSpeed = Speed;
  InitialSpeed();
  while (1) {
    PID(LeftBaseSpeed,RightBaseSpeed, PID_Kp, PID_Kd);
    ReadCalibrate();
    if ((F[0] > Ref && F[7] > Ref ) || (F[0] > Ref && F[3] > Ref) || (F[4] > Ref && F[7] > Ref)) {
      break;
    }
  }
  TrackSelect(Speed, select);
}

void FFC(int Speed,  char select) {
  BaseSpeed = Speed;
  InitialSpeed();
  while (1) {
    PID(LeftBaseSpeed,RightBaseSpeed, PID_Kp, PID_Kd);
    ReadCalibrate();
    if ((F[0] > Ref && F[7] > Ref)) {
      break;
    }
  }
  TrackSelect(Speed, select);
}

void FFR(int Speed,  char select) {
  BaseSpeed = Speed;
  InitialSpeed();
  while (1) {
    PID(LeftBaseSpeed,RightBaseSpeed, PID_Kp, PID_Kd);
    ReadCalibrate();
    if ((F[4] > Ref && F[7] > Ref)) {
      break;
    }
  }
  TrackSelect(Speed, select);
}
void FFR2(int Speed,  char select) {
  BaseSpeed = Speed;
  InitialSpeed();
  while (1) {
    PID(LeftBaseSpeed,RightBaseSpeed, PID_Kp, PID_Kd);
    ReadCalibrate();
    if ((F[4] > Ref && F[5] > Ref && F[6] > Ref && F[7] > Ref)) {
      break;
    }
  }
  TrackSelect(Speed, select);
}
void FFL(int Speed, char select) {
  BaseSpeed = Speed;
  InitialSpeed();
  while (1) {
    PID(LeftBaseSpeed,RightBaseSpeed, PID_Kp, PID_Kd);
    ReadCalibrate();
    if ((F[0] > Ref && F[3] > Ref)) {
      break;
    }
  }
  TrackSelect(Speed, select);
}

void FFL2(int Speed, char select) {
  BaseSpeed = Speed;
  InitialSpeed();
  while (1) {
    PID(LeftBaseSpeed,RightBaseSpeed, PID_Kp, PID_Kd);
    ReadCalibrate();
    if ((F[0] > Ref  && F[1] > Ref && F[2] > Ref && F[3] > Ref)) {
      break;
    }
  }
  TrackSelect(Speed, select);
}

void FF_DISTANCED(int Speed,char select) {
  BaseSpeed = Speed;
  InitialSpeed();
  while (1) {
    PID(LeftBaseSpeed,RightBaseSpeed, PID_Kp, PID_Kd);
    ReadCalibrate();
    if (analogRead(A3) < 550) {
      MotorStop();
      Beep(10);
      break;
    }
  }
  TrackSelect(Speed, select);
}

void FFTimer(int Speed, int TotalTime) {
  BaseSpeed = Speed;
  InitialSpeed();
  unsigned long StartTime = millis();
  unsigned long EndTime = StartTime + TotalTime;
  while (millis() <= EndTime) {
    PID(LeftBaseSpeed,RightBaseSpeed, PID_Kp, PID_Kd);
  }
  // Beep(10);
}

void FFNUM(int Speed, char select,int numm) {
  BaseSpeed = Speed;
  InitialSpeed();
  while (1) {
    PID(LeftBaseSpeed,RightBaseSpeed, PID_Kp, PID_Kd);
    ReadCalibrate();
    if (F[numm] > Ref) {
      break;
    }
  }
  TrackSelect(Speed, select);
}

void FFWhite(int Speed, char select) {
	BaseSpeed = Speed;
	InitialSpeed();
  while (1) {
    PID(LeftBaseSpeed,RightBaseSpeed, PID_Kp, PID_Kd);
    ReadCalibrate();
    if ((F[0] < Ref && F[1] < Ref && F[2] < Ref && F[3] < Ref && F[4] < Ref && F[5] < Ref && F[6] < Ref && F[7] < Ref)) {
      break;
    }
  }
  TrackSelect(Speed, select);
}

void FFBlack(int Speed, char select) {
	BaseSpeed = Speed;
	InitialSpeed();
  Move(LeftBaseSpeed,RightBaseSpeed,50);
  while (1) {
    Motor(LeftBaseSpeed,RightBaseSpeed);
    ReadCalibrate();
    if (F[2] > Ref || F[3] > Ref || F[4] > Ref || F[5] > Ref) {
      break;
    }
  }
  TrackSelect(Speed, select);
}


void MotorSensorF(int Speed, char select, int ch) {
  BaseSpeed = abs(Speed);
  InitialSpeed();
  while (1) {
    Motor(
      (Speed >= 0) ? LeftBaseSpeed  : -BackLeftBaseSpeed,
      (Speed >= 0) ? RightBaseSpeed : -BackRightBaseSpeed
    );
    ReadCalibrate();
    if (F[ch] > Ref) break;
  }

  TrackSelect(abs(Speed), select);
}

void MotorSensorC(int Speed, char select, int ch) {
  BaseSpeed = abs(Speed);
  InitialSpeed();
  while (1) {
    Motor(
      (Speed >= 0) ? LeftBaseSpeed  : -BackLeftBaseSpeed,
      (Speed >= 0) ? RightBaseSpeed : -BackRightBaseSpeed
    );
    ReadCalibrateC();
    if (C[ch] > Ref) break;
  }

  TrackSelect(abs(Speed), select);
}
