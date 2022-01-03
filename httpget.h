String httpget(String request) {
  String response="";

  // lazyBug specific pages

  if (request.indexOf("/lbStandUp")>=0) { lbStandUp(); }
  else if (request.indexOf("/lbTest1")>=0) { lbTest1(); }
  else if (request.indexOf("/lbTest2")>=0) { lbTest2(); }
  else if (request.indexOf("/turnLeftA")>=0) { turnLeftA(); }
  else if (request.indexOf("/turnLeftB")>=0) { turnLeftB(); }
  else if (request.indexOf("/turnLeftC")>=0) { turnLeftC(); }
  else if (request.indexOf("/turnRightA")>=0) { turnRightA(); }
  else if (request.indexOf("/turnRightB")>=0) { turnRightB(); }
  else if (request.indexOf("/goFrontA")>=0) { goFrontA(); }
  else if (request.indexOf("/goFrontB")>=0) { goFrontB(); }
  else if (request.indexOf("/goFrontC")>=0) { goFrontC(); }
  else if (request.indexOf("/goRearA")>=0) { goRearA(); }
  else if (request.indexOf("/goRearB")>=0) { goRearB(); }

  else if (request.indexOf("/calibrateTilt")>=0) { calibrateTilt(); }
  else if (request.indexOf("/loadTiltCalibration")>=0) { loadTiltCalibration(); }
  else if (request.indexOf("/saveTiltCalibration")>=0) { saveTiltCalibration(); }

  else if (request.indexOf("/getTilt")>=0) {
    response+=String(tilt.x) + "," + String(tilt.y) + "," + String(tilt.z) + "," + String(tilt.d) + "," + String(tilt.xy) + ","; }

  else if (request.indexOf("/setSweep")>=0) { int a=request.indexOf(",")+1; setSweep(request.substring(a).toInt()); }

  else if (request.indexOf("/setBalance")>=0) { int a=request.indexOf(",")+1; balanceMode=request.substring(a).toInt(); }

  else if (request.indexOf("/getLegAdjust")>=0) {
    for (int x=0;x<2;x++) { for (int y=0;y<3;y++) {
      response+=String(leg.adjustValue[x][y][K]) + ","; } } }

  else if (request.indexOf("/setLegAdjust")>=0) {
    int a=request.indexOf(",")+1; int b=request.indexOf(",",a)+1; int c=request.indexOf(",",b)+1;
    int x=request.substring(a,b-1).toInt(); int y=request.substring(b,c-1).toInt(); int z=request.substring(c).toInt();
    leg.adjustValue[x][y][K]+=z; leg.adjustValue[x][y][F]+=z; setLeg(x,y,Up,1,200); setLeg(x,y,Down,1,1); }

  else if (request.indexOf("/loadLegAdjust")>=0) { loadLegAdjust(); }
  else if (request.indexOf("/saveLegAdjust")>=0) { saveLegAdjust(); }

  // WLAN Choose specific pages

  else if (request.indexOf("/chooseAP")>=0) { response=choose_html; }

  else if (request.indexOf("/statusAP")>=0) { if (statusStation==true) { response="<div class=\"x1\">WLAN AP " + ssidStation + " connected.</div>";
    response+="<div class=\"x1\">IP Address " + WiFi.localIP().toString() + "</div>"; } else { response="<div class=\"x1\">No WLAN AP connected.</div>"; } }

  else if (request.indexOf("/configAP")>=0) { response=a2h(ssidStation) + "," + a2h(passwordStation) + ","; }

  else if (request.indexOf("/scanAP")>=0) {
    int indexes=WiFi.scanNetworks(); for (int index=0;index<indexes;++index) { if (WiFi.SSID(index)!="") {
      response+="<div class=\"x1\" onclick=\"setAP(\'" + WiFi.SSID(index) + "\');\">" + WiFi.RSSI(index) + "&nbsp;dB&nbsp;&nbsp;&nbsp;&nbsp;" + WiFi.SSID(index) + "</div>"; } } }

  else if (request.indexOf("/connectAP")>=0) {
    int a=request.indexOf(",")+1; int b=request.indexOf(",",a)+1;
    ssidStation=h2a(request.substring(a,b-1)); passwordStation=h2a(request.substring(b));
    reconnectWLAN(); }

  // Default page

  else { response=index_html; }

  return response; }
