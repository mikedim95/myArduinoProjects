void setup() {
  // put your setup code here, to run once:
pinMode(12,OUTPUT);
pinMode(13,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(12,HIGH);
digitalWrite(13,HIGH);
delay(500);
digitalWrite(12,LOW);
digitalWrite(13,LOW);
delay(500);
}
