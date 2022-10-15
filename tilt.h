//get library from https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/I2Cdev and
//get library from https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050 and
//read https://github.com/jrowberg/i2cdevlib/issues/688
#include "MPU6050_6Axis_MotionApps612.h"

TwoWire I2Ctwo=TwoWire(1);
MPU6050 mpu(0x68,&I2Ctwo);

#include <Preferences.h>
Preferences preferences;

struct tiltStruct { float x; float y; float z; float d; float xy; };
struct tiltStruct tilt;
unsigned long tiltTimer=millis()+100;
uint8_t fifoBuffer[64]; Quaternion q; VectorFloat gravity; float ypr[3];

void calibrateTilt() { mpu.CalibrateAccel(6); mpu.CalibrateGyro(6); mpu.PrintActiveOffsets(); }

bool loadTiltCalibration() {
  preferences.begin("mpu6050Cal",false); if (preferences.getBool("existFlag",false)==true) {
    mpu.setXGyroOffset(preferences.getFloat("XGyroOffset",0)); mpu.setYGyroOffset(preferences.getFloat("YGyroOffset",0)); mpu.setZGyroOffset(preferences.getFloat("ZGyroOffset",0));
    mpu.setXAccelOffset(preferences.getFloat("XAccelOffset",0)); mpu.setYAccelOffset(preferences.getFloat("YAccelOffset",0)); mpu.setZAccelOffset(preferences.getFloat("ZAccelOffset",0));
    preferences.end(); mpu.PrintActiveOffsets(); return true; } else { preferences.end(); return false; } }

void saveTiltCalibration() {
  preferences.begin("mpu6050Cal",false); preferences.putBool("existFlag",true);
  preferences.putFloat("XGyroOffset",mpu.getXGyroOffset()); preferences.putFloat("YGyroOffset",mpu.getYGyroOffset()); preferences.putFloat("ZGyroOffset",mpu.getZGyroOffset());
  preferences.putFloat("XAccelOffset",mpu.getXAccelOffset()); preferences.putFloat("YAccelOffset",mpu.getYAccelOffset()); preferences.putFloat("ZAccelOffset",mpu.getZAccelOffset());
  preferences.end(); }

void initTilt() {
  I2Ctwo.begin(17,16,400000); //SDA 17,SCL 16, 400 kHz
  mpu.initialize();
  mpu.dmpInitialize();
  if (!loadTiltCalibration()) { calibrateTilt(); calibrateTilt(); } //saveTiltCalibration();
  mpu.setDMPEnabled(true); }

void tiltWorker() {
  if (millis()>=tiltTimer) { tiltTimer=millis()+100;
    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
      mpu.dmpGetQuaternion(&q,fifoBuffer);
      mpu.dmpGetGravity(&gravity,&q);
      mpu.dmpGetYawPitchRoll(ypr,&q,&gravity);
      if (ypr[2]<-M_PI/2 || ypr[2]>M_PI/2) { if (ypr[1]<0) { ypr[1]=-M_PI-ypr[1]; } else { ypr[1]=M_PI-ypr[1]; } }
      if (ypr[1]<-M_PI/2 || ypr[1]>M_PI/2) { if (ypr[2]<0) { ypr[2]=-M_PI-ypr[2]; } else { ypr[2]=M_PI-ypr[2]; } }
      tilt.z=ypr[0]*180/M_PI; tilt.y=ypr[1]*180/M_PI; tilt.x=ypr[2]*180/M_PI;
      tilt.d=(atan2(ypr[1],ypr[2])*180/M_PI)+180;
      tilt.xy=sqrt(ypr[1]*ypr[1]+ypr[2]*ypr[2])*180/M_PI; } } }
