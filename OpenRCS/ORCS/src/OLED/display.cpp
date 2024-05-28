#include<src/OLED/display.h>

#ifdef MODE_NETWORK
  uint8_t frame_count = 3;
  FrameCallback frames[] = {drawStatusFrame, drawMessageFrame, drawGPSFrame};
#endif

SSD1306* display;
OLEDDisplayUi* ui = NULL;
bool change_frame = false;

void displayInit(){
  display = new SSD1306(0x3c, OLED_SDA, OLED_SCL);
  ui = new OLEDDisplayUi(display);
  ui->setTargetFPS(60);
  ui->setFrameAnimation(SLIDE_DOWN);
  ui->setFrames(frames, frame_count);
  ui->disableAutoTransition();
  ui->init();
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(50);
  digitalWrite(OLED_RST, HIGH);
  display->init();
  display->flipScreenVertically();
}

void displayNextFrame(){}

void setFrameCall(bool call){
  change_frame = call;
}

void displayUpdate(){
  if(change_frame){
    ui->nextFrame();
    change_frame = false;
  }
  ui->update();
}

#ifdef MODE_NETWORK
 void drawStatusFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y){
    display->setFont(ArialMT_Plain_10);
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    display->drawString(x, y, "Network Node");
    String alert_status = status.mq135_alert ? "ALERT": "no alert";
    display->drawString(x, y+16, "Alert status: " + alert_status);
    display->drawString(x, y+32, "Network: " + String(NETWORK_KEY));
  }

  void drawMessageFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y){
    display->setFont(ArialMT_Plain_10);
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    display->drawString(x, y, "Last Message: " + msg.timestamp + "\n");
    display->drawString(x, y+8, msg.access);
    display->drawString(x, y+16, msg.msg);
    display->drawString(x, y+24, msg.msg.substring(26));
    display->drawString(x, y+32, msg.msg.substring(52));
  }

  void drawGPSFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y){
    display->setFont(ArialMT_Plain_10);
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    char datetimestring[20];
    sprintf(datetimestring, "%04d/%02d/%02d %02d:%02d:%02d",
      status.gps.date.year(),
      status.gps.date.month(),
      status.gps.date.day(),
      status.gps.time.hour(),
      status.gps.time.minute(),
      status.gps.time.second()
    );
    display->drawString(x, y, "GPS    " + (status.gps.date.year() > 2000 ? String(datetimestring) : "----/--/-- --:--:--"));
  }
#endif