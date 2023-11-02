#pragma once
#include <string>

enum TokenType{
// Single Character
LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR, RAISETO,
BNRYAND, BNRYOR, COLON,
// Multi Character
BANG, BANG_EQUAL,
EQUAL, EQUAL_EQUAL,
GREATER, GREATER_EQUAL,
LESS, LESS_EQUAL,
LOGICAND, LOGICOR,
// Literals 
IDENTIFIER, STRING, NUMBER,
// Keywords
AND, CLASS, ELSE, FALSE, DEF, FOR, IF, NIL, OR,
SHOW, READ, RETURN, SUPER, THIS, TRUE, WHILE, VAR,
BOOL, SIZEOF,
// Indentation
INDENT, DEDENT,
// EOF TOKEN
END_OF_FILE
};

std::string toString(TokenType type) {
static const std::string strings[] = {
    "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE",
    "COMMA", "DOT", "MINUS", "PLUS", "SEMICOLON", "SLASH", "STAR", "RAISETO",
    "BNRYAND", "BNRYOR", "COLON",
    "BANG", "BANG_EQUAL",
    "EQUAL", "EQUAL_EQUAL",
    "GREATER", "GREATER_EQUAL",
    "LESS", "LESS_EQUAL",
    "LOGICAND", "LOGICOR",
    "IDENTIFIER", "STRING", "NUMBER",
    "AND", "CLASS", "ELSE", "FALSE", "DEF", "FOR", "IF", "NIL", "OR",
    "SHOW", "READ", "RETURN", "SUPER", "THIS", "TRUE", "WHILE", "VAR",
    "BOOL", "SIZEOF",
    "INDENT", "DEDENT",
    "END_OF_FILE"
};
return strings[static_cast<int>(type)];
}
