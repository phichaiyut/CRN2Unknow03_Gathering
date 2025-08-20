void SetKpKd() { //ตั้งค่า KP KD

  //setKpKd(SPD_10, KP, KD);

  setKpKd(SPD_10, 5, 5);
  setKpKd(SPD_20, 7, 7);
  setKpKd(SPD_30, 9, 9);
  setKpKd(SPD_40, 11, 11);
  setKpKd(SPD_50, 14, 14);
  setKpKd(SPD_60, 25, 25);
  setKpKd(SPD_70, 20, 20);
  setKpKd(SPD_80, 22, 22);
  setKpKd(SPD_90, 25, 25);
  setKpKd(SPD_100, 28, 28);
}
void SetSpeedForward() {  //เดินหน้า

  //setBalanceSpeed(SPD_10, ล้อซ้าย, ล้อขวา); ข้างไหนแรงกว่าไปเพิ่มข้างนั้น

  setBalanceSpeed(SPD_10, 0, 0);
  setBalanceSpeed(SPD_20, 0, 0);
  setBalanceSpeed(SPD_30, 0, 0);
  setBalanceSpeed(SPD_40, 0, 0);
  setBalanceSpeed(SPD_50, 0, 0);
  setBalanceSpeed(SPD_60, 0, 0);
  setBalanceSpeed(SPD_70, 0, 0);
  setBalanceSpeed(SPD_80, 0, 0);
  setBalanceSpeed(SPD_90, 0, 0);
  setBalanceSpeed(SPD_100, 0, 0);
}

void SetSpeedBackward() {  //ถอยหลัง

  //setBalanceBackSpeed(SPD_10, ล้อซ้าย, ล้อขวา); ข้างไหนแรงกว่าไปเพิ่มข้างนั้น

  setBalanceBackSpeed(SPD_10, 0, 0);
  setBalanceBackSpeed(SPD_20, 0, 0);
  setBalanceBackSpeed(SPD_30, 0, 0);
  setBalanceBackSpeed(SPD_40, 0, 0);
  setBalanceBackSpeed(SPD_50, 0, 0);
  setBalanceBackSpeed(SPD_60, 0, 0);
  setBalanceBackSpeed(SPD_70, 0, 0);
  setBalanceBackSpeed(SPD_80, 0, 0);
  setBalanceBackSpeed(SPD_90, 0, 0);
  setBalanceBackSpeed(SPD_100, 0, 0);
}