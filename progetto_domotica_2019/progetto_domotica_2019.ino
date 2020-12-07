/*
               Progetto domotica 2019  
*/

#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

#include <DHT.h>
#define DHT1TYPE   DHT11       // DHT type (DHT11, DHT22)
//#define DHT2TYPE   DHT11       // DHT type (DHT11, DHT22)
//#define DHT3TYPE   DHT11       // DHT type (DHT11, DHT22)
//#define DHT4TYPE   DHT11       // DHT type (DHT11, DHT22)
#define DHT1PIN    A0          // Broche du DHT / DHT Pin
//#define DHT2PIN    A1          // Broche du DHT / DHT Pin
//#define DHT3PIN    A2          // Broche du DHT / DHT Pin
//#define DHT4PIN    A3          // Broche du DHT / DHT Pin
DHT dht1(DHT1PIN, DHT1TYPE);
//DHT dht2(DHT2PIN, DHT2TYPE);
//DHT dht3(DHT3PIN, DHT3TYPE);
//DHT dht4(DHT4PIN, DHT4TYPE);


/*lm35
#define sensorPin 0 
int sensorValue = 0; 
float celsius = 0;
*/

// array per la gestione dello stato dei pin
int dac[] = { 0, 0, 0, 2000, 0, 20, 27};
int DigitalPin[] = {2, 3, 4, 7, 8, 9, 10, 11, 12, 13};   
int DacPin[] = {5, 6};  
int tempmin, tempmax;
// Instanzia oggetto server
YunServer server;

void setup() {

///*  
dht1.begin();

//*/
  // Pin di ingresso
  //2 pinMode(2,INPUT);  
  pinMode(4,INPUT);  
  pinMode(7,INPUT);  
  // Pin uscite rele'
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
    
  Bridge.begin();
  
  delay(1000);
  // Attiva il socket per l'ascolto dei messaggi REST
  // sulla porta 5555, solo da localhost
  server.listenOnLocalhost();
  server.begin();
}

void loop() {
  
 


  
  // Lo scketch si mette in attesa di messaggi entranti
  // attivando un client verso Yunserver
  YunClient client = server.accept();
  // Se c'è in arrivo un nuovo messaggio si richiama la funzione process() per gestirlo.
  // alla fine si chiude il client
  if (client) {
    process(client);
    client.stop();
  }
  delay(50); //Pausa di 50 ms
}

void process(YunClient client) {
  // Legge il contenuto del comando REST fino alla prima "/"
  // A seconda della richiesta richiama la funzione corretta
  String command = client.readStringUntil('/');
  // comando "digital"
  if (command == "digital") {
    digitalCommand(client);
  }

  // comando "dac"
  if (command == "dac") {
    dacCommand(client);
  }
  // comando "stato"
  if (command == "stato") {
    statoCommand(client);
  }
}
// funzione  trattamento comando "digital"
void digitalCommand(YunClient client) {
  int pin, value;
  // Lettura numero pin
  pin = client.parseInt();
  // Se troviamo una seconda "/" significa che il comando
  // richiede un'azione come: "/digital/13/1"
  // Recuperiamo il valore da assegnare al pin
  if (client.read() == '/') {
    value = client.parseInt();
    digitalWrite(pin, value);
  } 
  else {
    value = digitalRead(pin);
  }
}
// funzione  trattamento comando "dac"
void dacCommand(YunClient client) {
  int pin, value;
  // Lettura numero pin
  pin = client.parseInt();
  // Se troviamo una seconda "/" significa che il comando
  // richiede un'azione come: "/dac/3/200"
  // Recuperiamo il valore da assegnare al pin
  // In caso di scrittura salviamo  il valore anche nell'array
  // In caso di lettura lo leggiamo dall'array
  if (client.read() == '/') {
    value = client.parseInt();
    dac[pin] = value;
    analogWrite(pin, value);
  } 
  else {
    value = dac[pin];
  }
}

// legge lo stato di tutti i pin e li 
// invia in un unico, lungo messaggio
void statoCommand(YunClient client) {
  int pin, value;
    client.print(F("stato"));
    // Lettura pin digitali, ingressi e rele'
    for (int thisPin = 0; thisPin < 10; thisPin++) {
        pin = DigitalPin[thisPin];
        value = digitalRead(pin);
        client.print(F("#"));
        client.print(pin);
        client.print(F("="));
        client.print(value);
        } 
    // Lettura pin dac dall'array        
    for (int thisPin = 0; thisPin < 2; thisPin++) {
        pin = DacPin[thisPin];
        value = dac[pin];
        if (pin==5)
        tempmin=value;
        if (pin==6)
        tempmax=value;
        client.print(F("#"));
        client.print(pin);
        client.print(F("="));
        client.print(value);
        } 

        
        // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

float h1 = dht1.readHumidity();
float t1 = dht1.readTemperature();
//float h2 = dht2.readHumidity();
//float t2 = dht2.readTemperature();
//float h3 = dht3.readHumidity();
//float t3 = dht3.readTemperature();
//float h4 = dht4.readHumidity();
//float t4 = dht4.readTemperature();
 




    // Lettura pin analogici        
    for (int thisPin = 0; thisPin < 6; thisPin++) {
      switch(thisPin){
        case 0:
        value = t1;
        break;
        case 1:
        value = h1;
        break;
        case 2 :
        //value = (dht3.readTemperature());
        break;
        case 3 :
        //value = (dht4.readTemperature());
        break;
        case 4 :
        value = t1;
        {
          if (value < tempmin)
          digitalWrite(9,HIGH);
          if (value > tempmax)
          digitalWrite(8,HIGH);
          if (value > tempmin && value < tempmax)
          {
            digitalWrite(8,LOW);
            digitalWrite(9,LOW);
          }
        } 
        break;
        case 5 :
        break;
        }
       client.print(F("#A"));
       client.print(thisPin);
       client.print(F("="));
       client.print(value);
    }     
    // Chiusura messaggio con fine linea      
    client.println("");
    delay (100);
}    
