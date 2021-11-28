#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

TwoWire I2Ctwo=TwoWire(1);
Adafruit_MPU6050 mpu;

struct tiltStruct { float x; float y; float cax; float cay; float caz; };
struct tiltStruct tilt;

float wrap360(float value) {
  while (value>+180) { value-=360; }
  while (value<-180) { value+=360; }
  return value; }

void calibrateTilt() {
  sensors_event_t a,g,t;
  float ax=0; float ay=0; float az=0;
  for (int x=0;x<20;x++) { mpu.getEvent(&a,&g,&t);
    ax+=a.acceleration.x; ay+=a.acceleration.y; az+=a.acceleration.z; delay(200); }
  tilt.cax=ax/20.0; tilt.cay=ay/20.0; tilt.caz=az/20.0; }

void getTilt() {
  sensors_event_t a,g,t; mpu.getEvent(&a,&g,&t);
  float ax=a.acceleration.x-tilt.cax;
  float ay=a.acceleration.y-tilt.cay;
  float az=a.acceleration.z+(9.81-tilt.caz);
  tilt.x=wrap360((+atan2(ay,sqrt(az*az+ax*ax)))*57.29577951308232);
  tilt.y=wrap360((-atan2(ax,sqrt(az*az+ay*ay)))*57.29577951308232); }

void initTilt() {
  I2Ctwo.begin(17,16); //SDA 17,SCL 16
  mpu.begin(0x68,&I2Ctwo);
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G); //2,4,8,16
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);      //250,500,1000,2000
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);    //5,10,21,44,94,184,260
  calibrateTilt(); getTilt(); }
