
#include <ArduinoOTA.h>
#include <math.h>

#include "config.h"
#include "mqttClient.h"
#include "temperatureSensor.h"
#include "motionSensor.h"
#include "codeOTA.h"

MQTTClient *mqttClient;
TemperatureSensor *tempSensor;
MotionSensor *motion1;
MotionSensor *motion2;
CodeOTA *codeOTA;

void setup(void) {
  mqttClient = new MQTTClient(ssid, password, mqttServer, mqttUser, mqttPassword);
  mqttClient->setup();
  
  tempSensor = new TemperatureSensor(ONE_WIRE_BUS, temperatureTopic);
  tempSensor->setup();

  motion1 = new MotionSensor(MOTION_PIN1, motion1Topic);
  motion1->setup();

  motion2 = new MotionSensor(MOTION_PIN2, motion2Topic);
  motion2->setup();

  codeOTA = new CodeOTA(otaHostName, otaPassword);
  codeOTA->setup();
}

void loop(void) {
  codeOTA->loop();

  long timeNow = millis();
  mqttClient->loop(timeNow);
  tempSensor->loop(timeNow, mqttClient);

  motion1->loop(timeNow, mqttClient);
  motion2->loop(timeNow, mqttClient);
}

