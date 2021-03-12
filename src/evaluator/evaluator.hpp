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

    class ParseFailException {
        public:
            int line;
            ParseFailException(int line);
            ~ParseFailException();
    };

    enum Exception{FILE_CLOSED, FILE_OPEN_FAIL, END_OF_FILE};

    class FileReader{
        private:
            int line_n = 0;
            bool is_at_end = false;
            enum ReadState{NONE, NAME, SYMBOL, CHAR};
            std::string file_name;
            std::ifstream file;
            std::list<Token> parseLine(std::string line, int n);
            std::list<Token> parseLine(std::string line, int size, int n);
        public:
            FileReader();
            FileReader(std::string file_name);
            ~FileReader();
            void setFile(std::string file_name);
            std::list<Token> getLine();
            void openFile();
            void closeFile();
            bool isAtEnd();
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