#ifndef ORCS_DISPLAY
#define ORCS_DISPLAY

#include<src/config.h>
#include<src/objects.h>
#include<SSD1306.h>
#include<OLEDDisplayUi.h>

// Signatures
void displayInit();
void displayUpdate();
void displayNextFrame();
void setFrameCall(bool call);

// Frame signatures
void drawStatusFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);
void drawMessageFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);
void drawGPSFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);

// Global variables
extern IOMgr iomgr;
extern Status status;
extern Message msg;

#endif