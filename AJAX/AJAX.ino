#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include "DHT.h"
#define LED 2
#define DHTPIN 2
#define DHTTYPE DHT11
IPAddress staticIP(192, 168, 2, 35); //ESP static ip
IPAddress gateway(192, 168, 2, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
const byte dhtPin = 2;
DHT dht(dhtPin, DHTTYPE);
float temp, tempf, humi;
ESP8266WebServer server;
uint8_t pin_led = 2;
char* ssid = "DenThelwNaMilas";
char* password = "Stratologiko22@";
int Led1,Led2,Led3,Led4,Led5,Led6,Led7,Led8,Led9,Led10,Led11,Led12,Led13 = 0;
int Relay1,Relay2,Relay3,Relay4,Relay5,Relay6 = 0;
const char* imagefile = "/image.png";
void handleWebRequests(){
  if(loadFromSpiffs(server.uri())) return;
  String message = "File Not Detected\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " NAME:"+server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  Serial.println(message);
}
void handleADC() {  int a = analogRead(A0);  String adcValue = String(a);
 
server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
}
void handleLED() {  String ledState = "OFF";
 String t_state = server.arg("LEDstate"); //Refer  xhttp.open("GET","setLED?LEDstate="+led, true); 
Serial.println(t_state);  
if(t_state == "1")
 {   digitalWrite(12,LOW); //LED ON  
 Led1=1;
 ledState = "ON";
 }  else if(t_state == "0")
 {   digitalWrite(12,HIGH);    
Led1=0;
ledState = "OFF";
 } else if(t_state == "2")
 {   digitalWrite(13,HIGH);    
Led2=0;ledState = "OFF";
 } else if(t_state == "3")
 {    digitalWrite(13,LOW);   
Led2=1; ledState = "ON";
 } else if(t_state == "4")
 {   digitalWrite(2,HIGH);    
Led3=0;ledState = "OFF";
 } else if(t_state == "5")
 {    digitalWrite(2,LOW);   
Led3=1; ledState = "ON";
 } else if(t_state == "6")
 {  digitalWrite(2,HIGH);    
Led4=0;ledState = "OFF";
 } else if(t_state == "7")
 {    digitalWrite(2,LOW);    
Led4=1;ledState = "ON";
 } else if(t_state == "8")
 {   digitalWrite(2,HIGH);    
Led5=0;ledState = "OFF";
 } else if(t_state == "9")
 {    digitalWrite(2,LOW);   
Led5=1;ledState = "ON";
 } else if(t_state == "10")
 {   digitalWrite(2,HIGH);    
Led6=0;ledState = "OFF";
 } else if(t_state == "11")
 {    digitalWrite(2,LOW);   
Led6=1;ledState = "ON";
 } else if(t_state == "12")
 {   digitalWrite(2,HIGH);    
Led7=0;ledState = "OFF";
 } else if(t_state == "13")
 {    digitalWrite(2,LOW);   
Led7=1;ledState = "ON";
 } else if(t_state == "14")
 {   digitalWrite(2,HIGH);    
Led8=0;ledState = "OFF";
 } else if(t_state == "15")
 {    digitalWrite(2,LOW);   
Led8=1;ledState = "ON";
 }else if(t_state == "16")
 {   digitalWrite(2,HIGH);    
Led9=0;ledState = "OFF";
 }else if(t_state == "17")
 {    digitalWrite(2,LOW);   
Led9=1;ledState = "ON";
 }else if(t_state == "18")
 {   digitalWrite(2,HIGH);    
Led10=0;ledState = "OFF";
 }else if(t_state == "19")
 {    digitalWrite(2,LOW);   
Led10=1;ledState = "ON";
 }else if(t_state == "20")
 {   digitalWrite(2,HIGH);    
Led11=0;ledState = "OFF";
 }else if(t_state == "21")
 {    digitalWrite(2,LOW);   
Led11=1;ledState = "ON";
 }else if(t_state == "22")
 {   digitalWrite(2,HIGH);    
Led12=0;ledState = "OFF";
 }else if(t_state == "23")
 {   digitalWrite(2,LOW);   
Led12=1;ledState = "ON";
 }else if(t_state == "24")
 {   digitalWrite(2,HIGH);    
Led13=0;ledState = "OFF";
 }else if(t_state == "25")
 {    digitalWrite(2,LOW);   
Led13=1;ledState = "ON";
 }
 
server.send(200, "text/plane", ledState); //Send web page
}
void setup()
{dht.begin();
  SPIFFS.begin();
  pinMode(pin_led, OUTPUT);
  WiFi.config(staticIP, subnet, gateway);
  WiFi.begin(ssid,password);
  Serial.begin(115200);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/",serveIndexFile);
  server.on("/ledstate",getLEDState);
  server.onNotFound(handleWebRequests);      //Associate handler function to web requests   
  server.on("/setLED", handleLED);   
  server.on("/setRELAY", handleRELAY);
  server.on("/readADC", handleADC);
   server.on("/checkState", checkState);
   server.on("/checkState2", checkState2);
   server.on("/allOn", allOn);
   server.on("/allOff", allOff);
   server.on("/checkT", checkT);
     server.on("/checkH", checkH);
     server.on("/allOn2", allOn2);
   server.on("/allOff2", allOff2);
  server.begin();
}

void loop()
{
  server.handleClient();
}

void serveIndexFile()
{
  File file = SPIFFS.open("/index.html","r");
  server.streamFile(file, "text/html");
  file.close();
}

void toggleLED()
{
  digitalWrite(pin_led,!digitalRead(pin_led));
}

void getLEDState()
{
  
  String led_state = digitalRead(pin_led) ? "OFF" : "ON";
  server.send(200,"text/plain", led_state);
}
void allOn()
{
  
  Led1=1;
  Led2=1;
  Led3=1;
  Led4=1;
  Led5=1;
  Led6=1;
  Led7=1;
  Led8=1;
  Led9=1;
  Led10=1;
  Led11=1;
  Led12=1;
  Led13=1;
  Serial.print("all lights on e.g.: ");
   Serial.println(Led1+Led2+Led3+Led4);
  digitalWrite(2,LOW); 
  digitalWrite(2,LOW); 
  digitalWrite(2,LOW); 
  digitalWrite(2,LOW); 
  digitalWrite(2,LOW); 
  digitalWrite(2,LOW); 
  digitalWrite(2,LOW); 
  digitalWrite(2,LOW); 
  digitalWrite(2,LOW); 
  digitalWrite(2,LOW); 
  digitalWrite(2,LOW); 
  digitalWrite(2,LOW); 
  
}
void allOff()
{
  
  Led1=0;
  Led2=0;
  Led3=0;
  Led4=0;
  Led5=0;
  Led6=0;
  Led7=0;
  Led8=0;
  Led9=0;
  Led10=0;
  Led11=0;
  Led12=0;
  Led13=0;
   Serial.print("all lights off e.g.: ");
   Serial.println(Led1+Led2+Led3+Led4);
  digitalWrite(2,HIGH);
  digitalWrite(2,HIGH);
  digitalWrite(2,HIGH);
  digitalWrite(2,HIGH);
 digitalWrite(2,HIGH);
 digitalWrite(2,HIGH);
 digitalWrite(2,HIGH);
 digitalWrite(2,HIGH);
 digitalWrite(2,HIGH);
 
  
}
bool loadFromSpiffs(String path){
  
  
  String dataType = "text/plain";
  if(path.endsWith("/")) path += "index.htm";
 
  if(path.endsWith(".src")) path = path.substring(0, path.lastIndexOf("."));
  else if(path.endsWith(".html")) dataType = "text/html";
  else if(path.endsWith(".htm")) dataType = "text/html";
  else if(path.endsWith(".css")) dataType = "text/css";
  else if(path.endsWith(".js")) dataType = "application/javascript";
  else if(path.endsWith(".png")) dataType = "image/png";
  else if(path.endsWith(".gif")) dataType = "image/gif";
  else if(path.endsWith(".jpg")) dataType = "image/jpeg";
  else if(path.endsWith(".ico")) dataType = "image/x-icon";
  else if(path.endsWith(".xml")) dataType = "text/xml";
  else if(path.endsWith(".pdf")) dataType = "application/pdf";
  else if(path.endsWith(".zip")) dataType = "application/zip";
  File dataFile = SPIFFS.open(path.c_str(), "r");
  if (server.hasArg("download")) dataType = "application/octet-stream";
  if (server.streamFile(dataFile, dataType) != dataFile.size()) {
  }
 
  dataFile.close();
  return true;
}
void checkState(){
  
   String t_state = server.arg("LED");
   Serial.println(t_state); 
   if(t_state=="1"){ Serial.println("got into 1");
   if(Led1==0){
    server.send(200, "text/plane","off");
  }else if(Led1==1){
    server.send(200, "text/plane","on");
  }}
  else if(t_state=="2"){Serial.println("got into 2");
   if(Led2==0){
    server.send(200, "text/plane","off");
  }else if(Led2==1){
    server.send(200, "text/plane","on");
  }}
  else if(t_state=="3"){Serial.println("got into 3");
   if(Led3==0){
    server.send(200, "text/plane","off");
  }else if(Led3==1){
    server.send(200, "text/plane","on");
  }}
  else if(t_state=="4"){Serial.println("got into 4");
   if(Led4==0){
    server.send(200, "text/plane","off");
  }else if(Led4==1){
    server.send(200, "text/plane","on");
  }}
 else if(t_state=="5"){Serial.println("got into 5");
   if(Led5==0){
    server.send(200, "text/plane","off");
  }else if(Led5==1){
    server.send(200, "text/plane","on");
  }}
 else if(t_state=="6"){Serial.println("got into 6");
   if(Led6==0){
    server.send(200, "text/plane","off");
  }else if(Led6==1){
    server.send(200, "text/plane","on");
  }}
 else if(t_state=="7"){Serial.println("got into 7");
   if(Led7==0){
    server.send(200, "text/plane","off");
  }else if(Led7==1){
    server.send(200, "text/plane","on");
  }}
 else if(t_state=="8"){Serial.println("got into 8");
   if(Led8==0){
    server.send(200, "text/plane","off");
  }else if(Led8==1){
    server.send(200, "text/plane","on");
  }}
 else if(t_state=="9"){Serial.println("got into 9");
   if(Led9==0){
    server.send(200, "text/plane","off");
  }else if(Led9==1){
    server.send(200, "text/plane","on");
  }}
  else if(t_state=="10"){Serial.println("got into 10");
   if(Led10==0){
    server.send(200, "text/plane","off");
  }else if(Led10==1){
    server.send(200, "text/plane","on");
  }}else if(t_state=="11"){Serial.println("got into 11");
   if(Led11==0){
    server.send(200, "text/plane","off");
  }else if(Led11==1){
    server.send(200, "text/plane","on");
  }}else if(t_state=="12"){Serial.println("got into 12");
   if(Led12==0){
    server.send(200, "text/plane","off");
  }else if(Led12==1){
    server.send(200, "text/plane","on");
  }}else if(t_state=="13"){Serial.println("got into 13");
   if(Led13==0){
    server.send(200, "text/plane","off");
  }else if(Led13==1){
    server.send(200, "text/plane","on");
  }}



  
  }
  void checkT(){
    temp = dht.readTemperature();
    if (!isnan(temp)){
    server.send(200, "text/plane",String(temp));}
    else{
      server.send(200, "text/plane","error");
      }
    
    
    
    }
    void checkH(){
    humi = dht.readHumidity();
    if (!isnan(humi)){
    server.send(200, "text/plane",String(humi));}
    else{
      server.send(200, "text/plane","error");
      }
    
    
    
    }
    void allOn2()
{
  
  Relay1=1;
  Relay2=1;
  Relay3=1;
  Relay4=1;
  Relay5=1;
  Relay6=1;
  Serial.print("all lights off e.g.: ");
  Serial.print("Relay1: ");
  Serial.print(Relay1);
  Serial.print("Relay2: ");
  Serial.print(Relay2);
  Serial.print("Relay3: ");
  Serial.print(Relay3);
  Serial.print("Relay4: ");
  Serial.println(Relay4);
  
}
void allOff2()
{
  Relay1=0;
  Relay2=0;
  Relay3=0;
  Relay4=0;
  Relay5=0;
  Relay6=0;
  
  
   Serial.print("all lights off e.g.: ");
  Serial.print("Relay1: ");
  Serial.print(Relay1);
  Serial.print("Relay2: ");
  Serial.print(Relay2);
  Serial.print("Relay3: ");
  Serial.print(Relay3);
  Serial.print("Relay4: ");
  Serial.println(Relay4);
  
 
  
}
void checkState2(){
  
   String t_state = server.arg("Relay");
   Serial.println(t_state); 
   if(t_state=="1"){ Serial.println("got into 1");
   if(Relay1==0){
    server.send(200, "text/plane","off");
  }else if(Relay1==1){
    server.send(200, "text/plane","on");
  }}
  else if(t_state=="2"){Serial.println("got into 2");
   if(Relay2==0){
    server.send(200, "text/plane","off");
  }else if(Relay2==1){
    server.send(200, "text/plane","on");
  }}
  else if(t_state=="3"){Serial.println("got into 3");
   if(Relay3==0){
    server.send(200, "text/plane","off");
  }else if(Relay3==1){
    server.send(200, "text/plane","on");
  }}
  else if(t_state=="4"){Serial.println("got into 4");
   if(Relay4==0){
    server.send(200, "text/plane","off");
  }else if(Relay4==1){
    server.send(200, "text/plane","on");
  }}
 else if(t_state=="5"){Serial.println("got into 5");
   if(Relay5==0){
    server.send(200, "text/plane","off");
  }else if(Relay5==1){
    server.send(200, "text/plane","on");
  }}
 else if(t_state=="6"){Serial.println("got into 6");
   if(Relay6==0){
    server.send(200, "text/plane","off");
  }else if(Relay6==1){
    server.send(200, "text/plane","on");
  }}
  }
  void handleRELAY(){
     String ledState = "OFF";
 String t_state = server.arg("RELAYstate"); //Refer  xhttp.open("GET","setLED?LEDstate="+led, true); 
Serial.println(t_state);  
if(t_state == "1")
 {   digitalWrite(2,LOW); //LED ON  
 Relay1=1;
 ledState = "ON";
 }  else if(t_state == "0")
 {   digitalWrite(2,HIGH);    
Relay1=0;
ledState = "OFF";
 } else if(t_state == "2")
 {   digitalWrite(2,HIGH);    
Relay2=0;ledState = "OFF";
 } else if(t_state == "3")
 {    digitalWrite(2,LOW);   
Relay2=1; ledState = "ON";
 } else if(t_state == "4")
 {   digitalWrite(2,HIGH);    
Relay3=0;ledState = "OFF";
 } else if(t_state == "5")
 {    digitalWrite(2,LOW);   
Relay3=1; ledState = "ON";
 } else if(t_state == "6")
 {  digitalWrite(2,HIGH);    
Relay4=0;ledState = "OFF";
 } else if(t_state == "7")
 {    digitalWrite(2,LOW);    
Relay4=1;ledState = "ON";
 } else if(t_state == "8")
 {   digitalWrite(2,HIGH);    
Relay5=0;ledState = "OFF";
 } else if(t_state == "9")
 {    digitalWrite(2,LOW);   
Relay5=1;ledState = "ON";
 } else if(t_state == "10")
 {   digitalWrite(2,HIGH);    
Relay6=0;ledState = "OFF";
 } else if(t_state == "11")
 {    digitalWrite(2,LOW);   
Relay6=1;ledState = "ON";
 } 
    
    }
