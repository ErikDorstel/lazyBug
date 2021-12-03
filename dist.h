#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X vl530x=Adafruit_VL53L0X();

int dist;

void getDist() {
  VL53L0X_RangingMeasurementData_t m;
  vl530x.rangingTest(&m,false); //true for debug
  if (m.RangeStatus!=4) { dist=m.RangeMilliMeter; } else { dist=9999; } }

void initDist() {
  //VL53L0X_SENSE_DEFAULT; VL53L0X_SENSE_LONG_RANGE; VL53L0X_SENSE_HIGH_SPEED; VL53L0X_SENSE_HIGH_ACCURACY
  vl530x.begin(0x29,false,&I2Ctwo,Adafruit_VL53L0X::VL53L0X_SENSE_LONG_RANGE); //true for debug
  getDist(); }
