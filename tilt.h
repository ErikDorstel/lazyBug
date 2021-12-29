//get library from https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/I2Cdev and
//get library from https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050
#include "MPU6050_6Axis_MotionApps612.h"

TwoWire I2Ctwo=TwoWire(1);
MPU6050 mpu(0x68,&I2Ctwo);

struct tiltStruct { float yaw; float roll; float pitch; float d; float xy; };
struct tiltStruct tilt;
unsigned long tiltTimer=millis()+100;
uint8_t fifoBuffer[64]; Quaternion q; VectorFloat gravity; float yrp[3];

void calibrateTilt() { mpu.CalibrateAccel(6); mpu.CalibrateGyro(6); mpu.PrintActiveOffsets(); }

void initTilt() {
  I2Ctwo.begin(17,16);
  I2Ctwo.setClock(400000);
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
      mpu.dmpGetYawPitchRoll(yrp,&q,&gravity);
      tilt.yaw=yrp[0]*180/M_PI; tilt.roll=yrp[1]*180/M_PI; tilt.pitch=yrp[2]*180/M_PI;
      tilt.d=(atan2(yrp[1],yrp[2])*180/M_PI)+180;
      tilt.xy=sqrt(yrp[1]*yrp[1]+yrp[2]*yrp[2])*180/M_PI; } } }
