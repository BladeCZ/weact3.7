#pragma once
#include "esphome/core/component.h"
#include "esphome/components/display/display_buffer.h"
#include "il0398.h"

namespace esphome {
namespace weact3_7_epaper {

class WeAct3_7Epaper : public display::DisplayBuffer, public Component {
 public:
  void setup() override;
  void update() override;
  void dump_config() override;
  display::DisplayType get_display_type() override { return display::DisplayType::EPAPER; }

 protected:
  void draw_absolute_pixel_internal(int x, int y, Color color) override;
  void display_();
  IL0398 driver_;
};

}  // namespace weact3_7_epaper
}  // namespace esphome
