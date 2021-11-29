#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

TwoWire I2Ctwo=TwoWire(1);
Adafruit_MPU6050 mpu;

struct tiltStruct { float x; float y; float cax; float cay; float caz; };
struct tiltStruct tilt;

float wrap180(float value) {
  while (value>+180) { value-=360; }
  while (value<-180) { value+=360; }
  return value; }

void calibrateTilt(float count) {
  sensors_event_t a,g,t; float ax=0; float ay=0; float az=0;
  for (int x=0;x<count;x++) { mpu.getEvent(&a,&g,&t);
    ax+=a.acceleration.x; ay+=a.acceleration.y; az+=a.acceleration.z; delay(10); }
  tilt.cax=ax/count; tilt.cay=ay/count; tilt.caz=az/count-9.81; }

void getTilt(float count) {
  sensors_event_t a,g,t; float ax=0; float ay=0; float az=0;
  for (int x=0;x<count;x++) { mpu.getEvent(&a,&g,&t);
    ax+=a.acceleration.x; ay+=a.acceleration.y; az+=a.acceleration.z; delay(10); }
  ax=ax/count-tilt.cax; ay=ay/count-tilt.cay; az=az/count-tilt.caz;
  tilt.x=wrap180((+atan2(ay,sqrt(az*az+ax*ax)))*57.29577951308232);
  tilt.y=wrap180((-atan2(ax,sqrt(az*az+ay*ay)))*57.29577951308232); }

void initTilt() {
  I2Ctwo.begin(17,16); //SDA 17,SCL 16
  mpu.begin(0x68,&I2Ctwo);
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G); //2,4,8,16
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);      //250,500,1000,2000
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);    //5,10,21,44,94,184,260
  calibrateTilt(1); getTilt(1); }
