boolean debug=true;

#include "tilt.h"
#include "body.h"
#include "dist.h"
#include "brain.h"
#include "WLAN.h"
#include "DNS.h"
#include "HTTP.h"
#include "WEBSOCKET.h"

void setup() {
  if (debug) { Serial.begin(115200); }
  initWLAN();
  initTilt();
  initDist();
  initBody();
  initWEBSOCKET(); }

void loop() { httpWorker(); dnsWorker(); bodyWorker(); distWorker(); tiltWorker(); websocketWorker(); balanceWorker(); }
