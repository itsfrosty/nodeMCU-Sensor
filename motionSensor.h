#ifndef motionSensor_h
#define motionSensor_h

#include "Arduino.h"

#include "mqttClient.h"


class MotionSensor
{
  public:
    MotionSensor(int pin, const char* topic);
    void setup();
    void loop(long timeNow, MQTTClient* client);

  private:
    int _pin;
    bool _lastMotion;
    long _lastMotionTime;
    const char *_topic;
};

#endif
