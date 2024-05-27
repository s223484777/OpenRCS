#include<Arduino.h>
#include<src/config.h>
#include<src/IO/io.h>

unsigned long next_input = 0;

void ioInit(){
  pinMode(ONBOARD_BTN, INPUT_PULLUP);
  pinMode(BTN_0_I,     INPUT_PULLUP);
  pinMode(BTN_1_I,     INPUT_PULLUP);

  pinMode(ONBOARD_LED, OUTPUT);
  pinMode(BTN_0_O,     OUTPUT);
  pinMode(BTN_1_O,     OUTPUT);
  pinMode(BUZZ_PIN,    OUTPUT);

  pinMode(MQ135_A, INPUT);
  pinMode(MQ135_D, INPUT);
}

// TODO: Implement buzzer
void ioUpdate(){
  if(millis() > next_input){
    iomgr.btn_onboard = digitalRead(ONBOARD_BTN);
    iomgr.btn_a       = digitalRead(BTN_0_I);
    iomgr.btn_b       = digitalRead(BTN_1_I);
  }

  digitalWrite(ONBOARD_LED, iomgr.led_onboard);
  digitalWrite(BTN_0_O,     iomgr.led_a);
  digitalWrite(BTN_1_O,     iomgr.led_b);

  iomgr.mq_digital = !digitalRead(MQ135_D);
  status.mq135_alert = !digitalRead(MQ135_D);
}