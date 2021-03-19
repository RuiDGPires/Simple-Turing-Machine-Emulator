#ifndef __CMAIN_HPP__
#define __CMAIN_HPP__

#include "../../turingmachine/include/turingmachine.hpp"
#include "../../evaluator/include/evaluator.hpp"


#ifndef WX_PRECOMP
    #include <wx/wx.h>
    //#include <wx/vscroll.h>
#endif

#define DEFAULT_MAIN_SIZE wxSize(640,480)

class cMain : public wxFrame{
    private:
        tmch::TuringMachine tm;

    private:
        void setLabels(tmch::TuringMachine &t);
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
        wxStaticText *left_label;
        wxStaticText *mid_label;
        wxStaticText *right_label;
        wxStaticText *state_label;
        
};

#endif