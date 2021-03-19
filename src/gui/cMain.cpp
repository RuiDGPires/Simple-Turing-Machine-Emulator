#include "include/cMain.hpp"

#include <iostream>

enum{MAIN_FRAME=0};
enum{BTN_LOAD=100, BTN_RUN, BTN_STEP, TXTBOX, LABEL};
enum{MENU_OPEN=200};


wxBEGIN_EVENT_TABLE(cMain, wxFrame)
    EVT_BUTTON(BTN_RUN, cMain::OnButtonRunClicked)
    EVT_BUTTON(BTN_STEP, cMain::OnButtonStepClicked)
    EVT_BUTTON(BTN_LOAD, cMain::OnButtonLoadClicked)
    EVT_MENU(MENU_OPEN, cMain::OnMenuOpenClicked)
    EVT_SIZE(cMain::OnResizing)
    EVT_TEXT_ENTER(TXTBOX, cMain::OnButtonLoadClicked)
wxEND_EVENT_TABLE()

#define DEFAULT_MAIN_SIZE wxSize(640,480)

cMain::cMain() :wxFrame(nullptr, MAIN_FRAME, "Turing Machine Emulator", wxDefaultPosition, DEFAULT_MAIN_SIZE){
    evl::Evaluator ev(&tm);
    wxSize btn_size(120,50);
    this->Maximize();
    /* Sizers */
    main_sizer = new wxBoxSizer(wxVERTICAL);
    label_sizer = new wxBoxSizer(wxHORIZONTAL);
    //label_sizer->SetMinSize(wxSize(300,30));

    buttons_sizer = new wxBoxSizer(wxHORIZONTAL);
    textbox_sizer = new wxBoxSizer(wxHORIZONTAL);

    left_label = new wxStaticText(this, LABEL, "", wxPoint(0,0), wxSize(900,120), wxALIGN_RIGHT);
    mid_label = new wxStaticText(this, LABEL, "", wxPoint(0,0), wxSize(71,120), wxALIGN_CENTER_HORIZONTAL);
    right_label = new wxStaticText(this, LABEL, "", wxPoint(0,0), wxSize(901,120), wxALIGN_LEFT);
    
    state_label = new wxStaticText(this, LABEL, "Halt", wxPoint(0,0), wxSize(901,120), wxALIGN_CENTER_HORIZONTAL);

    wxFont label_fnt = wxFont(52, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxFont label_mid_fnt = wxFont(65, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
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
    
    
    /* Menu */
    menu_bar = new wxMenuBar();
    this->SetMenuBar(menu_bar);

    wxMenu *menuFile = new wxMenu();
    menuFile->Append(MENU_OPEN, "Open");
    menu_bar->Append(menuFile,"File");

    //label_sizer->AddStretchSpacer();

    label_sizer->Add(left_label, 0, wxALIGN_BOTTOM);
    label_sizer->Add(mid_label, 0, wxALIGN_BOTTOM);
    label_sizer->Add(right_label, 0, wxALIGN_BOTTOM);

    textbox_sizer->Add(txtbox_input, 0, wxALIGN_TOP,40);
    textbox_sizer->SetMinSize(wxSize(400,70));

    buttons_sizer->Add(btn_load, 0, wxALIGN_LEFT, 10);
    buttons_sizer->Add(btn_run, 0, wxALIGN_LEFT, 10);
    buttons_sizer->Add(btn_step, 0, wxALIGN_LEFT, 10);

    main_sizer->Add(label_sizer, 0, wxALIGN_CENTER_HORIZONTAL);
    main_sizer->Add(state_label, 0, wxALIGN_CENTER_HORIZONTAL);
    main_sizer->Add(textbox_sizer, 0, wxALIGN_CENTER_HORIZONTAL);
    main_sizer->Add(buttons_sizer, 0, wxALIGN_CENTER_HORIZONTAL);

    
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



/* Events */
void cMain::OnButtonLoadClicked(wxCommandEvent &evt){
    tm.load(std::string(txtbox_input->GetValue().mb_str()));
    setLabels(tm);
}

void cMain::OnButtonRunClicked(wxCommandEvent &evt){
    tm.load(std::string(txtbox_input->GetValue().mb_str()));
    tm.run();
    setLabels(tm);
}

void cMain::OnButtonStepClicked(wxCommandEvent &evt){
    tm.step();
    setLabels(tm);
}

void cMain::OnMenuOpenClicked(wxCommandEvent &evt){
    wxFileDialog dlg(this, "Open config file", "", "", "all (*.conf, *txt)|*.conf;*.txt|.conf files (*.conf)|*.conf|.txt files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (dlg.ShowModal() == wxID_OK){
        evl::Evaluator ev(&tm);
        ev.evalFile(std::string(dlg.GetPath().c_str())); 
    }
}

void cMain::OnResizing(wxSizeEvent &evt){
    evt.Skip();
    this->SetMinClientSize(DEFAULT_MAIN_SIZE/2);
}