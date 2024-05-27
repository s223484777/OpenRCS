#include<src/OLED/display.h>

SSD1306* display;
OLEDDisplayUi* ui = NULL;
uint8_t frame_count = 2;
FrameCallback frames[] = {drawStatusFrame, drawMessageFrame};
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

void displayNextFrame() {}

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

void drawStatusFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y){
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(x, y, "Network Node");
  display->drawString(x, y+16, "Alert status: " + String(status.mq135_alert));
}

void drawMessageFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y){
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(x, y, "Last Message: " + msg.timestamp + "\n");
  display->drawString(x, y+8, msg.access);
  display->drawString(x, y+16, msg.msg);
}