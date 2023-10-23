#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iterator>     // std::advance
#include <list>         // std::list
#include <cstring>


using namespace std;
class Scanner
{
    public:
    string source;
    Scanner(string source) {
    this->source = source;
  }
  
  private:
   
   static  map<string, string> keywords;
   
   void initializeKeywords() {
    keywords["and"] = "AND";
    keywords["class"] = "CLASS";
    keywords["else"] = "ELSE";
    keywords["false"] = "FALSE";
    keywords["for"] = "FOR";
    keywords["fun"] = "FUN";
    keywords["if"] = "IF";
    keywords["nil"] = "NIL";
    keywords["or"] = "OR";
    keywords["print"] = "PRINT";
    keywords["return"] = "RETURN";
    keywords["super"] = "SUPER";
    keywords["this"] = "THIS";
    keywords["true"] = "TRUE";
    keywords["var"] = "VAR";
    keywords["while"] ="WHILE";

}

vector<Token> tokens;

 int start = 0;
 int current = 0;
 int line = 1;

//   List<Token> scanTokens() {
    while (!isAtEnd()) {
      start = current;
      scanToken();
    }

     tokens.push_back(new Token(EOF, "", null, line));
    return tokens;
  

//vector<string> :: iterator ptr = tokens.begin();             //no need

void scanToken() {
    char c = advance();
    switch (c) {
      case '(': addToken("LEFT_PAREN"); break;
      case ')': addToken("RIGHT_PAREN"); break;
      case '{': addToken("LEFT_BRACE"); break;
      case '}': addToken("RIGHT_BRACE"); break;
      case ',': addToken("COMMA"); break;
      case '.': addToken("DOT"); break;
      case '-': addToken("MINUS"); break;
      case '+': addToken("PLUS"); break;
      case ';': addToken("SEMICOLON"); break;
      case '*': addToken("STAR"); break;
      case '/': addToken("SLASH"); break;
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
       
        case '"': sstring(); break;
       
        default:
        if (isDigit(c)) {
          number();

        } else if (isAlpha(c)) {
          identifier();

         } //else {
        //   Lox.error(line, "Unexpected character.");
        // }

        break;
    }
}

void identifier()
{       
           while(isAlphaNumeric(peek()))
           {
               advance();
           }
           
           string text;
               text = source.substr(start, current);

               //TokenType type = keywords.get(text);

            //   if(type == null)
            //   {
            //       type = IDENTIFIER;
            //   }
            //addToken(type);
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
    
    else {
    addToken(NUMBER, stod(source.substr(start, current)));
    }
}

void sstring()
{
    while(peek() != '"' && !isAtEnd())
    {
        if(peek() == '\n')
        {
            line++;
        }
        advance();
    }
    
    // if (isAtEnd()) {
    //   Lox.error(line, "Unterminated string.");
    //   return;
    // }
    
    else 
    {
        advance();
    
        string value;
        value = source.substr(start + 1, current -1);
        addToken(string, value);
    }
    
}

bool match(char expected)
{
    if(isAtEnd())
    {
        return false;
    }
    
    else if(source[current] != expected)
    {
        return false;
    }
    
    else 
    {
        current++;
        return true;
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

// void addToken(TokenType type)
// {
//     addToken(type, null);
// }

// void addToken(TokenType type, Object literal)
// {
//     string text;
//     text = source.substr(start, current);
//     tokens.add(new Token(type, text, literal, line));
// }

};



