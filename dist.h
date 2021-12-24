#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X vl53l0x=Adafruit_VL53L0X();

const byte xshutPin=19; //const byte intPin=18;
int dist; unsigned long distTimer;

void distWorker() {
  if (millis()>=distTimer) { distTimer=millis()+100;
    if (vl53l0x.isRangeComplete()) {
      int distTemp=vl53l0x.readRangeResult();
      if (vl53l0x.readRangeStatus()!=4) { dist=distTemp; } else { dist=9999; } } } }

void initDist() {
  pinMode(xshutPin,OUTPUT); digitalWrite(xshutPin,HIGH); //pinMode(intPin,INPUT_PULLUP);
  //VL53L0X_SENSE_DEFAULT; VL53L0X_SENSE_LONG_RANGE; VL53L0X_SENSE_HIGH_SPEED; VL53L0X_SENSE_HIGH_ACCURACY
  vl53l0x.begin(0x29,false,&I2Ctwo,Adafruit_VL53L0X::VL53L0X_SENSE_LONG_RANGE); //true for debug
  distTimer=millis()+100; vl53l0x.startRangeContinuous(100); }
