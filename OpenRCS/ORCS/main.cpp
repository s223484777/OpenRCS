#include<Arduino.h>
#include<SPI.h>
#include<src/config.h>
#include<src/objects.h>
#include<src/IO/io.h>
#include<src/OLED/display.h>
#include<src/loranet/loranet.h>
#include<TinyGPS++.h>

// Declare all the objects
Status status;
IOMgr iomgr;
IOMgr last_state;
Message msg;
LoRaConfig conf;

// Update the GPS object with new serial data
void updateGPS(){
  while(Serial2.available()){
    status.gps.encode(Serial2.read());
  }
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(GPS_BAUD);
  status.mode = 1;
  #ifdef MODE_PERSONAL
    status.mode = 2;
  #endif
  displayInit();
  ioInit();
  loraInit(WiFi.macAddress());
  last_state = iomgr;
}

void loop() {
  // Update everything
  ioUpdate();
  displayUpdate();
  updateGPS();
  if(loraUpdate()){
    if(loraMessage(msg)){
      // Message timestamp from GPS
      //char timestamp[10];
      //sprintf(timestamp, "%02d:%02d:%02d", status.gps.time.hour(), status.gps.time.minute(), status.gps.time.second());
      // Timestamp set in loranet.cpp
      //msg.timestamp = timestamp;
    }
  }

  // Handle changing the frame on the OLED
  if(iomgr.btn_onboard != last_state.btn_onboard){
    if(!iomgr.btn_onboard){
      setFrameCall(true);
    }
    iomgr.led_onboard = !iomgr.btn_onboard;
  }

  #ifdef MODE_NETWORK
    // Send a test page
    if(iomgr.btn_a != last_state.btn_a){
      if(!iomgr.btn_a){
        loranetPage("Test page. Test0 Test1 Test2.");
      }
    }

    // Send an alert
    if(iomgr.mq_digital != last_state.mq_digital){
      if(iomgr.mq_digital && status.mode == 1){
        loranetAlert("MQ135 Air Quality Alert!");
      }
    }
  #endif

  #ifdef MODE_PERSONAL
    if(iomgr.btn_a != last_state.btn_a){
      if(!iomgr.btn_a){
        // Clear message, but not alert. Alerts only clear when reset
        Message newMsg;
        msg = newMsg;
      }
    }
  #endif

  // Store the current state into the iomgr object
  last_state = iomgr;
}