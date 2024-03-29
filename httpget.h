String httpget(String request) {
  String response="";

  // lazyBug specific pages

  if (request.indexOf("/lbDefault")>=0) { lbDefault(); }
  else if (request.indexOf("/lbStandUp")>=0) { lbStandUp(); }
  else if (request.indexOf("/lbSitDown")>=0) { lbSitDown(); }
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
  else if (request.indexOf("/getSweep")>=0) { response+=String(dist.sweepActive) + ","; }

  else if (request.indexOf("/setBalancing")>=0) { int a=request.indexOf(",")+1; balanceMode=request.substring(a).toInt(); }
  else if (request.indexOf("/getBalancing")>=0) { response+=String(balanceMode) + ","; }

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

  else if (request.indexOf("/appName")>=0) {
    response+=String(appName) + ",";
    response+=String(appDesc) + ","; }

  else if (request.indexOf("/chooseAP")>=0) { response=choose_html; }

  else if (request.indexOf("/statusAP")>=0) { if (wlanConfig.statusStation) { response="<div class=\"x1\">WLAN AP " + wlanConfig.ssidStation + " connected.</div>";
    response+="<div class=\"x1\">IP Address " + WiFi.localIP().toString() + "</div>"; } else { response="<div class=\"x1\">No WLAN AP connected.</div>"; } }

  else if (request.indexOf("/configAP")>=0) {
    if (WiFi.softAPgetStationNum()==0) { response=a2h(wlanConfig.ssidStation) + "," + a2h(wlanConfig.passwordStation) + ","; }
    else { response=a2h(wlanConfig.ssidStation) + ",,"; } }

  else if (request.indexOf("/scanAP")>=0) {
    wlanTimer=millis()+20000; int indexes=WiFi.scanNetworks(); response+="<div class=\"x1\"><table>"; for (int index=0;index<indexes;++index) { if (WiFi.SSID(index)!="") {
      response+="<tr><td onclick=\"setAP(\'" + WiFi.SSID(index) + "\');\">" + WiFi.RSSI(index) + "&nbsp;dB&nbsp;&nbsp;&nbsp;&nbsp;" + WiFi.SSID(index) + "</td></tr>"; } } response+="</table></div>"; }

  else if (request.indexOf("/connectAP")>=0) {
    int a=request.indexOf(",")+1; int b=request.indexOf(",",a)+1;
    if (!wlanConfig.statusStation || WiFi.softAPgetStationNum()==0) {
      wlanConfig.ssidStation=h2a(request.substring(a,b-1)); wlanConfig.passwordStation=h2a(request.substring(b)); wlanConfig.reconnectCount=0; reconnectWLAN(); }
    else { if (debug) { Serial.println("WLAN Station reconnect prevented."); } } }

  // Default page

  else { response=index_html; }

  return response; }
