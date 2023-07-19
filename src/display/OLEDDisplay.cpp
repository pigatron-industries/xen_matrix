#include "OLEDDisplay.h"
#include <eurorack.h>

void OLEDDisplay::init() {
    u8g2.begin();
    u8g2.clearBuffer();	
    u8g2.sendBuffer();
    u8g2.setFont(DISPLAY_FONT);
    u8g2.setDrawColor(1);
}

void OLEDDisplay::clear() {
    u8g2.clearBuffer();
}

void OLEDDisplay::update() {
    u8g2.sendBuffer();
}

void OLEDDisplay::setTextColour(uint16_t colour) {
    u8g2.setDrawColor(colour);
}
        
void OLEDDisplay::text(const char* text, uint8_t x, uint8_t y) {
    u8g2.drawStr(x, y+DISPLAY_FONT_HEIGHT-1, text);
    u8g2.sendBuffer();
}

void OLEDDisplay::fillRectangle(int x, int y, int w, int h, int colour) {
    u8g2.setDrawColor(colour);
    u8g2.drawBox(x, y, w, h);
}

void OLEDDisplay::drawRectangle(int x, int y, int w, int h, int colour) {
    //TODO
}

// Deprecated
void OLEDDisplay::textLine(const char* text, uint8_t x, uint8_t y, uint8_t w) {
    u8g2.setFont(DISPLAY_FONT);
    u8g2.setDrawColor(0);
    u8g2.drawBox(y, x, w, DISPLAY_FONT_HEIGHT);
    u8g2.setDrawColor(1);
    u8g2.drawStr(y, x+DISPLAY_FONT_HEIGHT-1, text);
    u8g2.sendBuffer();
}

// Deprecated
void OLEDDisplay::textLine(int num, uint8_t x, uint8_t y, uint8_t w) {
    snprintf_P(buffer, sizeof(buffer), PSTR("%d"), num);
    textLine(buffer, x, y, w);
}
