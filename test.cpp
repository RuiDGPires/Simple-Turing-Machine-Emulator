#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "turingmachine.hpp"


TEST_CASE("Basic Turing Machines" ,"[factorial]"){
    tmch::TuringMachine tm;

    tm.setAccept("qac");
    tm.setReject("qrej");
    tm.setInitial("qi");
    tm.getState("qi").addRule('1', '1',tmch::RIGHT, "qac");
    tm.getState("qi").addRule('0', '0',tmch::RIGHT, "qrej");
    tm.load("1");
}