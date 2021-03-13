#include "evaluator.hpp"

#include <iostream>

#if DEBUG
void printList(std::list<evl::Token> l){
    for (auto const& i: l) {
        std::cout << i.str;
    }
    std::cout << std::endl;
}
#endif

evl::Evaluator::Evaluator(){}

evl::Evaluator::~Evaluator(){}

std::list<evl::Token> evl::Evaluator::getLine(){
    std::list<evl::Token> line;

    do{
        if (f.isAtEnd())
            return line;

        line = f.getLine();
    }while(line.empty());


    return line;
}

/* Appends one full expression to this->working_list.
*  If there are no more expressions to be retrieved, throws END_OF_FILE. 
*  If end of file leads to an incomplete expression, throws SyntaxFailException
*/
void evl::Evaluator::requestLine(){
    std::list<evl::Token> line;
    std::list<evl::Token> new_line;
    int size;
    
    line = getLine();
    
    if (line.empty())
        throw END_OF_FILE;

    size = line.size();
    std::list<evl::Token>::iterator it1 = std::next(line.begin(), size-1);

    while (it1->symb != evl::Symb::SEMICLN && it1->symb != evl::Symb::RBRACK){
        new_line = getLine();
        //printList(new_line);
        if (new_line.empty())
            throw SyntaxFailException(it1->line);
        size = new_line.size();
        it1 = std::next(new_line.begin(), size-1);
        line.splice(line.end(), new_line);
    }

    working_list.splice(working_list.end(), line);
    

}

void evl::Evaluator::nextSym(){
    if (working_list.empty()){
        requestLine();
    }
    current_tok = *(working_list.begin());
    working_list.pop_front();
}
bool evl::Evaluator::accept(Symb s){
    if (current_tok.symb == s){
        nextSym();
        return true;
    }
    return false;
}
void evl::Evaluator::expect(Symb s){
    if (current_tok.symb == s){
        nextSym();
    }else
        throw UnexpectedTokenException(current_tok.str, current_tok.line);
}

void evl::Evaluator::evalFile(std::string file_name){
    f.setFile(file_name);
    std::list<evl::Token> line;
    f.openFile();

    do{
        try{
            requestLine();
            printList(working_list);
        }catch(evl::ParseFailException e){
            std::cerr << "Parse error on line: " << e.line << std::endl;
            f.closeFile();
            return;
        }catch(evl::SyntaxFailException e){
            std::cerr << "Syntax error on line: " << e.line << std::endl;
            f.closeFile();
            return;
        }catch(evl::UnexpectedTokenException e){
            std::cerr << "Syntax error on line: " << e.line << std::endl << "Unexpected Token: " << e.str << std::endl;
            f.closeFile();
            return;
        }catch(evl::GenericException e){
            switch(e){
                case END_OF_FILE:
                    std::cout << "End of file" << std::endl;
                    f.closeFile();
                    return;
                    break;
            }
        }
    }while(1);
    
    f.closeFile();
}