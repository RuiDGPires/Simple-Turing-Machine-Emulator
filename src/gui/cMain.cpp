#include "include/cMain.hpp"

cMain::cMain() :wxFrame(nullptr, wxID_ANY, "Turing Machine Emulator", wxDefaultPosition, wxDefaultSize){
    this->SetMinSize(wxSize(640,480));
    txtbox_input = new wxTextCtrl(this, wxID_ANY,"", wxPoint(10,10), wxSize(200,10));
    menu_bar = new wxMenuBar();

    wxMenu *menu_file = new wxMenu();
    menu_file->Append(1001, "New");
    menu_file->Append(1001, "Open");
    menu_file->Append(1001, "Exit");
    menu_bar->Append(menu_file, "File");
    
}

cMain::~cMain(){}