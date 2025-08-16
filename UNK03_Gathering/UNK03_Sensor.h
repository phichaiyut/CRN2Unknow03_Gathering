#include <Adafruit_MCP3008.h>
#include <EEPROM.h>
Adafruit_MCP3008 adc1;
Adafruit_MCP3008 adc2;
#define NUM_SENSORS 8
int MinValue[NUM_SENSORS];
int MaxValue[NUM_SENSORS];
int MinValueC[NUM_SENSORS], MaxValueC[NUM_SENSORS];
uint8_t F_PIN[NUM_SENSORS] = { 0, 1, 2, 3, 4, 5, 6, 7 };
uint8_t C_PIN[NUM_SENSORS] = { 0, 1, 2, 3, 4, 5, 6, 7 };
int F[NUM_SENSORS];
int LineColor = 0;
int Ref = 0;
int RefC = 0;
int S[NUM_SENSORS];
int C[NUM_SENSORS];

uint8_t sck = 13;
uint8_t miso = 12;
uint8_t mosi = 11;
uint8_t ssf = 9;
uint8_t ssb = 10;

void TrackLineColor(int Col) {
  LineColor = Col;
}
void Beep(int delayb) {
  digitalWrite(8, 1);
  delay(delayb);
  digitalWrite(8, 0);
}

void BZon(){
  digitalWrite(8, 1);
}

void BZoff(){
  digitalWrite(8, 0);
}

void beginADC() {
    adc1.begin(sck, mosi, miso, ssf);
    adc2.begin(sck, mosi, miso, ssb);
}
void ReadSensor() {
  for (int _sensor = 0; _sensor < NUM_SENSORS; _sensor++) {
    F[_sensor] = adc1.readADC(F_PIN[_sensor]);
  }
}

int analog(int ch){
	ReadSensor();
	return F[ch];
}
void ReadSensorC() {
  for (int _sensor = 0; _sensor < NUM_SENSORS; _sensor++) {
    C[_sensor] = adc2.readADC(C_PIN[_sensor]);
  }
}
void CalibrateSensor(int pauseTime, int samples) {
  for (int i = 0; i < NUM_SENSORS; i++) {
    MinValue[i] = 1023;
    MaxValue[i] = 0;
  }
  for (int startSamp = 0; startSamp <= samples; startSamp++) {
    ReadSensor();
    for (int i = 0; i < NUM_SENSORS; i++) {
      MinValue[i] = (F[i] <= MinValue[i] ? F[i] : MinValue[i]);
      MaxValue[i] = (F[i] >= MaxValue[i] ? F[i] : MaxValue[i]);
    }
    delay(pauseTime);
  }
  for (int i = 0; i < NUM_SENSORS; i++) {
    MinValue[i] += 50;
    MaxValue[i] -= 100;
  }
}

void CalibrateSensorC(int pauseTime, int samples) {
  for (int i = 0; i < 2; i++) {
    MinValueC[i] = 1023;
    MaxValueC[i] = 0;
  }
  for (int startSamp = 0; startSamp <= samples; startSamp++) {
    ReadSensorC();
    for (int i = 0; i < 2; i++){
      MinValueC[i] = (C[i] <= MinValueC[i] ? C[i] : MinValueC[i]);
      MaxValueC[i] = (C[i] >= MaxValueC[i] ? C[i] : MaxValueC[i]);
    }
    delay(pauseTime);
  }
  for (int i = 0; i < 2; i++) {
    MinValueC[i] += 50;
    MaxValueC[i] -= 100;
  }
}

void SensorValueF(uint16_t minF0, uint16_t minF1, uint16_t minF2, uint16_t minF3, uint16_t minF4, uint16_t minF5, uint16_t minF6, uint16_t minF7, uint16_t maxF0, uint16_t maxF1, uint16_t maxF2, uint16_t maxF3, uint16_t maxF4, uint16_t maxF5, uint16_t maxF6, uint16_t maxF7) {
  MinValue[0] = minF0;
  MinValue[1] = minF1;
  MinValue[2] = minF2;
  MinValue[3] = minF3;
  MinValue[4] = minF4;
  MinValue[5] = minF5;
  MinValue[6] = minF6;
  MinValue[7] = minF7;

  MaxValue[0] = maxF0;
  MaxValue[1] = maxF1;
  MaxValue[2] = maxF2;
  MaxValue[3] = maxF3;
  MaxValue[4] = maxF4;
  MaxValue[5] = maxF5;
  MaxValue[6] = maxF6;
  MaxValue[7] = maxF7;
}

