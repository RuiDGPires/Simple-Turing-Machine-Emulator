#include "include/evaluator.hpp"

#include <iostream>

#if DEBUG
void printList(std::list<evl::Token> l){
    for (auto const& i: l) {
        std::cout << i.str;
    }
    std::cout << std::endl;
}
#endif


evl::Evaluator::Evaluator(tmch::TuringMachine *tm){
    this->tm = tm;
}

evl::Evaluator::~Evaluator(){
    delete current_path;
}

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
    
    evl::Token t;
    t.line = -1;
    t.str = "";
    t.symb = evl::Symb::END;

    if (line.empty()){
        line.push_back(t);
        working_list.splice(working_list.end(), line);
        return;
    }

    size = line.size();
    std::list<evl::Token>::iterator it1 = std::next(line.begin(), size-1);

    while (it1->symb != evl::Symb::SEMICLN && it1->symb != evl::Symb::RBRACK){
        new_line = getLine();
        if (new_line.empty())
            throw SyntaxFailException(f.file_name, it1->line);
        size = new_line.size();
        it1 = std::next(new_line.begin(), size-1);
        line.splice(line.end(), new_line);
    }
    working_list.splice(working_list.end(), line);
    

}

bool evl::Evaluator::evalFile(Path file_name, Path current_path){
    working_list.clear();

    *this->current_path = current_path;
    f.setFile(current_path.join(file_name));


    std::list<evl::Token> line;
    f.openFile();
    tm->clear();
    try{
        configuration();
    }catch(evl::ParseFailException e){
        std::cout << "Parse error on line: " << e.line << std::endl;
        f.closeFile();
        return false;
    }catch(evl::SyntaxFailException e){
        std::cout << "Syntax error on line: " << e.line << std::endl;
        f.closeFile();
        return false;
    }catch(evl::UnexpectedTokenException e){
        std::cout << "Syntax error on line: " << e.line << std::endl << "Unexpected Token: " << e.str << std::endl;
        f.closeFile();
        return false;
    }catch(evl::InvalidMethodException e){
        std::cout << "Invalid Method: " << e.name << std::endl;
        f.closeFile();
        return false;
    }catch(evl::InvalidDecoratorException e){
        std::cout << "Invalid Decorator: " << e.name << std::endl;
        f.closeFile();
        return false;
    }catch(evl::ConnectionExistsException e){
        std::cout << "Connection is already declared: " << e.name << std::endl;
        f.closeFile();
        return false;
    }catch(evl::FileOpenFail e){
        std::cout << "Error opening file: " << e.file << std::endl;
        f.closeFile();
        return false;
    }catch(evl::GenericException e){
        switch(e){
            case END_OF_FILE:
                tm->reset();
                f.closeFile();
                return true;
                break;
            default:
                throw e;
        }
    } 
    tm->reset();
    f.closeFile();
    return true;
}


bool evl::Evaluator::evalFile(std::string file_name){
    return evalFile(Path(Path(file_name).getFileName()), Path(file_name).getParentPath());
}