#ifndef __EVALUATOR_HPP__
#define __EVALUATOR_HPP__

#include <list>
#include <string>
#include <fstream>

#include "../turingmachine/turingmachine.hpp"
#include "exceptions.hpp"

namespace evl{
    enum Symb{NAME, LINK, LPAREN, RPAREN , LBRACK, RBRACK, SEMICLN, CLN, COMMA, END};
    struct Token{
        Symb symb;
        std::string str;
        int line;
    };

    struct MethodCall_t{
        std::string str;
        std::list<std::string> arguments;
    };

    struct Connection_t{
        std::string from, to;
        char in, out;
        tmch::Dir dir;
    };

    class FileReader{
        private:
            int line_n = 1;
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
            tmch::TuringMachine *tm;
            Token current_tok;
            std::list<evl::Token> working_list;

            evl::FileReader f;
            std::list<evl::Token> getLine();
            

            void requestLine();
            bool accept(Symb s);
            void expect(Symb s);
            void nextSym();

            //Stuff for evaluating
            void configuration();
            bool expression();
            bool arguments();
            void connection();
            void rule();
            void identifier();
            void character();
            void direction();

            void evalMethod();
            void evalConnection();

        public:
            Evaluator(tmch::TuringMachine *tm);
            ~Evaluator();
            bool evalFile(std::string file_name);
    };
}


#endif