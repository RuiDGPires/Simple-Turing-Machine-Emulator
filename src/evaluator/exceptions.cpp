#include "include/exceptions.hpp"

evl::ParseFailException::ParseFailException(std::string file, int line){
    this->file = file;
    this->line = line;
}
evl::ParseFailException::~ParseFailException(){}

evl::SyntaxFailException::SyntaxFailException(std::string file, int line){
    this->file = file;
    this->line = line;
}

evl::SyntaxFailException::~SyntaxFailException(){}

evl::MainStateExistsException::MainStateExistsException(std::string file, std::string state){
    this->file = file;
    this->state = state;
}
evl::MainStateExistsException::~MainStateExistsException(){}

evl::MainStateDoesntExistException::MainStateDoesntExistException(std::string file, std::string state){
    this->file = file;
    this->state = state;
}
evl::MainStateDoesntExistException::~MainStateDoesntExistException(){}


evl::UnexpectedTokenException::UnexpectedTokenException(std::string file, std::string str, int line){
    this->file = file;
    this->line = line;
    this->str = str;
}

evl::UnexpectedTokenException::~UnexpectedTokenException(){}

evl::InvalidMethodException::InvalidMethodException(std::string file, std::string name){
    this->file = file;
    this->name = name;
}

evl::InvalidMethodException::~InvalidMethodException(){}

evl::ConnectionExistsException::ConnectionExistsException(std::string file, std::string name){
    this->file = file;
    this->name = name;
}

evl::ConnectionExistsException::~ConnectionExistsException(){}

evl::ConnectionDoesntExistException::ConnectionDoesntExistException(std::string file, std::string name){
    this->file = file;
    this->name = name;
}

evl::ConnectionDoesntExistException::~ConnectionDoesntExistException(){}

evl::InvalidDecoratorException::InvalidDecoratorException(std::string file, std::string name){
    this->file = file;
    this->name = name;
}

evl::InvalidDecoratorException::~InvalidDecoratorException(){}


evl::FileOpenFail::FileOpenFail(std::string file){
    this->file = file;
}

evl::FileOpenFail::~FileOpenFail(){}

