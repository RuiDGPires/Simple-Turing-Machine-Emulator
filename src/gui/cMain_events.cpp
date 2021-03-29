#include "include/cMain.hpp"

#include <wx/utils.h>

/* Events */
void cMain::OnButtonLoadClicked(wxCommandEvent &evt){
    {
    wxCriticalSectionLocker enter(m_tmCS);
    tm.load(std::string(txtbox_input->GetValue().mb_str()));
    }
    setLabels(tm);
}

void cMain::OnButtonEvalClicked(wxCommandEvent &evt){
    wxCriticalSectionLocker enter(m_tmCS);
    tm.load(std::string(txtbox_input->GetValue().mb_str()));
    tm.run();
    setLabels(tm);
}

void cMain::OnButtonRunClicked(wxCommandEvent &evt){
    if (!running)
        doStartThread();
    else
        doStopThread();
}

void cMain::OnButtonStepClicked(wxCommandEvent &evt){
    wxCriticalSectionLocker enter(m_tmCS);
    tm.step();
    setLabels(tm);
}

void cMain::OnMenuOpenClicked(wxCommandEvent &evt){
    wxFileDialog dlg(this, "Open config file", "", "", "all (*.conf, *txt)|*.conf;*.txt|.conf files (*.conf)|*.conf|.txt files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    wxCriticalSectionLocker enter(m_tmCS);

    if (dlg.ShowModal() == wxID_OK){
        evl::Evaluator ev(&tm);
        ev.evalFile(std::string(dlg.GetPath().c_str())); 
        wxFile newFile(dlg.GetPath().c_str());

        wxString s;
        newFile.ReadAll(&s);
        editor->SetText(s);
        wxString text=editor->GetText().Upper();
        this->highlightSTCsyntax(0,editor->GetTextLength(),text);
    }

    tm.load(std::string(txtbox_input->GetValue().mb_str()));
    
    
    setLabels(tm);
}

void cMain::OnResizing(wxSizeEvent &evt){
    evt.Skip();
    this->SetMinClientSize(wxSize(label_sizer->GetMinSize().GetWidth(), DEFAULT_MAIN_SIZE.GetHeight()));
}

void cMain::OnThreadCompletion(wxCommandEvent &evt){
    running = false;
    wxMessageOutputDebug().Printf("Thread work completed");
    btn_run->SetLabelText("Run");
    btn_eval->Enable();
    btn_step->Enable();
    btn_load->Enable();
    menu_bar->Enable();
}

void cMain::OnThreadUpdate(wxCommandEvent &evt){
    setLabels(tm);
}