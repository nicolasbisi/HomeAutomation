#include <dht.h>
#define sensor01 A1 //DHT sensor 01 pin number
#define sensor02 A2 //DHT sensor 02 pin number
int bootDelay = 1000; //Time of boot to let sensors initialize (miliseconds)
dht DHT;

void setup(){
  Serial.begin(9600);
  boot();
}

void loop(){
  printDHTInfo(sensor01);
  printDHTInfo(sensor02);
  delay(1000);
}

void boot(){
  Serial.println();
  Serial.println("System v0.1 Booting:");
  Serial.print("|");
  for(int x = 0; x<10; x++){
    Serial.print(x);
    Serial.print("0-");
    delay(bootDelay/10);
  }
  Serial.println("100|");
  Serial.println("Boot Completed!");
}

void printDHTInfo(int pin){
  DHT.read11(pin);
  int sensorNumber;
  if (pin == A1){
    sensorNumber = 1;
  }
  if (pin == A2){
    sensorNumber = 2;
  }
  Serial.print("Temperature  on sensor ");
  Serial.print(sensorNumber);
  Serial.print(" = ");
  Serial.print(DHT.temperature,0); 
  Serial.print("C  ");

  Serial.print("Humidity on Sensor ");
  Serial.print(sensorNumber);
  Serial.print(" = ");
  Serial.print(DHT.humidity,0);
  Serial.print("%  ");
  Serial.println();
}
