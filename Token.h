#pragma once 

#include<iostream>
#include<string>
#include"TokenType.h"
#include<any>
#include<utility>   //std:: move

using namespace std;

class Token
{
    public:
    const TokenType type;
    const string lexeme;
    const any literal;
    const int line;

    Token(TokenType type, string lexeme, any literal, int line)
    : type{type}, lexeme{move(lexeme)}, literal{move(literal)}, line{line}
    {}
   
    string toString() const{
        string literal_text;

        switch (type)
        {
            case(IDENTIFIER):
            literal_text = lexeme;
            break;

            case(NUMBER):
            literal_text = to_string(any_cast<double>(literal));
            break;

            case(STRING):
            literal_text = any_cast<string>(literal);
            break;

            case(TRUE):
            literal_text = "t";

            case(FALSE):
            literal_text = "f";
            break;

            default:
            literal_text = "NULL";
        }

        return :: toString(type) + " " + lexeme + " " + literal_text;
    }
};
