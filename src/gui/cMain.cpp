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


cMain::cMain() :wxFrame(nullptr, wxID_ANY, "Turing Machine Emulator", wxDefaultPosition, wxDefaultSize){
    evl::Evaluator ev(&tm);
    
    //if (!ev.evalFile("example.txt"))
        //exit(1);
    
    this->SetMinSize(wxSize(640,480));
    
    /* Buttons */
    btn_load = new wxButton(this, BTN_LOAD, "Load", wxPoint(10,10), wxSize(100,30));
    btn_run = new wxButton(this, BTN_RUN, "Run", wxPoint(120,10), wxSize(100,30));
    btn_step = new wxButton(this, BTN_STEP, "Step", wxPoint(240,10), wxSize(100,30));
    
    txtbox_input = new wxTextCtrl(this, TXTBOX,"", wxPoint(10,80), wxSize(200,10));
    label1 = new wxStaticText(this, LABEL, "Output", wxPoint(10,120), wxSize(600,15));

    /* Menu */
    menu_bar = new wxMenuBar();
    this->SetMenuBar(menu_bar);

    wxMenu *menuFile = new wxMenu();
    menuFile->Append(MENU_OPEN, "Open");

    menu_bar->Append(menuFile,"File");
}

cMain::~cMain(){}

void cMain::OnButtonLoadClicked(wxCommandEvent &evt){
    tm.load(std::string(txtbox_input->GetValue().mb_str()));
    label1->SetLabelText(tm.toString());
}

void cMain::OnButtonRunClicked(wxCommandEvent &evt){
    tm.run();
    label1->SetLabelText(tm.toString());
}

void cMain::OnButtonStepClicked(wxCommandEvent &evt){
    tm.step();
    label1->SetLabelText(tm.toString());
}

void cMain::OnMenuOpenClicked(wxCommandEvent &evt){
    wxFileDialog dlg(this, "Open config file", "", "", ".txt files (*.txt)|*.txt| .conf files (*.conf)|*.conf", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (dlg.ShowModal() == wxID_OK){
        evl::Evaluator ev(&tm);
        ev.evalFile(std::string(dlg.GetPath().c_str())); 
    }
}