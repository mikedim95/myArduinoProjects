#include <HX711_ADC.h> 
#include <Wire.h>
#include <LCD.h> 
#include <LiquidCrystal_I2C.h>
#include <SD.h>
#include <SPI.h>
#include <Keypad.h>
#include <DS3231_Simple.h>
File dataFile;
int totalweight,savedDay,savedMonth,savedYear,savedHour,savedMinute,countTimes,countWeight;
String before,middle,after;
String savedTime;
char x;
int magikNumber, savedMagikNumber,key,i,effort[3];
 DateTime MyDateAndTime;
float date_max[] = {44,53,65,79,97,119,155,172,202,236,273,312,355,399,447,497,548,602,660,718,778,842,908,978,1050,1123,1199,1276,1354,1434,1514,1597,1679,1763,1848,1933,2019,2105,2192,2280,2368,2454,2541,2628,2715,2802,2887,2973,3058,3143};
float date_min[] = {40,50,61,75,92,112,136,162,191,223,258,295,335,377,422,469,518,569,623,678,735,795,858,924,992,1061,1132,1205,1279,1354,1430,1508,1586,1665,1745,1826,1907,1988,2070,2153,2236,2318,2400,2482,2564,2646,2727,2808,2888,2968};
float calValue,instantMean; // calibration value
long stabilisingtime = 2000;  // tare preciscion can be improved by adding a few seconds of stabilising time

//-----------------------------------------------------this is for the keypad

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {22, 24, 26, 28}; 
byte colPins[COLS] = {31,33,35};  
Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//-----------------------------------------------------this is for the LoadingCell

HX711_ADC LoadCell(4, 5); //Load Cell

//-----------------------------------------------------this is for the LCD

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //LCD

//-----------------------------------------------------this is for RTC

DS3231_Simple Clock;

//-----------------------------------------------------this is for SD


void setup() {
  Serial.begin(9600); delay(10);
  Serial.println();
  Serial.println("Starting...");
  //-----------------------------------------------------this is for RTC

 Clock.begin();
 
  //-----------------------------------------------------this is for the LCD
  
  lcd.begin(20, 4);
  lcd.noBacklight();// begins connection to the LCD module
  lcd.backlight(); // turns on the backlight 
  
  //-----------------------------------------------------this is for the LoadingCell

  //Setup Code here for LoadingCell

   //-----------------------------------------------------this is for SD
   
if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  SD.remove("Results.txt");
  
  //------------------------------------------------------ In this segment, initialise the system. this code is until * or #
  
  lcd.print("What day?");
  lcd.setCursor(0,1);
  i=-1;
  key = keypad.waitForKey();
  while(key != 42 && key != 35){
    i+=1;   
    adding(key,i);
    key = keypad.waitForKey();
  }
  if(key == 42){
    SD.remove("abc.txt");
    for(int j=0;j<=i;j++){
      magikNumber += round(effort[j]*pow(10,i-j)); 
    }
    lcd.setCursor(0,2);
    lcd.print("Day ");
    lcd.print(magikNumber);
    lcd.print(" Confirmed ");
    MyDateAndTime = Clock.read();
    savedDay =MyDateAndTime.Day;
    savedHour =MyDateAndTime.Hour;
    dataFile = SD.open("abc.txt", FILE_WRITE);
    delay(500);
     lcd.setCursor(0,3);
     lcd.print("Saving...");
     
    if (dataFile) {
      Serial.println("Writing to test.txt...");
      dataFile.print(savedDay);
      dataFile.print(":");
      dataFile.print(savedHour);
      dataFile.print("@");
       dataFile.print(magikNumber);
      Serial.print(savedDay);
      Serial.print(":");
      Serial.print(savedHour);
       Serial.print("@");
        Serial.println(magikNumber);
      dataFile.close();
    }
    

  }else{lcd.clear();
        lcd.home();
        lcd.print("Parsing memory data...");
        lcd.setCursor(0,1);
    if(SD.exists("abc.txt")){
      dataFile = SD.open("abc.txt");
      if (dataFile){
        while(dataFile.available()) {
        x=dataFile.read();
        savedTime+=String(x);
      }
      Serial.println(savedTime);
      int index1 = savedTime.indexOf(':');
      int index2 = savedTime.indexOf('@');
      before = savedTime.substring(0, index1);
      middle = savedTime.substring(index1 + 1,index2);
      after = savedTime.substring(index2+1);
      savedDay = before.toInt();
      savedHour=middle.toInt();
      magikNumber=after.toInt();
      lcd.print("Date: ");
      lcd.print(savedDay);
       lcd.setCursor(0,2);
       lcd.print("Hour: ");
      lcd.print(savedHour);
      lcd.setCursor(0,3);
      lcd.print("Chick days: ");
      lcd.print(magikNumber);
      lcd.setCursor(0,4);
      delay(5000);
      dataFile.close();
      }else {
        lcd.print("error opening test.txt");
      }
    }else{
      Serial.println("No saved time");
    }
  }lcd.clear();
  Serial.print("leaving with Date: ");
  Serial.print(savedDay);
  Serial.print(" Hour: ");
  Serial.print(savedHour);
  Serial.print(" and magiknumber: ");
  Serial.println(magikNumber);
}
  //-----------------------------------------------------------------------------------------
  
