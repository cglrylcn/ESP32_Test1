#include "stdbool.h"
#include <can_common.h>
#include <esp32_can.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing ...");
//  SET pins if it is not correct
//  pinMode(GPIO_NUM_16, OUTPUT);
//   digitalWrite(GPIO_NUM_16, LOW); //enable CAN transceiver
//   CAN0.setCANPins(GPIO_NUM_4, GPIO_NUM_5);
}

void initCAN0(unsigned long baudRate) {
  // Initialize CAN controller at the specified speed
  if(CAN0.begin(baudRate))
  {
    //Serial.println("Baudrate: %lu  ", baudRate);
    Serial.println("Init OK ...");
  } else {
    //Serial.println("Baudrate: %lu  ", baudRate);
    Serial.println("Init Failed ...");
  }
  CAN0.watchFor(); //read everything
  Serial.println("CANbus is Ready ...!");
}

CAN_FRAME rxMessage;
byte i = 0;
byte initOnce = 0;
void loop() {
  
  if(initOnce == 0) {
    initCAN0(250000);
    initOnce++;
  }
  
  if (CAN0.read(rxMessage)) {
    // Print message
    Serial.print("ID: ");
    Serial.println(rxMessage.id,HEX);
    Serial.print("Extended: ");
    if(rxMessage.extended) {
      Serial.println("Yes");
    } else {
      Serial.println("No");
    }
    Serial.print("Length: ");
    Serial.println(rxMessage.length,DEC);
    for(i = 0;i < rxMessage.length; i++) {
      Serial.print(rxMessage.data.byte[i],HEX);
      Serial.print(" ");
    }
    Serial.println();
    Serial.println();

    rxMessage.id++;
    //CAN0.sendFrame(rxMessage);
  }
}