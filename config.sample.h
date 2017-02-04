#ifndef config_h
#define config_h

#define MOTION_PIN1 D1
#define MOTION_PIN2 D2
#define ONE_WIRE_BUS D3

const char* ssid = "";
const char* password = "";

const char* mqttServer = "";
const char* mqttUser = "";
const char* mqttPassword = "";
const char* temperatureTopic = "";
const char* motion1Topic = "";
const char* motion2Topic = "";

const char* otaHostName = "";
const char* otaPassword = "";

#endif
