
float PID_Kp,PID_Kd;
int L[10], R[10];
int BL[10], BR[10];
float KP[10], KD[10];


#define SPD_10 0
#define SPD_20 1
#define SPD_30 2
#define SPD_40 3
#define SPD_50 4
#define SPD_60 5
#define SPD_70 6
#define SPD_80 7
#define SPD_90 8
#define SPD_100 9


void setBalanceSpeed(int ch,int spdL, int spdR) {
  L[ch] = spdL;
  R[ch] = spdR;
}

void setBalanceBackSpeed(int ch, int spdL, int spdR) {
  BL[ch] = spdL;
  BR[ch] = spdR;
}

void setKpKd(int ch ,float kp, float kd){
  KP[ch] = kp;
  KD[ch] = kd;
}

void InitialSpeed(){

  if(BaseSpeed<=10)
  {
    LeftBaseSpeed = BaseSpeed - L[SPD_10];
    RightBaseSpeed = BaseSpeed - R[SPD_10];
    BackLeftBaseSpeed = BaseSpeed - BL[SPD_10];
    BackRightBaseSpeed = BaseSpeed - BR[SPD_10];
    PID_Kp = KP[SPD_10];       //forward PID
    PID_Kd = KD[SPD_10];
  
  }
  else if(BaseSpeed<=20)
  {
    LeftBaseSpeed = BaseSpeed - L[SPD_20];
    RightBaseSpeed = BaseSpeed - R[SPD_20];
    BackLeftBaseSpeed = BaseSpeed - BL[SPD_20];
    BackRightBaseSpeed = BaseSpeed - BR[SPD_20];
    PID_Kp = KP[SPD_20];       //forward PID
    PID_Kd = KD[SPD_20];
  
  }
  else if(BaseSpeed<=30)
  {
    LeftBaseSpeed = BaseSpeed - L[SPD_30];
    RightBaseSpeed = BaseSpeed - R[SPD_30];
    BackLeftBaseSpeed = BaseSpeed - BL[SPD_30];
    BackRightBaseSpeed = BaseSpeed - BR[SPD_30];
    PID_Kp = KP[SPD_30];       //forward PID
    PID_Kd = KD[SPD_30];
  
  }
    else if(BaseSpeed<=40)
  {
    LeftBaseSpeed = BaseSpeed - L[SPD_40];
    RightBaseSpeed = BaseSpeed - R[SPD_40];
    BackLeftBaseSpeed = BaseSpeed - BL[SPD_40];
    BackRightBaseSpeed = BaseSpeed - BR[SPD_40];
    PID_Kp = KP[SPD_40];       //forward PID
    PID_Kd = KD[SPD_40];
  }
  else if(BaseSpeed<=50)
  {
    LeftBaseSpeed = BaseSpeed - L[SPD_50];
    RightBaseSpeed = BaseSpeed - R[SPD_50];
    BackLeftBaseSpeed = BaseSpeed - BL[SPD_50];
    BackRightBaseSpeed = BaseSpeed - BR[SPD_50];
    PID_Kp = KP[SPD_50];       //forward PID
    PID_Kd = KD[SPD_50];
  }
  else if(BaseSpeed<=60)
  {
     LeftBaseSpeed = BaseSpeed - L[SPD_60];
    RightBaseSpeed = BaseSpeed - R[SPD_60];
    BackLeftBaseSpeed = BaseSpeed - BL[SPD_60];
    BackRightBaseSpeed = BaseSpeed - BR[SPD_60];
    PID_Kp = KP[SPD_60];       //forward PID
    PID_Kd = KD[SPD_60];

  }
  else if(BaseSpeed<=70)
  {
     LeftBaseSpeed = BaseSpeed - L[SPD_70];
    RightBaseSpeed = BaseSpeed - R[SPD_70];
    BackLeftBaseSpeed = BaseSpeed - BL[SPD_70];
    BackRightBaseSpeed = BaseSpeed - BR[SPD_70];
    PID_Kp = KP[SPD_70];       //forward PID
    PID_Kd = KD[SPD_70];

  }
  else if(BaseSpeed<=80)
  {
     LeftBaseSpeed = BaseSpeed - L[SPD_80];
    RightBaseSpeed = BaseSpeed - R[SPD_80];
    BackLeftBaseSpeed = BaseSpeed - BL[SPD_80];
    BackRightBaseSpeed = BaseSpeed - BR[SPD_80];
    PID_Kp = KP[SPD_80];       //forward PID
    PID_Kd = KD[SPD_80];

  }
  else if(BaseSpeed<=90)
  {
     LeftBaseSpeed = BaseSpeed - L[SPD_90];
    RightBaseSpeed = BaseSpeed - R[SPD_90];
    BackLeftBaseSpeed = BaseSpeed - BL[SPD_90];
    BackRightBaseSpeed = BaseSpeed - BR[SPD_90];
    PID_Kp = KP[SPD_90];       //forward PID
    PID_Kd = KD[SPD_90];

  }
   else 
  {
     LeftBaseSpeed = BaseSpeed - L[SPD_100];
    RightBaseSpeed = BaseSpeed - R[SPD_100];
    BackLeftBaseSpeed = BaseSpeed - BL[SPD_100];
    BackRightBaseSpeed = BaseSpeed - BR[SPD_100];
    PID_Kp = KP[SPD_100];       //forward PID
    PID_Kd = KD[SPD_100];
  }
   
}