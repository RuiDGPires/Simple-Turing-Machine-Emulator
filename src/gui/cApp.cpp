#include "include/cApp.hpp"
#include "../turingmachine/include/turingmachine.hpp"
#include "../evaluator/include/evaluator.hpp"

wxIMPLEMENT_APP(cApp);

cApp::cApp(){}
cApp::~cApp(){}

bool cApp::OnInit(){
    frame1 = new cMain();
    frame1->SetMinSize(wxDefaultSize);
    frame1->Show(true);
    return true;
}