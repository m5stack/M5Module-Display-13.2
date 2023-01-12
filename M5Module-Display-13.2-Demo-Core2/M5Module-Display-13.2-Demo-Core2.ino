#include <Arduino.h>
#include "M5ModuleDisplay.h"
#include "M5Unified.h"

#include "wav_unsigned_8bit_click.cpp"

static void play_wav(void*);

extern const unsigned char pattern_test[13287];

static M5ModuleDisplay hdmi(1280, 720);
static M5GFX lcd;

void setup() {
    auto cfg         = M5.config();
    cfg.external_spk = true;
    cfg.internal_spk = false;

    M5.begin(cfg);

    hdmi.begin();
    hdmi.setRotation(1);
    hdmi.setTextSize(1.5);
    hdmi.setFont(&fonts::efontCN_24_b);
    hdmi.startWrite();
    hdmi.drawPng(pattern_test, ~0u, 0, 0, hdmi.width(), hdmi.height(), 0, 0,
                 3.0, 3.0, datum_t::middle_center);
    hdmi.endWrite();

    lcd.begin();
    lcd.startWrite();
    lcd.setFont(&fonts::efontCN_24_b);
    lcd.clear(WHITE);
    lcd.setTextColor(ORANGE);
    lcd.drawString("Display Module Demo", 50, 0);
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
    hdmi.clear(TFT_RED);
    hdmi.drawCentreString("M5STACK Display Module 13.2", hdmi.width() / 2, 10);
    hdmi.drawCentreString("红(RED)", hdmi.width() / 2, hdmi.height() / 2);
    delay(4000);

    hdmi.clear(TFT_GREEN);
    hdmi.drawCentreString("M5STACK Display Module 13.2", hdmi.width() / 2, 10);
    hdmi.drawCentreString("绿(GREEN)", hdmi.width() / 2, hdmi.height() / 2);
    delay(4000);

    hdmi.clear(TFT_BLUE);
    hdmi.drawCentreString("M5STACK Display Module 13.2", hdmi.width() / 2, 10);
    hdmi.drawCentreString("蓝(BLUE)", hdmi.width() / 2, hdmi.height() / 2);
    delay(4000);

    hdmi.clear(TFT_BLACK);
    hdmi.drawPng(pattern_test, ~0u, 0, 0, hdmi.width(), hdmi.height(), 0, 0,
                 (hdmi.width() / 320), (hdmi.height() / 240),
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
