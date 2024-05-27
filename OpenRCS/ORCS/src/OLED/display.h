#include<src/config.h>
#include<src/objects.h>
#include<SSD1306.h>
#include<OLEDDisplayUi.h>

void displayInit();
void displayUpdate();
void displayNextFrame();
void setFrameCall(bool call);

void drawStatusFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);
void drawMessageFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);

extern IOMgr iomgr;
extern Status status;
extern Message msg;