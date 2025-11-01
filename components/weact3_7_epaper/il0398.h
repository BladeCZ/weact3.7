#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

class IL0398 : public esphome::spi::SPIDevice {
 public:
  void init();
  void clear_frame();
  void write_frame(uint8_t *buffer, int w, int h);
  void refresh();
 private:
  void command(uint8_t cmd);
  void data(uint8_t data);
  void busy_wait();
};
