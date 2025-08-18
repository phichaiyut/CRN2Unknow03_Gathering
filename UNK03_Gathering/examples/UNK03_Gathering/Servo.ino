//________ตัวอย่างการใช้งานการใช้งาน SERVO ____________

//ServoMove(100,90, 80, 5);

//ServoUp(5);    // ยกขึ้น เร็ว (delay 5ms)
//ServoDown(5); // ลง ความเร็วทีละ 5 (delay 5ms)

//ServoOpen(5); //เปิดอ้า ความเร็วทีละ 5 (delay 5ms)
//ServoCloseSmall(5); //เก็บลูกเล็ก
//ServoCloseBig(5); //เก็บลูกใหญ่
// -------------------- ฟังก์ชันหลัก --------------------
void ServoMove(int target1, int target2, int target3, int spd) {
  MotorStop();
  while (pos1 != target1 || pos2 != target2 || pos3 != target3) {
    if (pos1 < target1) pos1++;
    else if (pos1 > target1) pos1--;

    if (pos2 < target2) pos2++;
    else if (pos2 > target2) pos2--;

    if (pos3 < target3) pos3++;
    else if (pos3 > target3) pos3--;

    servo(1, pos1);
    servo(2, pos2);
    servo(3, pos3);

    delay(spd);  // หน่วงเวลา
  }
  pos1 = target1;
  pos2 = target2;
  pos3 = target3;
  delay(150);
}

// -------------------- ฟังก์ชันย่อยพิเศษ (มีพารามิเตอร์) --------------------

// ปิดเล็ก
void ServoCloseSmall(int spd) {
  ServoMove(pos1, CloseLSmall, CloseRSmall, spd);
}

// ปิดใหญ่
void ServoCloseBig(int spd) {
  ServoMove(pos1, CloseL, CloseR, spd);
}

// เปิดปกติ
void ServoOpen(int spd) {
  ServoMove(pos1, OpenL, OpenR, spd);
}

// เปิดอีกแบบ (Open2)
void ServoOpen2(int spd, bool smooth) {
  ServoMove(pos1, OpenL2, OpenR2, spd);
}

// เปิดสุด (Max)
void ServoOpenMax(int spd) {
  ServoMove(pos1, OpenLMax, OpenRMax, spd);
}

// ยกขึ้น
void ServoUp(int spd) {
  ServoMove(Up, pos2, pos3, spd);
}

// ลง
void ServoDown(int spd) {
  ServoMove(Down, pos2, pos3, spd);
}


void Servo(int x, int y, int z) {
  MotorStop();
  servo(1, x);
  servo(2, y);
  servo(3, z);
  pos1 = x;
  pos2 = y;
  pos3 = z;
  delay(200);
}
