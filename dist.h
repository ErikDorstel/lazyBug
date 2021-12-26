#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X vl53l0x=Adafruit_VL53L0X();

struct distStruct {
  int servoRight;
  int servoMid;
  int servoLeft;
  int servoCurrent;
  int sweepDir;
  int sweepDelta;
  int sweepSteps;
  bool sweepActive;
  int Value;
  int valueArray[100]; };

struct distStruct dist;

const byte xshutPin=19; //const byte intPin=18;
unsigned long distTimer;

void distWorker() {
  if (millis()>=distTimer) { distTimer=millis()+50;
    if (vl53l0x.isRangeComplete()) {
      int distTemp=vl53l0x.readRangeResult();
      if (vl53l0x.readRangeStatus()!=4) { dist.Value=distTemp; } else { dist.Value=9999; } }
    int sweepStep=map(dist.servoCurrent,dist.servoRight,dist.servoLeft,0,dist.sweepSteps); dist.valueArray[sweepStep]=dist.Value;
    if (dist.sweepActive==false) { dist.valueArray[sweepStep-1]=dist.Value; dist.valueArray[sweepStep+1]=dist.Value; }
    else { dist.servoCurrent+=dist.sweepDelta*dist.sweepDir; pwmLinks.setPWM(11,0,dist.servoCurrent);
      if (dist.sweepDir==1 & dist.servoCurrent>=dist.servoLeft) { dist.sweepDir=-1; }
      else if (dist.sweepDir==-1 & dist.servoCurrent<=dist.servoRight) { dist.sweepDir=1; } } } }

void setSweep(bool sweepActive) {
  if (sweepActive==false) {
    dist.servoCurrent=dist.servoMid; pwmLinks.setPWM(11,0,dist.servoCurrent);
    for (int a=0;a<=dist.sweepSteps;a++) { dist.valueArray[a]=9999; } }
  dist.sweepActive=sweepActive; }

void initDist() {
  pinMode(xshutPin,OUTPUT); digitalWrite(xshutPin,HIGH); //pinMode(intPin,INPUT_PULLUP);
  //VL53L0X_SENSE_DEFAULT; VL53L0X_SENSE_LONG_RANGE; VL53L0X_SENSE_HIGH_SPEED; VL53L0X_SENSE_HIGH_ACCURACY
  vl53l0x.begin(0x29,false,&I2Ctwo,Adafruit_VL53L0X::VL53L0X_SENSE_LONG_RANGE); //true for debug
  distTimer=millis()+100; vl53l0x.startRangeContinuous(50);
  int servoFreq=50;
  dist.servoRight=4096/(1000/servoFreq)*0.75;
  dist.servoMid=4096/(1000/servoFreq)*1.5;
  dist.servoLeft=4096/(1000/servoFreq)*2.25;
  dist.servoCurrent=dist.servoMid;
  dist.sweepDir=1;
  dist.sweepDelta=5;
  dist.sweepSteps=(dist.servoLeft-dist.servoRight)/dist.sweepDelta;
  if ((dist.servoLeft-dist.servoRight)%dist.sweepDelta>0) { dist.sweepSteps++; }
  for (int a=0;a<=dist.sweepSteps;a++) { dist.valueArray[a]=9999; }
  setSweep(true); }
