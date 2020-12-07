#include<SoftwareSerial.h>
SoftwareSerial SUART(2, 3); //SRX=Dpin-2; STX-DPin-3
//-------------------------
#include <SimpleDHT.h>
int pinDHT11 = 4;  //Humidity DATA line at A0-pin of UNO
SimpleDHT11 dht11;  //object is created from class
byte temperature = 0;
byte humidity = 0;
//--------------------------------------------

void setup()
{
  Serial.begin(115200); //enable Serial Monitor
  SUART.begin(115200); //enable SUART Port

}

void loop()
{
  //---acquire Temp and Humidity signal and save in variables
 for(int i=0;i<=10;i++){delay(1000);
   SUART.println(i);}
 

  
}
