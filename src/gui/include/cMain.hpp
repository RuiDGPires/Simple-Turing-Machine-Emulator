#ifndef __CMAIN_HPP__
#define __CMAIN_HPP__

#include "../../turingmachine/include/turingmachine.hpp"
#include "../../evaluator/include/evaluator.hpp"


#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


class cMain : public wxFrame{
    private:
        tmch::TuringMachine tm;
    public:
        cMain();
        ~cMain();
        void OnButtonClicked(wxCommandEvent &evt);
        wxDECLARE_EVENT_TABLE();
    public:
        wxTextCtrl *txtbox_input;
        wxButton *btn;
        wxMenuBar *menu_bar;
        wxStaticText *label1;
        
};

#endif