#include "evaluator.hpp"

#include <iostream>
evl::Evaluator::Evaluator(){}

evl::Evaluator::~Evaluator(){}

std::list<evl::Token> evl::Evaluator::requestLine(evl::FileReader *f){
    std::list<evl::Token> line;

    do{
        if (f->isAtEnd())
            return line;

        line = f->getLine();
    }while(line.empty());


    return line;
}

void evl::Evaluator::evalFile(std::string file_name){
    evl::FileReader f(file_name);
    std::list<evl::Token> line;
    f.openFile();

    do{
        line = requestLine(&f);
        for (evl::Token const &t : line)
            std::cout << t.str + " ";
        std::cout << std::endl;
    }while(!line.empty());
    
    f.closeFile();
}