void SensorValueC(uint16_t minC0, uint16_t minC1, uint16_t maxC0, uint16_t maxC1) {
  MinValueC[0] = minC0;
  MinValueC[1] = minC1;

  MaxValueC[0] = maxC0;
  MaxValueC[1] = maxC1;
  
}
void OK() {
  while (1) {
    if (analogRead(A7) < 700) {
      break;
    }
  }
  Beep(200);
}

void swOK() {
  while (1) {
    if (analogRead(A7) < 200) {
      break;
    }
  }
  Beep(200);
}

int OK_PUSH() {
  if (analogRead(A7) > 700) return 0;
  else {
    return 1;
  }
}

int OK_UNPRESS() {
  if (analogRead(A7) < 700) return 1;
  else {
    return 0;
  }
}


void ReadCalibrate() {
  ReadSensor();
    if (LineColor == 0) {
      for (int i = 0; i < NUM_SENSORS; i++) {
        int x = map(F[i], MinValue[i], MaxValue[i], 0, 1000);
        if (x < 0) x = 0;
        if (x > 1000) x = 1000;
        F[i] = x;
      }
    } else {
      for (int i = 0; i < NUM_SENSORS; i++) {
        int x = map(F[i], MinValue[i], MaxValue[i], 1000, 0);
        if (x < 0) x = 0;
        if (x > 1000) x = 1000;
        F[i] = x;
      }
  }
}

void ReadCalibrateC() {
  ReadSensorC();
  if (LineColor == 0) {
      for (int i = 0; i < 2; i++){
        int x = map(C[i], MinValueC[i], MaxValueC[i], 0, 1000);
        if (x < 0) x = 0;
        if (x > 1000) x = 1000;
        C[i] = x;
      }
    } else {
      for (int i = 0; i < 2; i++) {
        int x = map(C[i], MinValueC[i], MaxValueC[i], 1000, 0);
        if (x < 0) x = 0;
        if (x > 1000) x = 1000;
        C[i] = x;
      }
  }
}

void SaveCalibration() {
  int addr = 0;

  // Front Sensor Min
  for (int i = 0; i < NUM_SENSORS; i++) {
    EEPROM.write(addr++, MinValue[i] / 10);
  }
  // Front Sensor Max
  for (int i = 0; i < NUM_SENSORS; i++) {
    EEPROM.write(addr++, MaxValue[i] / 10);
  }

  // Center Sensor Min (ใช้ตัวแปรถูกต้อง)
  for (int i = 0; i < 2; i++) {
    EEPROM.write(addr++, MinValueC[i] / 10);
  }
  // Center Sensor Max (ใช้ตัวแปรถูกต้อง)
  for (int i = 0; i < 2; i++) {
    EEPROM.write(addr++, MaxValueC[i] / 10);
  }

  Serial.println("Saved to EEPROM");
}


void CaliberateRobotSensor() {
  Serial.println("Press OK to start caribrate Front Sensor");
  OK();
  Serial.println("Caribrating");
  Beep(100);
  delay(500);
  CalibrateSensor(20, 200);
  Beep(100);
  delay(500);
Serial.println("Press OK to start caribrate Center Sensor");
  OK();
  Serial.println("Caribrating");
  Beep(100);
  delay(500);
  CalibrateSensorC(20, 200);
  Beep(100);
  delay(500);
  Serial.println("Finish");
  Serial.println("  ");
  Serial.print("SensorValueF (");
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print(MinValue[i]);
    if (i < NUM_SENSORS - 1) Serial.print(",");
    else Serial.print(",");
  }
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print(MaxValue[i]);
    if (i < NUM_SENSORS - 1) Serial.print(",");
    else Serial.println(");");
  }
  Serial.println("  ");
  Serial.print("SensorValueC (");
  for (int i = 0; i < 2; i++) {
    Serial.print(MinValueC[i]);
    if (i < 2 - 1) Serial.print(",");
    else Serial.print(",");
  }
  for (int i = 0; i < 2; i++) {
    Serial.print(MaxValueC[i]);
    if (i < 2 - 1) Serial.print(",");
    else Serial.println(");");
  }
      SaveCalibration();
      Serial.println("Finish Save EEPROM Complete!!!");
}


