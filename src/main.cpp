#include "turingmachine/turingmachine.hpp"
#include <iostream>

#include "evaluator/evaluator.hpp"




int main(){
    try{
        evl::FileReader f("example.txt");
        f.openFile();
        std::list<evl::Token> line = f.getLine();
        for (evl::Token const &t : line)
            std::cout << t.str + "-" << "\n";

        f.closeFile();
    }catch(evl::Exception e){
        std::cerr << e << std::endl;
    }
}