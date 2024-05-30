#ifndef ORCS_CONFIG
#define ORCS_CONFIG

// Uncomment the desired configuration
//#define MODE_NETWORK // 15964/255822
//#define MODE_PERSONAL // 15956/255026

// Includes
#include<src/secrets.h>
#include<WiFi.h>

// LoRa
#define LORA_SCK           5
#define LORA_MISO         19
#define LORA_MOSI         27
#define LORA_SS           18
#define LORA_RST          14
#define LORA_DIO0         26

// UI
#define ONBOARD_BTN        0
#define ONBOARD_LED        2
#define BTN_0_I           12 // Button input, pullup
#define BTN_0_O           32 // Blue LED output
#define BTN_1_I           13 // Button input, pullup
#define BTN_1_O           33 // Blue LED output
#define BUZZ_PIN          23
#define OLED_SDA           4
#define OLED_SCL          15 
#define OLED_RST          16
#define OLED_WIDTH       128
#define OLED_HEIGHT       64

// GPS
#define GPS_BAUD        9600

// MQ135 Sensor
#define MQ135_D           36
#define MQ135_A           37 // Requires voltage divider

// DHT11 Temp and humidity
#define DHT11_DATA        10

// BMP180
#define DEFAULT_PRES 1013.25

#endif