void SerialSensor() {
  while (1) {
    ReadSensor();
    for (int _serialF = 0; _serialF < NUM_SENSORS; _serialF++) {
      Serial.print(F[_serialF]);
      Serial.print("\t");
    }
    Serial.println("");
    delay(50);
    if (OK_PUSH() == 1) {
      Beep(40);
      break;
    }
  }
}

void SerialCalibrate() {
  while (1) {
    ReadCalibrate();
    for (int _serialF = 0; _serialF < NUM_SENSORS; _serialF++) {
      Serial.print(F[_serialF]);
      Serial.print("\t");
    }
    Serial.println("");
    delay(100);
    if (OK_PUSH() == 1) {
      Beep(40);
      break;
    }
  }
}

void SerialSensorC() {
  while (1) {
    ReadSensorC();
    for (int _serialF = 0; _serialF < NUM_SENSORS; _serialF++) {
      Serial.print(C[_serialF]);
      Serial.print("\t");
    }
    Serial.println("");
    delay(50);
    if (OK_PUSH() == 1) {
      Beep(40);
      break;
    }
  }
}

void SerialCalibrateC() {
  while (1) {
    ReadCalibrateC();
    for (int _serialF = 0; _serialF < NUM_SENSORS; _serialF++) {
      Serial.print(C[_serialF]);
      Serial.print("\t");
    }
    Serial.println("");
    delay(100);
    if (OK_PUSH() == 1) {
      Beep(40);
      break;
    }
  }
}



void LoadCalibration() {
  int addr = 0;

  // Front Sensor Min
  for (int i = 0; i < NUM_SENSORS; i++) {
    MinValue[i] = EEPROM.read(addr++) * 10;
  }
  // Front Sensor Max
  for (int i = 0; i < NUM_SENSORS; i++) {
    MaxValue[i] = EEPROM.read(addr++) * 10;
  }

  // Center Sensor Min
  for (int i = 0; i < 2; i++) {
    MinValueC[i] = EEPROM.read(addr++) * 10;
  }
  // Center Sensor Max
  for (int i = 0; i < 2; i++) {
    MaxValueC[i] = EEPROM.read(addr++) * 10;
  }

  Serial.println("Loaded from EEPROM");

  // แสดงค่า Front Sensor
  Serial.print("SensorValueF(");
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print(MinValue[i]);
    Serial.print(",");
  }
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print(MaxValue[i]);
    if (i < NUM_SENSORS - 1) Serial.print(",");
  }
  Serial.println(");");

  // แสดงค่า Center Sensor
  Serial.print("SensorValueC(");
  for (int i = 0; i < 2; i++) {
    Serial.print(MinValueC[i]);
    Serial.print(",");
  }
  for (int i = 0; i < 2; i++) {
    Serial.print(MaxValueC[i]);
    if (i < 1) Serial.print(",");
  }
  Serial.println(");");
}


void RefLineValue(int x) {
  Ref = x;
}

void RefCenterLineValue(int x) {
  RefC = x;
}


void SerialSensorBoth() {

    ReadSensor();
    ReadSensorC();
    Serial.print("SensorF : ");
    for (int i = 0; i < NUM_SENSORS; i++) {
      Serial.print(F[i]);
      Serial.print(" ");
    }

    Serial.print("\tSensorC : ");
    for (int i = 0; i < NUM_SENSORS; i++) {
      Serial.print(C[i]);
      Serial.print(" ");
    }
    Serial.println();

    delay(200);
   
}
