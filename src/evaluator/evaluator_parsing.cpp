#include "include/evaluator.hpp"

#if DEBUG
#include <iostream>
#endif


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
    if (accept(s));
    else throw UnexpectedTokenException(current_tok.str, current_tok.line);
}

void evl::Evaluator::configuration(){
    nextSym();
    while(expression());
    throw SyntaxFailException(current_tok.line);
}


bool evl::Evaluator::expression(){
    evl::MethodCall_t token_method;
    evl::Connection_t token_conn;

    token_method.str = current_tok.str;
    token_conn.from = current_tok.str;
    token_method.arguments.clear();
    
    identifier();
    if (accept(LPAREN)){
        if (accept(RPAREN));
        else{
            do{
                token_method.arguments.push_back(current_tok.str);
                identifier();
            }while(accept(COMMA));
            expect(RPAREN);
        }
        expect(SEMICLN);
        evalMethod(&token_method);
    }else{
        expect(LINK);
        if (accept(LBRACK)){
            do{
                connection(&token_conn);
            }while(!accept(RBRACK));
        }else{
            connection(&token_conn);
        }
    }
    
    return true;
}


void evl::Evaluator::connection(Connection_t *t){
    t->to = current_tok.str;
    identifier();
    expect(CLN);
    if (accept(LBRACK)){
        do{
            rule(t);
        }while(!accept(RBRACK));
    }else{
        rule(t);
    }
}   

void evl::Evaluator::rule(evl::Connection_t *t){
    t->in = current_tok.str[0];
    character();
    expect(LINK);
    t->out = current_tok.str[0];
    character();
    expect(COMMA);
    direction(t);
    expect(SEMICLN);
    evalConnection(t);
}   

void evl::Evaluator::identifier(){ 
    expect(NAME);
}

void evl::Evaluator::character(){
    if (current_tok.str.length() != 1)
        throw UnexpectedTokenException(current_tok.str, current_tok.line);
    expect(NAME);
}

void evl::Evaluator::direction(evl::Connection_t *t){
    if (current_tok.str.length() != 1 || current_tok.symb != NAME)
        throw UnexpectedTokenException(current_tok.str, current_tok.line);

    switch(current_tok.str[0]){
        case 'r':
        case 'R':
            t->dir = tmch::Dir::RIGHT;
            break;
        case 'l':
        case 'L':
            t->dir = tmch::Dir::LEFT;
            break;
        case 's':
        case 'S':
            t->dir = tmch::Dir::STAY;
            break;
        default:
            throw UnexpectedTokenException(current_tok.str, current_tok.line);
        break;
    }
    nextSym();
}

void evl::Evaluator::evalMethod(evl::MethodCall_t *t){
    // INIT
    if (t->str.compare("init") == 0){
        if (t->arguments.size() != 1)
            throw InvalidMethodException("init(state) takes 1 argument");
        tm->setInitial(*(t->arguments.begin()));
    //ACC
    }else if (t->str.compare("acc") == 0){
        if (t->arguments.size() != 1)
            throw InvalidMethodException("acc(state) takes 1 argument");
        tm->setAccept(*(t->arguments.begin()));
    //REJ
    }else if (t->str.compare("rej") == 0){
        if (t->arguments.size() != 1)
            throw InvalidMethodException("rej(state) takes 1 argument");
        tm->setReject(*(t->arguments.begin()));
    //REJECT OTHERS
    }else if (t->str.compare("rejectOthers") == 0){
        if (!t->arguments.empty())
            throw InvalidMethodException("rejectOthers() takes no arguments");
        tm->setRejectNoConnection(true);
    //EXTEND
    }else if (t->str.compare("extend") == 0){
        if (t->arguments.size() != 1)
            throw InvalidMethodException("extend() takes 1 argument");
        tm->setRejectNoConnection(true);
    }else
        throw InvalidMethodException("Unkown method: " + t->str);
}
void evl::Evaluator::evalConnection(evl::Connection_t *t){
    if (!tm->stateExists(t->from))
        tm->addState(t->from);
    if (!tm->stateExists(t->to))
        tm->addState(t->to);
    tm->getState(t->from).addRule(t->in, t->out, t->dir, t->to);
}