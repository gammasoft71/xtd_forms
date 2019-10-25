#include <xtd/forms/native/radio_button.hpp>
#include "wx_radio_button.hpp"

using namespace xtd;
using namespace xtd::drawing;
using namespace xtd::forms::native;

bool radio_button::checked(intptr_t control) {
  if (control == 0) return false;
  if (dynamic_cast<wxRadioButton*>(reinterpret_cast<control_handler*>(control)->control()) != nullptr)
    return static_cast<wxRadioButton*>(reinterpret_cast<control_handler*>(control)->control())->GetValue();
  return static_cast<wxToggleButton*>(reinterpret_cast<control_handler*>(control)->control())->GetValue();
}

void radio_button::checked(intptr_t control, bool checked) {
  if (control == 0) return;
  wx_radio_button* radio_button = reinterpret_cast<wx_radio_button*>(control);
  if (dynamic_cast<wxRadioButton*>(radio_button->control()) != nullptr) {
    radio_button->hiden_radio_button->SetValue(!checked);
    static_cast<wxRadioButton*>(radio_button->control())->SetValue(checked);
  } else {
    static_cast<wxToggleButton*>(radio_button->control())->SetValue(checked);
  }
}