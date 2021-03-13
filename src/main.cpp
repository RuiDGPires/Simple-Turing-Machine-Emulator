#include "turingmachine/turingmachine.hpp"
#include <iostream>

#include "evaluator/evaluator.hpp"




int main(){
    evl::Evaluator e;
    e.evalFile("tests/fail1.conf");
    return 0;
}