#include<SPI.h>
#include<LoRa.h>
#include<src/loranet/loranet.h>

unsigned long next_tx = 0;
String mac_addr;

void loraInit(String mac){
    mac_addr = mac;
    SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
    LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);
    LoRa.begin(conf.freq);
}

bool loraUpdate(){
  if(LoRa.parsePacket() > 0){
    String data = "";
    while(LoRa.available()){
      data += LoRa.readString();
    }

    if(data.length() < 40){
        return false;
    }

    msg.rssi = LoRa.packetRssi();
    msg.network = data.substring(0, 8);
    msg.access = data.substring(9, 18);
    msg.src_mac = data.substring(19, 37);
    msg.msg = data.substring(39);
    char timestamp[6];
    sprintf(timestamp, "%02d:%02d", status.gps.time.hour(), status.gps.time.minute());
    msg.timestamp = status.gps.date.year() > 2000 ? timestamp : "--:--";

    return true;
  }

  return false;
}

void loranetAlert(String msg){
  loraTX(msg, 2);
}

void loranetPage(String msg){
  loraTX(msg, 0);
}

bool loraMessage(Message msg){
  #ifdef MODE_NETWORK
    if(msg.access.startsWith(PUBLIC_NET_ACCESS)){ // General public message, rebroadcast
      loranetPage(msg.msg);
      return true;
    }else if(msg.access.startsWith(CONTROL_NET_ACCESS)){ // No network controls implemented yet
      return false;
    }else{ // Alert message, rebroadcast
      loranetAlert(msg.msg);
      return true;
    }
  #endif
}

bool loraTX(String msg, int access_idx){
  if(millis() > next_tx || access_idx == 2){ // Always rebroadcast an alert
    LoRa.beginPacket();
    LoRa.println(conf.network_key);
    LoRa.println(conf.access_key[access_idx]);
    LoRa.println(mac_addr);
    LoRa.println(msg);
    LoRa.endPacket();

    next_tx += NETWORK_TX_TIMEOUT_MS;
  }

  return false;
}