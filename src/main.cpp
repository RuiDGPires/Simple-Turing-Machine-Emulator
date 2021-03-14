#include "turingmachine/turingmachine.hpp"
#include <iostream>

#include "evaluator/evaluator.hpp"

#define PRINT_TITLE() (std::cout << "Simple Turing Machine Emulator v0.1" <<std::endl, (void) 0)
#define PRINT_USAGE()(std::cout << "Usage:\n\ttm <config file> <input>" << std::endl, (void)0)


int main(int argc, char *argv[]){
    if (argc != 3){
        PRINT_TITLE();
        PRINT_USAGE();
        return 0;
    }
    tmch::TuringMachine tm;
    evl::Evaluator e(&tm);
    try{
        if (e.evalFile(argv[1])){
            tm.load(argv[2]);
            tm.run();
            std::cout << tm << std::endl;
            return 0;
        }
    }catch(evl::GenericException e){
        if (e == evl::GenericException::FILE_OPEN_FAIL){
            PRINT_TITLE();
            std::cout << "An error occured opening config file: " << argv[1] << std::endl;
            PRINT_USAGE();
        }
    }
    
    
    
}