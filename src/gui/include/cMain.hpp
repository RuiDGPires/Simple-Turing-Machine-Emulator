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

        /* Events */
        void OnButtonRunClicked(wxCommandEvent &evt);
        void OnButtonStepClicked(wxCommandEvent &evt);
        void OnButtonLoadClicked(wxCommandEvent &evt);

        void OnMenuOpenClicked(wxCommandEvent &evt);
        
        wxDECLARE_EVENT_TABLE();
    public:
        wxTextCtrl *txtbox_input;

        /* Buttons */
        wxButton *btn_run;
        wxButton *btn_step;
        wxButton *btn_load;

        wxMenuBar *menu_bar;
        wxStaticText *label1;
        
};

#endif