void loop() {
  
  MyDateAndTime = Clock.read();
  int a = MyDateAndTime.Day;
  int b = MyDateAndTime.Month;
  int c = MyDateAndTime.Year;
  int d = MyDateAndTime.Hour;
  int e = MyDateAndTime.Minute;
  if(savedDay!= a && savedHour<d ){                               //if i find a day has passed, i update my magikNumber
    magikNumber += 1;
    savedDay +=1;
    SD.remove("abc.txt");
    dataFile = SD.open("abc.txt", FILE_WRITE);
    if(dataFile){
      Serial.println("Writing to test.txt...");
      dataFile.print(savedDay);
      dataFile.print(":");
      dataFile.print(savedHour);
      dataFile.print("@");
      dataFile.print(magikNumber); 
      dataFile.close();
    }
    instantMean = countWeight/countTimes;
    dataFile = SD.open("Results.txt", FILE_WRITE);
    if(dataFile){
      
      dataFile.print("------------instant mean until now is: ");
      dataFile.print(instantMean);
      dataFile.print(" ------------");
      dataFile.close();
    }
    instantMean = 0;
  }
                                     totalweight=55;             //Update your weight HERE!
  int i = 1;
  float last;
  float x=totalweight/i;
  
  if(totalweight<=date_min[magikNumber-1]){
     lcd.home();
  lcd.print("Weight:");
  lcd.print(totalweight);
  lcd.print(" Day:");
  lcd.print(magikNumber);
  lcd.setCursor(0,1);
  lcd.print("We have ");
  lcd.print("0");
  lcd.print(" chicks");
  lcd.setCursor(0,2);
  lcd.print("Avrg weight:");
  lcd.print("0");
  dataFile = SD.open("Results.txt", FILE_WRITE);                                                 //logging the data... they also are available on serial
  if (dataFile) {
    Serial.print("on day ");
    Serial.print(magikNumber);
    Serial.print(" i found ");
    Serial.print("0");
    Serial.print(" chicks, with total weight ");
    Serial.print(totalweight);
    Serial.print(" and average: ");
    Serial.print("0");
    Serial.print("Date:");
    Serial.print(a);
    Serial.print("/");
    Serial.print(b);
    Serial.print("/");
    Serial.print(c);
    Serial.print(" Time: ");
    Serial.print(d);
    Serial.print(":");
    Serial.println(e);
    dataFile.print("on day ");
    dataFile.print(magikNumber);
    dataFile.print(" i found ");
    dataFile.print("0");
    dataFile.print(" chicks, with total weight ");
    dataFile.print(totalweight);
    dataFile.print(" and average: ");
    dataFile.print("0");
    dataFile.print("Date:");
    dataFile.print(a);
    dataFile.print("/");
    dataFile.print(b);
    dataFile.print("/");
    dataFile.print(c);
    dataFile.print(" Time: ");
    dataFile.print(d);
    dataFile.print(":");
    dataFile.println(e);
    dataFile.close();
  }else{
    Serial.println("error opening test.txt");
  
  }
    }else{
  
  
  while(date_max[magikNumber-1]<x){                               //try to find the number of chicks here
    i+=1;
    last = x;
    x=totalweight/i;
  }
  if(abs((date_min[magikNumber-1]+ date_max[magikNumber-1])/2-last)<abs((date_min[magikNumber-1]+ date_max[magikNumber-1])/2-x  )){   //try to find if my guess is good enough, or it must be the previous one
    Serial.print("old guess: ");
    Serial.println(abs((date_min[magikNumber-1]+ date_max[magikNumber-1])/2-last));               //Here i show by how much my gusses missed my target average (min+max)/2
    Serial.print("new guess: ");
    Serial.println(abs((date_min[magikNumber-1]+ date_max[magikNumber-1])/2-x  ));
    i-=1;                                                                                         //so the chicks must be one less
    }
  lcd.home();
  lcd.print("Weight:");
  lcd.print(totalweight);
  lcd.print(" Day:");
  lcd.print(magikNumber);
  lcd.setCursor(0,1);
  lcd.print("We have ");
  lcd.print(i);
  lcd.print(" chicks");
  lcd.setCursor(0,2);
  lcd.print("Avrg weight:");
  lcd.print(totalweight/i);
  dataFile = SD.open("Results.txt", FILE_WRITE);                                                 //logging the data... they also are available on serial
  if (dataFile) {
    Serial.print("on day ");
    Serial.print(magikNumber);
    Serial.print(" i found ");
    Serial.print(i);
    Serial.print(" chicks, with total weight ");
    Serial.print(totalweight);
    Serial.print(" and average: ");
    Serial.print(totalweight/i);
    Serial.print("Date:");
    Serial.print(a);
    Serial.print("/");
    Serial.print(b);
    Serial.print("/");
    Serial.print(c);
    Serial.print(" Time: ");
    Serial.print(d);
    Serial.print(":");
    Serial.println(e);
    dataFile.print("on day ");
    dataFile.print(magikNumber);
    dataFile.print(" i found ");
    dataFile.print(i);
    dataFile.print(" chicks, with total weight ");
    dataFile.print(totalweight);
    dataFile.print(" and average: ");
    dataFile.print(totalweight/i);
    dataFile.print("Date:");
    dataFile.print(a);
    dataFile.print("/");
    dataFile.print(b);
    dataFile.print("/");
    dataFile.print(c);
    dataFile.print(" Time: ");
    dataFile.print(d);
    dataFile.print(":");
    dataFile.println(e);
    dataFile.close();
  }else{
    Serial.println("error opening test.txt");
  
  }
  }
  delay(10000); 
  lcd.clear();
}
void adding(int x, int i){                                     //function that helps getting data from keypad (fkin pain in tha ass)
  if(x==49){
    effort[i]=1;
    lcd.print(effort[i]);
  }else if(x==50){
    effort[i]=2;
    lcd.print(effort[i]);
  }else if(x==51){
    effort[i]=3;
    lcd.print(effort[i]);
  }else if(x==52){
    effort[i]=4;
    lcd.print(effort[i]);
  }else if(x==53){
    effort[i]=5;
    lcd.print(effort[i]);
  }else if(x==54){
    effort[i]=6;
    lcd.print(effort[i]);
  }else if(x==55){
    effort[i]=7;
    lcd.print(effort[i]);
  }else if(x==56){
    effort[i]=8;
    lcd.print(effort[i]);
  }else if(x==57){
    effort[i]=9;
    lcd.print(effort[i]);
  }else if(x==48){
    effort[i]=0;
    lcd.print(effort[i]);
  }
}
