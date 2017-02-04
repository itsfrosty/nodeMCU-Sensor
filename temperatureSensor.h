#ifndef temperatureSensor_h
#define temperatureSensor_h

#include "Arduino.h"
#include <DallasTemperature.h>
#include <OneWire.h>

#include "mqttClient.h"


class TemperatureSensor
{
  public:
    TemperatureSensor(int pin, const char* topic);
    void setup();
    void loop(long timeNow, MQTTClient* client);

  private:
    int _pin;
    float _lastTemperature;
    long _lastTempTime;
    OneWire* _oneWire;
    DallasTemperature* _dallasTemp;
    const char *_topic;

    float _getTemperature();
};

#endif
