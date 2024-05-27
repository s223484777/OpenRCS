#include<Arduino.h>
#include<SPI.h>
#include<src/config.h>
#include<src/objects.h>
#include<src/IO/io.h>
#include<src/OLED/display.h>
#include<src/loranet/loranet.h>
#include<TinyGPS++.h>

Status status;
IOMgr iomgr;
IOMgr last_state;
Message msg;
LoRaConfig conf;

void updateGPS(){
  while(Serial2.available()){
    status.gps.encode(Serial2.read());
  }
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(GPS_BAUD);
  status.mode = 1; // 1 = network, 2 = personal
  displayInit();
  ioInit();
  loraInit(WiFi.macAddress());
  last_state = iomgr;
}

void loop() {
  ioUpdate();
  displayUpdate();
  updateGPS();
  if(loraUpdate()){
    if(loraMessage(msg)){
      msg.timestamp = "";
      msg.timestamp += status.gps.time.hour();
      msg.timestamp += ":";
      msg.timestamp += status.gps.time.minute();
      msg.timestamp += ":";
      msg.timestamp += status.gps.time.second();
    }
  }

  if(iomgr.btn_onboard != last_state.btn_onboard){
    if(!iomgr.btn_onboard){
      setFrameCall(true);
    }
    iomgr.led_onboard = !iomgr.btn_onboard;
  }

  if(iomgr.btn_a != last_state.btn_a){
    if(!iomgr.btn_a){
      loranetPage("Test page.");
    }
  }

  if(iomgr.mq_digital != last_state.mq_digital){
    if(iomgr.mq_digital && status.mode == 1){
      loranetAlert("MQ135 Air Quality Alert!");
    }
  }

  last_state = iomgr;
}