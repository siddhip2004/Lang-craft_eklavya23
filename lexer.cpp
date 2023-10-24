#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iterator>     // std::advance
#include <list>         // std::list
#include <cstring>
#include<Token.h>
#include<Error.h>
#include <string_view>
#include <utility>      


using namespace std;
class Scanner
{
    int start = 0;
    int current = 0;
    int line = 1;
    string_view source;

    public:
    
    Scanner(string_view source) 
    : source {source}
    {}
  
  private:
   
     static const map<string, TokenType> keywords;
     vector<Token> tokens;

 
  public:
   vector<Token> scanTokens() {
    while (!isAtEnd()) {
      start = current;
      scanToken();
    }

     tokens.emplace_back(new Token(eof, "", nullptr, line));
    return tokens;
   }

//vector<string> :: iterator ptr = tokens.begin();             //no need
private:
void scanToken() {
    char c = advance();
    switch (c) {
      case '(': addToken(LEFT_PAREN); break;
      case ')': addToken(RIGHT_PAREN); break;
      case '{': addToken(LEFT_BRACE); break;
      case '}': addToken(RIGHT_BRACE); break;
      case ',': addToken(COMMA); break;
      case '.': addToken(DOT); break;
      case '-': addToken(MINUS); break;
      case '+': addToken(PLUS); break;
      //case ';': addToken("SEMICOLON"); break;
      case '*': addToken(STAR); break;
      //case '[0-9]+': addToken("NUMBER");break;
     
      case '!':
        addToken(match('=') ? "BANG_EQUAL" : "BANG");
        break;
      case '=':
        addToken(match('=') ? "EQUAL_EQUAL" : "EQUAL");
        break;
      case '<':
        addToken(match('=') ? "LESS_EQUAL" : "LESS");
        break;
      case '>':
        addToken(match('=') ? "GREATER_EQUAL" : "GREATER");
        break;
       
      case '/':

            if(match('/'))
            {
                while(peek() != '\n' && !isAtEnd())
                {
                    advance();
                }
            }
            
            else 
            {
                addToken(SLASH);
            }
            
            break;

      case ' ':
      case '\r':
      case '\t':
       
        break;

      case '\n':
        line++;
        break;
       
        case '"': string(); break;
       
        default:
        if (isDigit(c)) {
          number();

        } else if (isAlpha(c)) {
          identifier();

         } 
         else 
         {
           error(line, "Unexpected character.");
         }

        break;
    }
}

void identifier()
{       
           while(isAlphaNumeric(peek()))
           {
               advance();
           }
           
           std::string text = std::string{ source.substr(start, current-start)};
            
            TokenType type;
               auto match = keywords.find(text);
            if (match == keywords.end()) 
            {
              type = IDENTIFIER;
            } else 
            {        
              type = match->second;
            }

}

void number()
{
    while(isDigit(peek()))
    {
        advance();
    }
    
    if(peek() == '.' && isDigit(peekNext()))
    {
            advance();
            
            while(isDigit(peek()))
            {
                advance();
            }
    }
    
    
    addToken(NUMBER,  stod(std::string{source.substr(start, current-start)}));
    
}

void string()
{
    while(peek() != '"' && !isAtEnd())
    {
        if(peek() == '\n')
        {
            line++;
        }
        
        else{
        advance();
        }
    }
    
     if (isAtEnd()) {
       error(line, "Unterminated string.");
       return;
     }
    
    else 
    {
        advance();
    
        std::string value{source.substr(start + 1, current - 2 - start)};
        addToken(STRING, value);
    }
    
}

bool match(char expected)
{
    if(isAtEnd())
    {
        return FALSE;
    }
    
    else if(source[current] != expected)
    {
        return FALSE;
    }
    
    else 
    {
        current++;
        return TRUE;
    }
}

char peek()
{
    if(isAtEnd())
    {
        return '\0';
    }
    
    else 
    {
        return source[current];
    }
}

char peekNext()
{
    if(current + 1 >= source.length())
    {
        return '\0';
    }
    
    else 
    {
        return source[current+1];
    }
}

bool isAlpha(char c)
{
    if((c>= 'a' && c<='z') || (c>='A' && c<='Z') || c=='_')
    {
        return c;
    }
}
bool isAlphaNumeric(char c)
{
    return (isAlpha(c) || isDigit(c));
}

bool isDigit(char c)
{
    if(c>= '0' && c<='9')
    {
        return c;
    }
}

bool isAtEnd()
{
    if(current >= source.size())
    {
        return current;
    }
}

char advance()
{
    return source[current++];
}

 void addToken(TokenType type)
 {
     addToken(type, nullptr);
 }

 void addToken(TokenType type, any literal)
 {
     std::string text{source.substr(start, current - start)};

    tokens.emplace_back(type, move(text), move(literal),line);
 }

};

const std::map<std::string, TokenType> Scanner::keywords =
{
  {"and",    TokenType::AND},
  {"class",  TokenType::CLASS},
  {"else",   TokenType::ELSE},
  {"false",  TokenType::FALSE},
  {"for",    TokenType::FOR},
  {"fun",    TokenType::FUN},
  {"if",     TokenType::IF},
  {"NULL",   TokenType::NULL},
  {"or",     TokenType::OR},
  {"print",  TokenType::PRINT},
  {"return", TokenType::RETURN},
  {"this",   TokenType::THIS},
  {"true",   TokenType::TRUE},
  {"while",  TokenType::WHILE},
};

