#include "include/cMain.hpp"

#include <iostream>

enum{BTN, TXTBOX, LABEL};


wxBEGIN_EVENT_TABLE(cMain, wxFrame)
    EVT_BUTTON(BTN, cMain::OnButtonClicked)
wxEND_EVENT_TABLE()


cMain::cMain() :wxFrame(nullptr, wxID_ANY, "Turing Machine Emulator", wxDefaultPosition, wxDefaultSize){
    evl::Evaluator ev(&tm);
    
    if (!ev.evalFile("example.txt"))
        exit(1);
    
    this->SetMinSize(wxSize(640,480));
    
    btn = new wxButton(this, BTN, "Button", wxPoint(10,10), wxSize(150,50));
    txtbox_input = new wxTextCtrl(this, TXTBOX,"", wxPoint(10,80), wxSize(200,10));
    
    label1 = new wxStaticText(this, LABEL, "Output", wxPoint(10,120), wxSize(600,15));
}

cMain::~cMain(){}


void cMain::OnButtonClicked(wxCommandEvent &evt){
    tm.load(std::string(txtbox_input->GetValue().mb_str()));
    tm.run();
    label1->SetLabelText(tm.toString());
}