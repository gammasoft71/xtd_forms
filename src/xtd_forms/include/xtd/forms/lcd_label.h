#include <codecvt>
#include "control.h"
#include "dot_matrix_display.h"
#include "lcd_style.h"
#include "nine_segment_display.h"
#include "seven_segment_display.h"
#include "fourteen_segment_display.h"
#include "sixteen_segment_display.h"

namespace xtd {
  namespace forms {
    class lcd_label : public control {
      class idigit {
      public:
        ~idigit() = default;

        virtual wchar_t get_character() const = 0;
        virtual std::string get_valid_characters() const = 0;
        virtual int32_t get_thickness() const = 0;

        virtual void set_background_digit_transparency(double value) = 0;
        virtual void set_character(wchar_t value) = 0;
        virtual void set_segment_style(forms::segment_style value) = 0;
        virtual void set_dot_matrix_style(forms::dot_matrix_style value) = 0;
        virtual void set_show_background_digit(bool value) = 0;
        virtual void set_thickness(int32_t value) = 0;
      };

      class dot_matrix_display_digit : public dot_matrix_display, public idigit {
      public:
        dot_matrix_display_digit() = default;
        
        wchar_t get_character() const override {return character_;}
        std::string get_valid_characters() const override {return "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz=+-*/%\\_°\"'[](){}<>| .,:;!?&$€";}
        int32_t get_thickness() const override {return dot_matrix_display::thickness();}
        
