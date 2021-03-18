#include "include/cMain.hpp"

#include <iostream>

enum{BTN_LOAD, BTN_RUN, BTN_STEP, TXTBOX, LABEL};
enum{MENU_OPEN};


wxBEGIN_EVENT_TABLE(cMain, wxFrame)
    EVT_BUTTON(BTN_RUN, cMain::OnButtonRunClicked)
    EVT_BUTTON(BTN_STEP, cMain::OnButtonStepClicked)
    EVT_BUTTON(BTN_LOAD, cMain::OnButtonLoadClicked)
    EVT_MENU(MENU_OPEN, cMain::OnMenuOpenClicked)
wxEND_EVENT_TABLE()


cMain::cMain() :wxFrame(nullptr, wxID_ANY, "Turing Machine Emulator", wxDefaultPosition, wxSize(640,480)){
    evl::Evaluator ev(&tm);
    wxSize btn_size(120,50);
    this->SetMinSize(wxSize(640,480));
    
    /* Sizers */
    main_sizer = new wxBoxSizer(wxVERTICAL);
    label_sizer = new wxBoxSizer(wxHORIZONTAL);
    //label_sizer->SetMinSize(wxSize(300,30));

    buttons_sizer = new wxBoxSizer(wxHORIZONTAL);
    textbox_sizer = new wxBoxSizer(wxHORIZONTAL);

    label1 = new wxStaticText(this, LABEL, "Output", wxPoint(0,0), wxSize(620,120), wxALIGN_CENTER_HORIZONTAL);
    
    wxFont label_fnt = wxFont(60, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    label1->SetFont(label_fnt);

    /* Buttons */
    txtbox_input = new wxTextCtrl(this, TXTBOX, "", wxPoint(0,0), wxSize(200,50));
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

    label_sizer->AddStretchSpacer();
    label_sizer->Add(label1, 0, wxALIGN_BOTTOM,40);

    textbox_sizer->Add(txtbox_input, 0, wxALIGN_TOP,40);

    buttons_sizer->Add(btn_load, 0, wxALIGN_LEFT, 10);
    buttons_sizer->Add(btn_run, 0, wxALIGN_LEFT, 10);
    buttons_sizer->Add(btn_step, 0, wxALIGN_LEFT, 10);

    main_sizer->Add(label_sizer, 0, wxALIGN_CENTER_HORIZONTAL);
    main_sizer->Add(textbox_sizer, 0, wxALIGN_CENTER_HORIZONTAL);
    main_sizer->Add(buttons_sizer, 0, wxALIGN_CENTER_HORIZONTAL);

    SetSizer(main_sizer);
}

cMain::~cMain(){}

void cMain::OnButtonLoadClicked(wxCommandEvent &evt){
    tm.load(std::string(txtbox_input->GetValue().mb_str()));
    label1->SetLabelText(tm.toString());
}

void cMain::OnButtonRunClicked(wxCommandEvent &evt){
    tm.load(std::string(txtbox_input->GetValue().mb_str()));
    tm.run();
    label1->SetLabelText(tm.toString());
}

void cMain::OnButtonStepClicked(wxCommandEvent &evt){
    tm.step();
    label1->SetLabelText(tm.toString());
}

void cMain::OnMenuOpenClicked(wxCommandEvent &evt){
    wxFileDialog dlg(this, "Open config file", "", "", "all (*.conf, *txt)|*.conf;*.txt|.conf files (*.conf)|*.conf|.txt files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (dlg.ShowModal() == wxID_OK){
        evl::Evaluator ev(&tm);
        ev.evalFile(std::string(dlg.GetPath().c_str())); 
    }
}