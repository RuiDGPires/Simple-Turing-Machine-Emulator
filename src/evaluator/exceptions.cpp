#include "include/exceptions.hpp"

evl::ParseFailException::ParseFailException(int line){
    this->line = line;
}
evl::ParseFailException::~ParseFailException(){}

evl::SyntaxFailException::SyntaxFailException(int line){
    this->line = line;
}

evl::SyntaxFailException::~SyntaxFailException(){}


evl::UnexpectedTokenException::UnexpectedTokenException(std::string str, int line){
    this->line = line;
    this->str = str;
}

evl::UnexpectedTokenException::~UnexpectedTokenException(){}

evl::InvalidMethodException::InvalidMethodException(std::string name){
    this->name = name;
}

evl::InvalidMethodException::~InvalidMethodException(){}

evl::ConnectionExistsException::ConnectionExistsException(std::string name){
    this->name = name;
}

evl::ConnectionExistsException::~ConnectionExistsException(){}

evl::InvalidDecoratorException::InvalidDecoratorException(std::string name){
    this->name = name;
}

evl::InvalidDecoratorException::~InvalidDecoratorException(){}


