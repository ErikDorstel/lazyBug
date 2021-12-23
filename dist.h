#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X vl53l0x=Adafruit_VL53L0X();

const byte intPin=18; const byte xshutPin=19;
int dist;

void getDist(int count) {
  VL53L0X_RangingMeasurementData_t m; int d=0; int y=0;
  for (int x=0;x<count;x++) { if (x>0) { delay(10); } vl53l0x.rangingTest(&m,false); //true for debug
    if (m.RangeStatus!=4) { d+=m.RangeMilliMeter; y++; } }
  if (y>0) { dist=d/y; } else { dist=9999; } }

void initDist() {
  pinMode(intPin,INPUT); pinMode(xshutPin,OUTPUT); digitalWrite(xshutPin,HIGH);
  //VL53L0X_SENSE_DEFAULT; VL53L0X_SENSE_LONG_RANGE; VL53L0X_SENSE_HIGH_SPEED; VL53L0X_SENSE_HIGH_ACCURACY
  vl53l0x.begin(0x29,false,&I2Ctwo,Adafruit_VL53L0X::VL53L0X_SENSE_LONG_RANGE); //true for debug
  getDist(1); }
