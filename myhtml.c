#include "myhtml.h"  /* Include the header (not strictly necessary here) */

// wegen )"; aufpassen wegen Ende von R"(
// bei Funktionsaufrufen GetArduinoIO() " <- Leerzeichen


const char *HTML_CHAR = R"(<!DOCTYPE html>
<html>
    <head>
        <title>Arduino Ajax I/O</title>
        <script>
    strLED1 = "";
    strLED2 = "";
    strLED3 = "";
    strLED4 = "";
    var LED3_state = 0;
    var LED4_state = 0;
    function GetArduinoIO()
    {
      nocache = "&nocache=" + Math.random() * 1000000;
      var request = new XMLHttpRequest();
      request.onreadystatechange = function()
      {
        if (this.readyState == 4) {
          if (this.status == 200) {
            if (this.responseXML != null) {
              // XML file received - contains analog values, switch values and LED states
              var count;
              // get analog inputs
              var num_an = this.responseXML.getElementsByTagName('analog').length;
              for (count = 0; count < num_an; count++) {
                document.getElementsByClassName("analog")[count].innerHTML =
                  this.responseXML.getElementsByTagName('analog')[count].childNodes[0].nodeValue;
              }
              // get switch inputs
              var num_an = this.responseXML.getElementsByTagName('switch').length;
              for (count = 0; count < num_an; count++) {
                document.getElementsByClassName("switches")[count].innerHTML =
                  this.responseXML.getElementsByTagName('switch')[count].childNodes[0].nodeValue;
              }
              // LED 1
              if (this.responseXML.getElementsByTagName('LED')[0].childNodes[0].nodeValue === "checked") {
                document.LED_form.LED1.checked = true;
              }
              else {
                document.LED_form.LED1.checked = false;
              }
              // LED 2
              if (this.responseXML.getElementsByTagName('LED')[1].childNodes[0].nodeValue === "checked") {
                document.LED_form.LED2.checked = true;
              }
              else {
                document.LED_form.LED2.checked = false;
              }
              // LED 3
              if (this.responseXML.getElementsByTagName('LED')[2].childNodes[0].nodeValue === "on") {
                document.getElementById("LED3").innerHTML = "LED 3 is ON";
                LED3_state = 1;
              }
              else {
                document.getElementById("LED3").innerHTML = "LED 3 is OFF";
                LED3_state = 0;
              }
              // LED 4
              if (this.responseXML.getElementsByTagName('LED')[3].childNodes[0].nodeValue === "on") {
                document.getElementById("LED4").innerHTML = "LED 4 is ON ";
                LED4_state = 1;
              }
              else {
                document.getElementById("LED4").innerHTML = "LED 4 is OFF";
                LED4_state = 0;
              }
            }
          }
        }
      }
      // send HTTP GET request with LEDs to switch on/off if any
      request.open("GET", "ajax_inputs" + strLED1 + strLED2 + strLED3 + strLED4 + nocache, true);
      request.send(null);
      // setTimeout('GetArduinoIO()', 1000);
      strLED1 = "";
      strLED2 = "";
      strLED3 = "";
      strLED4 = "";
    }
    // service LEDs when checkbox checked/unchecked
    function GetCheck()
    {
      if (LED_form.LED1.checked) {
        strLED1 = "&LED1=1";
      }
      else {
        strLED1 = "&LED1=0";
      }
      if (LED_form.LED2.checked) {
        strLED2 = "&LED2=1";
      }
      else {
        strLED2 = "&LED2=0";
      }
    }
    function GetButton1()
    {
      if (LED3_state === 1) {
        LED3_state = 0;
        strLED3 = "&LED3=0";
      }
      else {
        LED3_state = 1;
        strLED3 = "&LED3=1";
      }
    }
    function GetButton2()
    {
      if (LED4_state === 1) {
        LED4_state = 0;
        strLED4 = "&LED4=0";
      }
      else {
        LED4_state = 1;
        strLED4 = "&LED4=1";
      }
    }
  </script>
  <style>
    .IO_box {
      float: left;
      margin: 0 20px 20px 0;
      border: 1px solid blue;
      padding: 0 5px 0 5px;
      width: 120px;
    }
    h1 {
      font-size: 120%;
      color: blue;
      margin: 0 0 10px 0;
    }
    h2 {
      font-size: 85%;
      color: #5734E6;
      margin: 5px 0 5px 0;
    }
    p, form, button {
      font-size: 80%;
      color: #252525;
    }
    .small_text {
      font-size: 70%;
      color: #737373;
    }
  </style>
    </head>
    <body onload="GetArduinoIO() ">
        <h1>Arduino Ajax I/O</h1>
        <div class="IO_box">
      <h2>Analog Inputs</h2>
      <p class="small_text">A0 used by Ethernet shield</p>
      <p class="small_text">A1 used by Ethernet shield</p>
      <p>A2: <span class="analog">...</span></p>
      <p>A3: <span class="analog">...</span></p>
      <p>A4: <span class="analog">...</span></p>
      <p>A5: <span class="analog">...</span></p>
    </div>
    <div class="IO_box">
      <h2>Switch Inputs</h2>
      <p class="small_text">D0: used by serial RX</p>
      <p class="small_text">D1: used by serial TX</p>
      <p>Switch 1 (D2): <span class="switches">...</span></p>
      <p>Switch 2 (D3): <span class="switches">...</span></p>
      <p class="small_text">D4: used by Ethernet shield</p>
      <p>Switch 3 (D5): <span class="switches">...</span></p>
    </div>
    <div class="IO_box">
      <h2>LEDs Using Checkboxes</h2>
      <form id="check_LEDs" name="LED_form">
        <input type="checkbox" name="LED1" value="0" onclick="GetCheck" />LED 1 (D6)<br /><br />
        <input type="checkbox" name="LED2" value="0" onclick="GetCheck" />LED 2 (D7)<br /><br />
      </form>
    </div>
    <div class="IO_box">
      <h2>LEDs Using Buttons</h2>
      <button type="button" id="LED3" onclick="GetButton1">LED 3 is OFF</button><br /><br />
      <button type="button" id="LED4" onclick="GetButton2">LED 4 is OFF</button><br /><br />
      <p class="small_text">D10 to D13 used by Ethernet shield</p>
    </div>
	<div class="IO_box">
	  <h2>submit test</h2>
	  <input type="button" onclick="myFunction() " name="dicker button" value="test" />
    </div>
    </body>
	<script>
	function myFunction() {
	  alert("url hopefully changed ");
	  window.history.pushState('page2', 'Title', '/test_url');
	}
	</script>
</html>
)";
