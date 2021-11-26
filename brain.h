void lbDefault() {
  setLeg(L,V,Default,1,200); setLeg(L,M,Default,100,1); setLeg(L,H,Default,100,1);
  setLeg(R,V,Default,100,1); setLeg(R,M,Default,100,1); setLeg(R,H,Default,100,1); }

void lbTest1() {
  setLeg(L,V,Up,1,200); setLeg(L,V,Down,1,1);
  setLeg(L,M,Up,1,1); setLeg(L,M,Down,1,1);
  setLeg(L,H,Up,1,1); setLeg(L,H,Down,1,1);
  setLeg(R,V,Up,1,1); setLeg(R,V,Down,1,1);
  setLeg(R,M,Up,1,1); setLeg(R,M,Down,1,1);
  setLeg(R,H,Up,1,1); setLeg(R,H,Down,1,1); }

void lbTest2() {
  setLeg(L,V,Up,1,200); setLeg(L,V,Front,0,0); setLeg(L,V,Down,1,1);
  setLeg(R,V,Up,1,1); setLeg(R,V,Front,0,0); setLeg(R,V,Down,1,1);
  setLeg(L,V,Rear,1,1); setLeg(L,V,Up,0,0); setLeg(L,V,Down,1,1);
  setLeg(R,V,Rear,1,1); setLeg(R,V,Up,0,0); setLeg(R,V,Down,1,1);
  setLeg(L,V,Up,1,1); setLeg(L,V,Mid,0,0); setLeg(L,V,Down,1,1);
  setLeg(R,V,Up,1,1); setLeg(R,V,Mid,0,0); setLeg(R,V,Down,1,1); }

void turnLeftA() {
  setTri(R,Up,1,200);
  setTri(L,Right,0,1);
  setTri(R,Down,1,1);
  setTri(L,Up,1,1);
  setTri(L,Mid,0,1);
  setTri(L,Down,1,1); }

void turnLeftB() {
  setTri(L,Up,1,200);
  setTri(R,Right,0,1);
  setTri(L,Down,1,1);
  setTri(R,Up,1,1);
  setTri(R,Mid,0,1);
  setTri(R,Down,1,1); }

void turnRightA() {
  setTri(R,Up,1,200);
  setTri(L,Left,0,1);
  setTri(R,Down,1,1);
  setTri(L,Up,1,1);
  setTri(L,Mid,0,1);
  setTri(L,Down,1,1); }

void turnRightB() {
  setTri(L,Up,1,200);
  setTri(R,Left,0,1);
  setTri(L,Down,1,1);
  setTri(R,Up,1,1);
  setTri(R,Mid,0,1);
  setTri(R,Down,1,1); }

void goFrontA() {
  setTri(R,Up,1,200);
  setTri(L,Rear,0,1);
  setTri(R,Down,1,1);
  setTri(L,Up,1,1);
  setTri(L,Mid,0,1);
  setTri(L,Down,1,1); }

void goFrontB() {
  setTri(L,Up,1,200);
  setTri(R,Rear,0,1);
  setTri(L,Down,1,1);
  setTri(R,Up,1,1);
  setTri(R,Mid,0,1);
  setTri(R,Down,1,1); }

void goRearA() {
  setTri(R,Up,1,200);
  setTri(L,Front,0,1);
  setTri(R,Down,1,1);
  setTri(L,Up,1,1);
  setTri(L,Mid,0,1);
  setTri(L,Down,1,1); }

void goRearB() {
  setTri(L,Up,1,200);
  setTri(R,Front,0,1);
  setTri(L,Down,1,1);
  setTri(R,Up,1,1);
  setTri(R,Mid,0,1);
  setTri(R,Down,1,1); }

void goFrontC() {
  setTri(R,Up,1,20);
  setTri(L,Rear,0,1);
  setTri(R,Down,1,1);
  setTri(L,Up,1,1);
  setTri(L,Mid,0,1);
  setTri(R,Rear,0,1);
  setTri(L,Down,1,1);
  setTri(R,Up,1,1);
  setTri(R,Mid,0,1);
  setTri(R,Down,1,1); }

void turnLeftC() {
  setTri(R,Up,1,20);
  setTri(L,Right,0,1);
  setTri(R,Down,1,1);
  setTri(L,Up,1,1);
  setTri(L,Mid,0,1);
  setTri(R,Right,0,1);
  setTri(L,Down,1,1);
  setTri(R,Up,1,1);
  setTri(R,Mid,0,1);
  setTri(R,Down,1,1); }
