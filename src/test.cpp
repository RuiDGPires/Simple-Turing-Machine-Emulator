#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"
#include "evaluator/include/evaluator.hpp"

#include <iostream>


TEST_CASE("Text syntax evaluation tests" ,"[Syntax]"){
    //std::cout.setstate(std::ios_base::failbit);
    evl::Evaluator e;
    REQUIRE(e.evalFile("tests/pass1.conf"));
    REQUIRE(e.evalFile("tests/pass2.conf"));
    REQUIRE(e.evalFile("tests/pass3.conf"));
    REQUIRE(!e.evalFile("tests/fail1.conf"));
    REQUIRE(!e.evalFile("tests/fail2.conf"));
    REQUIRE(!e.evalFile("tests/fail3.conf"));
}