#include<SoftwareSerial.h>

//-------------------------

//--------------------------------------------

void setup(){
  Serial.begin(115200); //enable Serial Monitor
 
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
  byte n = Serial.available(); //n != 0 means a character has arrived
  if (n != 0){
    char x = Serial.read();
    switch (x){
    
    
     case 'e':Serial.println("relay power 1 up"); digitalWrite(2,HIGH);digitalWrite(3,LOW);
      break;
     case 'f':Serial.println("relay power 2 up"); digitalWrite(4,HIGH);digitalWrite(5,LOW);
      break;
     case 'g':Serial.println("relay power 3 up"); digitalWrite(6,HIGH);digitalWrite(7,LOW);
      break;
     case 'h':Serial.println("relay power 4 up"); digitalWrite(8,HIGH);digitalWrite(9,LOW);
      break;
     case 'i':Serial.println("relay power 5 up"); digitalWrite(10,HIGH);digitalWrite(11,LOW);
      break;
     case 'j':Serial.println("relay power 6 up"); digitalWrite(12,HIGH);digitalWrite(13,LOW);
      break;
     case 'k':Serial.println("relay power 1 down"); digitalWrite(2,HIGH);digitalWrite(3,HIGH);
      break;
     case 'l':Serial.println("relay power 2 down"); digitalWrite(4,HIGH);digitalWrite(5,HIGH);
      break;
     case 'm':Serial.println("relay power 3 down"); digitalWrite(6,HIGH);digitalWrite(7,HIGH);
      break;
     case 'n':Serial.println("relay power 4 down"); digitalWrite(8,HIGH);digitalWrite(9,HIGH);
      break;
     case 'o':Serial.println("relay power 5 down"); digitalWrite(10,HIGH);digitalWrite(11,HIGH);
      break;
     case 'p':Serial.println("relay power 6 down"); digitalWrite(12,HIGH);digitalWrite(13,HIGH);
      break;
     case 'q':Serial.println("relay power 1 off"); digitalWrite(2,LOW);
      break;
     case 'r':Serial.println("relay power 2 off"); digitalWrite(4,LOW);
      break;
     case 's':Serial.println("relay power 3 off"); digitalWrite(6,LOW);
      break;
     case 't':Serial.println("relay power 4 off"); digitalWrite(8,LOW);
      break;
     case 'u':Serial.println("relay power 5 off"); digitalWrite(10,LOW);
      break;
     case 'v':Serial.println("relay power 6 off"); digitalWrite(12,LOW);
      break;
     case '.':Serial.println("ALIVE"); 
      break;
    
    }
  }
}
