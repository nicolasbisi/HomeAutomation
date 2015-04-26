#include <UIPEthernet.h>
#include <dht.h>
#define sensor01 A1 //DHT sensor 01 pin number
#define sensor02 A2 //DHT sensor 02 pin number

//Boot
int bootDelay = 1000; //Time of boot to let sensors initialize (miliseconds)

//Temperature and Humidity sensors
dht DHT;

//Network
EthernetServer server = EthernetServer(80);
byte mac[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; //Dont forget to change if necessary!
IPAddress myIP(192,168,1,43); //Dont forget to change if necessary!



void setup(){
  Serial.begin(9600);
  Ethernet.begin(mac,myIP);
  server.begin();
  boot();
}

void loop(){
  String input = "";
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    char c = client.read();
    if(c == 'G'){
      c = client.read();
      if(c == 'E'){
        c = client.read();
        if(c == 'T'){
          c = client.read();
          if(c == ' '){
            c = client.read();
            if(c == '/'){
              do{
                c = client.read();
                if(c != '/'){input = input+c;}
              }while (c != '/'); //URL must end in /
              if (input == "sensor01"){
                printDHTInfo(sensor01);
              }
              if (input == "sensor02"){
                printDHTInfo(sensor02);
              }
              client.print(input); //print request
            }
          }
        }
      }
    client.stop();
    }
  }
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
  Serial.print(DHT.temperature,0); //,0 prevent printing X,00 that always occour on DHT11
  Serial.print("C  ");

  Serial.print("Humidity on Sensor ");
  Serial.print(sensorNumber);
  Serial.print(" = ");
  Serial.print(DHT.humidity,0);
  Serial.print("%  ");
  Serial.println();
}
