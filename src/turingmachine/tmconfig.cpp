#include "turingmachine.hpp"

tmch::tmConfig::tmConfig(){

}

tmch::tmConfig::~tmConfig(){
    
}

void tmch::tmConfig::setRight(std::string right){
    this->right = right;
}
void tmch::tmConfig::setLeft(std::string left){
    this->left = left;
}
void tmch::tmConfig::setState(std::string state){
    this->state = state;
}

std::string tmch::tmConfig::getState() const{
    return state;
}
std::string tmch::tmConfig::getRight() const{
    return right;
}
std::string tmch::tmConfig::getLeft() const{
    return left;
}
std::string tmch::tmConfig::toString() const{
    return "(" + left + "|" + state + "|" + right + ")";
}

