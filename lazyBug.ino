boolean debug=true;

#include "tilt.h"
#include "dist.h"
#include "body.h"
#include "brain.h"
#include "WLAN.h"
#include "DNS.h"
#include "HTTP.h"

void setup() {
  if (debug) { Serial.begin(115200); }
  initWLAN();
  initTilt();
  initDist();
  initBody(); }

void loop() { httpWorker(); dnsWorker(); bodyWorker(); }
