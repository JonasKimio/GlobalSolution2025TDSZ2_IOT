#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASSWORD = ""; 
const char* MQTT_BROKER = "broker.hivemq.com"; 
const int MQTT_PORT = 1883;
const char* MQTT_TOPIC = "fiap/gs/workflow/sensor01"; 
const char* DEVICE_ID = "WS_001_HOME_OFFICE"; 
WiFiClient espClient;
PubSubClient client(espClient);
const int ANALOG_MQ135_PIN = 34;

float readAirQuality() {
  int rawValue = analogRead(ANALOG_MQ135_PIN);
  float ppm = map(rawValue, 0, 4095, 200, 700); 
  return ppm;
}

float readTemperature() {
  return random(220, 260) / 10.0; 
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(WIFI_SSID);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    if (client.connect(DEVICE_ID)) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando em 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  
  client.setServer(MQTT_BROKER, MQTT_PORT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); 

  float temp = readTemperature();
  float airQuality = readAirQuality();
  
  StaticJsonDocument<200> doc;
  doc["device_id"] = DEVICE_ID;
  doc["timestamp"] = millis();
  doc["temperature_c"] = temp;
  doc["air_quality_ppm"] = airQuality;

  char jsonBuffer[200];
  serializeJson(doc, jsonBuffer);

  Serial.print("Publicando: ");
  Serial.println(jsonBuffer);
  
  client.publish(MQTT_TOPIC, jsonBuffer);
  
  delay(10000); 
}