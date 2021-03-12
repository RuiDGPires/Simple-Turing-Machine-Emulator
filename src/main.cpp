#include "turingmachine/turingmachine.hpp"
#include <iostream>


int main(){
    tmch::TuringMachine tm;
    tm.setAccept("qac");
    tm.setReject("qrej");
    tm.setInitial("qi");
    tm.setRejectNoConnection(true);
    tm.addState("q1");
    tm.addState("q2");
    tm.addState("q3");

    tm.getState("qi").addRule('0', 'x',tmch::RIGHT, "q1");

    tm.getState("q1").addRule('0', 'x',tmch::RIGHT, "q2");

    tm.getState("q2").addRule('1', '1',tmch::RIGHT, "q3");

    tm.getState("q3").addRule('1', '1',tmch::RIGHT, "q3");

    tm.getState("q3").addRule(' ', ' ',tmch::RIGHT, "qac");


    tm.load("0111111");

    while(tm.state != tmch::ACCEPT && tm.state != tmch::REJECT){
        tm.step();
    }
    std::cout << tm << std::endl;
    
    return 0;
}