#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X vl53l0x=Adafruit_VL53L0X();

struct distStruct {
  int servoRight; int servoMid; int servoLeft;
  int sweepDir; int sweepStep; bool sweepActive;
  int Value; short valueArray[41]; bool valueUpdate; };

struct distStruct dist;

const byte xshutPin=19; //const byte intPin=18;
unsigned long distTimer=millis()+100;;

void distWorker() {
  if (millis()>=distTimer) { distTimer=millis()+50;
    if (vl53l0x.isRangeComplete()) {
      int distTemp=vl53l0x.readRangeResult();
      if (vl53l0x.readRangeStatus()!=4) { dist.Value=distTemp; } else { dist.Value=9999; } }
    if (dist.sweepActive==false) { for (int a=15;a<=25;a++) { dist.valueArray[a]=dist.Value; } dist.sweepStep+=dist.sweepDir; }
    else { dist.valueArray[dist.sweepStep]=dist.Value; dist.sweepStep+=dist.sweepDir;
      pwmLinks.setPWM(11,0,map(dist.sweepStep,0,40,dist.servoRight,dist.servoLeft)); }
    if (dist.sweepStep==0) { dist.sweepDir=1; dist.valueUpdate=true; } else if (dist.sweepStep==40) { dist.sweepDir=-1; dist.valueUpdate=true; } } }

void setSweep(bool sweepActive) {
  for (int a=0;a<=40;a++) { dist.valueArray[a]=9999; }
  dist.sweepStep=20; pwmLinks.setPWM(11,0,dist.servoMid);
  dist.sweepActive=sweepActive; }

void initDist() {
  pinMode(xshutPin,OUTPUT); digitalWrite(xshutPin,HIGH); //pinMode(intPin,INPUT_PULLUP);
  //VL53L0X_SENSE_DEFAULT; VL53L0X_SENSE_LONG_RANGE; VL53L0X_SENSE_HIGH_SPEED; VL53L0X_SENSE_HIGH_ACCURACY
  vl53l0x.begin(0x29,false,&I2Ctwo,Adafruit_VL53L0X::VL53L0X_SENSE_LONG_RANGE); //true for debug
  vl53l0x.startRangeContinuous(45);
  int servoFreq=50;
  dist.servoRight=4096/(1000/servoFreq)*0.75;
  dist.servoMid=4096/(1000/servoFreq)*1.5;
  dist.servoLeft=4096/(1000/servoFreq)*2.25;
  dist.sweepDir=1;
  dist.sweepStep=20;
  dist.valueUpdate=false;
  for (int a=0;a<=40;a++) { dist.valueArray[a]=9999; }
  setSweep(true); }
