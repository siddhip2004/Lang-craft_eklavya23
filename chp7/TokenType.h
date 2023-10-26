#pragma once

#include <string>

enum TokenType {
  // Single-character tokens.
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SLASH, STAR,

  // One or two character tokens.
  AND,BANG, BANG_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,OR,

  // Literals.
  IDENTIFIER, STRING, NUMBER,

  // Keywords.
  BOOL,CLASS, ELSE, FALSE,  FOR, IF, NIL, 
  READ, RETURN, SHOW, THIS, TRUE,  WHILE ,

  eof
};

std::string toString(TokenType type) {
  static const std::string strings[] = {
    "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE",
    "COMMA", "DOT", "MINUS", "PLUS",  "SLASH", "STAR",
    "AND","BANG", "BANG_EQUAL",
    "EQUAL", "EQUAL_EQUAL",
    "GREATER", "GREATER_EQUAL",
    "LESS", "LESS_EQUAL","OR",
    "IDENTIFIER", "STRING", "NUMBER",
    "BOOL", "CLASS", "ELSE", "FALSE","FOR", "IF", "NIL",
    "READ", "RETURN",  "SHOW", "THIS", "TRUE",  "WHILE", 
    
    "eof"
  };

  return strings[static_cast<int>(type)];
}
