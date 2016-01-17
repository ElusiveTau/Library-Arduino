#include "Arduino.h"
#include "Radio.h"
#include "SPI.h"
#include <RH_NRF24.h>

Radio::Radio(){

}

void Radio::start(int serialNum,RH_NRF24 transmitter){
    Serial.begin(serialNum);
  if (!transmitter.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!transmitter.setChannel(1))
    Serial.println("setChannel failed");
  if (!transmitter.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");  
}
void Radio::sendMessage(String message,RH_NRF24 transmitter){
    uint8_t data[RH_NRF24_MAX_MESSAGE_LEN];
    message.getBytes(data, message.length()+1);
    transmitter.send(data, sizeof(data));
    transmitter.waitPacketSent();
    Serial.println("Message sent");

    uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (transmitter.waitAvailableTimeout(500)){//If sender does not receive ACK message, time out
      // Should be a reply message for us now
     if (transmitter.recv(buf, &len)){
      Serial.println("Got response: "+ String((char*)buf));
      return;
    }
    else{
      Serial.println("recv failed");
    }
  } 
  else{
    Serial.println("Sender did not receive Receiver's ACK Message");
  }
  delay(400);
}

// bool Radio::isMessage(RH_NRF24 transmitter){
//   return(transmitter.available());
// }

String Radio::getMessage(RH_NRF24 transmitter){
 if (transmitter.available())
  {
    Serial.println("Got Message");
    // Should be a message for us now   
    uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (transmitter.recv(buf, &len))
    {
      // Send an aknowledgement reply that message was received
      buf[len] = '\0';//IMPORTANT: transmitter.recv(buff,&len) doesn't append null terminator
      uint8_t data[] = "Receiver: ACK Message Stored";
      transmitter.send(data, sizeof(data));
      transmitter.waitPacketSent();
      return(String((char*)buf));
    }
    else
    {
      return("Transmitter.recv contains garbage: Unable to store received message to buff");
    }
  }else{
    return "";
  }
//     Serial.println("SOMETHING WAS RECEIVED");
//  uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
//     uint8_t len = sizeof(buf);
//     if (transmitter.recv(buf, &len))
//     {
// //      NRF24::printBuffer("request: ", buf, len);
//       Serial.print("got request: ");
//       Serial.println((char*)buf);
      
//       // Send a reply
//       uint8_t data[] = "Message received";
//       transmitter.send(data, sizeof(data));
//       transmitter.waitPacketSent();
//       return ("Sent a reply");
//     }
//     else
//     {
//       return ("recv failed");
//     }
}

