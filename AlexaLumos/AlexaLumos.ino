#include <ESP8266WiFi.h>   
#include "SinricPro.h"
#include "SinricProSwitch.h"
 
#define WIFI_SSID         "Coloque_Aqui_o_nome_do_seu_WiFi"    
#define WIFI_PASS         "A_Senha_do_seu_WiFi"
#define APP_KEY           "Coloque aqui a chave do app, que você acha lá no site do Sinric Pro"      // O seu App Key é algo como "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "Coloque o senha do app, está na parte de credenciais"   // O seu App Secret é algo como "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
 
#define Abajour_ID       "Copie e cole aqui"    // Algo como "5dc1564130xxxxxxxxxxxxxx"
#define Abajour_Pin 16  // O pino fisico onde está ligado
#define Lampada_ID       "Copie e cole aqui"    // Algo como "5dc1564130xxxxxxxxxxxxxx"
#define Lampada_Pin 5  // O pino fisico onde está ligado
#define Regua_ID       "Copie e cole aqui"    // Algo como "5dc1564130xxxxxxxxxxxxxx"
#define Regua_Pin 4  // O pino fisico onde está ligado
#define Ventilador_ID       "Copie e cole aqui"    // Algo como "5dc1564130xxxxxxxxxxxxxx"
#define Ventilador_Pin 0  // O pino fisico onde está ligado
 
#define BAUD_RATE         9600                // Se precisar, pode trocar o baud rate
 
 
void setupWiFi();
void setupSinricPro();
bool AbajourState(const String &deviceId, bool &state);
bool LampadaState(const String &deviceId, bool &state);
bool ReguaState(const String &deviceId, bool &state);
bool VentiladorState(const String &deviceId, bool &state);
 
 
// main setup function
void setup() {
  Serial.begin(BAUD_RATE); Serial.printf("\r\n\r\n");
  setupWiFi();
  setupSinricPro(); 
  pinMode(Abajour_Pin, OUTPUT);
  pinMode(Lampada_Pin, OUTPUT);
  pinMode(Regua_Pin, OUTPUT);
  pinMode(Ventilador_Pin, OUTPUT);
}
 
void loop() {
  SinricPro.handle();
}
 
 
bool AbajourState(const String &deviceId, bool &state) {
  Serial.printf("O abajour foi %s\r\n", state?"ligado":"desligado");
  digitalWrite(Abajour_Pin, state);
  return true; // request handled properly
}
 
bool LampadaState(const String &deviceId, bool &state) {
  Serial.printf("A lampada foi %s\r\n", state?"ligada":"desligada");
  digitalWrite(Lampada_Pin, state);
  return true; // request handled properly
}
 
bool ReguaState(const String &deviceId, bool &state) {
  Serial.printf("A regua de energia foi %s\r\n", state?"ligada":"desligada");
  digitalWrite(Regua_Pin, state);
  return true; // request handled properly
}
 
bool VentiladorState(const String &deviceId, bool &state) {
  Serial.printf("O ventilador foi %s\r\n", state?"ligado":"desligado");
  digitalWrite(Ventilador_Pin, state);
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
  SinricProSwitch &mySwitch1 = SinricPro[Abajour_ID];
  mySwitch1.onPowerState(AbajourState);
 
  SinricProSwitch &mySwitch2 = SinricPro[Lampada_ID];
  mySwitch2.onPowerState(LampadaState);
 
  SinricProSwitch &mySwitch3 = SinricPro[Regua_ID];
  mySwitch3.onPowerState(ReguaState);
 
  SinricProSwitch &mySwitch4 = SinricPro[Ventilador_ID];
  mySwitch4.onPowerState(VentiladorState);
 
  // setup SinricPro
  SinricPro.onConnected([](){ Serial.printf("Conectado a nuvem SinricPro\r\n"); }); 
  SinricPro.onDisconnected([](){ Serial.printf("Desconectado a nuvem SinricPro\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
}