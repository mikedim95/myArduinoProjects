#include<SoftwareSerial.h>
SoftwareSerial SUART(2, 3); //SRX=Dpin-D2; STX-DPin-D3
//-------------------------

//--------------------------------------------

void setup(){
  Serial.begin(115200); //enable Serial Monitor
  SUART.begin(115200); //enable SUART Port
  pinMode(1,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);

  digitalWrite(1,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
}

void loop(){
  byte n = SUART.available(); //n != 0 means a character has arrived
  if (n != 0){
    char x = SUART.read();
    switch (x){
     case '1':Serial.println("Led1,Led2,Led3 OFF"); digitalWrite(1,HIGH);
      break;
     case '2':Serial.println("Led1,Led2,Led3 ON"); digitalWrite(1,LOW);
      break;
     case '3':Serial.println("Led4 OFF"); digitalWrite(4,HIGH);
      break;
     case '4':Serial.println("Led4 ON"); digitalWrite(4,LOW);
      break;
     case '5':Serial.println("Led5 OFF"); digitalWrite(5,HIGH);
      break;
     case '6':Serial.println("Led5 ON"); digitalWrite(5,LOW);
      break;
     case '7':Serial.println("Led6 OFF"); digitalWrite(6,HIGH);
      break;
     case '8':Serial.println("Led6 ON"); digitalWrite(6,LOW);
      break;
     case '9':Serial.println("Led7 OFF"); digitalWrite(7,HIGH);
      break;
     case 'a':Serial.println("Led7 ON"); digitalWrite(7,LOW);
      break;
     case 'b':Serial.println("Led8 OFF"); digitalWrite(8,HIGH);
      break;
     case 'c':Serial.println("Led8 ON"); digitalWrite(8,LOW);
      break;
     case 'd':Serial.println("Led9 OFF"); digitalWrite(9,HIGH);
      break;
     case '%':Serial.println("Led9 ON"); digitalWrite(9,LOW);
      break;
     case 'f':Serial.println("Led10 OFF"); digitalWrite(10,HIGH);
      break;
     case 'g':Serial.println("Led10 ON"); digitalWrite(10,LOW);
      break;
     case 'h':Serial.println("Led11 OFF"); digitalWrite(11,HIGH);
      break;
     case '$':Serial.println("Led11 ON"); digitalWrite(11,LOW);
      break;
     case 'j':Serial.println("Led12 OFF"); digitalWrite(12,HIGH);
      break;
     case 'k':Serial.println("Led12 ON"); digitalWrite(12,LOW);
      break;
     case 'l':Serial.println("Led13 OFF"); digitalWrite(13,HIGH);
      break;
     case 'm':Serial.println("Led13 ON"); digitalWrite(13,LOW);
      break;
     case '.':Serial.println("ALIVE"); 
      break;
    
    }
  }
}
