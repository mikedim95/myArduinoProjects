#include<SoftwareSerial.h>
SoftwareSerial SUART(2, 3); //SRX=Dpin-D2; STX-DPin-D1
//-------------------------

//--------------------------------------------

void setup()
{
  Serial.begin(115200); //enable Serial Monitor
  SUART.begin(115200); //enable SUART Port

}

void loop()
{
  byte n = SUART.available(); //n != 0 means a character has arrived
  if (n != 0)
  {
    char x = SUART.read();
    
    switch (x){
    case '1':Serial.println("Led1 ON"); 
     break;
     case '2':Serial.println("Led1 OFF"); 
     break;
    case '3':Serial.println("Led2 OFF"); 
     break;
     case '4':Serial.println("Led2 ON"); 
     break;
     case '5':Serial.println("Led3 OFF"); 
     break;
     case '6':Serial.println("Led3 ON"); 
     break;
     case '7':Serial.println("Led4 OFF"); 
     break;
     case '8':Serial.println("Led4 ON"); 
     break;
     case '9':Serial.println("Led5 OFF"); 
     break;
     case 'a':Serial.println("Led5 ON"); 
     break;
     case 'b':Serial.println("Led6 OFF"); 
     break;
     case 'c':Serial.println("Led6 ON"); 
     break;
     case 'd':Serial.println("Led7 OFF"); 
     break;
     case 'e':Serial.println("Led7 ON"); 
     break;
     case 'f':Serial.println("Led8 OFF"); 
     break;
     case 'g':Serial.println("Led8 ON"); 
     break;
     case '.':Serial.println("ALIVE"); 
     break;
     case 'r':Serial.println("opening 1...");
     break;
     case 's':Serial.println("opening 2...");
     break;
     case 't':Serial.println("opening 3...");
     break;
     case 'u':Serial.println("opening 4...");
     break;
     case 'v':Serial.println("opening 5...");
     break;
     case 'w':Serial.println("opening 6...");
     break;
     case 'x':Serial.println("closing 1...");
     break;
     case 'y':Serial.println("closing 2...");
     break;
     case 'z':Serial.println("closing 3...");
     break;
     case '!':Serial.println("closing 4...");
     break;
     case '@':Serial.println("closing 5...");
     break;
     case '#':Serial.println("closing 6...");
     break;
     case '$':Serial.println("pausing 1...");
     break;
     case '%':Serial.println("pausing 2...");
     break;
     case '^':Serial.println("pausing 3...");
     break;
     case '&':Serial.println("pausing 4...") ;
     break;
     case '*':Serial.println("pausing 5...");
     break;
     case '(':Serial.println("pausing 6...");
     break;
  
  
    }
  }
}
