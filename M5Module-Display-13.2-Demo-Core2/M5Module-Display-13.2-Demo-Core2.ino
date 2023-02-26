#include <Arduino.h>

#include <M5ModuleDisplay.h>

// Version 0.1.4 or higher required
#include <M5Unified.h>

#include "sunrise_anna_single_left.h"
extern const unsigned char pattern_test[13287];

void setup() {
    auto cfg = M5.config();

    cfg.external_speaker.module_display = true;
    cfg.external_display.module_display = true;

    // If you want to change the resolution, uncomment the following lines and
    // adjust the values
    //  cfg.module_display.logical_width = 1280;
    //  cfg.module_display.logical_height = 720;
    //  cfg.module_display.refresh_rate = 60;

    M5.begin(cfg);

    M5.Display.setFont(&fonts::efontCN_24_b);
    M5.Display.clear(WHITE);
    M5.Display.setTextColor(ORANGE);
    M5.Display.drawString("Display module 13.2 Demo", 20, 0);
    M5.Display.setCursor(0, 80);
    M5.Display.setTextColor(BLACK);
    M5.Display.print("Loop Display:");
    M5.Display.setCursor(0, 110);
    M5.Display.print("Test Pic->Red->Green->Blue");
    M5.Display.setTextColor(TFT_RED);
    M5.Display.setCursor(20, 180);
    M5.Display.print("A test wav will play!");

    // Change the primary display to ModuleDisplay.
    M5.setPrimaryDisplayType(m5gfx::board_M5ModuleDisplay);

    M5.Display.setTextSize(1.5);
    M5.Display.setFont(&fonts::efontCN_24_b);

    // If you want to change the volume, uncomment the following line and adjust
    // the value M5.Speaker.setVolume(128);

    // Endless playback of wavedata.
    M5.Speaker.playWav(sunrise_anna_single_left,
                       sizeof(sunrise_anna_single_left), 0);
}

void loop(void) {
    M5.Display.clear(TFT_BLACK);
    M5.Display.drawPng(pattern_test, ~0u, 0, 0, M5.Display.width(),
                       M5.Display.height(), 0, 0, (M5.Display.width() / 320),
                       (M5.Display.height() / 240), datum_t::middle_center);
    delay(4000);

    M5.Display.clear(TFT_RED);
    M5.Display.drawCentreString("M5STACK Display Module 13.2",
                                M5.Display.width() / 2, 10);
    M5.Display.drawCentreString("红(RED)", M5.Display.width() / 2,
                                M5.Display.height() / 2);
    delay(4000);

    M5.Display.clear(TFT_GREEN);
    M5.Display.drawCentreString("M5STACK Display Module 13.2",
                                M5.Display.width() / 2, 10);
    M5.Display.drawCentreString("绿(GREEN)", M5.Display.width() / 2,
                                M5.Display.height() / 2);
    delay(4000);

    M5.Display.clear(TFT_BLUE);
    M5.Display.drawCentreString("M5STACK Display Module 13.2",
                                M5.Display.width() / 2, 10);
    M5.Display.drawCentreString("蓝(BLUE)", M5.Display.width() / 2,
                                M5.Display.height() / 2);
    delay(4000);
}
