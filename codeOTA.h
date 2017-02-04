#ifndef codeOTA_h
#define codeOTA_h

#include <ArduinoOTA.h>

#include "Arduino.h"

class CodeOTA
{
  public:
    CodeOTA(const char* otaHostName, const char* otaPassword);
    void setup();
    void loop();

  private:
    const char* _otaHostName;
    const char* _otaPassword;
};

#endif
