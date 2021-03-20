#include "include/cMain.hpp"

#include <iostream>

#define SLEEP_TIME 120000000

wxDECLARE_EVENT(wxEVT_COMMAND_RUNNINGTHREAD_COMPLETED, wxThreadEvent);
wxDECLARE_EVENT(wxEVT_COMMAND_RUNNINGTHREAD_UPDATE, wxThreadEvent);


wxBEGIN_EVENT_TABLE(cMain, wxFrame)
    EVT_BUTTON(BTN_EVAL, cMain::OnButtonEvalClicked)
    EVT_BUTTON(BTN_RUN, cMain::OnButtonRunClicked)
    EVT_BUTTON(BTN_STEP, cMain::OnButtonStepClicked)
    EVT_BUTTON(BTN_LOAD, cMain::OnButtonLoadClicked)
    EVT_MENU(MENU_OPEN, cMain::OnMenuOpenClicked)
    EVT_SIZE(cMain::OnResizing)
    EVT_TEXT_ENTER(TXTBOX, cMain::OnButtonLoadClicked)

    EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_RUNNINGTHREAD_COMPLETED, cMain::OnThreadCompletion)
    EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_RUNNINGTHREAD_UPDATE, cMain::OnThreadUpdate)
wxEND_EVENT_TABLE()

wxDEFINE_EVENT(wxEVT_COMMAND_RUNNINGTHREAD_COMPLETED, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_RUNNINGTHREAD_UPDATE, wxThreadEvent);

