#include <xtd/forms/native/image_list.hpp>
#include <xtd/drawing/bitmap.hpp>
#include "../../../include/xtd/forms/image_list.hpp"

using namespace xtd;
using namespace xtd::forms;

image_list::image_list() {
  data_->handle_ = native::image_list::create(data_->image_size_);
  data_->images_.item_added += [&](size_t pos, drawing::image& item) {
    if (data_->image_size_ != item.size()) item = drawing::bitmap(item, data_->image_size_);
    native::image_list::insert_item(data_->handle_, pos, item);
  };
  
  data_->images_.item_erased += [&](size_t pos, const drawing::image& item) {
    native::image_list::delete_item(data_->handle_, pos);
  };
  
  data_->images_.item_updated += [&](size_t pos, drawing::image& item) {
    if (data_->image_size_ != item.size()) item = drawing::bitmap(item, data_->image_size_);
    native::image_list::update_item(data_->handle_, pos, item);
  };
}

image_list::~image_list() {
  images().clear();
  native::image_list::destroy(data_->handle_);
}

void image_list::image_size(const drawing::size& value) {
  if (value.width() < 16 || value.width() > 256 || value.height() < 16 || value.height() > 256) throw std::invalid_argument("The values for with and heignt must be between 16 and 256.");
  if (data_->image_size_ != value) {
    data_->image_size_ = value;
    native::image_list::destroy(data_->handle_);
    data_->handle_ = native::image_list::create(data_->image_size_);
  }
}