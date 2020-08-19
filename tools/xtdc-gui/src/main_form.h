/// @file
/// @brief Contains main_form class.
#pragma once
#include "project_type_item_control.h"
#include "project_type_items_control.h"
#include "xtd_example_item.h"
#include <memory>
#include <vector>
#include <xtd/forms/button.h>
#include <xtd/forms/check_box.h>
#include <xtd/forms/choice.h>
#include <xtd/forms/form.h>
#include <xtd/forms/label.h>
#include <xtd/forms/list_box.h>
#include <xtd/forms/panel.h>
#include <xtd/forms/picture_box.h>
#include <xtd/forms/tab_control.h>
#include <xtd/forms/tab_page.h>
#include <xtd/forms/text_box.h>

namespace xtdc_gui {
  /// @brief Represents the main form
  class main_form : public xtd::forms::form {
  public:
    /// @brief Initializes a new instance of the main_form class.
    main_form();

    // The main entry point for the application.
    static void main();
    
  private:
    void add_to_create_recent_projects(size_t create_project_items_index);
    void add_to_open_recent_projects(const std::string& project_path);
    void delete_from_create_recent_projects(size_t create_project_items_index);
    void delete_from_open_recent_projects(const std::string& project_path);
    void init();
    void init_create_create_recent_projects_list_box();
    void init_startup_open_recent_projects_list_box();
    void new_project(const std::string& project_path, size_t project_type_items_index);
    void new_project(const std::string& project_path, project_type type, project_language language, project_sdk sdk);
    void open_project(const std::string& project_path);
    void run_project(const std::string& project_path);

    xtd::forms::panel startup_panel_;
    xtd::forms::label startup_title_label_;
    xtd::forms::label startup_open_recent_project_title_label_;
    xtd::forms::list_box startup_open_recent_projects_list_box_;
    xtd::forms::label startup_get_started_title_label_;
    xtd::forms::button startup_open_project_button_;
    xtd::forms::button startup_run_project_button_;
    xtd::forms::button startup_new_project_button_;
    xtd::forms::button startup_open_xtd_examples_button_;

    xtd::forms::panel open_xtd_examples_panel_;
    xtd::forms::label open_xtd_examples_title_label_;
    xtd::forms::tab_control open_xtd_example_tab_control_;
    xtd::forms::tab_page open_xtd_example_console_tab_page_;
    xtd::forms::tab_page open_xtd_example_forms_tab_page_;
    xtd::forms::tab_page open_xtd_example_tunit_tab_page_;
    xtd::forms::picture_box open_xtd_example_console_picture_box_;
    xtd::forms::picture_box open_xtd_example_forms_picture_box_;
    xtd::forms::picture_box open_xtd_example_tunit_picture_box_;
    xtd::forms::label open_xtd_example_console_title_label_;
    xtd::forms::label open_xtd_example_forms_title_label_;
    xtd::forms::label open_xtd_example_tunit_title_label_;
    xtd::forms::list_box open_xtd_example_console_list_box_;
    xtd::forms::list_box open_xtd_example_forms_list_box_;
    xtd::forms::list_box open_xtd_example_tunit_list_box_;
    xtd::forms::text_box open_xtd_examples_information_text_box_;
    xtd::forms::picture_box open_xtd_examples_information_picture_box_;

    xtd::forms::panel create_panel_;
    xtd::forms::label create_title_label_;
    xtd::forms::label create_recent_project_title_label_;
    xtd::forms::list_box create_create_recent_projects_list_box_;
    xtd::forms::choice create_language_choice_;
    xtd::forms::choice create_platform_choice_;
    xtd::forms::choice create_type_choice_;
    project_type_items_control create_project_type_items_control_;

    xtd::forms::panel configure_panel_;
    xtd::forms::label configure_title_label_;
    xtd::forms::label configure_project_type_title_label_;
    xtd::forms::label configure_project_name_label_;
    xtd::forms::text_box configure_project_name_text_box_;
    xtd::forms::label configure_project_location_label_;
    xtd::forms::text_box configure_project_location_text_box_;
    xtd::forms::button configure_project_location_button_;

    xtd::forms::check_box auto_close_check_box_;
    xtd::forms::button previous_button_;
    xtd::forms::button next_button_;
    
