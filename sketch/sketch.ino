#include <Arduino.h>
#include <WiFi.h>
#include <DHT.h>

#define DHTPIN 15
#define DHTTYPE DHT22
#define PIRPIN 26
#define POTPIN 35

const char* ssid = "Wokwi-GUEST";   // sua rede WiFi
const char* password = "";           // senha da rede (vazia no Wokwi)

WiFiClient client;
DHT dht(DHTPIN, DHTTYPE);

unsigned long previousMillis = 0;
const long gpsInterval = 1000; // 1 segundo

// DADOS DO THINGSPEAK
const char* host = "api.thingspeak.com";
const char* writeAPIKey = "R31HFJLNF2MJO898";
unsigned long channelID = 2983958;

// Variáveis para simular GPS (latitude e longitude)
float latitude = 48.1173;   
float longitude = 11.5167;  

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(PIRPIN, INPUT_PULLUP);
  analogReadResolution(12);

  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WiFi conectado. IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Leitura dos sensores
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int potValue = analogRead(POTPIN);
  float batteryPercentage = map(potValue, 0, 4095, 0, 100);
  bool pirDetected = digitalRead(PIRPIN) == LOW;

  Serial.print("Temperatura: ");
  if (isnan(temperature)) Serial.print("Erro");
  else Serial.print(temperature, 2);  
  Serial.print(" °C, Umidade: ");
  if (isnan(humidity)) Serial.print("Erro");
  else Serial.print(humidity, 2);
  Serial.print(" %, Bateria: ");
  Serial.print(batteryPercentage, 2);
  Serial.print(" %, PIR detectado: ");
  Serial.print(pirDetected ? "SIM" : "NÃO");
  Serial.print(", Latitude: ");
  Serial.print(latitude, 6); 
  Serial.print(", Longitude: ");
  Serial.println(longitude, 6);

  // Envio via HTTP para o ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {
    if (client.connect(host, 80)) {
      String httpRequest = "GET /update?api_key=";
      httpRequest += writeAPIKey;
      httpRequest += "&field1=";
      httpRequest += isnan(temperature) ? 0 : temperature;
      httpRequest += "&field2=";
      httpRequest += isnan(humidity) ? 0 : humidity;
      httpRequest += "&field3=";
      httpRequest += batteryPercentage;
      httpRequest += "&field4=";
      httpRequest += pirDetected ? 1 : 0;
      httpRequest += "&field5=";
      httpRequest += latitude;
      httpRequest += "&field6=";
      httpRequest += longitude;
      httpRequest += " HTTP/1.1\r\nHost: ";
      httpRequest += host;
      httpRequest += "\r\nConnection: close\r\n\r\n";

      client.print(httpRequest);

      // Esperar resposta do servidor
      while (client.connected() || client.available()) {
        if (client.available()) {
          String line = client.readStringUntil('\n');
          Serial.println(line); // resposta HTTP para debug
        }
      }
      client.stop();
      Serial.println("Dados enviados ao ThingSpeak!");
    } else {
      Serial.println("Falha na conexão com ThingSpeak");
    }
  } else {
    Serial.println("WiFi não conectado");
  }

  delay(20000); // delay para respeitar limite do ThingSpeak 
}
