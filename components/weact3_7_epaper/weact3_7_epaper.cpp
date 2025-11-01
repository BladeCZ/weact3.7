#include "component.h"
#include "esphome/core/log.h"

namespace esphome {
namespace weact3_7_epaper {

static const char *TAG = "weact3.7.il0398";

void WeAct3_7Epaper::setup() {
  ESP_LOGI(TAG, "Initializing WeAct 3.7'' IL0398 panel (280x480)");
  this->driver_.init();
}

void WeAct3_7Epaper::dump_config() {
  ESP_LOGCONFIG(TAG, "WeAct 3.7'' e-Paper Display:");
  ESP_LOGCONFIG(TAG, "  Resolution: 280×480 px");
}

void WeAct3_7Epaper::update() {
  this->driver_.clear_frame();
  this->driver_.write_frame(this->buffer_, this->get_width_internal(), this->get_height_internal());
  this->driver_.refresh();
}

void WeAct3_7Epaper::draw_absolute_pixel_internal(int x, int y, Color color) {
  if (x < 0 || x >= 280 || y < 0 || y >= 480) return;
  // 0 = white, 1 = black
  this->buffer_[y * 280 + x] = color.is_on() ? 0 : 1;
}

}  // namespace weact3_7_epaper
}  // namespace esphome
