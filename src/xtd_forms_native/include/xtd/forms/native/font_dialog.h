#pragma once
#include <cstdint>
#include <xtd/delegate.h>
#include <xtd/static.h>
#include <xtd/drawing/color.h>
#include <xtd/drawing/font.h>

namespace xtd {
  namespace forms {
    namespace native {
      class font_dialog static_ {
      public:
        static bool run_dialog(intptr_t hwnd, drawing::font& font, drawing::color& color, size_t options, size_t min_size, size_t max_size, bool show_color);
        static void run_sheet(xtd::delegate<void(bool)> on_dialog_closed, intptr_t hwnd, drawing::font& font, drawing::color& color, size_t options, size_t min_size, size_t max_size, bool show_color);
      };
    }
  }
}
