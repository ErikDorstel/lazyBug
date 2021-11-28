String httpget(String request) {
  String response="";

  // lazyBug specific pages

  if (request.indexOf("/lbDefault")>=0) { lbDefault(); }
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

  else if (request.indexOf("/getTilt")>=0) {
    getTilt(); response+=String(tilt.x) + "," + String(tilt.y) + ","; }

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
