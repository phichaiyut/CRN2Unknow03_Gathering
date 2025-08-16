#define CFL 0
#define CFR 1


int LCh, LTurnSpdL, LTurnSpdR, TurnDelayL;
int RCh, RTurnSpdL, RTurnSpdR, TurnDelayR;
int tct, bct, tspd;
int tctL,tctR,bctL,bctR;

void TurnSpeedLeft(int Ch ,int l, int r, int de) {
  LCh = Ch;
  LTurnSpdL = l;
  LTurnSpdR = r;
  TurnDelayL = de;
}

void TurnSpeedRight(int Ch ,int l, int r, int de) {
  RCh = Ch;
  RTurnSpdL = l;
  RTurnSpdR = r;
  TurnDelayR = de;
}

void SetTurnSpeed(int tspdv) {
  tspd = tspdv;
}


void SetToCenterSpeed(int tctv) {
	
  tct = tctv;
  bct = tctv;
	BaseSpeed = tctv;
	InitialSpeed();
	tctL = LeftBaseSpeed;
	tctR = RightBaseSpeed;
	bctL = BackLeftBaseSpeed;
	bctR = BackRightBaseSpeed;
}

void TurnLeft() {
  Motor(-LTurnSpdL, LTurnSpdR);
  delay(TurnDelayL);
  while (1) {
    Motor(-LTurnSpdL, LTurnSpdR);
    ReadCalibrate();
    if (F[LCh] >= 500) {
      Motor(LTurnSpdL, -LTurnSpdR);
      delay(30);
      MotorStop();
      break;
    }
  }
}

void TurnRight() {
  Motor(RTurnSpdL, -RTurnSpdR);
  delay(TurnDelayR);
  while (1) {
    Motor(RTurnSpdL, -RTurnSpdR);
    ReadCalibrate();
    if (F[RCh] >= 500) {
      Motor(-RTurnSpdL, RTurnSpdR);
      delay(30);
      MotorStop();
      break;
    }
  }
}
void Left(int Ch, int Speed) {
  Motor(-Speed, Speed);
  delay(TurnDelayL);
  while (1) {
    Motor(-Speed, Speed);
    ReadCalibrate();
    if (F[Ch] >= 500) {
      Motor(Speed, -Speed);
      delay(map(Speed, 20, 100, 0, 30));
      MotorStop();
      break;
    }
  }
}
void Right(int Ch, int Speed) {
  Motor(Speed, -Speed);
  delay(TurnDelayR);
  while (1) {
    Motor(Speed, -Speed);
    ReadCalibrate();
    if (F[Ch] >= 500) {
      Motor(-Speed, Speed);
      delay(map(Speed, 20, 100, 0, 30));
      MotorStop();
      break;
    }
  }
}

void ToCenter() {
BZon();
  Motor(tctL, tctR);
  delay(20);
  while (1) {
    Motor(tctL, tctR);
    ReadCalibrateC();
    if (C[CFL] >= RefC || C[CFR] >= RefC) {
      Motor(-tct, -tct);
      delay(5);
      MotorStop();
      BZoff();
      break;
    }
  }
}

void ToCenterL() {
BZon();
  Motor(tctL, tctR);
  delay(20);
  while (1) {
    Motor(tctL, tctR);
    ReadCalibrateC();
    if (C[CFL] >= RefC) {
      Motor(-tct, -tct);
      delay(5);
      MotorStop();
      BZoff();
      break;
    }
  }
}

void ToCenterR() {
  BZon();
  Motor(tctL, tctR);
  delay(20);
  while (1) {
    Motor(tctL, tctR);
    ReadCalibrateC();
    if (C[CFR] >= RefC) {
      Motor(-tct, -tct);
      delay(5);
      MotorStop();
      BZoff();
      break;
    }
  }
}


void SpinL() {
  MotorStop();
  delay(10);
  Motor(-tspd, tspd);
  delay(60);
  while (1) {
    ReadCalibrate();
    Motor(-tspd, tspd);
    if (F[2] >= Ref) {
      Motor(tspd, -tspd);
      delay(5);
      MotorStop();
      break;
    }
  }
}

void SpinL2() {
  MotorStop();
  delay(10);
  Motor(-tspd, tspd);
  delay(20);
  while (1) {
    ReadCalibrate();
    Motor(-tspd, tspd);
    if (F[2] >= Ref) {
      break;
    }
  }
  Motor(-tspd, tspd);
  delay(50);
  while (1) {
    ReadCalibrate();
    Motor(-tspd, tspd);
    if (F[2] >= Ref) {
      Motor(tspd, -tspd);
      delay(5);
      MotorStop();
      break;
    }
  }
}

void SpinR() {
  MotorStop();
  delay(10);
  Motor(tspd, -tspd);
  delay(60);
  while (1) {
    ReadCalibrate();
    Motor(tspd, -tspd);
    if (F[5] >= Ref) {
      Motor(-tspd, tspd);
      delay(5);
      MotorStop();
      break;
    }
  }
}

void SpinR2() {
  MotorStop();
  delay(10);
  Motor(tspd, -tspd);
  delay(20);
  while (1) {
    ReadCalibrate();
    Motor(tspd, -tspd);
    if (F[5] >= Ref) {
      break;
    }
  }
  Motor(tspd, -tspd);
  delay(50);
  while (1) {
    ReadCalibrate();
    Motor(tspd, -tspd);
    if (F[5] >= Ref) {
      Motor(-tspd, tspd);
      delay(5);
      MotorStop();
      break;
    }
  }
}

