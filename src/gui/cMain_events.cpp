#include "include/cMain.hpp"

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