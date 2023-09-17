#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

enum TokenType {
// Keywords
AND, CLASS, ELSE, FALSE, FOR, IF, IN, OR, RETURN, TRUE, WHILE, ELIF, BOOL, INT, FLOAT, NUMBER, CHAR, NOT, GLOBAL, EXCEPT, SHOW, CONTINUE, BREAK, WITH, READ,
IDENTIFIER, LITERAL, EOF_TOKEN,
// Delimiters
LPAREN, RPAREN, L_SQR, R_SQR, LCURLY, RCURLY, COMMA, DOT, SEMICOLON, COLON, QUOTE, APOSTROPHE, BACKSLASH, UNDERSCORE, HASH, DOLLAR, PERCENT, 
AMPERSAND,
// Operators
PLUS, MINUS, MULTIPLY, DIVIDE, MODULO, POWER, ASSIGN, EQ, NOT_EQ, LESS_T, GREATER_T, LESS_T_EQ, GREATER_T_EQ, INCRE, DECRE
};

string list[65] = {"AND", "CLASS", "ELSE", "FALSE", "FOR", "IF", "IN", "OR", "RETURN", "TRUE", "WHILE", "ELIF", "BOOL", "INT", "FLOAT", "NUMBER", "CHAR", "NOT", "GLOBAL", "EXCEPT", "SHOW", "CONTINUE", "BREAK", "WITH", "READ",
"IDENTIFIER", "LITERAL", "EOF_TOKEN", "LPAREN", "RPAREN", "L_SQR", "R_SQR", "LCURLY", "RCURLY", "COMMA", "DOT", "SEMICOLON", "COLON", "QUOTE", "APOSTROPHE", "BACKSLASH", "UNDERSCORE", "HASH", "DOLLAR", "PERCENT", 
"AMPERSAND", "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MODULO", "POWER", "ASSIGN", "EQ", "NOT_EQ", "LESS_T", "GREATER_T", "LESS_T_EQ", "GREATER_T_EQ", "INCRE", "DECRE"};

struct Token {
    TokenType type;
    string lexeme;
    //string literal;
    int line;
};

class Scanner {
private:
    string source;
    vector<Token> tokens;
    int start;
    int current;
    int line;
    static map<string, TokenType> keywords;

public:
    Scanner(const string& source) : source(source), start(0), current(0), line(1) {}

    vector<Token> scanTokens() {
        while (!isAtEnd()) {
            start = current;
            scanToken();
        }

        tokens.push_back(Token{EOF_TOKEN, "", line});
        return tokens;
    }

private:

static void initializeKeywords() {
        keywords["and"] = AND;
        keywords["class"] = CLASS;
        keywords["else"] = ELSE;
        keywords["false"] = FALSE;
        keywords["for"] = FOR;
        keywords["if"] = IF;
        keywords["in"] = IN;
        keywords["or"] = OR;
        keywords["return"] = RETURN;
        keywords["true"] = TRUE;
        keywords["while"] = WHILE;
        keywords["elif"] = ELIF;
        keywords["bool"] = BOOL;
        keywords["int"] = INT;
        keywords["float"] = FLOAT;
        keywords["char"] = CHAR;
        keywords["not"] = NOT;
        keywords["global"] = GLOBAL;
        keywords["except"] = EXCEPT;
        keywords["continue"] = CONTINUE;
        keywords["show"] = SHOW;
        keywords["read"] = READ;
        keywords["break"] = BREAK;
        keywords["with"] = WITH;
}

bool isAtEnd() {
    return current >= source.length();
}

void scanToken(){
    char c = advance();
        switch (c) {
            case '(': addToken(LPAREN); break;
            case ')': addToken(RPAREN); break;
            case '{': addToken(LCURLY); break;
            case '}': addToken(RCURLY); break;
            case '[': addToken(L_SQR); break;
            case ']': addToken(R_SQR); break;
            case ',': addToken(COMMA); break;
            case '.': addToken(DOT); break;
            case ':': addToken(COLON); break;
            case '\'': addToken(APOSTROPHE); break;
            case '\\': addToken(BACKSLASH); break;
            case '_': addToken(UNDERSCORE); break;
            case '#': addToken(HASH); break;
            case '$': addToken(DOLLAR); break;
            case '%': addToken(PERCENT); break;
            case '&': addToken(AMPERSAND); break;
            case '*': addToken(match('*') ? POWER : MULTIPLY); break;
            case '-': addToken(match('-') ? DECRE : MINUS); break;
            case '+': addToken(match('+') ? INCRE : PLUS); break;
            case ';': addToken(SEMICOLON); break;
            case '!': addToken(match('=') ? NOT_EQ : NOT); break;
            case '=': addToken(match('=') ? EQ : ASSIGN); break;
            case '<': addToken(match('=') ? LESS_T_EQ : LESS_T); break;
            case '>': addToken(match('=') ? GREATER_T_EQ : GREATER_T); break;
            case '/':
                if (match('/')) {
                    while (peek() != '\n' && !isAtEnd()) advance();
                } else {
                    addToken(DIVIDE);
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
                } else {
                    cout << "Unexpected character." << endl;
                }
                break;
        }
}
char advance() {
        return source[current++];
    }

    void addToken(TokenType type) {
        addToken(type, nullptr);
    }

    void addToken(TokenType type, const char* literal) {
        std::string text = source.substr(start, current - start);
        tokens.push_back(Token{type, text, line});
    }

    bool match(char expected) {
        if (isAtEnd() || source[current] != expected)
            return false;

        current++;
        return true;
    }

    char peek() {
        if (isAtEnd())
            return '\0';

        return source[current];
    }

    bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    void number() {
        while (isDigit(peek()))
            advance();

        if (peek() == '.' && isDigit(peekNext())) {
            advance();

            while (isDigit(peek()))
                advance();
        }

        addToken(NUMBER);
    }

    char peekNext() {
        if (current + 1 >= source.length())
            return '\0';

        return source[current + 1];
    }

    bool isAlpha(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
    }

    bool isAlphaNumeric(char c) {
        return isAlpha(c) || isDigit(c);
    }

    void identifier() {
        while (isAlphaNumeric(peek()))
            advance();

        std::string text = source.substr(start, current - start);
        TokenType type = IDENTIFIER;

        auto keyword = keywords.find(text);
        if (keyword != keywords.end()) {
            type = keyword->second;
        }

        addToken(type);
    }

    void string() {
        while (peek() != '"' && !isAtEnd()) {
            if (peek() == '\n')
                line++;
            advance();
        }

        if (isAtEnd()) {
            cout << "Unterminated string." << endl;
            return;
        }

        advance();  // Consume the closing '"'

        std::string value = source.substr(start + 1, current - start - 2);
        addToken(LITERAL, value.c_str());
    }
};
map<string, TokenType> Scanner::keywords;

int main() {
    string sourceCode = "show 'Hello, world!'\na = read('Enter value :')\nb=4\nif a>b:\n\tshow 'a is greater'\nelse:\n\tshow 'b is greater'\n";
    Scanner scanner(sourceCode);
    vector<Token> tokens = scanner.scanTokens();

    for (const Token& token : tokens) {
        cout << list[token.type] << " " << token.lexeme << " " << token.line << endl;
    }

    return 0;
}