    size_t current_project_type_index_ = -1;
    size_t current_open_xtd_example_console_list_box_index_ = 0;
    size_t current_open_xtd_example_forms_list_box_index_ = 0;
    size_t current_open_xtd_example_tunit_list_box_index_ = 0;
    std::vector<xtd_example_item> xtd_console_examples_ {
      {"Console - background color", "shows how to set console background color.", {"xtd_console/console_background_color"}},
      {"Console - beep", "shows how to use console beep.", {"xtd_console/console_beep"}},
      {"Console - buffer", "shows how to use console buffer.\n\nThis code produces the following output:\n\nThe current buffer height is 300 rows.\nThe current buffer width is 85 columns.", {"xtd_console/console_buffer"}},
      {"Console - color", "shows how to set background and foreground color.", {"xtd_console/console_color"}},
      {"Console - cursor", "shows how to use console cursor position.\n\nThis code produces the following output:\n\n+---+\n|   |\n|   |\n|   |\n+---+\n\nAll done!", {"xtd_console/console_cursor"}},
      {"Console - in out", "shows how to use in and out stream properties.", {"xtd_console/console_in_out"}},
      {"Console - read line", "shows how to use read line.", {"xtd_console/console_read_line"}},
      {"Hello world - hello world (console)", "The classic first \"Hello, World!\" console application.\n\nThis code produces the following output with colors :\n\nHello, World!", {"xtd_console/hello_world_console"}},
      {"other - song", "Show how to play song with beep.", {"xtd_console/console_song"}},
    };
    std::vector<xtd_example_item> xtd_forms_examples_ {
      {"Application - application", "shows how to create an application with xtd::forms::application class.", {"xtd_forms/applications/application"}},
      {"Application - application context", "shows how to create an application with xtd::forms::application and xtd::forms::application_context classes.", {"xtd_forms/applications/application_context"}},
      {"Application - enable dark mode", "shows how to enbale dark mode with xtd::forms::application class.", {"xtd_forms/applications/application_enable_dark_mode"}},
      {"Application - enable light mode", "shows how to enbale light mode with xtd::forms::application class.", {"xtd_forms/applications/application_enable_light_mode"}},
      {"Application - icon", "shows how to set an application icon with xtd cmake helper : application_icon.", {"xtd_forms/applications/application_icon"}},
      {"Common controls - button", "represents a xtd::forms::button control.", {"xtd_forms/common_controls/button"}},
      {"Common controls - buttons", "shows how to create a button with xtd::froms::buttons factory class.", {"xtd_forms/common_controls/buttons"}},
      {"Common controls - check box", "represents a Windows xtd::forms::check_box control.", {"xtd_forms/common_controls/check_box"}},
      {"Common controls - check boxes", "shows how to create a check box with xtd::froms::check_boxes factory class", {"xtd_forms/common_controls/check_boxes"}},
      {"Common controls - checked list box", "represents a Windows control to display a list of check box.", {"xtd_forms/common_controls/checked_list_box"}},
      {"Common controls - choice", "represents a Windows xtd::forms::choice control.", {"xtd_forms/common_controls/choice"}},
      {"Common controls - combo box", "represents a Windows xtd::forms::combo_box control.", {"xtd_forms/common_controls/combo_box"}},
      {"Common controls - command link button", "represents a Windows xtd::forms::command_link_button control.", {"xtd_forms/common_controls/command_link_button"}},
      {"Common controls - control", "defines the base class for controls, which are components with visual representation.", {"xtd_forms/common_controls/control"}},
      {"Common controls - domain up down", "represents a Windows spin box (also known as an up-down control) that displays string values.", {"xtd_forms/common_controls/domain_up_down"}},
      {"Common controls - label", " represents a standard Windows xtd::forms::label.", {"xtd_forms/common_controls/label"}},
      {"Common controls - list box", "represents a Windows control to display a list of items.", {"xtd_forms/common_controls/list_box"}},
      {"Common controls - nunmeric up down", "represents a Windows spin box (also known as an up-down control) that displays numeric values.", {"xtd_forms/common_controls/numeric_up_down"}},
      {"Common controls - picture box", "represents a Windows picture box control for displaying an image.", {"xtd_forms/common_controls/picture_box"}},
      {"Common controls - progress bar", "represents a Windows xtd::forms::progress_bar control.", {"xtd_forms/common_controls/progress_bar"}},
      {"Common controls - radio button", "enables the user to select a single option from a group of choices when paired with other xtd::forms::radio_button controls.", {"xtd_forms/common_controls/radio_button"}},
      {"Common controls - radio buttons", "shows how to create a radio button with xtd::froms::radio_buttons factory class", {"xtd_forms/common_controls/radio_buttons"}},
      {"Common controls - text box", "represents a Windows xtd::forms::text_box control.", {"xtd_forms/common_controls/text_box"}},
      {"Common controls - track bar", "represents a standard Windows xtd::forms::track_bar.", {"xtd_forms/common_controls/track_bar"}},
      {"Common controls - up down button", "represents a Windows spin button.", {"xtd_forms/common_controls/up_down_button"}},
      {"Common controls - user control", "defines the base class for user controls.", {"xtd_forms/common_controls/user_control"}},
      {"Common dialogs - about dialog", "represents a common dialog box that displays about box.", {"xtd_forms/common_dialogs/about_dialog"}},
      {"Common dialogs - color dialog", "represents a common dialog box that displays available colors along with controls that enable the user to define custom colors.", {"xtd_forms/common_dialogs/color_dialog"}},
      {"Common dialogs - folder browser dialog", "prompts the user to select a folder.", {"xtd_forms/common_dialogs/folder_browser_dialog"}},
      {"Common dialogs - font dialog", "prompts the user to choose a font from among those installed on the local computer.", {"xtd_forms/common_dialogs/font_dialog"}},
      {"Common dialogs - input box", "prompts the user to input text.", {"xtd_forms/common_dialogs/input_box"}},
      {"Common dialogs - message box", "displays a message window, also known as a dialog box, which presents a message to the user. It is a modal window, blocking other actions in the application until the user closes it. A MessageBox can contain text, buttons, and symbols that inform and instruct the user.", {"xtd_forms/common_dialogs/message_box"}},
      {"Common dialogs - open file dialog", "displays a standard dialog box that prompts the user to open a file.", {"xtd_forms/common_dialogs/open_file_dialog"}},
      {"Common dialogs - save file dialog", "prompts the user to select a location for saving a file.", {"xtd_forms/common_dialogs/save_file_dialog"}},
      {"Components - background worker", "executes an operation on a separate thread.", {"xtd_forms/components/background_worker"}},
      {"Components - button images", "shows how to create a bitmap button with xtd::froms::button_images factory class.", {"xtd_forms/components/button_images"}},
      {"Components - cursor", "represents the image used to paint the mouse pointer.", {"xtd_forms/components/cursor"}},
      {"Components - image list", "provides methods to manage a collection of image objects.", {"xtd_forms/components/image_list"}},
      {"Components - screen", "represents a display device or multiple display devices on a single system.", {"xtd_forms/components/screen"}},
      {"Components - settings", "represents settings application.", {"xtd_forms/components/settings_example"}},
      {"Components - settings2", "represents settings application.", {"xtd_forms/components/settings_example2"}},
      {"Components - system images", "demonstrates the use of xtd::drawing::system_images class.", {"xtd_forms/components/system_images"}},
      {"Components - timer", "implements a timer that raises an event at user-defined intervals.", {"xtd_forms/components/timer"}},
      {"Containers - form", "represents a window or dialog box that makes up an application's user interface.", {"xtd_forms/containers/form"}},
      {"Containers - group box", "represents a Windows control that displays a frame around a group of controls with an optional caption.", {"xtd_forms/containers/group_box"}},
      {"Containers - panel", "used to group collections of controls.", {"xtd_forms/containers/panel"}},
      {"Containers - tab control", "manages a related set of tab pages.", {"xtd_forms/containers/tab_control"}},
      {"Custom controls - line", "demonstrates the use of xtd::forms::user_controlcontrol to draw simple lines.", {"xtd_forms/custom_controls/line"}},
      {"Custom controls - numeric text box", "demonstrates how to customize xtd::forms::text_box control.", {"xtd_forms/custom_controls/numeric_text_box"}},
      {"Custom dialogs - user dialog", "demonstrates the use of xtd::forms::form as dialog.", {"xtd_forms/custom_dialogs/user_dialog"}},
      {"Event - click", "demonstrates the use of xtd::forms::form control and click event.", {"xtd_forms/events/form_click"}},
      {"Event - enable changed event", "demonstrates the use of enable_changed event.", {"xtd_forms/events/enable_changed_event"}},
      {"Event - font changed event", "demonstrates the use of font_changed event.", {"xtd_forms/events/font_changed_event"}},
      {"Event - form events", "demonstrates some events received by xtd::forms::form.", {"xtd_forms/events/form_and_messages"}},
      {"Event - idle", "shows how to create an application with xtd::forms::application class and idle event.", {"xtd_forms/events/application_idle"}},
      {"Event - key events", "demonstrates the use of mouse events.", {"xtd_forms/events/key_events"}},
      {"Event - mouse events", "demonstrates the use of mouse events.", {"xtd_forms/events/mouse_events"}},
      {"Event - move form", "demonstrates the use of mouse events.", {"xtd_forms/events/move_form"}},
      {"Event - paint", "demonstrates paint event with xtd::forms::form.", {"xtd_forms/events/form_paint"}},
      {"Event - send message", "demonstrates how to send message to xtd::forms::form.", {"xtd_forms/events/send_message_to_form"}},
      {"Event - windows process", "demonstrates the use of wnd_proc method.", {"xtd_forms/events/wnd_proc"}},
      {"Games - game of life", "The Game of Life is not your typical computer game. It is a 'cellular automaton', and was invented by Cambridge mathematician John Conway.", {"xtd_forms/games/game_of_life"}},
      {"Games - minesweeper", "The goal of the game is to uncover all the squares that do not contain mines.", {"xtd_forms/games/minesweeper"}},
      {"Hello world - hello world (emoticons)", "The classic first \"Hello, World!\" with xtd::forms::emoticons component.", {"xtd_forms/hello_world_examples/hello_world_emoticons"}},
      {"Hello world - hello world (label)", "The classic first \"Hello, World!\" with xtd::forms::label control.", {"xtd_forms/hello_world_examples/hello_world_label"}},
      {"Hello world - hello world (message box)", "The classic first \"Hello, World!\" with xtd::forms::message_box dialog.", {"xtd_forms/hello_world_examples/hello_world_message_box"}},
      {"Hello world - hello world (paint)", "The classic first \"Hello, World!\" with GDI+ drawing objects.", {"xtd_forms/hello_world_examples/hello_world_paint"}},
      {"Menus and toolbars - menu", "provides a menu system for a form.", {"xtd_forms/menus_and_toolbars/menu"}},
      {"Other controls - dot matrix display", "represents a xtd::forms::fourteen_segment_display control.", {"xtd_forms/other_controls/dot_matrix_display"}},
      {"Other controls - fourteen segment display", "represents a xtd::forms::fourteen_segment_display control.", {"xtd_forms/other_controls/fourteen_segment_display"}},
      {"Other controls - lcd label", "represents a xtd::forms::lcd_label control.", {"xtd_forms/other_controls/lcd_label"}},
      {"Other controls - nine segment display", "represents a xtd::forms::nine_segment_display control.", {"xtd_forms/other_controls/fourteen_nine_display"}},
      {"Other controls - seven segment display", "represents a xtd::forms::seven_segment_display control.", {"xtd_forms/other_controls/seven_segment_display"}},
      {"Other controls - sixteen segment display", "represents a xtd::forms::sixteen_segment_display control.", {"xtd_forms/other_controls/sixteen_segment_display"}},
      {"Other controls - switch button", "represents a xtd::forms::switch_button control.", {"xtd_forms/other_controls/switch_button"}},
      {"Picker controls - color picker", "represents a Windows control that allows the user to select and display a color.", {"xtd_forms/picker_controls/color_picker"}},
      {"Picker controls - date time_picker", "represents a Windows control that allows the user to select a date and a time and to display the date and time with a specified format.", {"xtd_forms/picker_controls/date_time_picker"}},
      {"Picker controls - font picker", "represents a Windows control that allows the user to select and display a font.", {"xtd_forms/picker_controls/font_picker"}},
    };
    std::vector<xtd_example_item> xtd_tunit_examples_ {
      {"assert - abort", "Tshows how to use assert abort.", "xtd_tunit/assert_abort"},
      {"assert - abort", "Tshows how to use assert abort.", "xtd_tunit/assert_abort"},
      {"Hello world - hello world (assert)", "The classic first \"Hello, World!\" unit tests application.", "xtd_tunit/hello_world_tunit"},
    };
  };
}