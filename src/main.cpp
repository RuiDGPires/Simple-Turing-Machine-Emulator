#include "turingmachine/turingmachine.hpp"
#include <iostream>

#include "evaluator/evaluator.hpp"




int main(){
    evl::FileReader f("example.txt");
    f.openFile();

    try{
        while(!f.isAtEnd()){
            std::list<evl::Token> line = f.getLine();
            if (!line.empty()){
                for (evl::Token const &t : line)
                    std::cout << t.str + " ";
                std::cout << std::endl;
            }
        }
    }catch(evl::ParseFailException e){
        f.closeFile();
        std::cout << "Error on line: " + e.line << std::endl;
    }catch(evl::Exception e){
        if (e == evl::Exception::END_OF_FILE)
            std::cerr << "EOF" << std::endl;
        else
            std::cerr << e << std::endl;
    }
    f.closeFile();
}