#pragma once
#include <codecvt>
#include <stdexcept>
#include <string>
#include <vector>
#include <xtd/forms/create_params.hpp>
#include <xtd/forms/native/up_down_styles.hpp>
#include <wx/event.h>
#include <wx/panel.h>
#include <wx/spinctrl.h>
#include <wx/textctrl.h>
#include "control_handler.hpp"

class wxDomainSpinCtrl : public wxPanel {
public:
  wxDomainSpinCtrl(wxWindow* parent, wxWindowID winid = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long textBoxStyle = 0, long spinStyle = 0) : wxPanel(parent, winid, pos, size) {
    textBox = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, textBoxStyle);
    upDown = new wxSpinButton(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, spinStyle);

    if (size == wxDefaultSize) SetSize(120, textBox->GetSize().GetHeight());

    textBox->SetPosition(wxPoint(0, 0));
    textBox->SetSize(GetSize() - wxSize(upDown->GetSize().GetWidth(), 0));
    textBox->Bind(wxEVT_TEXT, [&](wxCommandEvent& event) {
      wxPostEvent(this, wxCommandEvent(wxEVT_TEXT, GetId()));
    });

    upDown->SetPosition(wxPoint(GetSize().GetWidth() - upDown->GetSize().GetWidth(), 0));
    upDown->SetSize(upDown->GetSize().GetWidth(), GetSize().GetHeight());
    upDown->SetRange(0, static_cast<int>(items.GetCount()) - 1);
    upDown->Bind(wxEVT_SPIN, [&](wxSpinEvent& event) {
      if (index == -1)
        upDown->SetValue(items.GetCount() - 1);
      index = items.GetCount() - 1 - upDown->GetValue();
      SetTextWithSelectedIndex();
    });

    Bind(wxEVT_SIZE, [&](wxEvent& ev) {
      textBox->SetSize(GetSize() - wxSize(upDown->GetSize().GetWidth(), 0));
      upDown->SetPosition(wxPoint(GetSize().GetWidth() - upDown->GetSize().GetWidth(), (GetSize().GetHeight() - upDown->GetSize().GetHeight()) / 2));
    });
  }

  wxArrayString& GetItems() { return items; }

  wxString GetValue() const { return textBox->GetValue(); }

  void SetValue(const wxString& value) { textBox->SetValue(value); }

  size_t GetSelectedIndex() const { return index; }

  void SetSelectedIndex(size_t index) {
    this->index = index;
    if (index != -1) upDown->SetValue(items.GetCount() - 1 - index);
    else upDown->SetValue(items.GetCount() - 1);
    SetTextWithSelectedIndex();
  }

  wxString GetLabel() const override {return textBox->GetValue();}

  void SetLabel(const wxString& value) override {textBox->SetValue(value);}
  
  void updateSpin() {
    upDown->SetRange(0, items.GetCount()-1);
  }

private:
  void SetTextWithSelectedIndex() {
    if (index != -1) textBox->SetValue(items[index]);
  }

  wxTextCtrl* textBox;
  wxSpinButton* upDown;
  wxArrayString items;
  size_t index = -1;
};

namespace xtd {
  namespace forms {
    namespace native {
      class wx_domain_up_down : public control_handler {
      public:
        wx_domain_up_down(const forms::create_params& create_params) {
          if (!create_params.parent()) throw std::invalid_argument("control must have a parent");
          int32_t height = create_params.height();
#if defined(__WXGTK__)
          if (height < 32) height = 32;
#endif
          this->control_handler::create<wxDomainSpinCtrl>(reinterpret_cast<control_handler*>(create_params.parent())->control(), wxID_ANY, wxPoint(create_params.x(), create_params.y()), wxSize(create_params.width(), height), style_to_wx_text_box_style(create_params.style(), create_params.ex_style()), style_to_wx_spin_style(create_params.style(), create_params.ex_style()));
        }
        
        static long style_to_wx_text_box_style(size_t style, size_t ex_style) {
          long wx_style = 0;
          
          if ((style & WS_BORDER) == WS_BORDER) wx_style |= wxBORDER_DEFAULT;
          else if ((ex_style & WS_EX_CLIENTEDGE) == WS_EX_CLIENTEDGE) wx_style |= wxBORDER_THEME;
          else wx_style |= wxBORDER_NONE;

          return wx_style;
        }
        
        static long style_to_wx_spin_style(size_t style, size_t ex_style) {
          long wx_style = 0;

          if ((style & UDS_WRAP) == UDS_WRAP) wx_style |= wxSP_WRAP;

          return wx_style;
        }
      };
    }
  }
}