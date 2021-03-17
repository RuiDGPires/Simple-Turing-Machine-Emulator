#include <iostream>

#include "turingmachine/include/turingmachine.hpp"
#include "evaluator/include/evaluator.hpp"

#define PRINT_TITLE() (std::cout << "Simple Turing Machine Emulator v1.0" <<std::endl, (void) 0)
#define PRINT_USAGE() (std::cout << "Usage:\n\ttm <config file> <input>" << std::endl, (void) 0)


int main(int argc, char *argv[]){
    if (argc != 3){
        PRINT_TITLE();
        PRINT_USAGE();
        return 0;
    }
    tmch::TuringMachine *tm = new tmch::TuringMachine();
    evl::Evaluator e(tm);
    try{
        if (e.evalFile(argv[1])){
            tm->load(argv[2]);
            tm->run();
            std::cout << tm->toString() << std::endl;
            return 0;
        }
    }catch(evl::GenericException e){
        if (e == evl::GenericException::FILE_OPEN_FAIL){
            PRINT_TITLE();
            std::cout << "An error occured opening config file: " << argv[1] << std::endl;
            PRINT_USAGE();
        }
    }
    delete tm;
    
    
}