        void set_background_digit_transparency(double value) override {dot_matrix_display::background_dot_transparency(value);}
        void set_character(wchar_t value) override {
          static std::map<wchar_t, dot_matrix_display::dot_collection> characters {
            {'0', {{2, 0}, {3, 0}, {4, 0}, {1, 1}, {5, 1}, {1, 2}, {4, 2}, {5, 2}, {1, 3}, {3, 3}, {5, 3}, {1, 4}, {2, 4}, {5, 4}, {1, 5}, {5, 5}, {2, 6}, {3, 6}, {4, 6}}},
            {'1', {{3, 0}, {2, 1}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}}},
            {'2', {{2, 0}, {3, 0}, {4, 0}, {1, 1}, {5, 1}, {5, 2}, {4, 3}, {3, 4}, {2, 5}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}}},
            {'3', {{2, 0}, {3, 0}, {4, 0}, {1, 1}, {5, 1}, {5, 2}, {2, 3}, {3, 3}, {4, 3}, {5, 4}, {1, 5}, {5, 5}, {2, 6}, {3, 6}, {4, 6}}},
            {'4', {{1, 0}, {5, 0}, {1, 1}, {5, 1}, {1, 2}, {5, 2}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {5, 4}, {5, 5}, {5, 6}}},
            {'5', {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {1, 1}, {1, 2}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 4}, {5, 5}, {1, 6}, {2, 6}, {3, 6}, {4, 6}}},
            {'6', {{2, 0}, {3, 0}, {4, 0}, {1, 1}, {1, 2}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {1, 4}, {5, 4}, {1, 5}, {5, 5}, {2, 6}, {3, 6}, {4, 6}}},
            {'7', {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {5, 1}, {5, 2}, {4, 3}, {4, 4}, {3, 5}, {3, 6}}},
            {'8', {{2, 0}, {3, 0}, {4, 0}, {1, 1}, {5, 1}, {1, 2}, {5, 2}, {2, 3}, {3, 3}, {4, 3}, {1, 4}, {5, 4}, {1, 5}, {5, 5}, {2, 6}, {3, 6}, {4, 6}}},
            {'9', {{2, 0}, {3, 0}, {4, 0}, {1, 1}, {5, 1}, {1, 2}, {5, 2}, {2, 3}, {3, 3}, {4, 3}, {5, 4}, {5, 5}, {2, 6}, {3, 6}, {4, 6}}},
            {'A', {{2, 0}, {3, 0}, {4, 0}, {1, 1}, {5, 1}, {1, 2}, {5, 2}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {1, 4}, {5, 4}, {1, 5}, {5, 5}, {1, 6}, {5, 6}}},
            {'B', {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {1, 1}, {5, 1}, {1, 2}, {5, 2}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {1, 4}, {5, 4}, {1, 5}, {5, 5}, {1, 6}, {2, 6}, {3, 6}, {4, 6}}},
            {'C', {{2, 0}, {3, 0}, {4, 0}, {1, 1}, {5, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {2, 6}, {3, 6}, {5, 5}, {4, 6}}},
            {'D', {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {1, 1}, {5, 1}, {1, 2}, {5, 2}, {1, 3}, {5, 3}, {1, 4}, {5, 4}, {1, 5}, {5, 5}, {1, 6}, {2, 6}, {3, 6}, {4, 6}}},
            {'E', {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {1, 1}, {1, 2}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {1, 4}, {1, 5}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}}},
            {'F', {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {1, 1}, {1, 2}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {1, 4}, {1, 5}, {1, 6}}},
            {'G', {{2, 0}, {3, 0}, {4, 0}, {1, 1}, {1, 2}, {1, 3}, {4, 3}, {5, 3}, {1, 4}, {5, 4}, {1, 5}, {5, 5}, {2, 6}, {3, 6}, {4, 6}}},
            {'H', {{1, 0}, {5, 0}, {1, 1}, {5, 1}, {1, 2}, {5, 2}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {1, 4}, {5, 4}, {1, 5}, {5, 5}, {1, 6}, {5, 6}}},
            {'I', {{3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}}},
            {'J', {{5, 0}, {5, 1}, {5, 2}, {5, 3}, {1, 4}, {5, 4}, {1, 5}, {5, 5}, {2, 6}, {3, 6}, {4, 6}}},
            {'K', {{1, 0}, {5, 0}, {1, 1}, {4, 1}, {1, 2}, {3, 2}, {1, 3}, {2, 3}, {1, 4}, {3, 4}, {1, 5}, {4, 5}, {1, 6}, {5, 6}}},
            {'L', {{1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}}},
            {'M', {{1, 0}, {5, 0}, {1, 1}, {2, 1}, {4, 1}, {5, 1}, {1, 2}, {3, 2}, {5, 2}, {1, 3}, {5, 3}, {1, 4}, {5, 4}, {1, 5}, {5, 5}, {1, 6}, {5, 6}}},
            {'N', {{1, 0}, {5, 0}, {1, 1}, {2, 1}, {5, 1}, {1, 2}, {3, 2}, {5, 2}, {1, 3}, {4, 3}, {5, 3}, {1, 4}, {5, 4}, {1, 5}, {5, 5}, {1, 6}, {5, 6}}},
            {'O', {{2, 0}, {3, 0}, {4, 0}, {1, 1}, {5, 1}, {1, 2}, {5, 2}, {1, 3}, {5, 3}, {1, 4}, {5, 4}, {1, 5}, {5, 5}, {2, 6}, {3, 6}, {4, 6}}},
            {'P', {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {1, 1}, {5, 1}, {1, 2}, {5, 2}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {1, 4}, {1, 5}, {1, 6}}},
            {'Q', {{2, 0}, {3, 0}, {4, 0}, {1, 1}, {5, 1}, {1, 2}, {5, 2}, {1, 3}, {5, 3}, {1, 4}, {5, 4}, {1, 5}, {4, 5}, {2, 6}, {3, 6}, {5, 6}}},
            {'R', {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {1, 1}, {5, 1}, {1, 2}, {5, 2}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {1, 4}, {3, 4}, {1, 5}, {4, 5}, {1, 6}, {5, 6}}},
            {'S', {{2, 0}, {3, 0}, {4, 0}, {1, 1}, {5, 1}, {1, 2}, {2, 3}, {3, 3}, {4, 3}, {5, 4}, {1, 5}, {5, 5}, {2, 6}, {3, 6}, {4, 6}}},
            {'T', {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}}},
            {'U', {{1, 0}, {5, 0}, {1, 1}, {5, 1}, {1, 2}, {5, 2}, {1, 3}, {5, 3}, {1, 4}, {5, 4}, {1, 5}, {5, 5}, {2, 6}, {3, 6}, {4, 6}}},
            {'V', {{1, 0}, {5, 0}, {1, 1}, {5, 1}, {1, 2}, {5, 2}, {2, 3}, {4, 3}, {2, 4}, {4, 4}, {3, 5}, {3, 6}}},
            {'W', {{1, 0}, {5, 0}, {1, 1}, {5, 1}, {1, 2}, {3, 2}, {5, 2}, {1, 3}, {3, 3}, {5, 3}, {1, 4}, {3, 4}, {5, 4}, {1, 5}, {2, 5}, {4, 5}, {5, 5}, {1, 6}, {5, 6}}},
            {'X', {{1, 0}, {5, 0}, {1, 1}, {5, 1}, {2, 2}, {4, 2}, {3, 3}, {2, 4}, {4, 4}, {1, 5}, {5, 5}, {1, 6}, {5, 6}}},
            {'Y', {{1, 0}, {5, 0}, {1, 1}, {5, 1}, {2, 2}, {4, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}}},
            {'Z', {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {5, 1}, {4, 2}, {3, 3}, {2, 4}, {1, 5}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}}},
            {'a', {{2, 2}, {3, 2}, {4, 2}, {5, 3}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {1, 5}, {5, 5}, {2, 6}, {3, 6}, {4, 6}, {5, 6}}},
            {'b', {{1, 0}, {1, 1}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {1, 3}, {5, 3}, {1, 4}, {5, 4}, {1, 5}, {5, 5}, {1, 6}, {2, 6}, {3, 6}, {4, 6}}},
            {'c', {{2, 2}, {3, 2}, {4, 2}, {5, 2}, {1, 3}, {1, 4}, {1, 5}, {2, 6}, {3, 6}, {4, 6}, {5, 6}}},
            {'d', {{5, 0}, {5, 1}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {1, 3}, {5, 3}, {1, 4}, {5, 4}, {1, 5}, {5, 5}, {2, 6}, {3, 6}, {4, 6}, {5, 6}}},
            {'e', {{2, 2}, {3, 2}, {4, 2}, {1, 3}, {5, 3}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {1, 5}, {2, 6}, {3, 6}, {4, 6}}},
            {'f', {{3, 0}, {4, 0}, {2, 1}, {2, 2}, {3, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}}},
            {'g', {{2, 0}, {3, 0}, {4, 0}, {1, 1}, {5, 1}, {1, 2}, {5, 2}, {1, 3}, {5, 3}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {5, 5}, {2, 6}, {3, 6}, {4, 6}}},
            {'h', {{1, 0}, {1, 1}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {1, 3}, {5, 3}, {1, 4}, {5, 4}, {1, 5}, {5, 5}, {1, 6}, {5, 6}}},
            {'i', {{3, 0}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}}},
            {'j', {{4, 0}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {2, 6}, {3, 6}}},
            {'k', {{1, 0}, {1, 1}, {1, 2}, {5, 2}, {1, 3}, {4, 3}, {1, 4}, {2, 4}, {3, 4}, {1, 5}, {4, 5}, {1, 6}, {5, 6}}},
            {'l', {{3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {4, 6}}},
            {'m', {{2, 2}, {4, 2}, {1, 3}, {3, 3}, {5, 3}, {1, 4}, {3, 4}, {5, 4}, {1, 5}, {3, 5}, {5, 5}, {1, 6}, {3, 6}, {5, 6}}},
            {'n', {{2, 2}, {3, 2}, {4, 2}, {1, 3}, {5, 3}, {1, 4}, {5, 4}, {1, 5}, {5, 5}, {1, 6}, {5, 6}}},
            {'o', {{2, 2}, {3, 2}, {4, 2}, {1, 3}, {5, 3}, {1, 4}, {5, 4}, {1, 5}, {5, 5}, {2, 6}, {3, 6}, {4, 6}}},
            {'p', {{1, 1}, {2, 1}, {3, 1}, {4, 1}, {1, 2}, {5, 2}, {1, 3}, {5, 3}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {1, 5}, {1, 6}}},
            {'q', {{2, 1}, {3, 1}, {4, 1}, {5, 1}, {1, 2}, {5, 2}, {1, 3}, {5, 3}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {5, 5}, {5, 6}}},
            {'r', {{2, 2}, {3, 2}, {4, 2}, {5, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}}},
            {'s', {{2, 2}, {3, 2}, {4, 2}, {5, 2}, {1, 3}, {2, 4}, {3, 4}, {4, 4}, {5, 5}, {1, 6}, {2, 6}, {3, 6}, {4, 6}}},
            {'t', {{3, 0}, {3, 1}, {2, 2}, {3, 2}, {4, 2}, {3, 3}, {3, 4}, {3, 5}, {4, 6}, {5, 6}}},
            {'u', {{1, 2}, {5, 2}, {1, 3}, {5, 3}, {1, 4}, {5, 4}, {1, 5}, {5, 5}, {2, 6}, {3, 6}, {4, 6}}},
            {'v', {{1, 2}, {5, 2}, {1, 3}, {5, 3}, {2, 4}, {4, 4}, {2, 5}, {4, 5}, {3, 6}}},
            {'w', {{1, 2}, {3, 2}, {5, 2}, {1, 3}, {3, 3}, {5, 3}, {1, 4}, {3, 4}, {5, 4}, {1, 5}, {3, 5}, {5, 5}, {2, 6}, {4, 6}}},
            {'x', {{1, 2}, {5, 2}, {2, 3}, {4, 3}, {3, 4}, {2, 5}, {4, 5}, {1, 6}, {5, 6}}},
            {'y', {{1, 1}, {5, 1}, {1, 2}, {5, 2}, {1, 3}, {5, 3}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {5, 5}, {2, 6}, {3, 6}, {4, 6}}},
            {'z', {{1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {4, 3}, {3, 4}, {2, 5}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}}},
            {'=', {{1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}}},
            {'+', {{3, 1}, {3, 2}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {3, 4}, {3, 5}}},
            {'-', {{1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}}},
            {'*', {{3, 0}, {1, 1}, {3, 1}, {5, 1}, {2, 2}, {3, 2}, {4, 2}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {2, 4}, {3, 4}, {4, 4}, {1, 5}, {3, 5}, {5, 5}, {3, 6}}},
            {'/', {{5, 1}, {4, 2}, {3, 3}, {2, 4}, {1, 5}}},
            {'%', {{1, 0}, {2, 0}, {1, 1}, {2, 1}, {5, 1}, {4, 2}, {3, 3}, {2, 4}, {1, 5}, {4, 5}, {5, 5}, {4, 6}, {5, 6}}},
            {'\\', {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}}},
            {'_', {{1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}}},
            {L'\u00B0', {{2, 0}, {3, 0}, {1, 1}, {4, 1}, {1, 2}, {4, 2}, {2, 3}, {3, 3}}},
            {'"', {{2, 0}, {5, 0}, {2, 1}, {5, 1}, {1, 2}, {4, 2}}},
            {'\'', {{3, 0}, {3, 1}, {2, 2}}},
            {'[', {{3, 0}, {4, 0}, {5, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {4, 6}, {5, 6}}},
            {']', {{1, 0}, {2, 0}, {3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {1, 6}, {2, 6}, {3, 6}}},
            {'(', {{4, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {4, 6}}},
            {')', {{2, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {2, 6}}},
            {'{', {{4, 0}, {5, 0}, {3, 1}, {3, 2}, {2, 3}, {3, 4}, {3, 5}, {4, 6}, {5, 6}}},
            {'}', {{1, 0}, {2, 0}, {3, 1}, {3, 2}, {4, 3}, {3, 4}, {3, 5}, {1, 6}, {2, 6}}},
            {'<', {{4, 1}, {3, 2}, {2, 3}, {3, 4}, {4, 5}}},
            {'>', {{2, 1}, {3, 2}, {4, 3}, {3, 4}, {2, 5}}},
            {'|', {{3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}}},
            {' ', {}},
            {'.', {{3, 6}}},
            {',', {{3, 5}, {2, 6}}},
            {':', {{3, 1}, {3, 5}}},
            {';', {{3, 2}, {3, 5}, {2, 6}}},
            {'!', {{3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 6}}},
            {'?', {{2, 0}, {3, 0}, {4, 0}, {1, 1}, {5, 1}, {5, 2}, {4, 3}, {3, 4}, {3, 6}}},
            {'&', {{2, 0}, {3, 0}, {1, 1}, {4, 1}, {1, 2}, {4, 2}, {2, 3}, {3, 3}, {5, 3}, {1, 4}, {4, 4}, {1, 5}, {4, 5}, {2, 6}, {3, 6}, {5, 6}}},
            {'$', {{3, 0}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {1, 2}, {3, 2}, {2, 3}, {3, 3}, {4, 3}, {3, 4}, {5, 4}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {3, 6}}},
            {L'\u20AC', {{3, 0}, {4, 0}, {5, 0}, {2, 1}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {2, 3}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {2, 5}, {3, 6}, {4, 6}, {5, 6}}},
          };
          if (character_ != value) {
            if (characters.find(value) == characters.end()) throw std::invalid_argument(strings::format("Only characters : \"{}\" are valid", get_valid_characters()));
            character_ = value;
            dot_matrix_display::dots(characters[value]);
          }
        }
        void set_segment_style(forms::segment_style value) override {}
        void set_dot_matrix_style(forms::dot_matrix_style value) override {dot_matrix_display::dot_matrix_style(value);}
        void set_show_background_digit(bool value) override {dot_matrix_display::show_background_dot(value);}
        void set_thickness(int32_t value) override {dot_matrix_display::thickness(value);}
        
      private:
        wchar_t character_ = ' ';
      };

      class fourteen_segment_display_digit : public fourteen_segment_display, public idigit {
      public:
        fourteen_segment_display_digit() = default;
        
        wchar_t get_character() const override {return character_;}
        std::string get_valid_characters() const override {return "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz=+-*/\\_°\"'[]()| .,:";}
        int32_t get_thickness() const override {return fourteen_segment_display::thickness();}
        
        void set_background_digit_transparency(double value) override {fourteen_segment_display::background_segment_transparency(value);}
        void set_character(wchar_t value) override {
          static std::map<wchar_t, forms::segments> characters {
            {'0', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::f},
            {'1', forms::segments::b|forms::segments::c|forms::segments::j},
            {'2', forms::segments::a|forms::segments::b|forms::segments::d|forms::segments::e|forms::segments::g1|forms::segments::g2},
            {'3', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::g2},
            {'4', forms::segments::b|forms::segments::c|forms::segments::f|forms::segments::g1|forms::segments::g2},
            {'5', forms::segments::a|forms::segments::c|forms::segments::d|forms::segments::f|forms::segments::g1|forms::segments::g2},
            {'6', forms::segments::a|forms::segments::c|forms::segments::d|forms::segments::e| forms::segments::f|forms::segments::g1|forms::segments::g2},
            {'7', forms::segments::a|forms::segments::l|forms::segments::j},
            {'8', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::f|forms::segments::g1|segments::g2},
            {'9', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::f|forms::segments::g1|forms::segments::g2},
            {'A', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::e|forms::segments::f|forms::segments::g1|forms::segments::g2},
            {'B', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d |forms::segments::g2|forms::segments::i|forms::segments::l},
            {'C', forms::segments::a|forms::segments::d|forms::segments::e|forms::segments::f},
            {'D', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d |forms::segments::i|forms::segments::l},
            {'E', forms::segments::a|forms::segments::d|forms::segments::e|forms::segments::f|forms::segments::g1|forms::segments::g2},
            {'F', forms::segments::a|forms::segments::e|forms::segments::f|forms::segments::g1|forms::segments::g2},
            {'G', forms::segments::a|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::f|forms::segments::g2},
            {'H', forms::segments::b|forms::segments::c|forms::segments::e|forms::segments::f|forms::segments::g1|forms::segments::g2},
            {'I', forms::segments::a|forms::segments::d|forms::segments::i|forms::segments::l},
            {'J', forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e},
            {'K', forms::segments::e|forms::segments::f|forms::segments::g1|forms::segments::j|forms::segments::m},
            {'L', forms::segments::d|forms::segments::e|forms::segments::f},
            {'M', forms::segments::b|forms::segments::c|forms::segments::e|forms::segments::f|forms::segments::h|forms::segments::j},
            {'N', forms::segments::b|forms::segments::c|forms::segments::e|forms::segments::f|forms::segments::h|forms::segments::m},
            {'O', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::f},
            {'P', forms::segments::a|forms::segments::b|forms::segments::e|forms::segments::f|forms::segments::g1|forms::segments::g2},
            {'Q', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::f|forms::segments::m},
            {'R', forms::segments::a|forms::segments::b|forms::segments::e|forms::segments::f|forms::segments::g1|forms::segments::g2|forms::segments::m},
            {'S', forms::segments::a|forms::segments::c|forms::segments::d|forms::segments::g2|forms::segments::h},
            {'T', forms::segments::a|forms::segments::i|forms::segments::l},
            {'U', forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::f},
            {'V', forms::segments::e|forms::segments::f|forms::segments::j|forms::segments::k},
            {'W', forms::segments::b|forms::segments::c|forms::segments::e|forms::segments::f|forms::segments::k|forms::segments::m},
            {'X', forms::segments::h|forms::segments::j|forms::segments::k|forms::segments::m},
            {'Y', forms::segments::h|forms::segments::j|forms::segments::l},
            {'Z', forms::segments::a|forms::segments::d|forms::segments::j|forms::segments::k},
            {'a', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::g1|forms::segments::g2},
            {'b', forms::segments::d|forms::segments::e|forms::segments::f|forms::segments::g1|forms::segments::m},
            {'c', forms::segments::d|forms::segments::e|forms::segments::g1|forms::segments::g2},
            {'d', forms::segments::b|forms::segments::c|forms::segments::d|segments::g2|segments::k},
            {'e', forms::segments::a|forms::segments::d|forms::segments::e|forms::segments::f|forms::segments::g1},
            {'f', forms::segments::a|forms::segments::e|forms::segments::f|forms::segments::g1},
            {'g', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::h|forms::segments::g2},
            {'h', forms::segments::c|forms::segments::e|forms::segments::f|forms::segments::g1|forms::segments::g2},
            {'i', forms::segments::l},
            {'j', forms::segments::b|forms::segments::c|forms::segments::d},
            {'k', forms::segments::i|forms::segments::l|forms::segments::j|forms::segments::m},
            {'l', forms::segments::i|forms::segments::l},
            {'m', forms::segments::c|forms::segments::e|forms::segments::g1|forms::segments::g2|forms::segments::l},
            {'n', forms::segments::e|forms::segments::g1|forms::segments::m},
            {'o', forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::g1|forms::segments::g2},
            {'p', forms::segments::a|forms::segments::e|forms::segments::f|forms::segments::g1|forms::segments::j},
            {'q', forms::segments::a|forms::segments::b|forms::segments::f|forms::segments::g1|forms::segments::g2|forms::segments::m},
            {'r', forms::segments::e|forms::segments::g},
            {'s', forms::segments::a|forms::segments::c|forms::segments::d|forms::segments::g2|forms::segments::h},
            {'t', forms::segments::d|forms::segments::e|forms::segments::f|forms::segments::g1},
            {'u', forms::segments::c|forms::segments::d|forms::segments::e},
            {'v', forms::segments::e|forms::segments::k},
            {'w', forms::segments::c|forms::segments::e|forms::segments::k|forms::segments::m},
            {'x', forms::segments::h|forms::segments::j|forms::segments::k|forms::segments::m},
            {'y', forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::g2|forms::segments::i},
            {'z', forms::segments::a|forms::segments::d|forms::segments::j|forms::segments::k},
            {'=', forms::segments::d|forms::segments::g1|forms::segments::g2},
            {'+', forms::segments::g1|forms::segments::g2|forms::segments::i|forms::segments::l},
            {'-', forms::segments::g1|forms::segments::g2},
            {'*', forms::segments::g1|forms::segments::g2|forms::segments::h|forms::segments::i|forms::segments::j|forms::segments::k|forms::segments::l|forms::segments::m},
            {'/', forms::segments::j|forms::segments::k},
            {'\\', forms::segments::h|forms::segments::m},
            {'_', forms::segments::d},
            {L'\u00B0', forms::segments::a|forms::segments::b|forms::segments::f|forms::segments::g1|forms::segments::g2},
            {'"', forms::segments::b|forms::segments::f},
            {'\'', forms::segments::f},
            {'[', forms::segments::a|forms::segments::d|forms::segments::e|forms::segments::f},
            {']', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d},
            {'(', forms::segments::j|forms::segments::m},
            {')', forms::segments::h|forms::segments::k},
            {'|', forms::segments::i|forms::segments::l},
            {' ', forms::segments::none},
            {'.', forms::segments::dp},
            {',', forms::segments::k},
            {':', forms::segments::pc}
          };
          if (character_ != value) {
            if (characters.find(value) == characters.end()) throw std::invalid_argument(strings::format("Only characters : \"{}\" are valid", get_valid_characters()));
            character_ = value;
            fourteen_segment_display::value(characters[value]);
          }
        }
        void set_segment_style(forms::segment_style value) override {fourteen_segment_display::segment_style(value);}
        void set_dot_matrix_style(forms::dot_matrix_style value) override {}
        void set_show_background_digit(bool value) override {fourteen_segment_display::show_background_segment(value);}
        void set_thickness(int32_t value) override {seven_segment_display::thickness(value);}
        
      private:
        wchar_t character_ = ' ';
      };

      class nine_segment_display_digit : public nine_segment_display, public idigit {
      public:
        nine_segment_display_digit() = default;
        
        wchar_t get_character() const override {return character_;}
        std::string get_valid_characters() const override {return "0123456789ABCDEFGHIJLNOPQRSTUYabcdefghijlnopqrstuy=-_°\"'[]| .,:";}
        int32_t get_thickness() const override {return nine_segment_display::thickness();}
        
        void set_background_digit_transparency(double value) override {nine_segment_display::background_segment_transparency(value);}
        void set_character(wchar_t value) override {
          static std::map<wchar_t, forms::segments> characters {
            {'0', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::f},
            {'1', forms::segments::b|forms::segments::c},
            {'2', forms::segments::a|forms::segments::b|forms::segments::d|forms::segments::i},
            {'3', forms::segments::a|forms::segments::g|forms::segments::h|forms::segments::i},
            {'4', forms::segments::b|forms::segments::c|forms::segments::f|forms::segments::g},
            {'5', forms::segments::a|forms::segments::c|forms::segments::d|forms::segments::f|forms::segments::g},
            {'6', forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::g|forms::segments::h},
            {'7', forms::segments::a|forms::segments::e|forms::segments::h},
            {'8', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::f|forms::segments::g},
            {'9', forms::segments::a|forms::segments::b|forms::segments::f|forms::segments::g|forms::segments::i},
            {'A', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::e|forms::segments::f|forms::segments::g},
            {'a', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::g},
            {'B', forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::f|forms::segments::g},
            {'b', forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::f|forms::segments::g},
            {'C', forms::segments::a|forms::segments::d|forms::segments::e|forms::segments::f},
            {'c', forms::segments::d|forms::segments::e|forms::segments::g},
            {'D', forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::g},
            {'d', forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::g},
            {'E', forms::segments::a|forms::segments::d|forms::segments::e|forms::segments::f|forms::segments::g},
            {'e', forms::segments::a|forms::segments::b|forms::segments::d|forms::segments::e|forms::segments::f|forms::segments::g},
            {'F', forms::segments::a|forms::segments::e|forms::segments::f|forms::segments::g},
            {'f', forms::segments::a|forms::segments::e|forms::segments::f|forms::segments::g},
            {'G', forms::segments::a|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::f},
            {'g', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::f|forms::segments::g},
            {'H', forms::segments::b|forms::segments::c|forms::segments::e|forms::segments::f|forms::segments::g},
            {'h', forms::segments::c|forms::segments::e|forms::segments::f|forms::segments::g},
            {'I', forms::segments::b|forms::segments::c},
            {'i', forms::segments::c},
            {'J', forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e},
            {'j', forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e},
            {'L', forms::segments::d|forms::segments::e|forms::segments::f},
            {'l', forms::segments::d|forms::segments::e},
            {'N', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::e|forms::segments::f},
            {'n', forms::segments::c|forms::segments::e|forms::segments::g},
            {'O', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::f},
            {'o', forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::g},
            {'P', forms::segments::a|forms::segments::b|forms::segments::e|forms::segments::f|forms::segments::g},
            {'p', forms::segments::a|forms::segments::b|forms::segments::e|forms::segments::f|forms::segments::g},
            {'Q', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::f|forms::segments::g},
            {'q', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::f|forms::segments::g},
            {'R', forms::segments::a|forms::segments::e|forms::segments::f},
            {'r', forms::segments::e|forms::segments::g},
            {'S', forms::segments::a|forms::segments::c|forms::segments::d|forms::segments::f|forms::segments::g},
            {'s', forms::segments::a|forms::segments::c|forms::segments::d|forms::segments::f|forms::segments::g},
            {'T', forms::segments::d|forms::segments::e|forms::segments::f|forms::segments::g},
            {'t', forms::segments::d|forms::segments::e|forms::segments::f|forms::segments::g},
            {'U', forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::f},
            {'u', forms::segments::c|forms::segments::d|forms::segments::e},
            {'Y', forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::f|forms::segments::g},
            {'y', forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::f|forms::segments::g},
            {'=', forms::segments::d|forms::segments::g}, {'-', forms::segments::g},
            {'_', forms::segments::d},
            {L'\u00B0', forms::segments::a|forms::segments::b|forms::segments::f|forms::segments::g},
            {'"', forms::segments::b|forms::segments::f},
            {'\'', forms::segments::f},
            {'[', forms::segments::a|forms::segments::d|forms::segments::e|forms::segments::f},
            {']', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d},
            {'|', forms::segments::b|forms::segments::c}, {' ', forms::segments::none},
            {'.', forms::segments::dp},
            {',', forms::segments::dp},
            {':', forms::segments::pc}
          };
          if (character_ != value) {
            if (characters.find(value) == characters.end()) throw std::invalid_argument(strings::format("Only characters : \"{}\" are valid", get_valid_characters()));
            character_ = value;
            nine_segment_display::value(characters[value]);
          }
        }
        void set_segment_style(forms::segment_style value) override {nine_segment_display::segment_style(value);}
        void set_dot_matrix_style(forms::dot_matrix_style value) override {}
        void set_show_background_digit(bool value) override {nine_segment_display::show_background_segment(value);}
        void set_thickness(int32_t value) override {seven_segment_display::thickness(value);}
        
      private:
        wchar_t character_ = ' ';
      };

      class seven_segment_display_digit : public seven_segment_display, public idigit {
      public:
        seven_segment_display_digit() = default;

        wchar_t get_character() const override {return character_;}
        std::string get_valid_characters() const override {return "0123456789ABCDEFGHIJLNOPQRSTUYabcdefghijlnopqrstuy=-_°\"'[]| .,:";}
        int32_t get_thickness() const override {return seven_segment_display::thickness();}

        void set_background_digit_transparency(double value) override {seven_segment_display::background_segment_transparency(value);}
        void set_character(wchar_t value) override {
          static std::map<wchar_t, forms::segments> characters {
            {'0', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::f},
            {'1', forms::segments::b|forms::segments::c},
            {'2', forms::segments::a|forms::segments::b|forms::segments::d|forms::segments::e|forms::segments::g},
            {'3', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::g},
            {'4', forms::segments::b|forms::segments::c|forms::segments::f|forms::segments::g},
            {'5', forms::segments::a|forms::segments::c|forms::segments::d|forms::segments::f|forms::segments::g},
            {'6', forms::segments::a|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::f|forms::segments::g},
            {'7', forms::segments::a|forms::segments::b|forms::segments::c},
            {'8', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::f|forms::segments::g},
            {'9', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::f|forms::segments::g},
            {'A', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::e|forms::segments::f|forms::segments::g},
            {'a', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::g},
            {'B', forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::f|forms::segments::g},
            {'b', forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::f|forms::segments::g},
            {'C', forms::segments::a|forms::segments::d|forms::segments::e|forms::segments::f},
            {'c', forms::segments::d|forms::segments::e|forms::segments::g},
            {'D', forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::g},
            {'d', forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::g},
            {'E', forms::segments::a|forms::segments::d|forms::segments::e|forms::segments::f|forms::segments::g},
            {'e', forms::segments::a|forms::segments::b|forms::segments::d|forms::segments::e|forms::segments::f|forms::segments::g},
            {'F', forms::segments::a|forms::segments::e|forms::segments::f|forms::segments::g},
            {'f', forms::segments::a|forms::segments::e|forms::segments::f|forms::segments::g},
            {'G', forms::segments::a|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::f},
            {'g', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::f|forms::segments::g},
            {'H', forms::segments::b|forms::segments::c|forms::segments::e|forms::segments::f|forms::segments::g},
            {'h', forms::segments::c|forms::segments::e|forms::segments::f|forms::segments::g},
            {'I', forms::segments::b|forms::segments::c},
            {'i', forms::segments::c},
            {'J', forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e},
            {'j', forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e},
            {'L', forms::segments::d|forms::segments::e|forms::segments::f},
            {'l', forms::segments::d|forms::segments::e},
            {'N', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::e|forms::segments::f},
            {'n', forms::segments::c|forms::segments::e|forms::segments::g},
            {'O', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::f},
            {'o', forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::g},
            {'P', forms::segments::a|forms::segments::b|forms::segments::e|forms::segments::f|forms::segments::g},
            {'p', forms::segments::a|forms::segments::b|forms::segments::e|forms::segments::f|forms::segments::g},
            {'Q', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::f|forms::segments::g},
            {'q', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::f|forms::segments::g},
            {'R', forms::segments::a|forms::segments::e|forms::segments::f},
            {'r', forms::segments::e|forms::segments::g},
            {'S', forms::segments::a|forms::segments::c|forms::segments::d|forms::segments::f|forms::segments::g},
            {'s', forms::segments::a|forms::segments::c|forms::segments::d|forms::segments::f|forms::segments::g},
            {'T', forms::segments::d|forms::segments::e|forms::segments::f|forms::segments::g},
            {'t', forms::segments::d|forms::segments::e|forms::segments::f|forms::segments::g},
            {'U', forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::e|forms::segments::f},
            {'u', forms::segments::c|forms::segments::d|forms::segments::e},
            {'Y', forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::f|forms::segments::g},
            {'y', forms::segments::b|forms::segments::c|forms::segments::d|forms::segments::f|forms::segments::g},
            {'=', forms::segments::d|forms::segments::g},
            {'-', forms::segments::g},
            {'_', forms::segments::d},
            {L'\u00B0', forms::segments::a|forms::segments::b|forms::segments::f|forms::segments::g},
            {'"', forms::segments::b|forms::segments::f},
            {'\'', forms::segments::f},
            {'[', forms::segments::a|forms::segments::d|forms::segments::e|forms::segments::f},
            {']', forms::segments::a|forms::segments::b|forms::segments::c|forms::segments::d},
            {'|', forms::segments::b|forms::segments::c}, {' ', forms::segments::none},
            {'.', forms::segments::dp},
            {',', forms::segments::dp},
            {':', forms::segments::pc}};
          if (character_ != value) {
            if (characters.find(value) == characters.end()) throw std::invalid_argument(strings::format("Only characters : \"{}\" are valid", get_valid_characters()));
            character_ = value;
            seven_segment_display::value(characters[value]);
          }
        }
        void set_segment_style(forms::segment_style value) override {seven_segment_display::segment_style(value);}
        void set_dot_matrix_style(forms::dot_matrix_style value) override {}
        void set_show_background_digit(bool value) override {seven_segment_display::show_background_segment(value);}
        void set_thickness(int32_t value) override {seven_segment_display::thickness(value);}

      private:
        wchar_t character_ = ' ';
      };

      class sixteen_segment_display_digit : public sixteen_segment_display, public idigit {
      public:
        sixteen_segment_display_digit() = default;
        
        wchar_t get_character() const override {return character_;}
        std::string get_valid_characters() const override {return "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz=+-*/\\_°\"'[]()| .,:";}
        int32_t get_thickness() const override {return sixteen_segment_display::thickness();}
        
        void set_background_digit_transparency(double value) override {sixteen_segment_display::background_segment_transparency(value);}
        void set_character(wchar_t value) override {
          static std::map<wchar_t, forms::segments> characters {
            {'0', forms::segments::a1|forms::segments::a2|forms::segments::b|forms::segments::c|forms::segments::d1|forms::segments::d2|forms::segments::e|forms::segments::f},
            {'1', forms::segments::b|forms::segments::c|forms::segments::j},
            {'2', forms::segments::a1|forms::segments::a2|forms::segments::b|forms::segments::d1|forms::segments::d2|forms::segments::e|forms::segments::g1|forms::segments::g2},
            {'3', forms::segments::a1|forms::segments::a2|forms::segments::b|forms::segments::c|forms::segments::d1|forms::segments::d2|forms::segments::g2},
            {'4', forms::segments::b|forms::segments::c|forms::segments::f|forms::segments::g1|forms::segments::g2},
            {'5', forms::segments::a1|forms::segments::a2|forms::segments::c|forms::segments::d1|forms::segments::d2|forms::segments::f|forms::segments::g1|forms::segments::g2},
            {'6', forms::segments::a1|forms::segments::a2|forms::segments::c|forms::segments::d1|forms::segments::d2|forms::segments::e|forms::segments::f|forms::segments::g1|forms::segments::g2},
            {'7', forms::segments::a1|forms::segments::a2|forms::segments::l|forms::segments::j},
            {'8', forms::segments::a1|forms::segments::a2|forms::segments::b|forms::segments::c|forms::segments::d1|forms::segments::d2|forms::segments::e|forms::segments::f|forms::segments::g1|segments::g2},
            {'9', forms::segments::a1|forms::segments::a2|forms::segments::b|forms::segments::c|forms::segments::f|forms::segments::g1|forms::segments::g2},
            {'A', forms::segments::a1|forms::segments::a2|forms::segments::b|forms::segments::c|forms::segments::e|forms::segments::f|forms::segments::g1|forms::segments::g2},
            {'B', forms::segments::a1|forms::segments::a2|forms::segments::b|forms::segments::c|forms::segments::d1|forms::segments::d2|forms::segments::g2|forms::segments::i|forms::segments::l},
            {'C', forms::segments::a1|forms::segments::a2|forms::segments::d1|forms::segments::d2|forms::segments::e|forms::segments::f},
            {'D', forms::segments::a1|forms::segments::a2|forms::segments::b|forms::segments::c|forms::segments::d1|forms::segments::d2|forms::segments::i|forms::segments::l},
            {'E', forms::segments::a1|forms::segments::a2|forms::segments::d1|forms::segments::d2|forms::segments::e|forms::segments::f|forms::segments::g1|forms::segments::g2},
            {'F', forms::segments::a1|forms::segments::a2|forms::segments::e|forms::segments::f|forms::segments::g1|forms::segments::g2},
            {'G', forms::segments::a1|forms::segments::a2|forms::segments::c|forms::segments::d1|forms::segments::d2|forms::segments::e|forms::segments::f|forms::segments::g2},
            {'H', forms::segments::b|forms::segments::c|forms::segments::e|forms::segments::f|forms::segments::g1|forms::segments::g2},
            {'I', forms::segments::a1|forms::segments::a2|forms::segments::d1|forms::segments::d2|forms::segments::i|forms::segments::l},
            {'J', forms::segments::b|forms::segments::c|forms::segments::d1|forms::segments::d2|forms::segments::e},
            {'K', forms::segments::e|forms::segments::f|forms::segments::g1|forms::segments::j|forms::segments::m},
            {'L', forms::segments::d1|forms::segments::d2|forms::segments::e|forms::segments::f},
            {'M', forms::segments::b|forms::segments::c|forms::segments::e|forms::segments::f|forms::segments::h|forms::segments::j},
            {'N', forms::segments::b|forms::segments::c|forms::segments::e|forms::segments::f|forms::segments::h|forms::segments::m},
            {'O', forms::segments::a1|forms::segments::a2|forms::segments::b|forms::segments::c|forms::segments::d1|forms::segments::d2|forms::segments::e|forms::segments::f},
            {'P', forms::segments::a1|forms::segments::a2|forms::segments::b|forms::segments::e|forms::segments::f|forms::segments::g1|forms::segments::g2},
            {'Q', forms::segments::a1|forms::segments::a2|forms::segments::b|forms::segments::c|forms::segments::d1|forms::segments::d2|forms::segments::e|forms::segments::f|forms::segments::m},
            {'q', forms::segments::a1|forms::segments::a2|forms::segments::b|forms::segments::f|forms::segments::g1|forms::segments::g2|forms::segments::m},
            {'R', forms::segments::a1|forms::segments::a2|forms::segments::b|forms::segments::e|forms::segments::f|forms::segments::g1|forms::segments::g2|forms::segments::m},
            {'S', forms::segments::a1|forms::segments::a2|forms::segments::c|forms::segments::d1|forms::segments::d2|forms::segments::g2|forms::segments::h},
            {'T', forms::segments::a1|forms::segments::a2|forms::segments::i|forms::segments::l},
            {'U', forms::segments::b|forms::segments::c|forms::segments::d1|forms::segments::d2|forms::segments::e|forms::segments::f},
            {'V', forms::segments::e|forms::segments::f|forms::segments::j|forms::segments::k},
            {'W', forms::segments::b|forms::segments::c|forms::segments::e|forms::segments::f|forms::segments::k|forms::segments::m},
            {'X', forms::segments::h|forms::segments::j|forms::segments::k|forms::segments::m},
            {'Y', forms::segments::h|forms::segments::j|forms::segments::l},
            {'Z', forms::segments::a1|forms::segments::a2|forms::segments::d1|forms::segments::d2|forms::segments::j|forms::segments::k},
            {'a', forms::segments::a1|forms::segments::a2|forms::segments::b|forms::segments::c|forms::segments::d1|forms::segments::d2|forms::segments::e|forms::segments::g1|forms::segments::g2},
            {'b', forms::segments::d1|forms::segments::d2|forms::segments::e|forms::segments::f|forms::segments::g1|forms::segments::m},
            {'c', forms::segments::d1|forms::segments::d2|forms::segments::e|forms::segments::g1|forms::segments::g2},
            {'d', forms::segments::b|forms::segments::c|forms::segments::d1|forms::segments::d2|segments::g2|segments::k},
            {'e', forms::segments::a1|forms::segments::a2|forms::segments::d1|forms::segments::d2|forms::segments::e|forms::segments::f|forms::segments::g1},
            {'f', forms::segments::a1|forms::segments::a2|forms::segments::e|forms::segments::f|forms::segments::g1},
            {'g', forms::segments::a1|forms::segments::a2|forms::segments::b|forms::segments::c|forms::segments::d1|forms::segments::d2|forms::segments::h|forms::segments::g2},
            {'h', forms::segments::c|forms::segments::e|forms::segments::f|forms::segments::g1|forms::segments::g2},
            {'i', forms::segments::l},
            {'j', forms::segments::b|forms::segments::c|forms::segments::d1|forms::segments::d2},
            {'k', forms::segments::i|forms::segments::l|forms::segments::j|forms::segments::m},
            {'l', forms::segments::i|forms::segments::l},
            {'m', forms::segments::c|forms::segments::e|forms::segments::g1|forms::segments::g2|forms::segments::l},
            {'n', forms::segments::e|forms::segments::g1|forms::segments::m},
            {'o', forms::segments::c|forms::segments::d1|forms::segments::d2|forms::segments::e|forms::segments::g1|forms::segments::g2},
            {'p', forms::segments::a1|forms::segments::a2|forms::segments::e|forms::segments::f|forms::segments::g1|forms::segments::j},
            {'r', forms::segments::e|forms::segments::g},
            {'s', forms::segments::a1|forms::segments::a2|forms::segments::c|forms::segments::d1|forms::segments::d2|forms::segments::g2|forms::segments::h},
            {'t', forms::segments::d1|forms::segments::d2|forms::segments::e|forms::segments::f|forms::segments::g1},
            {'u', forms::segments::c|forms::segments::d1|forms::segments::d2|forms::segments::e},
            {'v', forms::segments::e|forms::segments::k},
            {'w', forms::segments::c|forms::segments::e|forms::segments::k|forms::segments::m},
            {'x', forms::segments::h|forms::segments::j|forms::segments::k|forms::segments::m},
            {'y', forms::segments::b|forms::segments::c|forms::segments::d2|forms::segments::g2|forms::segments::i},
            {'z', forms::segments::g1|forms::segments::d1|forms::segments::k},
            {'=', forms::segments::d1|forms::segments::d2|forms::segments::g1|forms::segments::g2},
            {'+', forms::segments::g1|forms::segments::g2|forms::segments::i|forms::segments::l},
            {'-', forms::segments::g1|forms::segments::g2},
            {'*', forms::segments::g1|forms::segments::g2|forms::segments::h|forms::segments::i|forms::segments::j|forms::segments::k|forms::segments::l|forms::segments::m},
            {'/', forms::segments::j|forms::segments::k},
            {'\\', forms::segments::h|forms::segments::m},
            {'_', forms::segments::d1|forms::segments::d2},
            {L'\u00B0', forms::segments::a1|forms::segments::a2|forms::segments::b|forms::segments::f|forms::segments::g1|forms::segments::g2},
            {'"', forms::segments::b|forms::segments::f},
            {'\'', forms::segments::f},
            {'[', forms::segments::a1|forms::segments::a2|forms::segments::d1|forms::segments::d2|forms::segments::e|forms::segments::f},
            {']', forms::segments::a1|forms::segments::a2|forms::segments::b|forms::segments::c|forms::segments::d1|forms::segments::d2},
            {'(', forms::segments::j|forms::segments::m},
            {')', forms::segments::h|forms::segments::k},
            {'|', forms::segments::i|forms::segments::l},
            {' ', forms::segments::none},
            {'.', forms::segments::dp},
            {',', forms::segments::k},
            {':', forms::segments::pc}
          };
          if (character_ != value) {
            if (characters.find(value) == characters.end()) throw std::invalid_argument(strings::format("Only characters : \"{}\" are valid", get_valid_characters()));
            character_ = value;
            sixteen_segment_display::value(characters[value]);
          }
        }
        void set_segment_style(forms::segment_style value) override {sixteen_segment_display::segment_style(value);}
        void set_dot_matrix_style(forms::dot_matrix_style value) override {}
        void set_show_background_digit(bool value) override {sixteen_segment_display::show_background_segment(value);}
        void set_thickness(int32_t value) override {sixteen_segment_display::thickness(value);}
        
      private:
        wchar_t character_ = ' ';
      };

    public:
      lcd_label() {
        auto_size_mode_ = forms::auto_size_mode::grow_and_shrink;
        size_ = default_size();
      }
      
      double background_digit_transparency() const {return background_digit_transparency_;}
      lcd_label& background_digit_transparency(double value) {
        if (value < 0.0 && value > 1.0) throw std::invalid_argument("value must be between 0.0 and 1.0.");
        if (background_digit_transparency_ != value) {
          background_digit_transparency_ = value;
          set_digits_params();
        }
        return *this;
      }
      
      bool show_background_digit() const {return show_background_digit_;}
      lcd_label& show_background_digit(bool value) {
        if (show_background_digit_ != value) {
          show_background_digit_ = value;
          set_digits_params();
        }
        return *this;
      }

      int32_t digit_spacing() const {return digit_spacing_.value_or(lcd_style_ == lcd_style::dot_matrix_display ? 0 : thickness());}
      lcd_label& digit_spacing(int32_t value) {
        if (value < 0) throw std::invalid_argument("value must be positive");
        if (digit_spacing_ != value) {
          digit_spacing_ = value;
          set_digits_params();
        }
        return *this;
      }
      
      forms::lcd_style lcd_style() const {return lcd_style_;}
      lcd_label& lcd_style(forms::lcd_style value) {
        if (lcd_style_ != value) {
          lcd_style_ = value;
          std::string current_text = text();
          text("");
          text(current_text);
        }
        return *this;
      }
      
      forms::segment_style segment_style() const {return segment_style_;}
      lcd_label& segment_style(forms::segment_style value) {
        if (segment_style_ != value) {
          segment_style_ = value;
          for (auto& digit : digits_)
            digit->set_segment_style(value);
        }
        return *this;
      }
      
      forms::dot_matrix_style dot_matrix_style() const {return dot_matrix_style_;}
      lcd_label& dot_matrix_style(forms::dot_matrix_style value) {
        if (dot_matrix_style_ != value) {
          dot_matrix_style_ = value;
          for (auto& digit : digits_)
            digit->set_dot_matrix_style(value);
        }
        return *this;
      }

      int32_t thickness() const {return thickness_.value_or(digits_.size() ? digits_[0]->get_thickness() : 1);}
      lcd_label& thickness(int32_t value) {
        if (thickness_ != value) {
          thickness_ = value;
          set_digits_params();
        }
        return *this;
      }

      using control::text;
      control& text(const std::string& value) override {
        if (text_ != value) {
          suspend_layout();
          std::wstring str = std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().from_bytes(value.c_str());
          if (str.size() < digits_.size())
            digits_.erase(digits_.begin() + value.size(), digits_.end());
          if (str.size() > digits_.size())
            for (size_t index = digits_.size(); index < str.size(); index++) {
              switch (lcd_style_) {
                case lcd_style::seven_segment_display: digits_.push_back(std::make_shared<seven_segment_display_digit>()); break;
                case lcd_style::nine_segment_display: digits_.push_back(std::make_shared<nine_segment_display_digit>()); break;
                case lcd_style::fourteen_segment_display: digits_.push_back(std::make_shared<fourteen_segment_display_digit>()); break;
                case lcd_style::sixteen_segment_display: digits_.push_back(std::make_shared<sixteen_segment_display_digit>()); break;
                case lcd_style::dot_matrix_display: digits_.push_back(std::make_shared<dot_matrix_display_digit>()); break;
                default: throw std::invalid_argument("lcd_style invalid");
              }
              dynamic_cast<control*>(digits_[digits_.size() - 1].get())->parent(*this);
              dynamic_cast<control*>(digits_[digits_.size() - 1].get())->click += [this] {on_click(event_args::empty);};
              dynamic_cast<control*>(digits_[digits_.size() - 1].get())->mouse_down += [this](control& sender, const mouse_event_args& e) {on_mouse_down(mouse_event_args(e.button(), e.location() + drawing::size(sender.location()), e.clicks(), e.delta()));};
              dynamic_cast<control*>(digits_[digits_.size() - 1].get())->mouse_move += [this](control& sender, const mouse_event_args& e) {on_mouse_move(mouse_event_args(e.button(), e.location() + drawing::size(sender.location()), e.clicks(), e.delta()));};
              dynamic_cast<control*>(digits_[digits_.size() - 1].get())->mouse_up += [this](control& sender, const mouse_event_args& e) {on_mouse_up(mouse_event_args(e.button(), e.location() + drawing::size(sender.location()), e.clicks(), e.delta()));};
            }
          for (size_t index = 0; index < str.size(); index++)
            digits_[index]->set_character(str[index]);
          set_digits_params();
          control::text(value);
          resume_layout();
        }
        return *this;
      }
      
      std::string valid_characters() {
        switch (lcd_style_) {
          case lcd_style::seven_segment_display: return std::make_shared<seven_segment_display_digit>()->get_valid_characters();
          case lcd_style::nine_segment_display: return std::make_shared<nine_segment_display_digit>()->get_valid_characters();
          case lcd_style::fourteen_segment_display: return std::make_shared<fourteen_segment_display_digit>()->get_valid_characters();
          case lcd_style::sixteen_segment_display: return std::make_shared<sixteen_segment_display_digit>()->get_valid_characters();
          case lcd_style::dot_matrix_display: return std::make_shared<dot_matrix_display_digit>()->get_valid_characters();
          default: throw std::invalid_argument("lcd_style invalid");
        }
      }

    protected:
      drawing::size default_size() const override {return {100, 25};}

      void set_digits_params() {
        int32_t offset_left = 0;
        for (auto& digit : digits_) {
          dynamic_cast<control*>(digit.get())->height(size_.height());
          dynamic_cast<control*>(digit.get())->left(offset_left);
          digit->set_background_digit_transparency(background_digit_transparency_);
          digit->set_show_background_digit(show_background_digit_);
          digit->set_segment_style(segment_style_);
          digit->set_dot_matrix_style(dot_matrix_style_);
          if (thickness_.has_value()) digit->set_thickness(thickness());
          offset_left += dynamic_cast<control*>(digit.get())->width() - 2 + digit_spacing();
        }
      }
      
      void on_handle_created(const event_args& e) override {
        control::on_handle_created(e);
        set_digits_params();
      }
      
      void on_size_changed(const event_args& e) override {
        set_digits_params();
        control::on_size_changed(e);
      }
      
      void on_resize(const event_args& e) override {
        set_digits_params();
        control::on_resize(e);
      }

      drawing::size measure_control() const override {
        if (digits_.size() == 0) return {0, size_.height()};
        return drawing::size((dynamic_cast<control*>(digits_[0].get())->width() - 2 + digit_spacing()) * static_cast<int32_t>(digits_.size()) - digit_spacing() + 2, size_.height());
      }

    private:
      bool show_background_digit_ = true;
      double background_digit_transparency_ = 0.05;
      std::optional<int32_t> digit_spacing_;
      forms::lcd_style lcd_style_ = forms::lcd_style::seven_segment_display;
      forms::segment_style segment_style_ = forms::segment_style::standard;
      forms::dot_matrix_style dot_matrix_style_ = forms::dot_matrix_style::standard;
      std::vector<std::shared_ptr<idigit>> digits_;
      std::optional<int32_t> thickness_;
    };
  }
}
