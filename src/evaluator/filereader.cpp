#include "evaluator.hpp"

#include <iostream>

evl::FileReader::FileReader(){}

evl::FileReader::FileReader(std::string file_name){
    setFile(file_name);
}

evl::FileReader::~FileReader(){}

void evl::FileReader::setFile(std::string file_name){
    this->file_name = file_name;
}

std::list<evl::Token> evl::FileReader::getLine(){
    if (!(file.is_open()))
        throw evl::FILE_CLOSED;

    char c;
    std::string line;

    while(file.get(c)){
        line.push_back(c);
        if (c == ';') break;
    }
    line.push_back('\0');
    return parseLine(line);
}

void evl::FileReader::openFile(){
    file.open(file_name, std::ios::in);

    if (!(file.is_open()))
        throw FILE_OPEN_FAIL;
}
void evl::FileReader::closeFile(){
    file.close();
}

std::list<evl::Token> evl::FileReader::parseLine(std::string line){
    return parseLine(line, line.size());
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

void dumpToken(std::list<evl::Token> *l, std::string *buffer, evl::Symb sy){
    evl::Token t;
    t.str = *buffer;
    t.symb = sy;
    buffer->clear();
    l->push_back(t);
}

std::list<evl::Token> evl::FileReader::parseLine(std::string line, int size){
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
                }else if (line[i] == ' ')
                    i++;
                else if (line[i] == '\0')
                    i++;
                else
                  throw PARSE_FAIL;
                break;
            case evl::FileReader::ReadState::NAME:
                if (!(isLetter(line[i]) || isNumber(line[i]))){
                    state = evl::FileReader::ReadState::NONE;
                    dumpToken(&ret, &buffer, evl::Symb::NAME);
                }else{
                    buffer.push_back(line[i]);
                    i++;
                }
                break;
            case evl::FileReader::ReadState::SYMBOL:
                buffer.push_back(line[i]);

                if (line[i] == '-'){
                    i++;
                    break;
                }else if (line[i] == '>'){
                    if (buffer.length() != 2)
                        throw PARSE_FAIL;
                    if (buffer[0] != '-')
                        throw PARSE_FAIL;
                    dumpToken(&ret, &buffer, evl::Symb::LINK);
                    state = evl::FileReader::ReadState::NONE;
                    i++;
                    break;
                }
                
                if (line[i] == '(')
                    dumpToken(&ret, &buffer, evl::Symb::LPAREN);
                else if (line[i] == ')')
                    dumpToken(&ret, &buffer, evl::Symb::RPAREN);
                else if (line[i] == '{')
                    dumpToken(&ret, &buffer, evl::Symb::LBRACK);
                else if (line[i] == '}')
                    dumpToken(&ret, &buffer, evl::Symb::RBRACK);
                else if (line[i] == ';')
                    dumpToken(&ret, &buffer, evl::Symb::SEMICLN);
                else if (line[i] == ':')
                    dumpToken(&ret, &buffer, evl::Symb::CLN);
                else if (line[i] == ',')
                    dumpToken(&ret, &buffer, evl::Symb::COMMA);
                state = evl::FileReader::ReadState::NONE;
                i++;
                break;
            case evl::FileReader::ReadState::CHAR:
                if (line[i] == '\''){
                    if (buffer.length() != 1)
                        throw PARSE_FAIL;
                    else{
                        dumpToken(&ret, &buffer, evl::Symb::NAME);
                        i++;
                        state = evl::FileReader::ReadState::NONE;
                        break;
                    }
                }

                if (!(buffer.empty()))
                    throw PARSE_FAIL;
                buffer.push_back(line[i]);
                i++;
                state = evl::FileReader::ReadState::NONE;
                break;
        }
    }
    return ret;
}