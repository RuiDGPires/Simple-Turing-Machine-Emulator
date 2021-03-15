#include "evaluator.hpp"

#if DEBUG
#include <iostream>
#endif

evl::MethodCall_t token_method;
evl::Connection_t token_conn;



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
        evalMethod();
    }else{
        expect(LINK);
        if (accept(LBRACK)){
            do{
                connection();
            }while(!accept(RBRACK));
        }else{
            connection();
        }
    }
    
    return true;
}


void evl::Evaluator::connection(){
    token_conn.to = current_tok.str;
    identifier();
    expect(CLN);
    if (accept(LBRACK)){
        do{
            rule();
        }while(!accept(RBRACK));
    }else{
        rule();
    }
}   

void evl::Evaluator::rule(){
    token_conn.in = current_tok.str[0];
    character();
    expect(LINK);
    token_conn.out = current_tok.str[0];
    character();
    expect(COMMA);
    direction();
    expect(SEMICLN);
    evalConnection();
}   

void evl::Evaluator::identifier(){ 
    expect(NAME);
}

void evl::Evaluator::character(){
    if (current_tok.str.length() != 1)
        throw UnexpectedTokenException(current_tok.str, current_tok.line);
    expect(NAME);
}

void evl::Evaluator::direction(){
    if (current_tok.str.length() != 1 || current_tok.symb != NAME)
        throw UnexpectedTokenException(current_tok.str, current_tok.line);

    switch(current_tok.str[0]){
        case 'r':
        case 'R':
            token_conn.dir = tmch::Dir::RIGHT;
            break;
        case 'l':
        case 'L':
            token_conn.dir = tmch::Dir::LEFT;
            break;
        case 's':
        case 'S':
            token_conn.dir = tmch::Dir::STAY;
            break;
        default:
            throw UnexpectedTokenException(current_tok.str, current_tok.line);
        break;
    }
    nextSym();
}

void evl::Evaluator::evalMethod(){
    if (token_method.str.compare("init") == 0){
        if (token_method.arguments.size() != 1)
            throw InvalidMethodException("init(state) takes 1 argument");
        tm->setInitial(*(token_method.arguments.begin()));
    }else if (token_method.str.compare("acc") == 0){
        if (token_method.arguments.size() != 1)
            throw InvalidMethodException("acc(state) takes 1 argument");
        tm->setAccept(*(token_method.arguments.begin()));
    }else if (token_method.str.compare("rej") == 0){
        if (token_method.arguments.size() != 1)
            throw InvalidMethodException("rej(state) takes 1 argument");
        tm->setReject(*(token_method.arguments.begin()));
    }else if (token_method.str.compare("rejectOthers") == 0){
        if (!token_method.arguments.empty())
            throw InvalidMethodException("rejectOthers() takes no arguments");
        tm->setRejectNoConnection(true);
    }else
        throw InvalidMethodException("Unkown method: " + token_method.str);
}
void evl::Evaluator::evalConnection(){
    if (!tm->stateExists(token_conn.from))
        tm->addState(token_conn.from);
    if (!tm->stateExists(token_conn.to))
        tm->addState(token_conn.to);
    tm->getState(token_conn.from).addRule(token_conn.in, token_conn.out, token_conn.dir, token_conn.to);
}