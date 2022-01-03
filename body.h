#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwmLinks=Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwmRechts=Adafruit_PWMServoDriver(0x41);

enum {L,R};   // Links, Rechts
enum {V,M,H}; // Vorne, Mitte, Hinten
enum {S,K,F}; // Schulter, Knie, Fuß
enum {Default,Up,Up2,Down,Down2,Front,Mid,Rear,Left,Right};

struct legStruct {
  int upValue[2][3][3];
  int up2Value[2][3][3];
  int midValue[2][3][3];
  int downValue[2][3][3];
  int down2Value[2][3][3];
  int frontValue[2][3][3];
  int rearValue[2][3][3];
  int adjustValue[2][3][3];
  int adjDirValue[2][3][3];
  int balanceValue[2][3][3];
  int currentValue[2][3][3];
  int nowValue[2][3][3];
  int channel[2][3][3]; };

struct legStruct leg;

struct queueStruct {
  int steps[100];
  unsigned long timeValue[100];
  int servo[100][3];
  int channel[100];
  float currentValue[100];
  float deltaValue[100];
  int targetValue[100]; };

struct queueStruct queue;

unsigned long bodyTimer; unsigned long balanceTimer; unsigned long lastTime; int lastSteps; int lastSpeed; bool balanceMode;

void bodyWorker() {
  if (millis()>=bodyTimer) { bodyTimer=millis()+10;
    for (int a=0;a<100;a++) { if (queue.steps[a]>0) {
      if (millis()>=queue.timeValue[a]) {
        queue.currentValue[a]+=queue.deltaValue[a]; queue.steps[a]--;
        if (queue.steps[a]==0) { queue.currentValue[a]=queue.targetValue[a];
          if (debug) { Serial.println("Ready Queue " + String(a) + " " + String(queue.servo[a][0]) + " " + String(queue.channel[a]) + "."); } }
        leg.nowValue[queue.servo[a][0]][queue.servo[a][1]][queue.servo[a][2]]=queue.currentValue[a];
        if (queue.servo[a][0]==L) { pwmLinks.setPWM(queue.channel[a],0,queue.currentValue[a]+leg.balanceValue[L][queue.servo[a][1]][queue.servo[a][2]]); }
        if (queue.servo[a][0]==R) { pwmRechts.setPWM(queue.channel[a],0,queue.currentValue[a]+leg.balanceValue[R][queue.servo[a][1]][queue.servo[a][2]]); } } } } } }

void doBalancing() {
  for (int y=0;y<3;y++) { for (int z=1;z<3;z++) {
    pwmLinks.setPWM(leg.channel[L][y][z],0,leg.nowValue[L][y][z]+leg.balanceValue[L][y][z]*2);
    pwmRechts.setPWM(leg.channel[R][y][z],0,leg.nowValue[R][y][z]+leg.balanceValue[R][y][z]*2); } } }

void balanceWorker() {
  if (millis()>=balanceTimer) { balanceTimer=millis()+100; if (balanceMode) {
    if (tilt.x>+1) { for (int x=0;x<2;x++) { for (int z=1;z<3;z++) {
      leg.balanceValue[x][V][z]+=leg.adjDirValue[x][V][z]; leg.balanceValue[x][H][z]-=leg.adjDirValue[x][H][z]; } } doBalancing(); }
    else if (tilt.x<-1) { for (int x=0;x<2;x++) { for (int z=1;z<3;z++) {
      leg.balanceValue[x][V][z]-=leg.adjDirValue[x][V][z]; leg.balanceValue[x][H][z]+=leg.adjDirValue[x][H][z]; } } doBalancing(); }
    if (tilt.y>+1) { for (int y=0;y<3;y++) { for (int z=1;z<3;z++) {
      leg.balanceValue[L][y][z]-=leg.adjDirValue[L][y][z]; leg.balanceValue[R][y][z]+=leg.adjDirValue[R][y][z]; } } doBalancing(); }
    else if (tilt.y<-1) { for (int y=0;y<3;y++) { for (int z=1;z<3;z++) {
      leg.balanceValue[L][y][z]+=leg.adjDirValue[L][y][z]; leg.balanceValue[R][y][z]-=leg.adjDirValue[R][y][z]; } } doBalancing(); } } } }

