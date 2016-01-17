#ifndef Radio_h
#define Radio_h

#include "Arduino.h"
#include "SPI.h"
#include <RH_NRF24.h>

class Radio
{
  public:
  	Radio();
  	void start(int, RH_NRF24);
    void sendMessage(String,RH_NRF24);
    // bool isMessage(RH_NRF24);
    String getMessage(RH_NRF24);
};

#endif
