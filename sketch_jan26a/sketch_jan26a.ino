
 /* *  ESP8266 Communication and Protocols *  AJAX (Asynchronous JavaScript and XML) *  -Manoj R. Thakur */
 
#include <ESP8266WiFi.h> 
#include <ESP8266WebServer.h>
 
#include "htmlPage.h" //Our HTML JavaScript Web page
 
const char* wifiName = "Nova-Panos666"; 
const char* wifiPass = "200820082008";
 
#define LED 2
 
ESP8266WebServer server(80);  //Define server object
 
//Handles http request 
void handleRoot() {  server.send(200, "text/html", webPage); 
}
 

 
void setup() {

   Serial.begin(115200);  delay(10);  pinMode(LED,OUTPUT);  Serial.println();
 
  Serial.print("Connecting");
 
  WiFi.begin(wifiName, wifiPass);   //Connect to Wi-Fi
 
  while (WiFi.status() != WL_CONNECTED) {    delay(500);    Serial.print(".");  }
 
  Serial.println("");  Serial.println("Wi-Fi connected");  Serial.println("IP address: ");  Serial.println(WiFi.localIP());   
  server.on("/", handleRoot);     

 
  server.begin(); 
  Serial.println("HTTP server started"); 
  }
 
void loop() {  
  server.handleClient(); 
  }
