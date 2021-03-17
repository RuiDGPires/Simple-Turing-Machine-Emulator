#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"
#include "evaluator/include/evaluator.hpp"

#include <iostream>


TEST_CASE("Text syntax evaluation tests" ,"[Syntax]"){
    tmch::TuringMachine tm;
    std::cout.setstate(std::ios_base::failbit);
    evl::Evaluator e(&tm);
    REQUIRE(e.evalFile("tests/syntax/pass1.conf"));
    REQUIRE(e.evalFile("tests/syntax/pass2.conf"));
    REQUIRE(e.evalFile("tests/syntax/pass3.conf"));
    REQUIRE(!e.evalFile("tests/syntax/fail1.conf"));
    REQUIRE(!e.evalFile("tests/syntax/fail2.conf"));
    REQUIRE(!e.evalFile("tests/syntax/fail3.conf"));
}