#include <UNK03_PID.h>
#include <SPI.h>

#include <Servo.h>

#define BUZZER_PIN 8
Servo SV1;
Servo SV2;
Servo SV3;
Servo SV4;



long Timer;
int SW_OK_Status;

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

void StartTimer()  {
  Timer = millis();
}
long int ReadTimer()  {
  return(millis() - Timer);
}

#define No 0
#define Yes 1

void Mode() {
  SW_OK_Status = No;
  while (SW_OK_Status == No) {  // รอให้กดปุ่ม OK
    if (OK_UNPRESS()) {         // ตรวจสอบว่าปุ่ม OK ถูกกด (0 หมายถึงปุ่มถูกกด)
      StartTimer();             // เริ่มนับเวลาเมื่อปุ่ม OK ถูกกด
      SW_OK_Status = Yes;       // เปลี่ยนสถานะเพื่อออกจากลูปด้านนอก
      Beep(100);                // ส่งเสียง beep หนึ่งครั้งเพื่อบอกว่ากดปุ่มแล้ว
      while (OK_UNPRESS()) {        // ตรวจสอบว่าปุ่มยังคงถูกกดอยู่ (0 หมายถึงปุ่มถูกกด)
        if (ReadTimer() >= 1500) {  // ตรวจสอบว่าเวลาผ่านไป 2000ms หรือยัง
          Beep(100);                // ส่งเสียง beep สองครั้งถ้าถูกกดค้างนานเกินไป
          delay(50);                // หน่วงเวลาระหว่างเสียง beep
          Beep(100);
          delay(50);  // หน่วงเวลาระหว่างเสียง beep
          Beep(100);
         CaliberateRobotSensor();
          
          while (OK_UNPRESS()) {
            // รอการปล่อยปุ่ม
          }

          SW_OK_Status = No;  // ตั้งค่าสถานะเป็น No ถ้ากดค้างนานเกินไป
        }
      }

      // ปุ่มถูกปล่อย ออกจากลูป
    }
  }
}