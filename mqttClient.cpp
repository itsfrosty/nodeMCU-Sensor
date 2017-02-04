#include "mqttClient.h"

MQTTClient::MQTTClient(
  const char *ssid,
  const char *password,
  const char *mqttServer,
  const char *mqttUser,
  const char *mqttPassword
) {
  _subClient = new PubSubClient(_wifiClient);
  _mqttServer = mqttServer;
  _ssid = ssid;
  _password = password;
  _mqttUser = mqttUser;
  _mqttPassword = mqttPassword;
}
void MQTTClient::setup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(_ssid, _password);
  _subClient->setServer(_mqttServer, 1883);
  Serial.println("");

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(_ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void MQTTClient::publish(const char* topic, const char* payload, boolean retained) {
  if (!_subClient->connected()) {
    _reconnect();
  }
  _subClient->publish(topic, payload, retained);
}

void MQTTClient::loop(long timeNow) {
  _subClient->loop();
}

void MQTTClient::_reconnect() {
  // Loop until we're reconnected
  while (!_subClient->connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (_subClient->connect("ESP8266Client", _mqttUser, _mqttPassword)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(_subClient->state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(2000);
    }
  }
}
