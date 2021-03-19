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
        bool running = false;
    public:
        cMain();
        ~cMain();

        void doStartThread();
        void doStopThread();
        void setLabels(tmch::TuringMachine &t);
        /* Events */
        void OnButtonEvalClicked(wxCommandEvent &evt);
        void OnButtonStepClicked(wxCommandEvent &evt);
        void OnButtonLoadClicked(wxCommandEvent &evt);
        void OnButtonRunClicked(wxCommandEvent &evt);

        void OnMenuOpenClicked(wxCommandEvent &evt);
        
        void OnResizing(wxSizeEvent &evt);

        void OnThreadCompletion(wxCommandEvent &evt);
        void OnThreadUpdate(wxCommandEvent &evt);
        
        wxDECLARE_EVENT_TABLE();
    public:
        tmch::TuringMachine tm;

        wxThread *m_pThread;
        wxCriticalSection m_pThreadCS;    // protects the m_pThread pointer
        wxCriticalSection m_tmCS;

        wxBoxSizer *main_sizer;
        wxBoxSizer *label_sizer;
        wxBoxSizer *textbox_sizer;
        wxBoxSizer *buttons_sizer;

        wxTextCtrl *txtbox_input;

        /* Buttons */
        wxButton *btn_run;
        wxButton *btn_eval;
        wxButton *btn_step;
        wxButton *btn_load;

        wxMenuBar *menu_bar;
        wxStaticText *left_label;
        wxStaticText *mid_label;
        wxStaticText *right_label;
        wxStaticText *state_label;
        
};

class RunningThread : public wxThread
{
    private:
        cMain *main;
    public:
        RunningThread(cMain *main);
        ~RunningThread();

        // thread execution starts here
        virtual wxThread::ExitCode Entry();
};
#endif