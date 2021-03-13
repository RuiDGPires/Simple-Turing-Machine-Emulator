#include "evaluator.hpp"

#include <iostream>

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
    identifier();
    if (accept(LPAREN)){
        if (accept(RPAREN));
        else{
            do{
                identifier();
            }while(accept(COMMA));
            expect(RPAREN);
        }
        expect(SEMICLN);
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
    character();
    expect(LINK);
    character();
    expect(COMMA);
    direction();
    expect(SEMICLN);
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
    if (current_tok.str[0] != 'r' && current_tok.str[0] != 'R' && current_tok.str[0] != 'l' && current_tok.str[0] != 'L' && current_tok.str[0] != 's' && current_tok.str[0] != 'S')
        throw UnexpectedTokenException(current_tok.str, current_tok.line);
    nextSym();
}