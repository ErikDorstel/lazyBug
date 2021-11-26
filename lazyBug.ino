boolean debug=true;

#include "body.h"
#include "brain.h"
#include "WLAN.h"
#include "DNS.h"
#include "HTTP.h"

void setup() {
  if (debug) { Serial.begin(115200); }
  initWLAN();
  initBody(); }

void loop() { httpWorker(); dnsWorker(); bodyWorker(); }
