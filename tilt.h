//get library from https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/I2Cdev and
//get library from https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050
#include "MPU6050_6Axis_MotionApps612.h"

TwoWire I2Ctwo=TwoWire(1);
MPU6050 mpu(0x68,&I2Ctwo);

struct tiltStruct { float x; float y; float z; float d; float xy; };
struct tiltStruct tilt;
unsigned long tiltTimer=millis()+100;
uint8_t fifoBuffer[64]; Quaternion q; VectorFloat gravity; float ypr[3];

void calibrateTilt() { mpu.CalibrateAccel(6); mpu.CalibrateGyro(6); mpu.PrintActiveOffsets(); }

void initTilt() {
  I2Ctwo.begin(17,16,400000); //SDA 17,SCL 16, 400000 Hz
  mpu.initialize();
  mpu.dmpInitialize();
  //mpu.setXGyroOffset(27); mpu.setYGyroOffset(-10); mpu.setZGyroOffset(53);
  //mpu.setXAccelOffset(2400); mpu.setYAccelOffset(169); mpu.setZAccelOffset(2270);
  calibrateTilt();
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
