#include <Arduino.h>
#include <SensirionI2CSen5x.h>
#include <Wire.h>
#include <WiFi.h>

SensirionI2CSen5x sen5x;

const char* ssid = "ssid";
const char* password = "pw";

WiFiServer server(80);

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  sen5x.begin(Wire);
  uint16_t error = sen5x.deviceReset();

  float tempOffset = 0.0;
  error = sen5x.setTemperatureOffsetSimple(tempOffset);
  error = sen5x.startMeasurement();

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
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    float massConcentrationPm1p0;
    float massConcentrationPm2p5;
    float massConcentrationPm4p0;
    float massConcentrationPm10p0;
    float ambientHumidity;
    float ambientTemperature;
    float vocIndex;
    float noxIndex;
    currentTime = millis();
    previousTime = currentTime;
    String line = "";
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (line.length() == 0) {

            uint16_t error = sen5x.readMeasuredValues(
                               massConcentrationPm1p0, massConcentrationPm2p5, massConcentrationPm4p0,
                               massConcentrationPm10p0, ambientHumidity, ambientTemperature, vocIndex,
                               noxIndex);

            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/plain");
            client.println("Connection: close");
            client.println();

            client.print("sen055_mass_concentration{size=\"pm_1_0\"} ");  client.print(massConcentrationPm1p0); client.print('\n');
            client.print("sen055_mass_concentration{size=\"pm_2_5\"} ");  client.print(massConcentrationPm2p5); client.print('\n');
            client.print("sen055_mass_concentration{size=\"pm_4_0\"} ");  client.print(massConcentrationPm4p0); client.print('\n');
            client.print("sen055_mass_concentration{size=\"pm_10_0\"} "); client.print(massConcentrationPm10p0); client.print('\n');
            client.print("sen055_ambient_humidity{} ");     client.print(ambientHumidity); client.print('\n');
            client.print("sen055_ambient_temperature{} ");  client.print(ambientTemperature); client.print('\n');
            client.print("sen055_voc_index{} ");            client.print(vocIndex); client.print('\n');
            client.print("sen055_nox_index{} ");            client.print(noxIndex); client.print('\n');

          } else {
            line = "";
          }
        } else if (c != '\r') {
          line += c;
        }
      }
    }
    client.stop();
    
    Serial.print("MassConcentrationPm1p0:");
    Serial.print(massConcentrationPm1p0);
    Serial.print("\t");
    Serial.print("MassConcentrationPm2p5:");
    Serial.print(massConcentrationPm2p5);
    Serial.print("\t");
    Serial.print("MassConcentrationPm4p0:");
    Serial.print(massConcentrationPm4p0);
    Serial.print("\t");
    Serial.print("MassConcentrationPm10p0:");
    Serial.print(massConcentrationPm10p0);
    Serial.print("\t");
    Serial.print("AmbientHumidity:");
    if (isnan(ambientHumidity)) {
      Serial.print("n/a");
    } else {
      Serial.print(ambientHumidity);
    }
    Serial.print("\t");
    Serial.print("AmbientTemperature:");
    if (isnan(ambientTemperature)) {
      Serial.print("n/a");
    } else {
      Serial.print(ambientTemperature);
    }
    Serial.print("\t");
    Serial.print("VocIndex:");
    if (isnan(vocIndex)) {
      Serial.print("n/a");
    } else {
      Serial.print(vocIndex);
    }
    Serial.print("\t");
    Serial.print("NoxIndex:");
    if (isnan(noxIndex)) {
      Serial.println("n/a");
    } else {
      Serial.println(noxIndex);
    }
  }
}
