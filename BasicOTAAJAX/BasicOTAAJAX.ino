#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#ifndef STASSID
#define STASSID "Nova-Panos666"
#define STAPSK  "200820082008"
#endif


#include <ESP8266WebServer.h>
#include <FS.h>
#include "DHT.h"
#include<SoftwareSerial.h>
SoftwareSerial SUART(4, 5); //SRX=Dpin-D2; STX-DPin-D1
#define LED 2
#define DHTPIN 2
#define DHTTYPE DHT11
const byte dhtPin = 2; //@@@ το πινακι του αισθητηρα θερμοκρασιας υγρασιας
DHT dht(dhtPin, DHTTYPE);
float temp, tempf, humi;
ESP8266WebServer server;
uint8_t pin_led = 2;
char* ssid = "Nova-Panos666";//@@@ κοντινό Wifi
char* password = "200820082008";
int Led5,Led6,Led7,Led8,Led9,Led10,Led11,Led12,Led13 = 0; //@@@ τα κλειστα φωτα με το ξεκινημα
int Led1,Led2,Led3,Led4=1;//@@@ τα ανοιχτα φωτα με το ξεκινημα.
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
 String t_state = server.arg("LEDstate"); //@@@ Εδώ δέχεται εντολές από το 1ο ταμπ(φώτα) και κάνει κάτι για κάθε εντολή. στέλνει 2 χαρακτήρες στο nano για καθε μια από την κατάσταση του κάθε λεντ(ανοιχτο κλειστό)  @@@
  //Εδώ για κάθε κατάσταση βάλε το δικό σου @@@. υπόψει τα 1 ,2 ,3... αφορουν 2 διαφορετικες καταστάσεις του ιδιου λεντ, αρα για 16 relays θα χρειαστεί 32 χαρακτήρες. εδω εχω 26 για 13 φωτα δλδ 13 πινακια
if(t_state == "1")//Εδώ πήρε 1, το λεντ 1 ανοιξε  @@@
 {  SUART.println('1');
 Led1=1;
 ledState = "ON";
 }  else if(t_state == "0")///Εδώ πήρε 0, το λεντ 1 εκλεισε  @@@
 {   SUART.println('2');   
Led1=0;
ledState = "OFF";
 } else if(t_state == "2")//Εδώ πήρε 2, το λεντ 2 εκλεισε  @@@
 {   SUART.println('3');    
Led2=0;ledState = "OFF";
 } else if(t_state == "3")//Εδώ πήρε 3, το λεντ 2 ανοιξε  @@@
 {    SUART.println('4');   
Led2=1; ledState = "ON";
 } else if(t_state == "4")//Εδώ πήρε 4, το λεντ 3 έκλεισε  @@@
 {   SUART.println('5');   
Led3=0;ledState = "OFF";
 } else if(t_state == "5")//Εδώ πήρε 4, το λεντ 3 ανοιξε  @@@
 {   SUART.println('6');  
Led3=1; ledState = "ON";
 } else if(t_state == "6")
 { SUART.println('7');   
Led4=0;ledState = "OFF";
 } else if(t_state == "7")
 {    SUART.println('8');   
Led4=1;ledState = "ON";
 } else if(t_state == "8")
 {   SUART.println('9');   
Led5=0;ledState = "OFF";
 } else if(t_state == "9")
 {   SUART.println('a'); 
Led5=1;ledState = "ON";
 } else if(t_state == "10")
 {  SUART.println('b');   
Led6=0;ledState = "OFF";
 } else if(t_state == "11")
 {    SUART.println('c');  
Led6=1;ledState = "ON";
 } else if(t_state == "12")
 {   SUART.println('d');    
Led7=0;ledState = "OFF";
 } else if(t_state == "13")
 {  SUART.println('e');    
Led7=1;ledState = "ON";
 } else if(t_state == "14")
 {   SUART.println('f');    
Led8=0;ledState = "OFF";
 } else if(t_state == "15")
 {    SUART.println('g'); 
Led8=1;ledState = "ON";
 }else if(t_state == "16")
 {  SUART.println('h');    
Led9=0;ledState = "OFF";
 }else if(t_state == "17")
 {    SUART.println('i');    
Led9=1;ledState = "ON";
 }else if(t_state == "18")
 {  SUART.println('g');   
Led10=0;ledState = "OFF";
 }else if(t_state == "19")
 {    SUART.println('k');   
Led10=1;ledState = "ON";
 }else if(t_state == "20")
 {   SUART.println('l');   
Led11=0;ledState = "OFF";
 }else if(t_state == "21")
 {    SUART.println('m'); ;   
Led11=1;ledState = "ON";
 }else if(t_state == "22")
 {  //SUART.println('n');    
Led12=0;ledState = "OFF";
 }else if(t_state == "23")
 {   //SUART.println('o');    
Led12=1;ledState = "ON";
 }else if(t_state == "24")
 {  //SUART.println('p');    
Led13=0;ledState = "OFF";
 }else if(t_state == "25")
 {    //SUART.println('q');    
Led13=1;ledState = "ON";
 }
 
