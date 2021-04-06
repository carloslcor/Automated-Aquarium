String input;
#define MAX_LENGTH 64
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"

//para o WIFI
#include <WiFi.h>

const char* ssid     = "Freedom Home";
const char* password = "freedom1984";

WiFiServer server(80);
//////////////////////////////////

DHT dht(5, DHT22);
float t; //Temperatura
float h; // Umidade

const int oneWireBus = 4;// GPIO where the DS18B20 is connected to    
int value = LOW;                // último valor do LED
long previousMillis = 0;        // último momento que o LED foi atualizado
long interval = 1000;           // tempo de transição entre estados (milisegundos)

OneWire oneWire(oneWireBus);// Setup a oneWire instance to communicate with any OneWire devices
DallasTemperature sensors(&oneWire);// Pass our oneWire reference to Dallas Temperature sensor 

const int ledPin = 2;   // LED conectado ao pino digital 13
/*const int bombaSubmersa = 18; //OBS: DEVE SER DESCONECTADO PARA PODER EXECUTAR A GRAVAÇÃO VIA USB
const int bombaCirculacao = 13;
const int skimmer = 14;
const int cooler = 15; //Pino que aciona o sistema de ventilação*/
const int sensorNivel = 25; //Pino que aciona o sistema de ventilação
int sensorNivelState = 0;


const int RELE1 = 13;
const int RELE2 = 14;
const int RELE3 = 15;
const int RELE4 = 18;
const int RELE5 = 19;
const int RELE6 = 21;
const int RELE7 = 22;
const int RELE8 = 23;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  pinMode(ledPin, OUTPUT);      // configura o pino digital como saída
  pinMode(sensorNivel, INPUT_PULLUP);      // configura o pino digital como saída

  pinMode(RELE1, OUTPUT);      // configura o pino digital como saída
  pinMode(RELE2, OUTPUT);      // configura o pino digital como saída
  pinMode(RELE3, OUTPUT);      // configura o pino digital como saída
  pinMode(RELE4, OUTPUT);      // configura o pino digital como saída
  pinMode(RELE5, OUTPUT);
  pinMode(RELE6, OUTPUT);
  pinMode(RELE7, OUTPUT);
  pinMode(RELE8, OUTPUT);

  digitalWrite(RELE1, HIGH);
  digitalWrite(RELE2, HIGH);
  digitalWrite(RELE3, HIGH);
  digitalWrite(RELE4, HIGH);
  digitalWrite(RELE5, HIGH);
  digitalWrite(RELE6, HIGH);
  digitalWrite(RELE7, HIGH);
  digitalWrite(RELE8, HIGH);

  Serial.begin(115200);  // Start the Serial Monitor
  Serial.println("AguaFreedom v0.1"); //Mensagem de saudação
  Serial.println("Data:06/04/2021"); //Mensagem de saudação
  Serial.println("by Carlos Rodrigues"); //Mensagem de saudação
  input.reserve(MAX_LENGTH + 1);  // Define o tamanho máximo do buffer (+ 1 por causa do \0 no final
  sensors.begin();  // Start the DS18B20 sensor
  dht.begin();


  // We start by connecting to a WiFi network
  Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();