cMain::cMain() :wxFrame(nullptr, MAIN_FRAME, "Turing Machine Emulator", wxDefaultPosition, DEFAULT_MAIN_SIZE){
    evl::Evaluator ev(&tm);
    wxSize btn_size(120,50);
    this->Maximize();
    /* Sizers */
    main_sizer = new wxBoxSizer(wxVERTICAL);
    label_sizer = new wxBoxSizer(wxHORIZONTAL);
    buttons_sizer = new wxBoxSizer(wxHORIZONTAL);
    textbox_sizer = new wxBoxSizer(wxHORIZONTAL);
    editor_sizer = new wxBoxSizer(wxHORIZONTAL);

    /* Labels */
    left_label = new wxStaticText(this, LABEL, "", wxPoint(0,0), wxSize(600,120), wxALIGN_RIGHT);
    mid_label = new wxStaticText(this, LABEL, "", wxPoint(0,0), wxSize(71,120), wxALIGN_CENTER_HORIZONTAL);
    right_label = new wxStaticText(this, LABEL, "", wxPoint(0,0), wxSize(601,120), wxALIGN_LEFT);
    
    state_label = new wxStaticText(this, LABEL, "Halt", wxPoint(0,0), wxSize(901,120), wxALIGN_CENTER_HORIZONTAL);

    wxFont label_fnt = wxFont(52, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxFont label_mid_fnt = wxFont(65, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, true);
    left_label->SetFont(label_fnt);
    mid_label->SetFont(label_mid_fnt);
    right_label->SetFont(label_fnt);
    state_label->SetFont(label_fnt);

    /* Buttons */
    txtbox_input = new wxTextCtrl(this, TXTBOX, "", wxPoint(0,0), wxSize(400,50), wxTE_PROCESS_ENTER);
    wxFont txtbox_fnt = wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    txtbox_input->SetFont(txtbox_fnt);

    btn_load = new wxButton(this, BTN_LOAD, "Load", wxPoint(0,0), btn_size);
    btn_run = new wxButton(this, BTN_RUN, "Run", wxPoint(0,0), btn_size);
    btn_step = new wxButton(this, BTN_STEP, "Step", wxPoint(0,0), btn_size);
    btn_eval = new wxButton(this, BTN_EVAL, "Evaluate", wxPoint(0,0), btn_size);
    
    /* Menu */
    menu_bar = new wxMenuBar();
    this->SetMenuBar(menu_bar);

    wxMenu *menuFile = new wxMenu();
    menuFile->Append(MENU_OPEN, "Open");
    menu_bar->Append(menuFile,"File");

    /* Text Editor */
    editor_sizer->Add(setupEditor(wxSize(800,600)), 0, wxALIGN_CENTER);
    editor_sizer->SetMinSize(wxSize(800,800));

    label_sizer->Add(left_label, 0, wxALIGN_BOTTOM);
    label_sizer->Add(mid_label, 0, wxALIGN_BOTTOM);
    label_sizer->Add(right_label, 0, wxALIGN_BOTTOM);

    textbox_sizer->Add(txtbox_input, 0, wxALIGN_TOP,40);
    textbox_sizer->SetMinSize(wxSize(400,70));

    buttons_sizer->Add(btn_load, 0, wxALIGN_LEFT, 10);
    buttons_sizer->Add(btn_eval, 0, wxALIGN_LEFT, 10);
    buttons_sizer->Add(btn_step, 0, wxALIGN_LEFT, 10);
    buttons_sizer->Add(btn_run, 0, wxALIGN_LEFT, 10);

    main_sizer->Add(label_sizer, 0, wxALIGN_CENTER_HORIZONTAL);
    main_sizer->Add(state_label, 0, wxALIGN_CENTER_HORIZONTAL);
    main_sizer->Add(textbox_sizer, 0, wxALIGN_CENTER_HORIZONTAL);
    main_sizer->Add(buttons_sizer, 0, wxALIGN_CENTER_HORIZONTAL);
    main_sizer->Add(editor_sizer, 0, wxALIGN_CENTER_HORIZONTAL);

    
    SetSizer(main_sizer);
    
}

cMain::~cMain(){}

void cMain::setLabels(tmch::TuringMachine &tm){
    std::string s = tm.getConfig().getRight();
    s.erase(s.begin());
   

    left_label->SetLabelText(tm.getConfig().getLeft());
    mid_label->SetLabelText(tm.getConfig().getRight()[0]);
    right_label->SetLabelText(s);

    state_label->SetLabelText(tm.stateToString());
    label_sizer->Layout();
}

void cMain::doStartThread(){
    m_pThread = new RunningThread(this);
    if ( m_pThread->Run() != wxTHREAD_NO_ERROR )
    {
        wxLogError("Can't create the thread!");
        delete m_pThread;
        m_pThread = NULL;
    }
    running = true;
    btn_run->SetLabelText("Stop");
    btn_eval->Disable();
    btn_step->Disable();
    btn_load->Disable();
    menu_bar->Disable();
}

void cMain::doStopThread(){
    {
    wxCriticalSectionLocker enter(m_pThreadCS);
    if (m_pThread)         // does the thread still exist?
    {
        wxCriticalSectionLocker enter(m_tmCS);
        wxMessageOutputDebug().Printf("MYFRAME: deleting thread");
        if (m_pThread->Delete() != wxTHREAD_NO_ERROR )
            wxLogError("Can't delete the thread!");
    }
    } 
    while (1)
    {
        { // was the ~MyThread() function executed?
            wxCriticalSectionLocker enter(m_pThreadCS);
            if (!m_pThread) break;
        }
        // wait for thread completion
        wxThread::This()->Sleep(1);
    }
    running = false;
    btn_run->SetLabelText("Run");
    btn_eval->Enable();
    btn_step->Enable();
    btn_load->Enable();
    menu_bar->Enable();
}

RunningThread::RunningThread(cMain *main) : wxThread(wxTHREAD_DETACHED){
    this->main = main;
}

RunningThread::~RunningThread(){
    wxCriticalSectionLocker enter(main->m_pThreadCS);
    main->m_pThread = NULL;
}

wxThread::ExitCode RunningThread::Entry(){
    bool isRunning = false;
    do{
        {
        wxCriticalSectionLocker enter1(main->m_pThreadCS);
        wxCriticalSectionLocker enter(main->m_tmCS);
        main->tm.step();   
        wxQueueEvent(main, new wxThreadEvent(wxEVT_COMMAND_RUNNINGTHREAD_UPDATE));
        isRunning = main->tm.state == tmch::State::RUNNING;
        }
        for (int i = 0; i < SLEEP_TIME;i++);
    }while(isRunning && !TestDestroy());

    wxQueueEvent(main, new wxThreadEvent(wxEVT_COMMAND_RUNNINGTHREAD_COMPLETED));
    return (wxThread::ExitCode) 0;
}