server.send(200, "text/plane", ledState); //Send web page
}

void setup() {

  dht.begin();
SUART.begin(115200);
  SPIFFS.begin();
  pinMode(pin_led, OUTPUT);
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
   server.on("/giveUpOrder", giveUpOrder);
   server.on("/giveDownOrder", giveDownOrder);
   server.on("/givePauseOrder", givePauseOrder);
  server.begin();
  SUART.println('.'); 

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle();server.handleClient();
  }void serveIndexFile()
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
void checkState(){//τρεχει συνεχεια και ενημερώνει όποιον μπαίνει για τη κατάσταση των λεντ@@@
  
   String t_state = server.arg("LED");
  
   if(t_state=="1"){ 
   if(Led1==0){
    server.send(200, "text/plane","off");
  }else if(Led1==1){
    server.send(200, "text/plane","on");
  }}
  else if(t_state=="2"){
   if(Led2==0){
    server.send(200, "text/plane","off");
  }else if(Led2==1){
    server.send(200, "text/plane","on");
  }}
  else if(t_state=="3"){
   if(Led3==0){
    server.send(200, "text/plane","off");
  }else if(Led3==1){
    server.send(200, "text/plane","on");
  }}
  else if(t_state=="4"){
   if(Led4==0){
    server.send(200, "text/plane","off");
  }else if(Led4==1){
    server.send(200, "text/plane","on");
  }}
 else if(t_state=="5"){
   if(Led5==0){
    server.send(200, "text/plane","off");
  }else if(Led5==1){
    server.send(200, "text/plane","on");
  }}
 else if(t_state=="6"){;
   if(Led6==0){
    server.send(200, "text/plane","off");
  }else if(Led6==1){
    server.send(200, "text/plane","on");
  }}
 else if(t_state=="7"){
   if(Led7==0){
    server.send(200, "text/plane","off");
  }else if(Led7==1){
    server.send(200, "text/plane","on");
  }}
 else if(t_state=="8"){
   if(Led8==0){
    server.send(200, "text/plane","off");
  }else if(Led8==1){
    server.send(200, "text/plane","on");
  }}
 else if(t_state=="9"){
   if(Led9==0){
    server.send(200, "text/plane","off");
  }else if(Led9==1){
    server.send(200, "text/plane","on");
  }}
  else if(t_state=="10"){
   if(Led10==0){
    server.send(200, "text/plane","off");
  }else if(Led10==1){
    server.send(200, "text/plane","on");
  }}else if(t_state=="11"){
   if(Led11==0){
    server.send(200, "text/plane","off");
  }else if(Led11==1){
    server.send(200, "text/plane","on");
  }}else if(t_state=="12"){
   if(Led12==0){
    server.send(200, "text/plane","off");
  }else if(Led12==1){
    server.send(200, "text/plane","on");
  }}else if(t_state=="13"){
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
    void allOn2()//@@@εδώ υλοποιείται το κουμί all Up για τα ρελε
{
  
  Relay1=1;
  Relay2=1;
  Relay3=1;
  Relay4=1;
  Relay5=1;
  Relay6=1;
  
  
}
void allOff2()//@@@εδώ υλοποιείται το κουμί all Down για τα ρελε
{
  Relay1=0;
  Relay2=0;
  Relay3=0;
  Relay4=0;
  Relay5=0;
  Relay6=0;
  
  
   
  
 
  
}
void checkState2(){
  
   String t_state = server.arg("Relay");
   Serial.println(t_state); 
   if(t_state=="1"){ 
   if(Relay1==0){
    server.send(200, "text/plane","off");
  }else if(Relay1==1){
    server.send(200, "text/plane","on");
  }}
  else if(t_state=="2"){
   if(Relay2==0){
    server.send(200, "text/plane","off");
  }else if(Relay2==1){
    server.send(200, "text/plane","on");
  }}
  else if(t_state=="3"){
   if(Relay3==0){
    server.send(200, "text/plane","off");
  }else if(Relay3==1){
    server.send(200, "text/plane","on");
  }}
  else if(t_state=="4"){
   if(Relay4==0){
    server.send(200, "text/plane","off");
  }else if(Relay4==1){
    server.send(200, "text/plane","on");
  }}
 else if(t_state=="5"){
   if(Relay5==0){
    server.send(200, "text/plane","off");
  }else if(Relay5==1){
    server.send(200, "text/plane","on");
  }}
 else if(t_state=="6"){
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
void giveUpOrder(){// ο χρήστης στέλνει απο 0 εως 5 για να σηκώσει. για κάθε φάση εδώ βάλε ότι θες@@@
  String t_state = server.arg("Relay");
  if(t_state=="0"){
     Serial.println("opening 1...");
     SUART.println('r');
  }else if(t_state=="1"){
     Serial.println("opening 2...");SUART.println('s');
  }else if(t_state=="2"){
     Serial.println("opening 3...");SUART.println('t');
  }else if(t_state=="3"){
     Serial.println("opening 4...");SUART.println('u');
  }else if(t_state=="4"){
     Serial.println("opening 5...");SUART.println('v');
  }else if(t_state=="5"){
     Serial.println("opening 6...");SUART.println('w');
  }
  }
  void giveDownOrder(){// ο χρήστης στέλνει απο 0 εως 5 για να κατεβάσει. για κάθε φάση εδώ βάλε ότι θες@@@
  String t_state = server.arg("Relay");
  if(t_state=="0"){
     Serial.println("closing 1...");SUART.println('x');
  }else if(t_state=="1"){
     Serial.println("closing 2...");SUART.println('y');
  }else if(t_state=="2"){
     Serial.println("closing 3...");SUART.println('z');
  }else if(t_state=="3"){
     Serial.println("closing 4...");SUART.println('!');
  }else if(t_state=="4"){
     Serial.println("closing 5...");SUART.println('@');
  }else if(t_state=="5"){
     Serial.println("closing 6...");SUART.println('#');
  }
  }
  void givePauseOrder(){// ο χρήστης στέλνει απο 0 εως 5 για να σταματήσει. για κάθε φάση εδώ βάλε ότι θες@@@
  String t_state = server.arg("Relay");
  if(t_state=="0"){
     Serial.println("pausing 1...");SUART.println('$');
  }else if(t_state=="1"){
     Serial.println("pausing 2...");SUART.println('%');
  }else if(t_state=="2"){
     Serial.println("pausing 3...");SUART.println('^');
  }else if(t_state=="3"){
     Serial.println("pausing 4...");SUART.println('&');
  }else if(t_state=="4"){
     Serial.println("pausing 5...");SUART.println('*');
  }else if(t_state=="5"){
     Serial.println("pausing 6...");SUART.println('(');
  }
  
  
  }
