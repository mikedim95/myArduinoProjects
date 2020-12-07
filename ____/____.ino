#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {50, 49, 48, 47}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {46, 45, 44}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
String code = "123";
int theDay,key,i,effort[3];

boolean proceed = false;

void setup(){
  Serial.begin(9600);
  Serial.println("give the Day of the chicks ;) and press '#' or '*' to reset the input");
  key = keypad.waitForKey();
  i=0;
  effort[i] =  key;
  Serial.print(key);
  key = keypad.waitForKey();
  while(key != "*" && key != "#"){
        i+=1;
        effort[i] =  key;
        key = keypad.waitForKey();
        }
    
 
     
     if(key == "*"){
        effort[0]=0;
        effort[1]=0;
        effort[2]=0;

      
    }else{// key = #
   
    int x = (sizeof(effort) / sizeof(effort[0]));
    for(i=0;i<x;i++){
    theDay += effort[i]*10^(x-i-1);
    }
    Serial.print("theDay is: ");
    Serial.println(theDay);
     

   
    }
    
    
}

void loop(){
  
  
 
}

    
      
       
  
  
  

 
