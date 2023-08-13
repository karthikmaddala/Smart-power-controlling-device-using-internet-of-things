#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>


#define LED D4

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

void handleRoot();              // function prototypes for HTTP handlers
void handleNotFound();

void setup(void){
  Serial.begin(115200);         // Start the Serial communication to senMd messages to the computer
  delay(10);
  Serial.println('\n');
  
  pinMode(LED, OUTPUT);
  digitalWrite(LED,HIGH);

  wifiMulti.addAP("Jai Balayya", "VRSEC123");   // add Wi-Fi networks you want to connect to
  wifiMulti.addAP("vrsec", "123456789");
  wifiMulti.addAP("gopi redmi", "12345678");
  wifiMulti.addAP("moto G(4)", "1234567890");
  wifiMulti.addAP("ganjisai19", "goldenstar");
  
  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
   // hi hello how are you  whats up what are you doing
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());               // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());            // Send the IP address of the ESP8266 to the computer

  if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  server.on("/", HTTP_GET, handleRoot);        // Call the 'handleRoot' function when a client requests URI "/"
  server.onNotFound(handleNotFound);           // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin();                            // Actually start the server
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();                     // Listen for HTTP requests from clients
}



void handleRoot(){
  
server.send_P(200,"text/html","<!DOCTYPE html>\n\n<html>\n\n<head>\n\n \n<title>Battery Status</title>\n \n<script>\n   \nsetInterval(function () {\n \n     function updateBatteryStatus(battery) {\n\nvar batt=battery.level*100;\n\nvar form = document.getElementById(\"theForm\");\n\ndocument.getElementById(\"1\").value=batt;\nform.submit();\n\n\n<!--document.querySelector('#level').textContent = battery.level*100;-->\n       \n };\n\n     \n navigator.getBattery().then(function(battery) {\n     \n  // Update the battery status initially when the promise resolves ...\n       \nupdateBatteryStatus(battery);\n\n\n        // .. and for any subsequent updates.\n     \n  battery.onchargingchange = function () {\n       \n  updateBatteryStatus(battery);\n       \n };\n\n       \n battery.onlevelchange = function () {\n       \n  updateBatteryStatus(battery);\n     \n  };\n\n       \nbattery.ondischargingtimechange = function () {\n       \n   updateBatteryStatus(battery);\n       \n };\n     \n });\n   \n },5000);\n\n \n </script>\n\n</head>\n\n<body onload=\"function()\">\n\n<form   method=\"GET\" id=\"theForm\">\n<input type=\"text\" name=\"b\" id=\"1\">\n\n<input type=\"submit\">\n\n</form>\n\n \n</body>\n\n</html>\n");
              
  String message;
  int value=99   ;
               message = server.arg("b");
        
               if(message.toInt()<=value){
                Serial.println("charging..");
               digitalWrite(LED,LOW);
                }
                else if(message.toInt()>value){
                  Serial.println("charge completed ..");
                  digitalWrite(LED,HIGH);
                  }   

}
            
void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}
