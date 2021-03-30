#include "lexer.hpp"

enum State{sNONE, sNAME, sCHAR, sSYMBOL, sQUOTE, sCOMMENT, sDECORATOR};

bool isCharLetter(char c){
    return (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || (c == '_'));
}
bool isCharNumber(char c){
    return ((c >= '0') && (c <= '9'));
}
bool isCharSymbol(char c){
    return c == '(' || c == ')' || c == '-' || c == '>' || c == ':' || c == '{' || c == '}' || c == ';' || c == ',' || c == '@';
}


void dumpToken(wxStyledTextCtrl *editor, size_t fromPos,  size_t startpos, size_t endpos, int style){
    size_t length=(endpos-startpos);

    editor->StartStyling(startpos + fromPos);
    editor->SetStyling(length, style); //must match the style set above
}

void styleParseString(size_t fromPos,size_t toPos, wxString &text, wxStyledTextCtrl *editor){
    size_t actual_cursorpos = 0, startpos = 0, end_of_text = text.length();
    char actualchar;

   
    State state = State::sNONE;

    //remove old styling
    editor->StartStyling(fromPos); //from here
    editor->SetStyling(toPos-fromPos,0); //with that length and style -> cleared
    

    while (actual_cursorpos < end_of_text) {
        actualchar = text[actual_cursorpos];

        switch(state){
            case State::sNONE:
                if (isCharLetter(actualchar) || isCharNumber(actualchar)){
                    state = State::sNAME;
                    startpos = actual_cursorpos;
                }else if (actualchar == '\''){
                    state = State::sCHAR;
                    startpos = actual_cursorpos++;
                }else if (isCharSymbol(actualchar)){
                    state = State::sSYMBOL;
                    startpos = actual_cursorpos;
                }else if (actualchar == '"'){
                    state = State::sQUOTE;
                    startpos = actual_cursorpos++;
                }else if (actualchar == '#'){
                    state = State::sCOMMENT;
                    startpos = actual_cursorpos++;
                }else{
                    actual_cursorpos++;
                }
                break;
            case State::sNAME:
                if (!(isCharLetter(actualchar) || isCharNumber(actualchar))){
                    state = State::sNONE;
                    if (actualchar == '(')
                        dumpToken(editor, fromPos, startpos, actual_cursorpos, Styles::METHOD);
                    else
                        dumpToken(editor, fromPos, startpos, actual_cursorpos, Styles::NAME);
                }else
                    actual_cursorpos++;
                break;
            case State::sQUOTE:
                if (actualchar == '"'){
                    state = State::sNONE;
                    dumpToken(editor, fromPos, startpos, ++actual_cursorpos, Styles::NAME);
                }else{
                    actual_cursorpos++;
                }
                break;
            case State::sSYMBOL:
                if (actualchar == '-' && actual_cursorpos != end_of_text -1){
                    if (text[actual_cursorpos+1] == '>'){
                        dumpToken(editor, fromPos, startpos, actual_cursorpos+2, Styles::LINK);
                        actual_cursorpos += 2;
                        state = State::sNONE;
                        break;
                    }
                }

                state = State::sNONE;
                if (actualchar == '{' || actualchar == '}')
                    dumpToken(editor, fromPos, actual_cursorpos, actual_cursorpos+1, Styles::BRACK);
                else if (actualchar == '(' || actualchar == ')')
                    dumpToken(editor, fromPos, actual_cursorpos, actual_cursorpos+1, Styles::PAREN);
                else if (actualchar == ';')
                    dumpToken(editor, fromPos, actual_cursorpos, actual_cursorpos+1, Styles::SEMICLN);
                else if (actualchar == '@')
                    state = State::sDECORATOR;

                actual_cursorpos++;
                break;
            case State::sCHAR:
                if (actualchar == '\''){
                    dumpToken(editor, fromPos, startpos, actual_cursorpos+1, Styles::CHAR);
                    state =  State::sNONE;
                }
                actual_cursorpos++;
                break;
            case State::sDECORATOR:
                if (actualchar == ';'){
                    dumpToken(editor, fromPos, startpos, actual_cursorpos+1, Styles::DECORATOR);
                    state = State::sNONE;
                }
                actual_cursorpos++;
                break;
            case State::sCOMMENT:
                if (actualchar == '\n'){
                    state = State::sNONE;
                    dumpToken(editor, fromPos, startpos, actual_cursorpos, Styles::COMMENT);
                }
                actual_cursorpos++;
                break;
        }
    }
}