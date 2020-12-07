#include <SPI.h>
#include <RFID.h>
#include <SD.h>
#include <DS3231_Simple.h>
//-----------------------------------------RFID
#define SS_PIN 10
#define RST_PIN 9
    RFID rfid(SS_PIN, RST_PIN); 
    int serNum0;
    int serNum1;
    int serNum2;
    int serNum3;
    int serNum4;
//------------------------------------------SD
    File myFile;
//------------------------------------------Clock
    DS3231_Simple Clock;
    DateTime MyDateAndTime;
    int Hour,Minutes;
   String DATE[6];
//-----------------------------------------wait()
    long interval = 100;
    long current_time=0;
//------------------------------------------Serial
   String inChar;
 //-----------------------------------------Battery
 float Volts;
 int Pin = A3;
 //-----------------------------------------buzzer
 int buzzer = 8;
//=======================================SETUP======================================================================================================================================
void setup(){ digitalWrite(2,HIGH);
  
  pinMode(A3,INPUT);
   pinMode(2,OUTPUT);
    pinMode(3,OUTPUT);digitalWrite(3,LOW);
  pinMode(8,OUTPUT);Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


 

  if (!SD.begin(4)) {
   
    
  }

  SPI.begin(); wait();
  rfid.init();wait();
  Clock.begin();wait();digitalWrite(2,LOW);
  notificationBegin();
}
void(* resetFunc) (void) = 0;
//=======================================loop=========================================================================================================================
void loop(){ 
    rfid.halt();
    while(!(rfid.isCard()&&rfid.readCardSerial())){ digitalWrite(3,HIGH);//-----------------------perimenw na adopisw karta
      if (Serial.available()) {
       notification2();digitalWrite(3,LOW);
        serialEvent();
      }
    }digitalWrite(3,LOW);
   notification();
    serNum0 = rfid.serNum[0];
    serNum1 = rfid.serNum[1];
    serNum2 = rfid.serNum[2];
    serNum3 = rfid.serNum[3];
    serNum4 = rfid.serNum[4];
   
    MyDateAndTime = Clock.read();//--------------diabazw tin wra
    writeToSD(MyDateAndTime.Hour, MyDateAndTime.Minute,serNum0,serNum1,serNum2,serNum3,serNum4);
    waitTillNextScan(); 
 //------------elenxos batarias
 if(checkBattery()){
//alarm();

  
 }
 
  //--------------------------------------------diaxeirisi input
  
}
//===============================================================================================================
//_______________________________WAIT__________________________________________________________________
void wait(){
 
  while(millis()-current_time < interval){
  
  }
  current_time = millis();
}
//____________________________writeToSD__________________________________________________________________
void writeToSD(int x, int y,int a,int b,int c,int d,int e){
myFile = SD.open("test.txt", FILE_WRITE);//--ta api8ikeuw stin SD
 
  if (myFile) {
  
    myFile.print( a);
    myFile.print( ":");
    myFile.print( b);
    myFile.print( ":");
    myFile.print( c);
    myFile.print( ":");
    myFile.print( d);
    myFile.print( ":");
    myFile.print( e);
    myFile.print( "#");
    myFile.print( x );
    myFile.print(":");
    myFile.print( y );
    myFile.println("@");
    myFile.close();
   
    }
}
void writeToSDConf(String x,int a,int b,int c,int d,int e){
    myFile = SD.open("test2.txt", FILE_WRITE);
    if (myFile) {
      myFile.print( a);
      myFile.print( ":");
      myFile.print( b);
      myFile.print( ":");
      myFile.print( c);
      myFile.print( ":");
      myFile.print( d);
      myFile.print( ":");
      myFile.print( e);
      myFile.print( "#");
      myFile.print(inChar);
      myFile.println("@");
      myFile.close();
    } 
    myFile = SD.open("test2.txt");
    if (myFile) {
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      myFile.close();
    }
    delay(1000);
}
void serialEvent(){ 
    inChar = Serial.readStringUntil('\n');
    if     (inChar == "1"){//Λήψη logging
      File myFile = SD.open("Test.txt");
      if (myFile) {
        while (myFile.available()) {
        Serial.write(myFile.read());
        }
      myFile.close();
      }
    }
    else if(inChar == "2"){//Διαγραφή Logging
    SD.remove("test.txt");
    if (SD.exists("test.txt")){
    Serial.print(2);}
    else{Serial.print(1);}
        }  
    else if(inChar == "3"){//Λήψη UID
      notification2();
      while(!(rfid.isCard()&&rfid.readCardSerial())){//-----------------------perimenw na adopisw karta
      }notification2();
      //-----------------diabazw tin karta pou molis edopisa
        serNum0 = rfid.serNum[0];
        serNum1 = rfid.serNum[1];
        serNum2 = rfid.serNum[2];
        serNum3 = rfid.serNum[3];
        serNum4 = rfid.serNum[4];
        Serial.print(serNum0);
        Serial.print(":");
        Serial.print(serNum1);
        Serial.print(":");
        Serial.print(serNum2);
        Serial.print(":");
        Serial.print(serNum3);
        Serial.print(":");
        Serial.print(serNum4);
        Serial.println("!");
      delay(1500);
    }
    else if(inChar == "4"){//Διαγραφή Αντιστοιχιών 
    SD.remove("test2.txt");
    }
    else if(inChar == "5"){//Λήψη Αντιστοιχιών
      File myFile = SD.open("Test2.txt");
      if (myFile) {
        while (myFile.available()) {
        Serial.write(myFile.read());
        }
      myFile.close();
      }
    }
    else if(inChar == "6"){//Προβολή Ώρας
      notification2();
      notification2();
      MyDateAndTime = Clock.read();
      
      Serial.print(MyDateAndTime.Day);   
      Serial.print("@");
      Serial.print(MyDateAndTime.Month);   
      Serial.print("@");
      Serial.print(MyDateAndTime.Year);   
      Serial.print("@");
      Serial.print(MyDateAndTime.Hour);   
      Serial.print("@");
      Serial.print(MyDateAndTime.Minute);   
      Serial.print("@");
    }
    else if(inChar == "7"){//Ρύθμιση ώρας
      DateTime MyTimestamp;
       
      delay(2000);
      int i=0;
      while (Serial.available()){
      
      
        DATE[i]= Serial.readStringUntil('\n');
        
        i++;
        }
        
  MyTimestamp.Day    = DATE[0].toInt();
  MyTimestamp.Month  = DATE[1].toInt();
  MyTimestamp.Year   = DATE[2].toInt();
  MyTimestamp.Hour   = DATE[3].toInt();
  MyTimestamp.Minute = DATE[4].toInt();
  
  
  // Then write it to the clock
  Clock.write(MyTimestamp);
    }
    else if(inChar == "8"){//επαναρύθμιση αντιτοιχιών
     SD.remove("Test2.txt");
      File myFile = SD.open("Test2.txt",FILE_WRITE);
      while (!Serial.available()){
      
     
      }  
      String x = Serial.readString();
     
      myFile.print(x);
      myFile.close();
    }
    else if(inChar == "9"){//test
       resetFunc();
    }
   
}
bool checkBattery(){
  int sensor = A3;
double volts = map(analogRead(sensor),0,1023,0.0,5.0);
if(volts<=2.9){
  return true;
}
}
void alarm(){
   tone(buzzer, 1000);
   digitalWrite(3,HIGH); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);
  digitalWrite(3,LOW);// Stop sound...
  delay(1000);  
  
}
void notification(){
  digitalWrite(3,HIGH);
  tone(buzzer,1000);
  delay(200);
  noTone(buzzer);
  
  digitalWrite(3,LOW);
}

    void notification2(){
  digitalWrite(2,HIGH);
  tone(buzzer,100);
  delay(50);
  noTone(buzzer);
  
  digitalWrite(2,LOW);
}
void notificationBegin(){
  
 
  tone(buzzer,800);digitalWrite(2,HIGH); digitalWrite(3,HIGH);
  delay(50);
  noTone(buzzer); digitalWrite(2,LOW); digitalWrite(3,LOW);
  delay(50);
   tone(buzzer,1100);digitalWrite(2,HIGH); digitalWrite(3,HIGH);
  delay(50);
  noTone(buzzer); digitalWrite(2,LOW); digitalWrite(3,LOW);
   delay(50);
   tone(buzzer,1400);digitalWrite(2,HIGH); digitalWrite(3,HIGH);
  delay(50);
   noTone(buzzer); digitalWrite(2,LOW); digitalWrite(3,LOW);
 
}
void notification3(){
  digitalWrite(2,HIGH);
  tone(buzzer,300);
  delay(50);
  noTone(buzzer);
  
  digitalWrite(2,LOW);
}
 void waitTillNextScan(){
  for(int i=0;i<=4;i++){
  digitalWrite(2,HIGH);
  delay(300);
   digitalWrite(2,LOW);
  delay(300);
  }
  
  }
