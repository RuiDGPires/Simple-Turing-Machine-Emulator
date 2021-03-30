#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#include <string>
#include <vector>

#include <wx/wx.h>
#include <wx/stc/stc.h>

enum Styles{COMMENT = 10, NAME, METHOD, LINK, CHAR, BRACK, PAREN, SEMICLN, DECORATOR};

void styleParseString(size_t fromPos,size_t toPos, wxString &text, wxStyledTextCtrl *editor);

#endif