#ifndef ORCS_OBJECTS
#define ORCS_OBJECTS

#include<Arduino.h>
#include<src/config.h>
#include<TinyGPS++.h>

// Stores the states for the IO
struct IOMgr{
  bool btn_onboard = false;
  bool btn_a       = false;
  bool btn_b       = false;

  bool led_onboard = false;
  bool led_a       = false;
  bool led_b       = false;
  uint8_t buzz_pwm =     0;

  bool mq_digital;
};

// Stores the configuration for the LoRa module
struct LoRaConfig{
  double freq = NETWORK_BAND;
  char network_key[9] = NETWORK_KEY;
  char access_key[3][9] = {PUBLIC_NET_ACCESS, CONTROL_NET_ACCESS, ALERT_NET_ACCESS};
  int tx_timeout = NETWORK_TX_TIMEOUT_MS;
};

// Stores the statuses
struct Status{
  int mode;
  TinyGPSPlus gps;
  bool mq135_alert = false;
  bool wifi = false;
  int wifi_status = 0;
};

// Stores the message data
struct Message{
  float rssi;
  String timestamp = "Waiting";
  String network;
  String access;
  String src_mac;
  String msg;
};

#endif