#include "temperatureSensor.h"

TemperatureSensor::TemperatureSensor(int pin, const char* topic) {
  _pin = pin;
  _lastTempTime = 0;
  _lastTemperature = 0;
  _topic = topic;
}

void TemperatureSensor::setup() {
  _oneWire = new OneWire(_pin);
  _dallasTemp = new DallasTemperature(_oneWire);
}

void TemperatureSensor::loop(long timeNow, MQTTClient* client) {
  if (timeNow - _lastTempTime < 5000) {
    return;
  }
  _lastTempTime = timeNow;
  float temperature = _getTemperature();
  temperature = roundf(temperature * 10) / 10;
  if (temperature == _lastTemperature || isnan(temperature)) {
    return;
  }
  _lastTemperature = temperature;
  Serial.print("New temperature:");
  Serial.println(_lastTemperature);

  char temperatureFString[10];
  dtostrf(_lastTemperature, 6, 1, temperatureFString);
  client->publish(_topic, temperatureFString, true);
}

float TemperatureSensor::_getTemperature() {
  float temp;
  float tempF;
  do {
    _dallasTemp->requestTemperatures();
    temp = _dallasTemp->getTempFByIndex(0);
    delay(100);
  } while (temp > 180 || temp < -190);
  return temp;
}
