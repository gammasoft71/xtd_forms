cmake_minimum_required(VERSION 3.3)

project(application_icon)
find_package(xtd.forms REQUIRED)
application_icon(resources/xtd_forms)
add_sources(src/application_icon.cpp)
target_type(GUI_APPLICATION)
