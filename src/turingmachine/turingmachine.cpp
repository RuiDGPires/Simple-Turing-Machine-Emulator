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

tmch::tmConfig &tmch::TuringMachine::getConfig(){
    return this->config;
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

bool tmch::TuringMachine::hasInitial(){
    return !initial_state.empty();
}

void tmch::TuringMachine::setAccept(std::string key){
    accept_state = key;
}
bool tmch::TuringMachine::hasAccept(){
    return !accept_state.empty();
}

void tmch::TuringMachine::setReject(std::string key){
    reject_state = key;
}
bool tmch::TuringMachine::hasReject(){
    return !reject_state.empty();
}

void tmch::TuringMachine::addState(std::string name){
    if (stateExists(name))
        throw STATE_EXISTS;
    states.insert(std::pair<std::string, tmch::tmState>(name,tmState(name)));
}

void tmch::TuringMachine::removeState(std::string name){
    if (!stateExists(name))
        throw STATE_DOESNT_EXIST;
    states.erase(states.find(name));
}

void tmch::TuringMachine::reset(){
    config.setLeft(" ");
    config.setRight(" ");
    config.setState(initial_state);
}

void tmch::TuringMachine::clearExcessEmptySpaceRight(std::string &s, int *size){
    if (*size >= 1)
        if (s[*size-1] == ' ')
                while(*size > 1 && s[*size-2] == ' ')
                    s.erase(--(*size),1);
}

void tmch::TuringMachine::clearExcessEmptySpaceLeft(std::string &s, int *size){
    if (*size >= 1)
        if (s[0] == ' ')
            while(*size > 1 && s[1]==' '){
                s.erase(1,1);
                (*size)--;
            }
}
void tmch::TuringMachine::clearExcessEmptySpace(std::string &s, int *size){
   clearExcessEmptySpaceLeft(s, size);
   clearExcessEmptySpaceRight(s, size);
}


void tmch::TuringMachine::load(std::string s){
    this->reset();
    state = HALT;
    int size = s.size();

    clearExcessEmptySpace(s, &size);
    if (s[size-1] != ' ')
        s.push_back(' ');
    
    config.setRight(s);
}

void tmch::TuringMachine::step(){
    if (state == ACCEPT || state == REJECT || initial_state.compare("") == 0)
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

    /* Clear extra white space that might have been created
     * Ugly solution but it is what it is 
     */
    std::string s = config.getRight();
    int size = s.size();
    clearExcessEmptySpaceRight(s, &size);
    config.setRight(s);
    s = config.getLeft();
    size = s.size();
    clearExcessEmptySpaceLeft(s, &size);
    config.setLeft(s);


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

void tmch::TuringMachine::clear(){
    states.clear();
    initial_state.clear();
    accept_state.clear();
    reject_state.clear();
    reject_no_conn = false;
    this->reset();
}
std::string tmch::TuringMachine::stateToString() const{
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
    return s;
}

std::string tmch::TuringMachine::toString() const{
    
    return config.toString() + " >> " + stateToString(); 
}

tmch::tmState &tmch::TuringMachine::getState(std::string key){
    return states.at(key);
}

std::ostream& operator<< (std::ostream &out, tmch::TuringMachine const &tm){
    out << tm.toString();
    return out;
}

