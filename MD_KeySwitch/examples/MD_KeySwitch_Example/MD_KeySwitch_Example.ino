// Example showing use of the MD_KeySwitch library
//
#include <MD_KeySwitch.h>

#define  SWITCH_PIN  7

MD_KeySwitch  S(SWITCH_PIN);

void setup() 
{
  Serial.begin(57600);
  Serial.println("[MD_KeySwitch example]");
  
  S.begin();
}

void loop() 
{
  if (S.read())
    Serial.println("ON");
}
