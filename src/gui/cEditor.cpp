#include "include/cMain.hpp"

enum{
    MARGIN_LINE_NUMBERS,
};

#define BACKGROUND_COLOR wxColour(13,5,23)
#define FOREGROUND_COLOR wxColour(250,255,255)
#define LINE_BACKGROUND_COLOR wxColour(15,5,32)
#define DEFAULT_FONT wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL)

#define MY_FOLDMARGIN 2
#define m_GCodecolor wxColor(255,130,0)

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

    wxString text=editor->GetText().Upper();
    //this->highlightSTCsyntax(0,editor->GetTextLength(),text);


    return editor;
}

void cMain::OnEditorStyleNeeded(wxStyledTextEvent &evt){
    size_t line_end=editor->LineFromPosition(editor->GetCurrentPos());
    size_t line_start=editor->LineFromPosition(editor->GetEndStyled());


    //if it is so small that all lines are visible, style the whole document
    if(editor->GetLineCount()==editor->LinesOnScreen()){
        line_start=0;
        line_end=editor->GetLineCount()-1;
    }
    if(line_end<line_start) {
        //that happens when you select parts that are in front of the styled area
        size_t temp=line_end;
        line_end=line_start;
        line_start=temp;
    }
    //style the line following the style area too (if present) in case fold level decreases in that one
    if(line_end<editor->GetLineCount()-1){
        line_end++;
    }
    //get exact start positions
    size_t startpos=editor->PositionFromLine(line_start);
    size_t endpos=(editor->GetLineEndPosition(line_end));

    wxString text=editor->GetTextRange(startpos,endpos).Upper();
    //call highlighting function
    this->highlightSTCsyntax(startpos,endpos,text);


}

void cMain::highlightSTCsyntax(size_t fromPos,size_t toPos, wxString &text) {
    //this vector will hold the start and end position of each word to highlight
    //if you want to highlight more than one, you should pass a whole class or struct containing the offsets
    std::vector<std::pair<size_t,size_t>>GcodeVector;
    //the following example is a quick and dirty parser for G-Codes.
    //it just iterates through the Text Range and finds "Gxx" where xx is a digit.
    //you could also use regex, but one can build a pretty fast routine based on single char evaluation
    size_t actual_cursorpos = 0;
    size_t startpos = 0;
    size_t end_of_text = text.length();
    bool word_boundary = true; //check for word boundary
    char actualchar;
    while (actual_cursorpos<end_of_text) {
        actualchar= text[actual_cursorpos];
        //check if syntax matches "G" followed by a couple of numbers
        if((actualchar=='#')&&(word_boundary==true)) {
            //this is a new G-Code, store startposition
            startpos=actual_cursorpos;
            word_boundary=false;
            actual_cursorpos++;
            if(actual_cursorpos<end_of_text) {
                //refresh actual character
                actualchar= text[actual_cursorpos];
            }
            //add digits
            while(actual_cursorpos<end_of_text) {
                actual_cursorpos++;
                actualchar= text[actual_cursorpos];
            }
            //check if word boundary occurs at end of digits
            if((actualchar=='\n')||(actualchar=='\r')||(actual_cursorpos==end_of_text)) {
                //success, append this one
                if((actual_cursorpos-startpos)>1) {
                    //success, append to vector. DO NOT FORGET THE OFFSET HERE! We start from fromPos, so we need to add this
                    GcodeVector.push_back(std::make_pair(startpos+fromPos, actual_cursorpos+fromPos));
                }
                word_boundary=true;
            }
        }
        if((actualchar==' ')||(actualchar=='\n')||(actualchar=='\r')||(actualchar=='\t')||(actual_cursorpos==end_of_text)) {
            word_boundary=true;
        }
        actual_cursorpos++;
    }
    //remove old styling
    editor->StartStyling(fromPos); //from here
    editor->SetStyling(toPos-fromPos,0); //with that length and style -> cleared
    //now style the G-Codes
    for (int i=0; i<GcodeVector.size(); i++) {
        size_t startpos=GcodeVector[i].first;
        size_t endpos=GcodeVector[i].second;
        size_t length=(endpos-startpos);
        editor->StartStyling(startpos);
        editor->SetStyling(length,19); //must match the style set above
    }
 }