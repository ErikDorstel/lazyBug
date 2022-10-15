boolean debug=true;

const char* appName="lazyBug";
const char* appDesc="Hexapod Robot";

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
  initDNS();
  initHTTP();
  initTilt();
  initDist();
  initBody();
  initWEBSOCKET(); }

void loop() { wlanWorker(); dnsWorker(); httpWorker(); bodyWorker(); distWorker(); tiltWorker(); websocketWorker(); balanceWorker(); }
