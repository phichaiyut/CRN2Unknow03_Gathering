#include <UNK03_Gathering.h>

void setup() {

  RobotSetup();       // Setup หุ่นยนต์
  LoadCalibration();  //โหลดค่าที่บันทึกไว้ใน EEPROM

  // SensorValueF(61, 61, 60, 62, 61, 60, 61, 62, 675, 703, 572, 728, 631, 631, 707, 719);
  // SensorValueC(51, 61, 703, 700);
  TurnSpeedLeft(2, 25, 80, 40);   // ค่าเลี้ยวซ้าย TurnSpeedLeft(ช่องเซนเซอร์, มอเตอร์ซ้าย, มอเตอร์ขวา, เวลาเลี้ยว);
  TurnSpeedRight(5, 80, 25, 40);  // ค่าเลี้ยวขวา TurnSpeedRight(ช่องเซนเซอร์, มอเตอร์ซ้าย, มอเตอร์ขวา, เวลาเลี้ยว);
  TrackLineColor(0);              //สีของเส้น 1 = ขาว , 0 = ดำ

  SetKpKd();           //ตั้งค่า kp kd
  SetSpeedForward();   // setup balance เดินหน้า
  SetSpeedBackward();  // setup balance ถอยหลัง

  RefLineValue(500);        // ค่าในการจับเส้น เซนเซอร์หน้า
  RefCenterLineValue(400);  //// ค่าในการจับเส้น เซนเซอร์คู่กลาง

  SetTurnSpeed(40);      //ความเร็วเลี้ยวเข้าแยก
  SetToCenterSpeed(30);  //ความเร็วเข้าแยก
  MaxMinSpeed(100, -5);  //MaxMinSpeed(ความเร็วสูงสุด,ความเร็วต่ำสุด);
  MODEPidStatus(0);      //โหมดวิ่ง PID

  //OK();        // รอจนกว่าจะกดปุ่ม OK

  Mode();  //กดค้าง 2 วิ เข้าโหมดคาลิเบตเซนเซอร์

  Servo(120, 90, 90);  //ตั้งค่าเซอร์โวตอนเริ่มต้น

  OK();
  delay(500);  // หน่วงเวลา 0.5 วินาที
  // SerialSensor();  // Serial Monitor ค่าของ Sensor ข้างหน้า
  // SerialCalibrate();  // Serial Monitor ค่าของ Sensor ข้างหน้า ที่ Calibrate แล้ว
  // SerialSensorC();  // Serial Monitor ค่าของ Sensor ตรงข้างล้อ
  // SerialCalibrateC();  // Serial Monitor ค่าของ Sensor ตรงข้างล้อ ที่ Calibrate แล้ว

  // CaliberateRobotSensor();  // Serial Monitor Calibrate ค่าแสงหุ่นยนต์


  //__________________________________วางโค้ดใหม่หลังจากนี้บรรทัดนี้ทั้งหมด______________________________________________________________________

  Mission();


  //____________________________________ห้ามวางโค้ดหลังจากบรรทัดนี้____________________________________________________________________________

}  //_________________ปีกกาตัวนี้ห้ามลบ______________________________

void loop() {

  MotorStop();         // หยุดการทำงานมอเตอร์
  SerialSensorBoth();  //อ่านค่าเซนเซอร์ทั้งหมด
}
