#include "turingmachine/turingmachine.hpp"
#include <iostream>

#include "evaluator/evaluator.hpp"




int main(){
    evl::Evaluator e;
    e.evalFile("example.txt");
    return 0;
}