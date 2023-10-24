#pragma once
#include <any>
#include <string>
#include <utility>
#include "TokenType.h"
class Token {
public:
const TokenType type;
const std::string lexeme;
const std::any literal;
const int line;
Token (TokenType type, std::string lexeme, std::any literal, int line):
    type{type},
    lexeme{std::move(lexeme)},
    literal{std::move(literal)},
    line{line}
    {}
std::string toString() const {
    std::string text;
    switch(type){
        case(IDENTIFIER):
        text = lexeme;
        break;
        case(STRING):
        text = std::any_cast<std::string>(literal);
        break;
      case(NUMBER):
        text = std::to_string(std::any_cast<double>(literal));
        break;
      case(TRUE):
        text = "t";
        break;
      case(FALSE):
        text = "f";
        break;
      default:
        text = "nil";
    }
    return ::toString(type) + " " + lexeme + " " + text;
}
};