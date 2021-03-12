#ifndef __EVALUATOR_HPP__
#define __EVALUATOR_HPP__

#include <list>
#include <string>
#include <fstream>

#include "../turingmachine/turingmachine.hpp"

namespace evl{
    enum Symb{NAME, LINK, LPAREN, RPAREN , LBRACK, RBRACK, SEMICLN, CLN, COMMA, END};
    struct Token{
        Symb symb;
        std::string str;
    };

    enum Exception{FILE_CLOSED, FILE_OPEN_FAIL, PARSE_FAIL};

    class FileReader{
        private:
            enum ReadState{NONE, NAME, SYMBOL, CHAR};
            std::string file_name;
            std::ifstream file;
            std::list<Token> parseLine(std::string line);
            std::list<Token> parseLine(std::string line, int size);
        public:
            FileReader();
            FileReader(std::string file_name);
            ~FileReader();
            void setFile(std::string file_name);
            std::list<Token> getLine();
            void openFile();
            void closeFile();
    };
    
    class Evaluator {
        private:
            tmch::TuringMachine tm;
        public:
            Evaluator();
            ~Evaluator();
            void evalFile(std::string file_name);
    };
}


#endif