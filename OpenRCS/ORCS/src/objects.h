#ifndef ORCS_OBJECTS
#define ORCS_OBJECTS

#include<Arduino.h>
#include<src/config.h>
#include<TinyGPS++.h>

struct IOMgr{
  bool btn_onboard = false;
  bool btn_a       = false;
  bool btn_b       = false;

  bool led_onboard = false;
  bool led_a       = false;
  bool led_b       = false;
  int buzz_pwm     =     0;

  bool mq_digital;
};

struct APConfig{
  char ap_ssid[13] = "OpenRCS Node";
  char ap_pass[9] = WiFi_PSK;
};

struct LoRaConfig{
  double freq = NETWORK_BAND;
  char network_key[9] = NETWORK_KEY;
  char access_key[3][9] = {PUBLIC_NET_ACCESS, CONTROL_NET_ACCESS, ALERT_NET_ACCESS};
  int tx_timeout = NETWORK_TX_TIMEOUT_MS;
};

struct Status{
  int mode;
  TinyGPSPlus gps;
  bool mq135_alert = false;
  bool wifi = false;
  int wifi_status = 0;
};

struct Message{
  float rssi;
  String timestamp = "Waiting";
  String network;
  String access;
  String src_mac;
  String msg;
};

#endif