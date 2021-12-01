#include <ESP8266WiFi.h>
#ifndef STASSID
#define STASSID "Alexandre"
#define STAPSK  "*******"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

int ledPin = 2; 
int rele = 12;
int dutyCycle = 0;

WiFiServer server(80);

void setup() {
  pinMode(rele, OUTPUT);
  digitalWrite(rele, LOW);
  
  Serial.begin(115200);
  
  Serial.println();
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  server.begin();
  Serial.println(WiFi.localIP());
}

void loop() {
 
   WiFiClient client = server.available();

    if(client){
      String currentLine = "";
      while (client.connected()){
        if(client.available()){
          char c = client.read();
          Serial.write(c);
          if(c == '\n'){
            
            if(currentLine.length() == 0){
              client.println("HTTP/1.1 200 OK");
              client.println("content-type:text/html");
              client.println();
              client.print("Click <a href=\"/0\">here</a> Dimer Desligado.<br>");
              client.print("Click <a href=\"/1\">here</a> Dimer 10%.<br>");
              client.print("Click <a href=\"/2\">here</a> Dimer 20%.<br>");
              client.print("Click <a href=\"/3\">here</a> Dimer 30%.<br>");
              client.print("Click <a href=\"/4\">here</a> Dimer 40%.<br>");
              client.print("Click <a href=\"/5\">here</a> Dimer 50%.<br>");
              client.print("Click <a href=\"/6\">here</a> Dimer 60%.<br>");
              client.print("Click <a href=\"/7\">here</a> Dimer 70%.<br>");
              client.print("Click <a href=\"/8\">here</a> Dimer 80%.<br>");
              client.print("Click <a href=\"/9\">here</a> Dimer 90%.<br>");
              client.print("Click <a href=\"/10\">here</a> Dimer 100%.<br>");
              client.print("Click <a href=\"/fade\">here</a>Efeito Fade.<br>");
              client.print("Click <a href=\"/lampada\">here</a> Ligar Lampada.<br>");
              client.println();
              break;
              }else {    
               currentLine = "";
              }
             } else if (c != '\r') {  
                currentLine += c;      
              }

              if (currentLine.endsWith("GET /0")) {
                dutyCycle = 0;
                analogWrite(ledPin, dutyCycle);         
              }
              if (currentLine.endsWith("GET /1")) {
                dutyCycle = 100;
                analogWrite(ledPin, dutyCycle);         
              }
              if (currentLine.endsWith("GET /2")) {
                dutyCycle = 200;
                analogWrite(ledPin, dutyCycle);         
              }
              if (currentLine.endsWith("GET /3")) {
                dutyCycle = 300;
                analogWrite(ledPin, dutyCycle);         
              }
              if (currentLine.endsWith("GET /4")) {
                dutyCycle = 400;
                analogWrite(ledPin, dutyCycle);         
              }
              if (currentLine.endsWith("GET /5")) {
                dutyCycle = 500;
                analogWrite(ledPin, dutyCycle);         
              }
              if (currentLine.endsWith("GET /6")) {
                dutyCycle =600;
                analogWrite(ledPin, dutyCycle);         
              }
              if (currentLine.endsWith("GET /7")) {
                dutyCycle = 700;
                analogWrite(ledPin, dutyCycle);         
              }
              if (currentLine.endsWith("GET /8")) {
                dutyCycle = 800;
                analogWrite(ledPin, dutyCycle);         
              }
              if (currentLine.endsWith("GET /9")) {
                dutyCycle = 900;
                analogWrite(ledPin, dutyCycle);         
              }
              if (currentLine.endsWith("GET /10")) {
                dutyCycle = 1023;
                analogWrite(ledPin, dutyCycle);         
              }
              
              if(currentLine.endsWith("GET /fade")){
                for(int dutyCycle = 500; dutyCycle > 0; dutyCycle--){
                analogWrite(ledPin, dutyCycle);
                delay(1);
                }
                dutyCycle = 0;
                analogWrite(ledPin, dutyCycle); 
              }
              if (currentLine.endsWith("GET /lampada")) {
                digitalWrite(rele, !digitalRead(rele));        
              }
          }
       }
       client.stop();
     }
     
   }  
  
  

  
