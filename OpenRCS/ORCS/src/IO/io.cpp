#include<Arduino.h>
#include<src/config.h>
#include<src/IO/io.h>

// Debounce delay
unsigned long next_input = 0;

// Configure all the pins
void ioInit(){
  pinMode(ONBOARD_BTN, INPUT_PULLUP);
  pinMode(BTN_0_I,     INPUT_PULLUP);
  pinMode(BTN_1_I,     INPUT_PULLUP);

  pinMode(ONBOARD_LED, OUTPUT);
  pinMode(BTN_0_O,     OUTPUT);
  pinMode(BTN_1_O,     OUTPUT);

  pinMode(MQ135_A, INPUT);
  pinMode(MQ135_D, INPUT);
}

// Update the IOMgr object and the outputs
void ioUpdate(){
  #ifdef MODE_NETWORK
    iomgr.mq_digital = !digitalRead(MQ135_D);
    status.mq135_alert = !digitalRead(MQ135_D);
  #endif

  // Manual debounce
  if(millis() > next_input){
    iomgr.btn_onboard = digitalRead(ONBOARD_BTN);
    iomgr.btn_a       = digitalRead(BTN_0_I);
    iomgr.btn_b       = digitalRead(BTN_1_I);
    next_input += 50;
  }

  iomgr.led_a = status.mq135_alert;

  digitalWrite(ONBOARD_LED, iomgr.led_onboard);
  digitalWrite(BTN_0_O,     iomgr.led_a);
  digitalWrite(BTN_1_O,     iomgr.led_b);
  digitalWrite(BTN_0_O, status.mq135_alert);
}