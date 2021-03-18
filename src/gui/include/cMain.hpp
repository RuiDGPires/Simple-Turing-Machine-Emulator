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
        
        void OnResizing(wxSizeEvent &evt);
        wxDECLARE_EVENT_TABLE();
    public:
        wxBoxSizer *main_sizer;
        wxBoxSizer *label_sizer;
        wxBoxSizer *textbox_sizer;
        wxBoxSizer *buttons_sizer;

        wxTextCtrl *txtbox_input;

        /* Buttons */
        wxButton *btn_run;
        wxButton *btn_step;
        wxButton *btn_load;

        wxMenuBar *menu_bar;
        wxStaticText *label1;
        
};

#endif