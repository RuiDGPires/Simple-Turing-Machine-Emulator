#ifndef __EVALUATOR_HPP__
#define __EVALUATOR_HPP__

#include <list>
#include <string>
#include <fstream>

#include "../../turingmachine/include/turingmachine.hpp"
#include "exceptions.hpp"
#include "../../pathLib/include/pathLib.hpp"

namespace evl{
    enum Symb{NAME, LINK, LPAREN, RPAREN , LBRACK, RBRACK, SEMICLN, CLN, COMMA, DECORATOR, END};
    enum Decorator{OVERRIDE = 1, RESET = 2, REJECTOTHERS = 4, SURPRESS = 8};

    struct Token{
        Symb symb;
        std::string str;
        int line;
    };

    struct MethodCall_t{
        std::string str;
        std::list<std::string> arguments;
        int decorators;
    };

    struct Connection_t{
        std::string from, to;
        char in, out;
        tmch::Dir dir;
        int decorators;
    };

    class FileReader{
        private: 
            enum ReadState{NONE, NAME, SYMBOL, CHAR, QUOTE};
        private:
            int line_n = 1;
            bool is_at_end = false;
            std::ifstream file;
        private:
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
            std::list<Token> parseLine(std::string line, int n);
        public:
            std::string file_name;
    };
    
    class Evaluator {
        private:
            tmch::TuringMachine *tm;
            Token current_tok;
            std::list<evl::Token> working_list;
            evl::FileReader f;

            Path *current_path = new Path("");
            
        private:
            std::list<evl::Token> getLine();
            
            void requestLine();
            bool accept(Symb s);
            void expect(Symb s);
            void nextSym();

            //Stuff for evaluating
            void configuration();
            bool expression();
            bool arguments();
            void connection(Connection_t *t);
            void rule(Connection_t *t);
            void identifier();
            void character();
            void direction(Connection_t *t);
            void Decorators(int *n);

            void evalMethod(MethodCall_t *t);
            void evalConnection(Connection_t *t);
            
            bool evalFile(Path path, Path current_path);
        public:
            Evaluator(tmch::TuringMachine *tm);
            ~Evaluator();
            bool evalFile(std::string file_name);
    };
}


#endif