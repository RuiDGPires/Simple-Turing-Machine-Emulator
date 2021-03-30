#include "include/cMain.hpp"
#include "lexer.hpp"

enum{
    MARGIN_LINE_NUMBERS,
};

#define BACKGROUND_COLOR wxColour(13,5,23)
#define FOREGROUND_COLOR wxColour(250,255,255)
#define LINE_BACKGROUND_COLOR wxColour(15,5,32)
#define DEFAULT_FONT wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL)

#define MY_FOLDMARGIN 2
#define COLOR_COMMENTS wxColor  (130,130,130)
#define COLOR_NAMES wxColor     (206, 215, 217)
#define COLOR_METHODS wxColor   (78, 139, 237)
#define COLOR_LINKS wxColor     (237, 179, 5)
#define COLOR_CHARS wxColor     (240, 237, 151)
#define COLOR_BRACK wxColor     (43, 255, 227)
#define COLOR_PAREN wxColor     (218, 211, 230)
#define COLOR_SEMICLN wxColor   (90, 98, 99)
#define COLOR_DECORATORS wxColor(93, 120, 96)

wxStyledTextCtrl *cMain::setupEditor(wxSize size){
    
    wxStyledTextCtrl *editor = new wxStyledTextCtrl(this, EDITOR, wxPoint(0,0), size);
    editor->StyleSetBackground(wxSTC_STYLE_DEFAULT, BACKGROUND_COLOR);
    editor->StyleSetForeground(wxSTC_STYLE_DEFAULT, FOREGROUND_COLOR);
    editor->StyleSetFont(wxSTC_STYLE_DEFAULT, DEFAULT_FONT);
    editor->SetCaretForeground(FOREGROUND_COLOR);

    editor->SetLexer(wxSTC_LEX_CONTAINER); //Set to custom lexer
    editor->Bind(wxEVT_STC_STYLENEEDED, &cMain::OnEditorStyleNeeded, this);

    editor->StyleClearAll();
    editor->SetMarginWidth (MARGIN_LINE_NUMBERS, 50);
    editor->StyleSetForeground (wxSTC_STYLE_LINENUMBER, wxColour (250, 250, 255) );
    editor->StyleSetBackground (wxSTC_STYLE_LINENUMBER, LINE_BACKGROUND_COLOR);
    editor->SetMarginType (MARGIN_LINE_NUMBERS, wxSTC_MARGIN_NUMBER);
    
    //set colors for highlighting
    editor->StyleSetForeground(Styles::COMMENT,COLOR_COMMENTS);
    editor->StyleSetForeground(Styles::NAME,COLOR_NAMES);
    editor->StyleSetForeground(Styles::METHOD,COLOR_METHODS);
    editor->StyleSetForeground(Styles::LINK,COLOR_LINKS);
    editor->StyleSetForeground(Styles::CHAR,COLOR_CHARS);
    editor->StyleSetForeground(Styles::BRACK,COLOR_BRACK);
    editor->StyleSetForeground(Styles::PAREN,COLOR_PAREN);
    editor->StyleSetForeground(Styles::SEMICLN,COLOR_SEMICLN);
    editor->StyleSetForeground(Styles::DECORATOR,COLOR_DECORATORS);

    wxString text=editor->GetText().Upper();
    this->highlightSTCsyntax(0,editor->GetTextLength(),text);


    return editor;
}

void cMain::OnEditorStyleNeeded(wxStyledTextEvent &evt){
    size_t line_start=0;

    
    //get exact start positions
    size_t startpos=editor->PositionFromLine(line_start);
    size_t endpos=(editor->GetLineEndPosition(editor->GetEndAtLastLine()));

    wxString text=editor->GetText();
    //call highlighting function
    this->highlightSTCsyntax(0,text.length(),text);
}

void cMain::highlightSTCsyntax(size_t fromPos,size_t toPos, wxString &text) {
    if (fromPos == 0 && toPos == 0)
        return;
    
    styleParseString(fromPos, toPos, text, editor);
 }