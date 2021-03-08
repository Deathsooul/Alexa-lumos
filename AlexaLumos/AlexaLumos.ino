#include <ESP8266WiFi.h>   
#include "SinricPro.h"
#include "SinricProSwitch.h"


// Infos da Rede
#define WIFI_SSID ""    
#define WIFI_PASS ""

// Insira o App Key do Sinric
#define APP_KEY ""

// Insira o App Secret do Sinric
#define APP_SECRET ""

// ID do dispositivo
#define Lampada_ID ""
// O pino fisico onde está ligado
#define Lampada_Pin 5


// Se precisar, pode trocar o baud rate
#define BAUD_RATE 9600
 
 
void setupWiFi();
void setupSinricPro();

bool LampadaState(const String &deviceId, bool &state);

 
 
// main setup function
void setup() {
  Serial.begin(BAUD_RATE); Serial.printf("\r\n\r\n");
  setupWiFi();
  setupSinricPro();   
  pinMode(Lampada_Pin, OUTPUT);
}
 
void loop() {
  SinricPro.handle();
}
 

bool LampadaState(const String &deviceId, bool &state) {
  Serial.printf("A lampada foi %s\r\n", state?"ligada":"desligada");
  digitalWrite(Lampada_Pin, state);
  return true; // request handled properly
}
 
 
// setup das conexões Wifi
void setupWiFi() {
  Serial.printf("\r\n[Wifi]: Conectando...");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }
 
  Serial.printf("Conectado!\r\n[WiFi]: Endereço de IP e %s\r\n", WiFi.localIP().toString().c_str());
}
 
// setup das funções para o SinricPro
void setupSinricPro() {
  // add devices and callbacks to SinricPro

 
  SinricProSwitch &mySwitch = SinricPro[Lampada_ID];
  mySwitch.onPowerState(LampadaState);
 
  // setup SinricPro
  SinricPro.onConnected([](){ Serial.printf("Conectado a nuvem SinricPro\r\n"); }); 
  SinricPro.onDisconnected([](){ Serial.printf("Desconectado a nuvem SinricPro\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
}