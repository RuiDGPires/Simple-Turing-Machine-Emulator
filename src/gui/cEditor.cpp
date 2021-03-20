#include "include/cMain.hpp"

enum{
    MARGIN_LINE_NUMBERS,
};

#define BACKGROUND_COLOR wxColour(13,5,23)
#define FOREGROUND_COLOR wxColour(250,255,255)
#define LINE_BACKGROUND_COLOR wxColour(15,5,32)
#define DEFAULT_FONT wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL)

wxStyledTextCtrl *cMain::setupEditor(wxSize size){
    
    wxStyledTextCtrl *editor = new wxStyledTextCtrl(this, EDITOR, wxPoint(0,0), size);
    editor->StyleSetBackground(wxSTC_STYLE_DEFAULT, BACKGROUND_COLOR);
    editor->StyleSetForeground(wxSTC_STYLE_DEFAULT, FOREGROUND_COLOR);
    editor->StyleSetFont(wxSTC_STYLE_DEFAULT, DEFAULT_FONT);
    editor->SetCaretForeground(FOREGROUND_COLOR);


    editor->StyleClearAll();
    editor->SetMarginWidth (MARGIN_LINE_NUMBERS, 50);
    editor->StyleSetForeground (wxSTC_STYLE_LINENUMBER, wxColour (250, 250, 255) );
    editor->StyleSetBackground (wxSTC_STYLE_LINENUMBER, LINE_BACKGROUND_COLOR);
    editor->SetMarginType (MARGIN_LINE_NUMBERS, wxSTC_MARGIN_NUMBER);

    return editor;
}