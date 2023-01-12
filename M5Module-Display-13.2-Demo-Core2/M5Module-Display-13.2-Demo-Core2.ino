#include <Arduino.h>
#include "M5ModuleDisplay.h"
#include "M5Unified.h"

#include "wav_unsigned_8bit_click.cpp"

static void play_wav(void*);

extern const unsigned char pattern_test[13287];

static M5ModuleDisplay display(1280, 720);
static M5GFX lcd;

void setup() {
    auto cfg         = M5.config();
    cfg.external_spk = true;
    cfg.internal_spk = false;

    M5.begin(cfg);

    display.begin();
    display.setRotation(1);
    display.setTextSize(1.5);
    display.setFont(&fonts::efontCN_24_b);
    display.startWrite();
    display.drawPng(pattern_test, ~0u, 0, 0, display.width(), display.height(),
                    0, 0, 3.0, 3.0, datum_t::middle_center);
    display.endWrite();

    lcd.begin();
    lcd.startWrite();
    lcd.setFont(&fonts::efontCN_24_b);
    lcd.clear(WHITE);
    lcd.setTextColor(ORANGE);
    lcd.drawString("Display module 13.2 Demo", 20, 0);
    lcd.setCursor(0, 80);
    lcd.setTextColor(BLACK);
    lcd.print("Loop Display:");
    lcd.setCursor(0, 110);
    lcd.print("Test Pic->Red->Green->Blue");
    lcd.setTextColor(TFT_RED);
    lcd.setCursor(20, 180);
    lcd.print("A test wav will play!");
    lcd.endWrite();

    delay(2000);

    auto spk_cfg        = M5.Speaker.config();
    spk_cfg.sample_rate = 96000;
    if (M5.getBoard() == m5gfx::boards::board_M5StackCore2) {
        spk_cfg.pin_ws       = 0;
        spk_cfg.pin_data_out = 2;
        spk_cfg.pin_bck      = 27;
    } else if (M5.getBoard() == m5gfx::boards::board_M5Stack) {
        spk_cfg.pin_ws       = 0;
        spk_cfg.pin_data_out = 15;
        spk_cfg.pin_bck      = 12;
    }

    M5.Speaker.config(spk_cfg);
    M5.Speaker.begin();
    M5.Speaker.setVolume(255);
    M5.Speaker.setChannelVolume(0, 255);
    M5.Speaker.setChannelVolume(1, 255);

    xTaskCreatePinnedToCore(play_wav, "play_wav", 8192, NULL, 1, NULL, 1);
}

void loop(void) {
    display.clear(TFT_RED);
    display.drawCentreString("M5STACK Display Module 13.2", display.width() / 2,
                             10);
    display.drawCentreString("红(RED)", display.width() / 2,
                             display.height() / 2);
    delay(4000);

    display.clear(TFT_GREEN);
    display.drawCentreString("M5STACK Display Module 13.2", display.width() / 2,
                             10);
    display.drawCentreString("绿(GREEN)", display.width() / 2,
                             display.height() / 2);
    delay(4000);

    display.clear(TFT_BLUE);
    display.drawCentreString("M5STACK Display Module 13.2", display.width() / 2,
                             10);
    display.drawCentreString("蓝(BLUE)", display.width() / 2,
                             display.height() / 2);
    delay(4000);

    display.clear(TFT_BLACK);
    display.drawPng(pattern_test, ~0u, 0, 0, display.width(), display.height(),
                    0, 0, (display.width() / 320), (display.height() / 240),
                    datum_t::middle_center);
    delay(4000);
}

static void play_wav(void*) {
    while (true) {
        M5.Speaker.playWav(sunrise_anna_single_left,
                           sizeof(sunrise_anna_single_left), ~0u, 0, true);
        delay(3000);
        M5.Speaker.stop(0);
    }
}
