#include <xtd/xtd.forms>

using namespace xtd;
using namespace xtd::forms;

int main() {
  main_menu menu;
  
  menu.menu_items().push_back("File");
  menu.menu_items().push_back("Edit");
  menu.menu_items().push_back("View");
  
  form form_main;
  form_main.text("Manual tests");
  //form_main.menu(menu);

  application::run(form_main);
}
