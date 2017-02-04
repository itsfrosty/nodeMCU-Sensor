#include "motionSensor.h"

MotionSensor::MotionSensor(int pin, const char* topic) {
  _pin = pin;
  _lastMotion = false;
  _lastMotionTime = 0;
  _topic = topic;
}

void MotionSensor::setup() {
  pinMode(_pin, INPUT);
  _lastMotion = !digitalRead(_pin);
}

void MotionSensor::loop(long timeNow, MQTTClient* client) {
  if (timeNow - _lastMotionTime < 10) {
    return;
  }
  _lastMotionTime = timeNow;
  bool motion = digitalRead(_pin);
  if (motion == _lastMotion) {
    return;
  }
  _lastMotion = motion;
  Serial.print(_topic);
  Serial.print(" Motion changed: ");
  Serial.println(motion);

  if (motion) {
    client->publish(_topic, "ON", true);
  } else {
    client->publish(_topic, "OFF", true);
  }
}
