// ATtiny85 IR serial transceiver, using YS-IRTM encoder/decoder at each end.
#include <SoftwareSerial.h>
SoftwareSerial mySerial(4,3);  //rxPin, txPin
const int led1 = 0; 
const int led2 = 1;
int analogPin =  A1;  // voltage divider input pin. 10k in series with 10k or 5k depending on button press

int val = 0;         // variable for saving button press analog value
 
byte incomingByte1 =0x00;
byte incomingByte2 =0x00;
byte incomingByte3  =0x00;
byte incomingByte4  =0x00;
byte incomingByte5  =0x00;
// the setup routine runs once when you press reset:
void setup() {
  
// OSCCAL  = 83;    //use code at bottom as needed              
  mySerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
    
 
  
   
   mySerial.write(0xA1);   //0xA1 & 0xF1 are the standard prefix.
   mySerial.write(0xF1);
   mySerial.write(incomingByte5); //"A" group of three expected, so just duplicated the first letter
   mySerial.write(0x2F); //"A"
   mySerial.write(0x15); //"A"
  
   Serial.print("i have response: ");
   Serial.println(mySerial.available());
   Serial.print("which is: ");
   incomingByte4 = mySerial.read();
   Serial.println(incomingByte4,HEX);
 delay(2000);

  

}















































































/*#include <SoftwareSerial.h>

SoftwareSerial mySerial(4,3);  //rxPin, txPin
const int led1 = 0; 
const int led2 = 1;
int analogPin =  A1;  // voltage divider input pin. 10k in series with 10k or 5k depending on button press

int val = 0;         // variable for saving button press analog value
int incomingByte = 0;
// the setup routine runs once when you press reset:
void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
// OSCCAL  = 83;    //use code at bottom as needed              
  mySerial.begin(9600);
  
}

void loop() {
   
if (mySerial.available() > 0) {
            // read the incoming byte:
   incomingByte = mySerial.read();
   
  }
if (incomingByte=='A'){
  digitalWrite(led1, HIGH); // led1 and led2 change color of one 2 pin red/green led
  digitalWrite(led2, LOW);
  delay(200);         // echo the command back
  mySerial.write(0xA1);   //0xA1 & 0xF1 are the standard prefix.
  mySerial.write(0xF1);
  mySerial.write(0x41); //"A" group of three expected, so just duplicated the first letter
  mySerial.write(0x41); //"A"
  mySerial.write(0x41); //"A"
 }
if (incomingByte=='B'){
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  delay(200);  // echo the command back
  mySerial.write(0xA1);
  mySerial.write(0xF1);
  mySerial.write(0x42); //"B"
  mySerial.write(0x42); //"B"
  mySerial.write(0x42); //"B"
 }
    
val = analogRead(analogPin); 
  if((val > 200) && (val < 400)){
  mySerial.write(0xA1);   //0xA1 & 0xF1 are the standard prefix.
  mySerial.write(0xF1);
  mySerial.write(0x41); //"A" group of three expected, so just duplicated the first letter
  mySerial.write(0x41); //"A"
  mySerial.write(0x41); //"A"
  }
  if((val > 401) && (val < 600)){  
  mySerial.write(0xA1);
  mySerial.write(0xF1);
  mySerial.write(0x42); //"B"
  mySerial.write(0x42); //"B"
  mySerial.write(0x42); //"B"
  }
  
}

OSCCAL calibration:

void setup()
{
 delay(2000);
 Serial.begin(9600);   // Or even 115200...
 for (int i=0; i<256; ++i) {
   OSCCAL  = i;
   delay(1);
   Serial.println();
   serial.print("This was printed with OSCCAL=");
   serial.print(i);
 }
}
void loop()
{
}
*/
