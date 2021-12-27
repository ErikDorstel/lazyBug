#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

TwoWire I2Ctwo=TwoWire(1);
Adafruit_MPU6050 mpu;

struct tiltStruct { float x; float y; float d; float xy; float ax; float ay; float az; float cax; float cay; float caz; };
struct tiltStruct tilt;
unsigned long tiltTimer=millis()+100;; int tiltCalibrateCount=0;
const float RADtoDEG=57.29577951308232;

float wrap180(float value) {
  while (value>+180) { value-=360; }
  while (value<-180) { value+=360; }
  return value; }

void calibrateTilt() { tilt.cax=tilt.ax; tilt.cay=tilt.ay; tilt.caz=tilt.az-9.81; }

void tiltWorker() {
  if (millis()>=tiltTimer) { tiltTimer=millis()+100; tiltCalibrateCount++;
    if (tiltCalibrateCount==50) { calibrateTilt(); }
    sensors_event_t a,g,t; mpu.getEvent(&a,&g,&t);
    tilt.ax=(tilt.ax+a.acceleration.x)/2; tilt.ay=(tilt.ay+a.acceleration.y)/2; tilt.az=(tilt.az+a.acceleration.z)/2;
    float ax=tilt.ax-tilt.cax; float ay=tilt.ay-tilt.cay; float az=tilt.az-tilt.caz;
    tilt.x=wrap180((+atan2(ay,sqrt(az*az+ax*ax)))*RADtoDEG);
    tilt.y=wrap180((-atan2(ax,sqrt(az*az+ay*ay)))*RADtoDEG);
    tilt.d=wrap180(atan2(ax,ay)*RADtoDEG)+180;
    tilt.xy=sqrt(ax*ax+ay*ay)/9.81*90; } }

void initTilt() {
  I2Ctwo.begin(17,16); //SDA 17,SCL 16
  mpu.begin(0x68,&I2Ctwo);
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G); //2,4,8,16
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);      //250,500,1000,2000
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);    //5,10,21,44,94,184,260
  tilt.ax=0; tilt.ay=0; tilt.az=0; tilt.cax=0; tilt.cay=0; tilt.caz=0; }
