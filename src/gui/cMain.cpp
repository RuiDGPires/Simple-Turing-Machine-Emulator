#include "include/cMain.hpp"

cMain::cMain() :wxFrame(nullptr, wxID_ANY, "Turing Machine Emulator"){
    txtbox_input = new wxTextCtrl(this, wxID_ANY,"", wxPoint(10,10), wxSize(200,10));
}

cMain::~cMain(){}