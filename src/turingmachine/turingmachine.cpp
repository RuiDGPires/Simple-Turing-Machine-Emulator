#include "include/turingmachine.hpp"

/////////////////////////
// Class TuringMachine //

#if DEBUG
#include <iostream>
#endif


tmch::TuringMachine::TuringMachine(){
}
tmch::TuringMachine::~TuringMachine(){   
}

bool tmch::TuringMachine::stateExists(std::string key){
    if (key.compare(initial_state) == 0)
        return true;
    if (key.compare(accept_state) == 0)
        return true;
    if (key.compare(reject_state) == 0)
        return true;

    return states.count(key)>0;
}

void tmch::TuringMachine::setInitial(std::string key){
    std::map<std::string, tmState>::iterator it = states.find(key);

    if (it == states.end()){
        addState(key);
    }
    initial_state = key;
}

void tmch::TuringMachine::setAccept(std::string key){
    accept_state = key;
}

void tmch::TuringMachine::setReject(std::string key){
    reject_state = key;
}

void tmch::TuringMachine::addState(std::string name){
    if (stateExists(name))
        throw STATE_EXISTS;
    states.insert(std::pair<std::string, tmch::tmState>(name,tmState(name)));
}

void tmch::TuringMachine::reset(){
    config.setLeft(" ");
    config.setRight(" ");
    config.setState(initial_state);
}

void tmch::TuringMachine::load(std::string s){
    this->reset();
    state = HALT;
    s.push_back(' ');
    config.setRight(s);
}

void tmch::TuringMachine::step(){
    if (state == ACCEPT || state == REJECT)
        return;
        
    state = RUNNING;

    try{
        states.at(config.getState()).accept(&config);
    } catch(Exception e){
        if (e == NO_CONNECTION){
            if (reject_no_conn)
                config.setState(reject_state);
            else
                state = HALT;
        }
    }
    
    if (config.getState().compare(accept_state) == 0)
        state = ACCEPT;
    else if (config.getState().compare(reject_state) == 0)
        state = REJECT;
}

void tmch::TuringMachine::run(){
    do{
        this->step();
    }while(state == State::RUNNING);
}

void tmch::TuringMachine::setRejectNoConnection(bool v){
    reject_no_conn = v;
}

std::string tmch::TuringMachine::toString() const{
    std::string s;
    switch(state){  
        case tmch::RUNNING:
            s = "Running";
            break;
        case tmch::ACCEPT:
            s = "Accepted";
            break;
        case tmch::REJECT:
            s = "Rejected";
            break;
        case tmch::HALT:
        default:
            s = "Halt";
            break;
    }
    return config.toString() + " >> " + s; 
}

tmch::tmState &tmch::TuringMachine::getState(std::string key){
    return states.at(key);
}

std::ostream& operator<< (std::ostream &out, tmch::TuringMachine const &tm){
    out << tm.toString();
    return out;
}

