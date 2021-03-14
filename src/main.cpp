#include "turingmachine/turingmachine.hpp"
#include <iostream>

#include "evaluator/evaluator.hpp"


int main(){
    tmch::TuringMachine tm;
    evl::Evaluator e(&tm);
    if (e.evalFile("example.txt")){
        tm.load("0111");
        tm.run();
        std::cout << tm << std::endl;
        return 0;
    }
}