#include "il0398.h"
#include "esphome/core/log.h"

static const char *TAG = "il0398";

void IL0398::command(uint8_t cmd) {
  this->dc_pin_->digital_write(false);
  this->write_byte(cmd);
}

void IL0398::data(uint8_t data) {
  this->dc_pin_->digital_write(true);
  this->write_byte(data);
}

void IL0398::busy_wait() {
  while (this->busy_pin_->digital_read()) {
    delay(10);
  }
}

void IL0398::init() {
  ESP_LOGI(TAG, "IL0398 init...");

  this->reset_pin_->digital_write(false);
  delay(10);
  this->reset_pin_->digital_write(true);
  delay(10);

  busy_wait();

  command(0x01); // POWER SETTING
  data(0x03);
  data(0x00);
  data(0x2B);
  data(0x2B);

  command(0x06); // BOOSTER
  data(0x17);
  data(0x17);
  data(0x17);

  command(0x04); // POWER ON
  busy_wait();

  command(0x00); // PANEL SETTING
  data(0x3F);

  command(0x30); // PLL
  data(0x3C);

  command(0x61); // Resolution
  data(0x01);  // 280
  data(0x18);
  data(0x01);  // 480
  data(0xE0);

  command(0x82); // VCOM
  data(0x1A);

  ESP_LOGI(TAG, "IL0398 init done");
}

void IL0398::clear_frame() {
  command(0x10);
  for (int i = 0; i < 280 * 480 / 8; i++)
    data(0xFF);
}

void IL0398::write_frame(uint8_t *buffer, int w, int h) {
  command(0x13);
  for (int i = 0; i < w * h / 8; i++)
    data(buffer[i]);
}

void IL0398::refresh() {
  command(0x12);
  busy_wait();
}
