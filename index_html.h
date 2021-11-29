char *index_html=R"(

<!DOCTYPE html>
<html lang="en"><head>
<title>lazyBug - Hexapod</title>
<meta name="author" content="Erik Dorstel">
<meta name="generator" content="vi">
<meta name="repository" content="https://github.com/ErikDorstel/lazyBug">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta charset="utf-8">
<style>
html { font-family:Arial; }
div  { background-color:#888888; color:#ffffff; border:0px; padding:0px; margin:0px; text-align:center; width:100%; user-select:none; display:inline-block; }
.x0a { background-color:#C0A0A0; padding:0.2em 0em 0.1em; width:100%; font-size:1.5em; }
.x0b { background-color:#C0A0A0; padding:0.1em 0em 0.2em; width:100%; font-size:1.2em; }
.x0  { background-color:#C0A0A0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x1  { background-color:#A0B0C0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x2  { background-color:#888888; padding:0.3em 0em; width:48%; font-size:1.4em; }
.x3  { background-color:#888888; padding:0.3em 0em; width:32%; font-size:1.4em; }
.x4  { background-color:#888888; padding:0.3em 0em; width:24%; font-size:1.4em; }
</style>
<script>

function lazyBuginit() {
  ajaxObj=[]; tiltX=0; tiltY=0;
  getTilt(); getTiltID=window.setInterval("getTilt();",1000);
  doDisplay(); }
  
function doDisplay() {
  document.getElementById("tiltX").innerHTML="X "+tiltX+" Grad";
  document.getElementById("tiltY").innerHTML="Y "+tiltY+" Grad"; }

function doRange(doSet) { }

function lbDefault() { requestAJAX('lbDefault'); }
function lbTest1() { requestAJAX('lbTest1'); }
function lbTest2() { requestAJAX('lbTest2'); }
function turnLeftA() { requestAJAX('turnLeftA'); }
function turnLeftB() { requestAJAX('turnLeftB'); }
function turnLeftC() { requestAJAX('turnLeftC'); }
function turnRightA() { requestAJAX('turnRightA'); }
function turnRightB() { requestAJAX('turnRightB'); }
function goFrontA() { requestAJAX('goFrontA'); }
function goFrontB() { requestAJAX('goFrontB'); }
function goFrontC() { requestAJAX('goFrontC'); }
function goRearA() { requestAJAX('goRearA'); }
function goRearB() { requestAJAX('goRearB'); }
function getTilt() { requestAJAX('getTilt'); }
function calibrateTilt() { window.clearInterval(getTiltID); tiltX=999; tiltY=999; doDisplay(); requestAJAX('calibrateTilt'); }

function requestAJAX(value) {
  ajaxObj[value]=new XMLHttpRequest; ajaxObj[value].url=value; ajaxObj[value].open("GET",value,true);
  ajaxObj[value].setRequestHeader("Content-Type","application/x-www-form-urlencoded"); ajaxObj[value].addEventListener('load',replyAJAX); ajaxObj[value].send(); }

function replyAJAX(event) {
  if (event.target.status==200) {
    if (event.target.url=="getTilt") { tiltX=event.target.responseText.split(",")[0]*1; tiltY=event.target.responseText.split(",")[1]*1; doDisplay(); }
    else if (event.target.url=="calibrateTilt") { getTiltID=window.setInterval("getTilt();",1000); } } }

</script></head><body onload="lazyBuginit();">

<div><div class="x0a">lazyBug</div></div>
<div><div class="x0b">Hexapod</div></div>

<div class="x1" onclick="location.replace('/chooseAP');">Choose WLAN AP</div></div>

<div>
<div><div class="x2" id="tiltX" onclick="getTilt();"></div>
     <div class="x2" id="tiltY" onclick="getTilt();"></div></div>
<div><div class="x1" onclick="calibrateTilt();">Calibrate Tilt Sensor</div></div>
<div><div class="x1" onclick="lbDefault();">Default</div></div>
<div><div class="x1" onclick="lbTest1();">Test 1</div></div>
<div><div class="x1" onclick="lbTest2();">Test 2</div></div>
<div><div class="x2" onclick="turnLeftA();">Turn Left A</div>
     <div class="x2" onclick="turnLeftB();">Turn Left B</div></div>
<div><div class="x2" onclick="turnRightA();">Turn Right A</div>
     <div class="x2" onclick="turnRightB();">Turn Right B</div></div>
<div><div class="x2" onclick="goFrontA();">Go Front A</div>
     <div class="x2" onclick="goFrontB();">Go Front B</div></div>
<div><div class="x2" onclick="goRearA();">Go Rear A</div>
     <div class="x2" onclick="goRearB();">Go Rear B</div></div>
<div><div class="x1" onclick="goFrontC();">Go Front C</div></div>
<div><div class="x1" onclick="turnLeftC();">Turn Left C</div></div>
</div>

</body></html>

)";
