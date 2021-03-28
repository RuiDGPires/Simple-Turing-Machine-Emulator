#define PY_SSIZE_T_CLEAN
#define CATCH_CONFIG_MAIN

#include "catch/catch.hpp"
#include "evaluator/include/evaluator.hpp"

#include <iostream>


TEST_CASE("Text syntax evaluation tests" ,"[Syntax]"){
    tmch::TuringMachine tm;
    std::cout.setstate(std::ios_base::failbit); // Disable prints
    evl::Evaluator e(&tm);

    
    REQUIRE(e.evalFile("tests/syntax/pass1.conf"));
    REQUIRE(e.evalFile("tests/syntax/pass2.conf"));
    REQUIRE(e.evalFile("tests/syntax/pass3.conf"));
    REQUIRE(e.evalFile("tests/syntax/pass4.conf"));
    REQUIRE(e.evalFile("tests/syntax/pass5.conf"));
    REQUIRE(e.evalFile("tests/syntax/pass6.conf"));
    REQUIRE(e.evalFile("tests/syntax/pass7.conf"));
    REQUIRE(e.evalFile("tests/syntax/pass8.conf"));
    REQUIRE(e.evalFile("tests/syntax/pass9.conf"));
    REQUIRE(e.evalFile("tests/syntax/pass10.conf"));
    REQUIRE(!e.evalFile("tests/syntax/fail1.conf"));
    REQUIRE(!e.evalFile("tests/syntax/fail2.conf"));
    REQUIRE(!e.evalFile("tests/syntax/fail3.conf")); 
    REQUIRE(!e.evalFile("tests/syntax/fail4.conf")); 
    REQUIRE(!e.evalFile("tests/syntax/fail5.conf")); 
    REQUIRE(!e.evalFile("tests/syntax/fail6.conf")); 
    REQUIRE(!e.evalFile("tests/syntax/fail7.conf")); 
    
}