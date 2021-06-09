//βιβλιοθήκες
#include <dht.h>
#include <Servo.h>
dht DHT;
#define DHT11_PIN 7

//μεταβλητές
float hum;
float temp;
int sensorPin = A0; 
int sensorValue;
Servo serv; 



void setup(){
  Serial.begin(9600);
  //καθορισμός θυρών
  pinMode(7, INPUT); //θερμοκρασία/υγρασία ατμόσφαιρας
  pinMode(3, OUTPUT); //ανεμιστήρας
  pinMode(4, OUTPUT); //θερμενόμενο σύρμα
  serv.attach(9); //βαλβίδα νερού
  pinMode(10, OUTPUT); //led

  digitalWrite(10, HIGH);

  serv.write(40); //ορίζει την θέση του servo για να είναι κλειστή η βαλβίδα
  
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
}

void loop(){

  //εντολές αισθητήρα DHT11(υγρ./θερμ.) 
  int chk = DHT.read11(DHT11_PIN);
  hum = DHT.humidity;
  temp = DHT.temperature;
  Serial.print("Temperature = C");
  Serial.println(temp);
  Serial.print("Humidity = %");
  Serial.println(hum);


  //ρυθμίσεις ανεμιστήρα και θέρμανσης
  if (hum > 80){
    digitalWrite(3, LOW);
  }
  else {
    digitalWrite(3, HIGH);
  }


  if (temp < 22){
    digitalWrite(4, LOW);
  }
  else {
    digitalWrite(4, HIGH);
  }

  //εντολές αισθητήρα υγρασίας εδάφους
  sensorValue = analogRead(sensorPin); 
  Serial.print ("Soil Moisture = ");
  Serial.println(sensorValue);


  //ρυθμίσεις βαλβίδας νερού
  if (sensorValue > 400) { 
  serv.write(0); //στην θέση 0, η βαλβίδα είναι ανοιχτή
  delay(10000);
  serv.write(40); //το servo επαναφέρεται στην αρχική θέση και το καλαμάκι σπάει
  }
  else {
    serv.write(40);
  }
 
 
  delay(5000);
}
