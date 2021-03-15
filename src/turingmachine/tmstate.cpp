#include "turingmachine.hpp"

#if DEBUG
#include <iostream>
#endif

tmch::tmState::tmState(std::string name){
    this->name = name;
}

tmch::tmState::~tmState(){
    
}

std::string tmch::tmState::getName() const{
    return name;
}

bool tmch::tmState::hasMapping(char key){
    return mapping.count(key) > 0;
}

void tmch::tmState::addRule(char current, char dest, Dir dir, std::string state){
    if (hasMapping(current))
        throw RULE_EXISTS;
    else{
        Rule r;
        r.c = dest;
        r.dir = dir;
        r.state = state;
        mapping.insert({current, r});
    }

}

void tmch::tmState::accept(tmch::tmConfig *current_config){
    std::string right = current_config->getRight();
    std::string left = current_config->getLeft();
    
    if (!(hasMapping(right[0])))
        throw NO_CONNECTION;

    Rule r = mapping[right[0]];
    right[0] = r.c;
    
    if (r.dir == tmch::RIGHT){
        left.push_back(right[0]);
        right.erase(right.begin());
        if (right.empty())
            right.push_back(' ');
    }else if (r.dir == tmch::LEFT){
        std::string s;
        s.push_back(left[left.size() - 1]);
        left.pop_back();
        s.append(right);
        right = s;
    }


    current_config->setLeft(left);
    current_config->setRight(right);
    current_config->setState(r.state);
}