//int value = 0;//ver se precisa disso msm
  ////////////////////////
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() 
{
  //Wifi Function
   WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("<a href=\"/L1\">L1</a>");
            client.print("<a href=\"/D1\"> D1</a><br>");
            client.print("<a href=\"/L2\">L2</a>");
            client.print("<a href=\"/D2\"> D2</a><br>");
            client.print("<a href=\"/L3\">L3</a>");
            client.print("<a href=\"/D3\"> D3</a><br>");
            client.print("<a href=\"/L4\">L4</a>");
            client.print("<a href=\"/D4\"> D4</a><br>");
            client.print("<a href=\"/L5\">L5</a>");
            client.print("<a href=\"/D5\"> D5</a><br>");
            client.print("<a href=\"/L6\">L6</a>");
            client.print("<a href=\"/D6\"> D6</a><br>");
            client.print("<a href=\"/L7\">L7</a>");
            client.print("<a href=\"/D7\"> D7</a><br>");
            client.print("<a href=\"/L8\">L8</a>");
            client.print("<a href=\"/D8\"> D8</a><br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /L1")) {
          digitalWrite(RELE1, LOW);               // GET /H turns the LED on
        }
        else if (currentLine.endsWith("GET /D1")) {
          digitalWrite(RELE1, HIGH);                // GET /L turns the LED off
        }
        else if (currentLine.endsWith("GET /L2")) {
          digitalWrite(RELE2, LOW);                // GET /L turns the LED off
        }
        else if (currentLine.endsWith("GET /D2")) {
          digitalWrite(RELE2, HIGH);                // GET /L turns the LED off
        }
        else if (currentLine.endsWith("GET /L3")) {
          digitalWrite(RELE3, LOW);                // GET /L turns the LED off
        }
        else if (currentLine.endsWith("GET /D3")) {
          digitalWrite(RELE3, HIGH);                // GET /L turns the LED off
        }
        else if (currentLine.endsWith("GET /L4")) {
          digitalWrite(RELE4, LOW);                // GET /L turns the LED off
        }
        else if (currentLine.endsWith("GET /D4")) {
          digitalWrite(RELE4, HIGH);                // GET /L turns the LED off
        }
        else if (currentLine.endsWith("GET /L5")) {
          digitalWrite(RELE5, LOW);                // GET /L turns the LED off
        }
        else if (currentLine.endsWith("GET /D5")) {
          digitalWrite(RELE5, HIGH);                // GET /L turns the LED off
        }
        else if (currentLine.endsWith("GET /L6")) {
          digitalWrite(RELE6, LOW);                // GET /L turns the LED off
        }
        else if (currentLine.endsWith("GET /D6")) {
          digitalWrite(RELE6, HIGH);                // GET /L turns the LED off
        }
        else if (currentLine.endsWith("GET /L7")) {
          digitalWrite(RELE7, LOW);                // GET /L turns the LED off
        }
        else if (currentLine.endsWith("GET /D7")) {
          digitalWrite(RELE7, HIGH);                // GET /L turns the LED off
        }
        else if (currentLine.endsWith("GET /L8")) {
          digitalWrite(RELE8, LOW);                // GET /L turns the LED off
        }
        else if (currentLine.endsWith("GET /D8")) {
          digitalWrite(RELE8, HIGH);                // GET /L turns the LED off
        }

      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
  //////////////////////////

  /*// check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  sensorNivelState = digitalRead(sensorNivel);
  if (sensorNivelState == HIGH) {
    // turn LED on:
    //LIGAR MOTOR RO
  } else {
    // turn LED off:
    //DESLIGAR MOTOR RO
  }*/
  tratamentoSerial();
  timer1Segundo();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void timer1Segundo(){
  if (millis() - previousMillis > interval) {
    previousMillis = millis();   // lembre-se do último tempo que piscamos o LED
    if (value == LOW){
      value = HIGH;//printTemperatura();
      /*digitalWrite(aux1, HIGH);
      digitalWrite(aux2, HIGH);
      digitalWrite(aux3, HIGH);
      digitalWrite(aux4, HIGH);*/
    }
    else{
      value = LOW;//printTemperatura();
      /*digitalWrite(aux1, LOW);
      digitalWrite(aux2, LOW);
      digitalWrite(aux3, LOW);
      digitalWrite(aux4, LOW);*/
    }
    digitalWrite(ledPin, value);   
  } 
  //controleTemperatura();
  //TemperaturaUmidade();
}
void tratamentoSerial(){
  if (Serial.available()){
    char c = Serial.read(); // Recebe um caracter
    if(c == '\n') {     // Se foi digitado um ENTER entao processa a String       
    //Serial.println("A string digitada foi ");Serial.println(input);         
    input.toUpperCase();    // Converte toda a String para maiusculo
    input.trim();           // Tira os espacos antes e depois                
      if(input == "TEMP"){    
        printTemperatura();
      }
      else if (input == "STATUS") {
        controleTemperatura();
        TemperaturaUmidade();
      }      
      else if (input == "L1") {
        digitalWrite(RELE1, LOW);
        Serial.println("R1: ON");
      } 
      else if (input == "D1") {
        digitalWrite(RELE1, HIGH);
        Serial.println("R1: OFF");
      }   
      else if (input == "L2") {
        digitalWrite(RELE2, LOW);
        Serial.println("R2: ON");
      } 
      else if (input == "D2") {
        digitalWrite(RELE2, HIGH);
        Serial.println("R2: OFF");
      }   
      else if (input == "L3") {
        digitalWrite(RELE3, LOW);
        Serial.println("R3: ON");
      } 
      else if (input == "D3") {
        digitalWrite(RELE3, HIGH);
        Serial.println("R3: OFF");
      }   
      else if (input == "L4") {
        digitalWrite(RELE4, LOW);
        Serial.println("R4: ON");
      } 
      else if (input == "D4") {
        digitalWrite(RELE4, HIGH);
        Serial.println("R4: OFF");
      }   
      else if (input == "L5") {
        digitalWrite(RELE5, LOW);
        Serial.println("R5: ON");
      } 
      else if (input == "D5") {
        digitalWrite(RELE5, HIGH);
        Serial.println("R5: OFF");
      }   
      else if (input == "L6") {
        digitalWrite(RELE6, LOW);
        Serial.println("R6: ON");
      } 
      else if (input == "D6") {
        digitalWrite(RELE6, HIGH);
        Serial.println("R6: OFF");
      }   
      else if (input == "L7") {
        digitalWrite(RELE7, LOW);
        Serial.println("R7: ON");
      } 
      else if (input == "D7") {
        digitalWrite(RELE7, HIGH);
        Serial.println("R7: OFF");
      }   
      else if (input == "L8") {
        digitalWrite(RELE8, LOW);
        Serial.println("R8: ON");
      } 
      else if (input == "D8") {
        digitalWrite(RELE8, HIGH);
        Serial.println("R8: OFF");
      }   
      else if (input == "LT") {
        digitalWrite(RELE1, LOW);
        digitalWrite(RELE2, LOW);
        digitalWrite(RELE3, LOW);
        digitalWrite(RELE4, LOW);
        digitalWrite(RELE5, LOW);
        digitalWrite(RELE6, LOW);
        digitalWrite(RELE7, LOW);
        digitalWrite(RELE8, LOW);
        Serial.println("R1,R2,R3,R4,R5,R6, R7 e R8: ON");
      } 
      else if (input == "DT") {
        digitalWrite(RELE1, HIGH);
        digitalWrite(RELE2, HIGH);
        digitalWrite(RELE3, HIGH);
        digitalWrite(RELE4, HIGH);
        digitalWrite(RELE5, HIGH);
        digitalWrite(RELE6, HIGH);
        digitalWrite(RELE7, HIGH);
        digitalWrite(RELE8, HIGH);
        Serial.println("R1,R2,R3,R4,R5,R6, R7 e R8: OFF");
      }   
      input = "";// Limpa a String para comecar a armazenar de novo         
    } 
    else{    
      // Se nao veio um ENTER entao vai armazenando até o tamanho maximo que a string pode suportar        
      if(input.length() < MAX_LENGTH){
        if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')){ // Aqui estamos filtrando so as letras. Poderia filtrar numeros e espaco por exemplo
          input += c;
        }
      }
    }
  }
}
void printTemperatura(){
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  //float temperatureF = sensors.getTempFByIndex(0);
  Serial.println("Temperatura aquário: "+String(temperatureC)+"ºC");
}
void controleTemperatura(){
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  if(temperatureC >= 27){
    //digitalWrite(cooler, HIGH);   
    Serial.println("Cooler Ligado, Temperatura aquário: "+String(temperatureC)+"ºC");
  }
  else if(temperatureC <= 28){
    //digitalWrite(cooler, LOW);   
    Serial.println("Cooler Desligado, Temperatura aquário: "+String(temperatureC)+"ºC");
  }
}
void TemperaturaUmidade(){
  h = dht.readHumidity();
  t = dht.readTemperature();
  Serial.println("Temperatura equipamentos: "+String(t)+"ºC");
  Serial.println("Umidade: "+String(h)+"%");
}
