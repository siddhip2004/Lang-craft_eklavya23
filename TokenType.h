#include<iostream>
#include<string>

using namespace std;


enum TokenType
{
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, COLON, SLASH, STAR,

  
  BANG, BANG_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

  
  IDENTIFIER, STRING, NUMBER,

  //KEYWORDS

  AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NULL, OR,
  PRINT, RETURN, THIS, TRUE,  WHILE,

  eof
};

string toString(TokenType type) 
{
  static const std::string strings[] = {
    "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE",
    "COMMA", "DOT", "MINUS", "PLUS", "SEMICOLON", "SLASH", "STAR",
    "BANG", "BANG_EQUAL",
    "EQUAL", "EQUAL_EQUAL",
    "GREATER", "GREATER_EQUAL",
    "LESS", "LESS_EQUAL",
    "IDENTIFIER", "STRING", "NUMBER",
    "AND", "CLASS", "ELSE", "FALSE", "FOR", "IF", "NULL", "OR",
    "PRINT", "RETURN", "THIS", "TRUE", "WHILE","eof"
  };

  return strings[static_cast<int>(type)];
}