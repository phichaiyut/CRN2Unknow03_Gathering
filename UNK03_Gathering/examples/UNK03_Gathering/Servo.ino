#define SV1pin A0
#define SV2pin A1
#define SV3pin A2
#define SV4pin A3


void servo(char servoDev, signed int angle) {
  if (servoDev == 1) {
    if (angle == -1) {
      SV1.detach();
    } else {
      if (!(SV1.attached())) {
        SV1.attach(SV1pin);
      }
      SV1.write(angle);
    }
  } else if (servoDev == 2) {
    if (angle == -1) {
      SV2.detach();
    } else {
      if (!(SV2.attached())) {
        SV2.attach(SV2pin);
      }
      SV2.write(angle);
    }
  } else if (servoDev == 3) {
    if (angle == -1) {
      SV3.detach();
    } else {
      if (!(SV3.attached())) {
        SV3.attach(SV3pin);
      }
      SV3.write(angle);
    }
  } else if (servoDev == 4) {
    if (angle == -1) {
      SV4.detach();
    } else {
      if (!(SV4.attached())) {
        SV4.attach(SV4pin);
      }
      SV4.write(angle);
    }
  }
}


void Servo(int x, int y, int z) {
  servo(1, x);
  servo(2, y);
  servo(3, z);
}