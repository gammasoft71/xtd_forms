#include "../../../include/xtd/forms/button.hpp"
#include "../../../include/xtd/forms/form.hpp"
#include <xtd/diagnostics/cdebug.hpp>
#include <xtd/forms/native/window_button.hpp>

using namespace std;
using namespace xtd;
using namespace xtd::forms;

button::button() {
  this->make_control(*this);
}

button& button::operator=(const button& value) {
  this->button_base::operator=(value);
  return *this;
}

button& button::auto_size_mode(forms::auto_size_mode value) {
  this->set_auto_size_mode(value);
  return *this;
}

button& button::dialog_result(forms::dialog_result dialog_result) {
  if (this->data_->dialog_result_ != dialog_result)
    this->data_->dialog_result_ = dialog_result;
  return *this;
}

forms::create_params button::create_params() const {
  forms::create_params create_params = this->button_base::create_params();
  
  create_params.style(create_params.style() | BS_PUSHBUTTON);
  
  return create_params;
}

void button::on_click(const event_args& e) {
  this->control::on_click(e);
  if (this->data_->dialog_result_ != forms::dialog_result::none &&  dynamic_cast<form*>(&this->top_level_control()) != nullptr && static_cast<form&>(this->top_level_control()).modal()) {
    static_cast<form&>(this->top_level_control()).dialog_result(this->dialog_result());
    static_cast<form&>(this->top_level_control()).close();
  }
}
