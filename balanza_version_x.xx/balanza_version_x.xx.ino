#include "Arduino.h"
//#include "RTClib.h"
#include <SPI.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
//#include "DHT.h"
#include "variables.h"
#include <HX711.h>

#ifndef APSSID
#define APSSID "BALANZA_200K"
#define APPSK  "123456789"
#endif

#define DHTPIN 0
#define DHTTYPE DHT11
#define EEPROM_SIZE 4096

const char *ssid = APSSID;
const char *password = APPSK;

//RTC_DS3231 RTC;
//DHT dht(DHTPIN, DHTTYPE);
WiFiServer server(80);
HX711 scale;

void setup() {
  delay(1000);
  Serial.begin(115200);
//  dht.begin();
  EEPROM.begin(EEPROM_SIZE);
  Wire.begin(); // Start the I2C
//  RTC.begin();  // Init RTC
//  RTC.adjust(DateTime(__DATE__, __TIME__)); 
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(factor_scale);
//  scale.tare(20);
//  eeprom_read();  
  Serial.println();
  
  Serial.print("Configurando punto de acceso...");
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Direccion de IP AP: ");
  Serial.println(myIP);  
  server.begin();
  Serial.println("HTTP server en linea");
}
/*
void read_dht(){
  h = dht.readHumidity();
  t = dht.readTemperature();
}
*/

void read_balanza(){
  lectura_balanza = scale.get_units(5);
  lectura_balanza *= factor_palanca;
  lectura_balanza += 9.45;
}
/*
String read_rtc(){
  String fecha_hora;
  DateTime now = RTC.now();
  fecha_hora += String(now.day(), DEC);
  fecha_hora += "/";
  fecha_hora += String(now.month(), DEC);
  fecha_hora += "/";
  fecha_hora += String(now.year(), DEC);
  fecha_hora += "---";
  fecha_hora += String(now.hour(), DEC);
  fecha_hora += ":";
  fecha_hora += String(now.minute(), DEC);
  fecha_hora += ":";
  fecha_hora += String(now.second(), DEC);
  return(fecha_hora);
  }
  */
  
void loop() {
 webExc();
}
