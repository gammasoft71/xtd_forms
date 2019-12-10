#include <xtd/forms/native/timer.hpp>
#include "../../../include/xtd/forms/application.hpp"
#include "../../../include/xtd/forms/timer.hpp"

using namespace xtd;
using namespace xtd::forms;

void timer::enabled(bool enabled) {
  if (!application::message_loop()) return;
  if (this->enabled_ != enabled) {
    this->enabled_ = enabled;
    if (this->enabled_ == true)
      this->handle_ = native::timer::create(this->interval_, {*this, &timer::on_tick});
    else
      native::timer::destroy(this->handle_);
  }
}

void timer::interval(int32_t interval) {
  if (!application::message_loop()) return;
  if (this->interval_ != interval) {
    this->interval_ = interval;
    
    if (this->enabled_ == true) {
      this->stop();
      this->start();
    }
  }
}

void timer::on_tick(const event_args& e) {
  this->tick(*this, e);
}
