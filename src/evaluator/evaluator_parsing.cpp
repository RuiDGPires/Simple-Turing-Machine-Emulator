#include "include/evaluator.hpp"

#include <iostream>

void evl::Evaluator::nextSym(){
    if (working_list.empty()){
        requestLine();
    }
    current_tok = *(working_list.begin());
    working_list.pop_front();
}

bool evl::Evaluator::accept(Symb s){
    if (current_tok.symb == Symb::END)
        throw END_OF_FILE;

    if (current_tok.symb == s){
        nextSym();
        return true;
    }
    return false;
}

void evl::Evaluator::expect(Symb s){
    if (accept(s));
    else throw UnexpectedTokenException(f.file_name, current_tok.str, current_tok.line);
}

void evl::Evaluator::configuration(){
    nextSym();
    while(expression());
    throw SyntaxFailException(f.file_name, current_tok.line);
}


bool evl::Evaluator::expression(){
    evl::MethodCall_t token_method;
    evl::Connection_t token_conn;
    int decorators = 0;

    if (accept(DECORATOR))
        Decorators(&decorators);
    token_method.decorators |= decorators;
    token_conn.decorators |= decorators;

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
    int decorators = 0;
    if (accept(DECORATOR))
        Decorators(&decorators);
    t->decorators |= decorators;

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
    int decorators = 0;
    if (accept(DECORATOR))
        Decorators(&decorators);
    t->decorators |= decorators;
    
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
        throw UnexpectedTokenException(f.file_name, current_tok.str, current_tok.line);
    expect(NAME);
}

void evl::Evaluator::direction(evl::Connection_t *t){
    if (current_tok.str.length() != 1 || current_tok.symb != NAME)
        throw UnexpectedTokenException(f.file_name, current_tok.str, current_tok.line);

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
            throw UnexpectedTokenException(f.file_name, current_tok.str, current_tok.line);
        break;
    }
    nextSym();
}

int parseDecorator(std::string s){
    if (s.compare("Override"))
        return evl::Decorator::OVERRIDE;
    else if (s.compare("Reset"))
        return evl::Decorator::RESET;
    else if (s.compare("RejectOthers"))
        return evl::Decorator::RESET;
    else
        return -1;
}

void evl::Evaluator::Decorators(int *n){
    int d;
    do {
        d = parseDecorator(current_tok.str);
        if (d == -1)
            throw evl::InvalidDecoratorException(f.file_name, current_tok.str);
        *n |= d;
        expect(NAME);
    }while(accept(COMMA));
    expect(SEMICLN);
}


void evl::Evaluator::evalMethod(evl::MethodCall_t *t){
    // INIT
    if (t->str.compare("init") == 0){
        if (t->arguments.size() != 1)
            throw InvalidMethodException(f.file_name, "init(state) takes 1 argument");
        tm->setInitial(*(t->arguments.begin()));
    //ACC
    }else if (t->str.compare("acc") == 0){
        if (t->arguments.size() != 1)
            throw InvalidMethodException(f.file_name, "acc(state) takes 1 argument");
        tm->setAccept(*(t->arguments.begin()));
    //REJ
    }else if (t->str.compare("rej") == 0){
        if (t->arguments.size() != 1)
            throw InvalidMethodException(f.file_name, "rej(state) takes 1 argument");
        tm->setReject(*(t->arguments.begin()));
    //REJECT OTHERS
    }else if (t->str.compare("rejectOthers") == 0){
        if (!t->arguments.empty())
            throw InvalidMethodException(f.file_name, "rejectOthers() takes no arguments");
        tm->setRejectNoConnection(true);
    //EXTEND
    }else if (t->str.compare("extend") == 0){
        if (t->arguments.size() != 1)
            throw InvalidMethodException(f.file_name, "extend() takes 1 argument");
        Evaluator e(tm);
        e.evalFile(this->current_path->join(*(t->arguments.begin())));
    }else
        throw InvalidMethodException(f.file_name, "Unkown method: " + t->str);
}
void evl::Evaluator::evalConnection(evl::Connection_t *t){
    if (!tm->stateExists(t->from))
        tm->addState(t->from);
    if (!tm->stateExists(t->to))
        tm->addState(t->to);

    try{
    tm->getState(t->from).addRule(t->in, t->out, t->dir, t->to);
    }catch(tmch::Exception e){
        if (e == tmch::Exception::RULE_EXISTS)
            throw ConnectionExistsException(f.file_name, t->from + "->" + t->to + ": " + t->in);
    }
}