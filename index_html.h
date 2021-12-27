char *index_html=R"(

<!DOCTYPE html>
<html lang="en"><head>
<title>lazyBug - Hexapod Robot</title>
<meta name="author" content="Erik Dorstel">
<meta name="generator" content="vi">
<meta name="repository" content="https://github.com/ErikDorstel/lazyBug">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta charset="utf-8">
<style>
html   { font-family:Arial; }
div    { background-color:#888888; color:#ffffff; border:0px; padding:0px; margin:0px; text-align:center; width:100%; user-select:none; display:inline-block; }
select { background-color:#888888; color:#ffffff; font-size:1.0em; border:0px; padding:0px; margin:0px; }
table  { margin-left:auto; margin-right:auto; }
td     { text-align:right; }
.x0a   { background-color:#C0A0A0; padding:0.2em 0em 0.1em; width:100%; font-size:1.5em; }
.x0b   { background-color:#C0A0A0; padding:0.1em 0em 0.2em; width:100%; font-size:1.2em; }
.x0    { background-color:#C0A0A0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x1    { background-color:#A0B0C0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x2    { background-color:#888888; padding:0.3em 0em; width:48%; font-size:1.4em; }
.x3    { background-color:#888888; padding:0.3em 0em; width:32%; font-size:1.4em; }
.x4    { background-color:#888888; padding:0.3em 0em; width:24%; font-size:1.4em; }
</style>
<script>

function lazyBuginit() {
  ajaxObj=[]; tiltX=0; tiltY=0; tiltD=0; tiltXY=0; dist=9999; legAdjust="0,0,0,0,0,0,";
  getSensor(); getSensorID=window.setInterval("getSensor();",1000);
  openStream(); getLegAdjust();
  doDisplay(); }
  
function doDisplay() {
  id("tiltX").innerHTML="X: "+tiltX+" &#176;";
  id("tiltY").innerHTML="Y: "+tiltY+" &#176;";
  id("tiltD").innerHTML="Dir: "+tiltD+" &#176;";
  id("tiltXY").innerHTML="Tilt: "+tiltXY+" &#176;";
  id("dist").innerHTML="Dist: "+dist+" mm";
  html="<table><tr><td> </td><td>Front</td><td>Middle</td><td>Rear</td></tr>";
  html+="<tr><td>Right</td><td>"+legAdjust.split(",")[3]+"</td><td>"+legAdjust.split(",")[4]+"</td><td>"+legAdjust.split(",")[5]+"</td></tr>";
  html+="<tr><td>Left</td><td>"+legAdjust.split(",")[0]+"</td><td>"+legAdjust.split(",")[1]+"</td><td>"+legAdjust.split(",")[2]+"</td></tr></table>";
  id("adjBtn").innerHTML=html; }

function doRange(doSet) { }

function openStream() { 
  stream=new WebSocket("ws://"+window.location.hostname+":81");
  stream.binaryType="arraybuffer"; stream.onmessage=streamMessage; }

function streamMessage(event) { sweepArray=new Int16Array(event.data); doDisplaySweep(); }

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
function getSensor() { requestAJAX('getSensor'); }
function setSweep(value) { requestAJAX('setSweep,'+value); }
function calibrateTilt() { id("calBtn").style.color="#888888"; requestAJAX('calibrateTilt'); }
function getLegAdjust() { requestAJAX('getLegAdjust'); }
function loadLegAdjust() { id("loaBtn").style.color="#888888"; requestAJAX('loadLegAdjust'); }
function saveLegAdjust() { id("savBtn").style.color="#888888"; requestAJAX('saveLegAdjust'); }
function setLegAdjust(value) { requestAJAX('setLegAdjust,'+id("xSel").selectedIndex+','+id("ySel").selectedIndex+','+value); getLegAdjust(); }

function doDisplaySweep() {
  xx=id('sweepFrame').width; yy=id('sweepFrame').height;
  sweepFrame=id('sweepFrame').getContext('2d');
  sweepFrame.clearRect(0,0,xx,yy);
  sweepFrame.strokeStyle="black"; sweepFrame.lineWidth=1;
  for (a=0.1;a<=1;a+=0.1) { sweepFrame.beginPath(); sweepFrame.arc(xx/2,yy,(yy*a)-1,Math.PI,2*Math.PI); sweepFrame.stroke(); }
  sweepFrame.strokeStyle="black"; sweepFrame.lineWidth=3;
  sweepFrame.beginPath();
  for (a=0;a<=40;a++) {
    r=mapValue(sweepArray[a],0,1000,0,yy-1);
    w=mapValue(a,0,40,2*Math.PI,Math.PI);
    x=(xx/2)+(Math.cos(w)*r); y=(yy)+(Math.sin(w)*r);
    if (a==0) { sweepFrame.moveTo(x,y); }
    else if (sweepArray[a-1]<=1000 & sweepArray[a]<=1000) { sweepFrame.lineTo(x,y); }
    else { sweepFrame.moveTo(x,y); } } sweepFrame.stroke(); }

function requestAJAX(value) {
  ajaxObj[value]=new XMLHttpRequest; ajaxObj[value].url=value; ajaxObj[value].open("GET",value,true);
  ajaxObj[value].setRequestHeader("Content-Type","application/x-www-form-urlencoded"); ajaxObj[value].addEventListener('load',replyAJAX); ajaxObj[value].send(); }

function replyAJAX(event) {
  if (event.target.status==200) {
    if (event.target.url=="getSensor") { tiltX=event.target.responseText.split(",")[0]*1; tiltY=event.target.responseText.split(",")[1]*1;
      tiltD=event.target.responseText.split(",")[2]*1; tiltXY=event.target.responseText.split(",")[3]*1; dist=event.target.responseText.split(",")[4]*1; doDisplay(); }
    else if (event.target.url=="calibrateTilt") { id("calBtn").style.color="#ffffff"; }
    else if (event.target.url=="loadLegAdjust") { getLegAdjust(); id("loaBtn").style.color="#ffffff"; }
    else if (event.target.url=="saveLegAdjust") { id("savBtn").style.color="#ffffff"; }
    else if (event.target.url=="getLegAdjust") { legAdjust=event.target.responseText; doDisplay(); } } }

function mapValue(value,inMin,inMax,outMin,outMax) { return (value-inMin)*(outMax-outMin)/(inMax-inMin)+outMin; }
function id(id) { return document.getElementById(id); }

</script></head><body onload="lazyBuginit();">

<div><div class="x0a">lazyBug</div></div>
<div><div class="x0b">Hexapod Robot</div></div>

<div class="x1" onclick="location.replace('/chooseAP');">Choose WLAN AP</div></div>

<div>
<div><div class="x2" id="tiltX"></div>
     <div class="x2" id="tiltY"></div></div>
<div><div class="x2" id="tiltD"></div>
     <div class="x2" id="tiltXY"></div></div>
<div><div class="x1" id="dist"></div></div>
<div><div class="x1"><canvas id="sweepFrame" width="400px" height="200px"></canvas></div></div>
<div><div class="x2" onclick="setSweep(1);">Sweep On</div>
     <div class="x2" onclick="setSweep(0);">Sweep Off</div></div>
<div><div class="x1" id="calBtn" onclick="calibrateTilt();">Calibrate Tilt Sensor</div></div>
<div><div class="x1" id="loaBtn" onclick="loadLegAdjust();">Load Leg Adjust Values</div></div>
<div><div class="x1" id="savBtn" onclick="saveLegAdjust();">Save Leg Adjust Values</div></div>
<div><div class="x1" id="adjBtn"></div></div>
<div><div class="x3">Adjust Leg</div>
     <div class="x3"><select id="xSel">
     <option value="0">Left</option>
     <option value="1">Right</option></select></div>
     <div class="x3"><select id="ySel">
     <option value="0">Front</option>
     <option value="1">Middle</option>
     <option value="2">Rear</option></select></div></div>
<div><div class="x4" onclick="setLegAdjust(-10);">&#8722; 10</div>
     <div class="x4" onclick="setLegAdjust(-1);">&#8722; 1</div>
     <div class="x4" onclick="setLegAdjust(1);">+ 1</div>
     <div class="x4" onclick="setLegAdjust(10);">+ 10</div></div>
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
