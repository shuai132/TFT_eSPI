#include "TFT_eSPI.h"
#include "render_sdl.h"

#include "RingBuffer.hpp"
#include "chart.h"
#include "rpc_msg.h"
#include "screen.h"
#include "ui.h"
#include "value.h"

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 80
#define SCREEN_SCALE 2
#define SCREEN_BG TFT_BLACK

InaMsg g_ina_current;
USBMsg g_adc_current;
float g_temperature;

TFT_eSPI g_tft = TFT_eSPI();
TFT_eSprite g_spr(&g_tft);
ScreenConfig g_screen_config;
RingBuffer<InaMsg, UI_CHART_WIDTH> g_sensor_buffer;

static void drawTest() {
  g_spr.createSprite(SCREEN_WIDTH, SCREEN_HEIGHT);
  ui_value_update();
  ui_chart_update();
}

int main() {
  SDLRenderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_SCALE);
  if (!renderer.init()) {
    return 1;
  }

  // test
  drawTest();

  // update display
  renderer.updateDisplay(&g_spr, 0, 0);

  // run event loop
  SDLRenderer::runEventLoop();
  return 0;
}
