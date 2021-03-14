#include "turingmachine/turingmachine.hpp"
#include <iostream>

#include "evaluator/evaluator.hpp"




int main(){
    tmch::TuringMachine tm;
    evl::Evaluator e(&tm);
    e.evalFile("example.txt");
    tm.load("0111");
    
    do{
        tm.step();
    }while(tm.state == tmch::State::RUNNING);
    std::cout << tm << std::endl;
    return 0;
}