void setQueue(int x,int y,int z,int targetValue,unsigned long timeValue,int speedValue) {
  //timeValue=0 starts at the same time as last
  //timeValue=1 starts after last stops
  //timeValue=x starts x ms after last stops
  //speedValue=0 use a speed to end simultaneously with last
  //speedValue=1 use last speed
  //speedValue=x speed is x per second
  for (int a=0;a<100;a++) { if (queue.steps[a]==0) {
    queue.servo[a][0]=x; queue.servo[a][1]=y; queue.servo[a][2]=z;
    queue.channel[a]=leg.channel[x][y][z];
    queue.currentValue[a]=leg.currentValue[x][y][z];
    queue.targetValue[a]=targetValue+(leg.adjustValue[x][y][z]*leg.adjDirValue[x][y][z]);
    if (speedValue==1) { speedValue=lastSpeed; }
    if (speedValue==0) { queue.steps[a]=lastSteps; }
    else { queue.steps[a]=abs(queue.targetValue[a]-queue.currentValue[a])*100/speedValue; lastSpeed=speedValue; }
    if (queue.steps[a]==0) { queue.steps[a]=1; }
    queue.deltaValue[a]=(queue.targetValue[a]-queue.currentValue[a])/queue.steps[a];
    if (timeValue==1) { timeValue=lastSteps*10; }
    else if (timeValue>1) { timeValue+=lastSteps*10; }
    queue.timeValue[a]=max(lastTime+timeValue,millis());
    lastSteps=queue.steps[a]; lastTime=queue.timeValue[a];
    if (debug) { Serial.println("Set Queue " + String(x) + " " + String(y) + " " + String(z) + " to Value " + String(targetValue) + " in " + String(lastTime-millis()) + " ms."); }
    break; } }
  leg.currentValue[x][y][z]=targetValue+(leg.adjustValue[x][y][z]*leg.adjDirValue[x][y][z]); }
    
void setLeg(int x,int y, int z,unsigned long timeValue, int speedValue) {
  if (z==Default) {
    setQueue(x,y,S,leg.midValue[x][y][S],timeValue,speedValue);
    setQueue(x,y,K,leg.midValue[x][y][K],0,0);
    setQueue(x,y,F,leg.midValue[x][y][F],0,0); }
  if (z==Up) {
    setQueue(x,y,K,leg.upValue[x][y][K],timeValue,speedValue);
    setQueue(x,y,F,leg.downValue[x][y][F],0,0); }
  if (z==Up2) {
    setQueue(x,y,K,leg.up2Value[x][y][K],timeValue,speedValue);
    setQueue(x,y,F,leg.down2Value[x][y][F],0,0); }
  if (z==Down) {
    setQueue(x,y,K,leg.midValue[x][y][K],timeValue,speedValue);
    setQueue(x,y,F,leg.midValue[x][y][F],0,0); }
  if (z==Front) { setQueue(x,y,S,leg.frontValue[x][y][S],timeValue,speedValue); }
  if (z==Mid) { setQueue(x,y,S,leg.midValue[x][y][S],timeValue,speedValue); }
  if (z==Rear) { setQueue(x,y,S,leg.rearValue[x][y][S],timeValue,speedValue); }
  if (z==Left) { if (x==L) { setQueue(x,y,S,leg.rearValue[x][y][S],timeValue,speedValue); } else { setQueue(x,y,S,leg.frontValue[x][y][S],timeValue,speedValue); } }
  if (z==Right) { if (x==R) { setQueue(x,y,S,leg.rearValue[x][y][S],timeValue,speedValue); } else { setQueue(x,y,S,leg.frontValue[x][y][S],timeValue,speedValue); } } }

void setTri(int tri,int z,unsigned long timeValue, int speedValue) {
  if (tri==L) { setLeg(R,M,z,timeValue,speedValue); setLeg(L,V,z,0,1); setLeg(L,H,z,0,1); }
  if (tri==R) { setLeg(L,M,z,timeValue,speedValue); setLeg(R,V,z,0,1); setLeg(R,H,z,0,1); } }

