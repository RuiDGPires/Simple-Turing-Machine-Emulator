#include "include/evaluator.hpp"

#if DEBUG
#include <iostream>
#endif

evl::FileReader::FileReader(){}

evl::FileReader::FileReader(std::string file_name){
    setFile(file_name);
}

evl::FileReader::~FileReader(){}

void evl::FileReader::setFile(std::string file_name){
    this->file_name = file_name;
    is_at_end = false;
}

std::list<evl::Token> evl::FileReader::getLine(){
    if (!(file.is_open()))
        throw evl::FILE_CLOSED;

    char c;
    std::string line;
    while(file.get(c)){
        if (c == '\n'){
            line_n++;
            break;
        }
        line.push_back(c);
        if (c == ';' || c == '}') break;
    }
    
    if (c == EOF || file.peek() == EOF){
        is_at_end = true;
    }
    line.push_back('\0');
    return parseLine(line, line_n);
}

void evl::FileReader::openFile(){
    file.open(file_name, std::ios::in);

    if (!(file.is_open()))
        throw FILE_OPEN_FAIL;
}
void evl::FileReader::closeFile(){
    file.close();
}

std::list<evl::Token> evl::FileReader::parseLine(std::string line, int n){
    return parseLine(line, line.size(), n);
}

////////////////////////////////////

bool isLetter(char c){
    return (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || (c == '_'));
}
bool isNumber(char c){
    return ((c >= '0') && (c <= '9'));
}
bool isSymbol(char c){
    return c == '(' || c == ')' || c == '-' || c == '>' || c == ':' || c == '{' || c == '}' || c == ';' || c == ',';
}

void dumpToken(std::list<evl::Token> *l, std::string *buffer, evl::Symb sy, int line_n){
    evl::Token t;
    t.str = *buffer;
    t.symb = sy;
    t.line = line_n;
    buffer->clear();
    l->push_back(t);
}

std::list<evl::Token> evl::FileReader::parseLine(std::string line, int size, int n){
    int i= 0;
    std::list<evl::Token> ret;

    std::string buffer;
    ReadState state = evl::FileReader::ReadState::NONE;

    while(i < size){
        switch(state){
            case evl::FileReader::ReadState::NONE:
                if (isLetter(line[i]) || isNumber(line[i])){
                    state = evl::FileReader::ReadState::NAME;
                } else if (line[i] == '\''){
                    state = evl::FileReader::ReadState::CHAR;
                    i++;
                } else if (isSymbol(line[i])){
                    state = evl::FileReader::ReadState::SYMBOL;
                }else if (line[i] == '"'){
                    state = evl::FileReader::ReadState::QUOTE;
                    i++;
                }else if (line[i] == ' ' || line[i] == '\0' || line[i] == '\n' || line[i] == '\r' || line[i] == '\t')
                    i++;
                else if (line[i] == '#')
                    return ret;
                else
                    throw ParseFailException(n);
                break;
            case evl::FileReader::ReadState::NAME:
                if (!(isLetter(line[i]) || isNumber(line[i]))){
                    state = evl::FileReader::ReadState::NONE;
                    dumpToken(&ret, &buffer, evl::Symb::NAME, n);
                }else
                    buffer.push_back(line[i++]);
                
                break;
            case evl::FileReader::ReadState::QUOTE:
                if (line[i] == '"'){
                    if (buffer.empty())
                        throw ParseFailException(n);
                    else{
                        dumpToken(&ret, &buffer, evl::Symb::NAME, n);
                        state = evl::FileReader::ReadState::NONE;
                        i++;
                    }
                }else if (line[i] == '\\'){
                    buffer.push_back(line[++i]);
                    i++;
                }else
                    buffer.push_back(line[i++]);
                break;
            case evl::FileReader::ReadState::SYMBOL:
                buffer.push_back(line[i]);

                if (line[i] == '-'){
                    i++;
                    break;
                }else if (line[i] == '>'){
                    if (buffer.length() != 2)
                        throw ParseFailException(n);
                    if (buffer[0] != '-')
                        throw ParseFailException(n);
                    dumpToken(&ret, &buffer, evl::Symb::LINK, n);
                    state = evl::FileReader::ReadState::NONE;
                    i++;
                    break;
                }
                
                if (line[i] == '(')
                    dumpToken(&ret, &buffer, evl::Symb::LPAREN, n);
                else if (line[i] == ')')
                    dumpToken(&ret, &buffer, evl::Symb::RPAREN, n);
                else if (line[i] == '{')
                    dumpToken(&ret, &buffer, evl::Symb::LBRACK, n);
                else if (line[i] == '}')
                    dumpToken(&ret, &buffer, evl::Symb::RBRACK, n);
                else if (line[i] == ';')
                    dumpToken(&ret, &buffer, evl::Symb::SEMICLN, n);
                else if (line[i] == ':')
                    dumpToken(&ret, &buffer, evl::Symb::CLN, n);
                else if (line[i] == ',')
                    dumpToken(&ret, &buffer, evl::Symb::COMMA, n);
                state = evl::FileReader::ReadState::NONE;
                i++;
                break;
            case evl::FileReader::ReadState::CHAR:
                if (line[i] == '\''){
                    if (buffer.length() != 1)
                        throw ParseFailException(n);
                    else{
                        dumpToken(&ret, &buffer, evl::Symb::NAME, n);
                        i++;
                        state = evl::FileReader::ReadState::NONE;
                        break;
                    }
                }

                if (!(buffer.empty()))
                    throw ParseFailException(n);
                buffer.push_back(line[i]);
                i++;
                break;
        }
    }
    return ret;
}

bool evl::FileReader::isAtEnd(){
    return is_at_end;
}