// -------------------- Library --------------------
#include <UNK03_PID.h>
#include <SPI.h>
#include <Servo.h>

// -------------------- Define --------------------
#define BUZZER_PIN 8

#define SV1pin A0
#define SV2pin A1
#define SV3pin A2
#define SV4pin A3

#define No  0
#define Yes 1

// -------------------- Servo --------------------
Servo SV1;
Servo SV2;
Servo SV3;
Servo SV4;

// -------------------- Global Variables --------------------
int pos1 = 90, pos2 = 90, pos3 = 90;

// Servo positions
int OpenL, OpenR;
int CloseL, CloseR;
int CloseLSmall, CloseRSmall;
int Up, Up45, Down;
int OpenL2, OpenR2;
int OpenRMax, OpenLMax;

// Timer
long Timer;

// Switch status
int SW_OK_Status;

// -------------------- Setup --------------------
void RobotSetup() {
  Serial.begin(9600);
  beginADC();

  for (int i = 2; i <= 8; i++) {
    pinMode(i, OUTPUT);
  }

  pinMode(A6, INPUT);
  pinMode(A7, INPUT);

  Beep(100);
  delay(50);
  Beep(100);
}

// -------------------- Servo Control --------------------
void servo(char servoDev, signed int angle) {
  Servo* sv;
  int pin;

  switch (servoDev) {
    case 1: sv = &SV1; pin = SV1pin; break;
    case 2: sv = &SV2; pin = SV2pin; break;
    case 3: sv = &SV3; pin = SV3pin; break;
    case 4: sv = &SV4; pin = SV4pin; break;
    default: return;
  }

  if (angle == -1) {
    sv->detach();
  } else {
    if (!(sv->attached())) {
      sv->attach(pin);
    }
    sv->write(angle);
  }
}

// -------------------- Timer --------------------
void StartTimer() {
  Timer = millis();
}

long int ReadTimer() {
  return (millis() - Timer);
}

// -------------------- Mode Control --------------------
void Mode() {
  SW_OK_Status = No;

  while (SW_OK_Status == No) {  
    if (OK_UNPRESS()) {   // ปุ่ม OK ถูกกด
      StartTimer();
      SW_OK_Status = Yes;
      Beep(100);

      while (OK_UNPRESS()) {  
        if (ReadTimer() >= 1500) {  // กดค้างเกิน 1.5 วิ
          Beep(100);
          delay(50);
          Beep(100);
          delay(50);
          Beep(100);

          CaliberateRobotSensorEEPROM(); // เรียกฟังก์ชัน Calibrate

          while (OK_UNPRESS()) {
            // รอปล่อยปุ่ม
          }
          SW_OK_Status = No;  // กลับไปเริ่มใหม่
        }
      }
    }
  }
}

// -------------------- Servo Position Setters --------------------
void setOpen(int degree1, int degree2) {
  OpenL = degree1;
  OpenR = degree2;
}

void setOpen2(int degree1, int degree2) {
  OpenL2 = degree1;
  OpenR2 = degree2;
}

void setOpenMax(int degree1, int degree2) {
  OpenLMax = degree1;
  OpenRMax = degree2;
}

void setCloseBig(int degree1, int degree2) {
  CloseL = degree1;
  CloseR = degree2;
}

void setCloseSmall(int degree1, int degree2) {
  CloseLSmall = degree1;
  CloseRSmall = degree2;
}

void setUpDown(int degree1, int degree2) {
  Up = degree1;
  Down = degree2;
}