void loadLegAdjust() {
  preferences.begin("lazyBug",false);
  if (preferences.isKey("adjustValue")) { preferences.getBytes("adjustValue",leg.adjustValue,72); }
  else { for (int x=0;x<2;x++) { for (int y=0;y<3;y++) { for (int z=0;z<3;z++) { leg.adjustValue[x][y][z]=0; } } } }
  preferences.end(); }

void saveLegAdjust() {
  preferences.begin("lazyBug",false);
  preferences.putBytes("adjustValue",leg.adjustValue,72);
  preferences.end(); }

void initBody() {
  bodyTimer=millis()+10; balanceTimer=millis()+100; lastTime=millis()+10; lastSteps=100; lastSpeed=100; balanceMode=false; loadLegAdjust();
  for (int a=0;a<100;a++) { queue.steps[a]=0; }
  int servoFreq=50;
  int servoMin2=4096/(1000/servoFreq)*1;
  int servoMin=4096/(1000/servoFreq)*1.25;
  int servoDef=4096/(1000/servoFreq)*1.5;
  int servoMax=4096/(1000/servoFreq)*1.75;
  int servoMax2=4096/(1000/servoFreq)*2;

  int c=0; for (int y=0;y<3;y++) { for (int z=0;z<3;z++) {
    leg.midValue[L][y][z]=servoDef; leg.midValue[R][y][z]=servoDef;
    leg.balanceValue[L][y][z]=0; leg.balanceValue[R][y][z]=0;
    if (z==S) {
      leg.frontValue[L][y][z]=servoMax; leg.frontValue[R][y][z]=servoMin;
      leg.rearValue[L][y][z]=servoMin; leg.rearValue[R][y][z]=servoMax;
      leg.adjDirValue[L][y][z]=1; leg.adjDirValue[R][y][z]=-1;
      leg.currentValue[L][y][z]=servoDef+(leg.adjustValue[L][y][z]*leg.adjDirValue[L][y][z]);
      leg.currentValue[R][y][z]=servoDef+(leg.adjustValue[R][y][z]*leg.adjDirValue[R][y][z]); }
    if (z==K) {
      leg.upValue[L][y][z]=servoMax; leg.upValue[R][y][z]=servoMin;
      leg.up2Value[L][y][z]=servoMax2; leg.up2Value[R][y][z]=servoMin2;
      leg.downValue[L][y][z]=servoMin; leg.downValue[R][y][z]=servoMax;
      leg.down2Value[L][y][z]=servoMin2; leg.down2Value[R][y][z]=servoMax2;
      leg.adjDirValue[L][y][z]=1; leg.adjDirValue[R][y][z]=-1;
      leg.currentValue[L][y][z]=servoMax2+(leg.adjustValue[L][y][z]*leg.adjDirValue[L][y][z]);
      leg.currentValue[R][y][z]=servoMin2+(leg.adjustValue[R][y][z]*leg.adjDirValue[R][y][z]); }
    if (z==F) {
      leg.upValue[L][y][z]=servoMin; leg.upValue[R][y][z]=servoMax;
      leg.up2Value[L][y][z]=servoMin2; leg.up2Value[R][y][z]=servoMax2;
      leg.downValue[L][y][z]=servoMax; leg.downValue[R][y][z]=servoMin;
      leg.down2Value[L][y][z]=servoMax2; leg.down2Value[R][y][z]=servoMin2;
      leg.adjDirValue[L][y][z]=1; leg.adjDirValue[R][y][z]=-1;
      leg.currentValue[L][y][z]=servoMin2+(leg.adjustValue[L][y][z]*leg.adjDirValue[L][y][z]);
      leg.currentValue[R][y][z]=servoMax2+(leg.adjustValue[R][y][z]*leg.adjDirValue[R][y][z]); }

    leg.nowValue[L][y][z]=leg.currentValue[L][y][z]; leg.nowValue[R][y][z]=leg.currentValue[R][y][z];
    leg.channel[L][y][z]=c; leg.channel[R][y][z]=c;
    if (c==2) { c=7; } else if (c==9) { c=13; } else { c++; } } }

  pwmLinks.begin(); pwmLinks.setPWMFreq(servoFreq);
  pwmRechts.begin(); pwmRechts.setPWMFreq(servoFreq);
  Wire.setClock(400000); }
