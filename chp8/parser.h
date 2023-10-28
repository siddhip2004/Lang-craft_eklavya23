#pragma once 

#include <cassert>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>      
#include <vector>
#include "Error.h"
#include "Stmt.h"
#include "Expr.h"
#include "Token.h"
#include "TokenType.h"


using namespace std;

class Parser 
{
  struct ParseError: public std::runtime_error 
  {
    using std::runtime_error::runtime_error;
  };

  

    const vector<Token>& tokens;
    int current = 0;

    public:
    Parser(const vector<Token>& tokens) :tokens{tokens}
    {}

    vector<std::shared_ptr<Stmt>> parse() {
    std::vector<std::shared_ptr<Stmt>> statements;
    while (!isAtEnd()) {
      // statements.push_back(statement());
      statements.push_back(declaration());
    }

    return statements;
  }


    private:
    shared_ptr<Expr> expression() {
    return assignment();
  }

     shared_ptr<Stmt> declaration() {
    try {
      if (match(IDENTIFIER)) return Declaration();

      return statement();
    } catch (ParseError error) {
      synchronize();
      return nullptr;
    }
  }

  shared_ptr<Stmt> expressionStatement() {
    std::shared_ptr<Expr> expr = expression();
    return std::make_shared<Expression>(expr);
  }


     shared_ptr<Stmt> statement() {
    if (match(SHOW)) return printStatement();
    if (match(LEFT_BRACE)) return std::make_shared<Block>(block());

    return expressionStatement();
  }

  vector<std::shared_ptr<Stmt>> block() {
    std::vector<std::shared_ptr<Stmt>> statements;

    while (!check(RIGHT_BRACE) && !isAtEnd()) {
      statements.push_back(declaration());
    }

    consume(RIGHT_BRACE, "Expect '}' after block.");
    return statements;
  }


  shared_ptr<Stmt> printStatement() {
    std::shared_ptr<Expr> value = expression();
    return std::make_shared<Show>(value);
  }

  shared_ptr<Stmt> Declaration() {
    Token name = consume(IDENTIFIER, "Expect variable name.");

    std::shared_ptr<Expr> initializer = nullptr;
    if (match(EQUAL)) {
      initializer = expression();
    }

    return std::make_shared<Var>(std::move(name), initializer);
  }

  shared_ptr<Expr> assignment() {
    std::shared_ptr<Expr> expr = equality();

    if (match(EQUAL)) {
      Token equals = previous();
      std::shared_ptr<Expr> value = assignment();

      if (Variable* e = dynamic_cast<Variable*>(expr.get())) {
        Token name = e->name;
        return std::make_shared<Assign>(std::move(name), value);
      }

      error(std::move(equals), "Invalid assignment target.");
    }

    return expr;
  }
  
     
      shared_ptr<Expr> equality()
      {
        shared_ptr<Expr> expr = comparison();

        while (match(BANG_EQUAL, EQUAL_EQUAL)) 
        {
          Token op = previous();
          std::shared_ptr<Expr> right = comparison();
          expr = std::make_shared<Binary>(expr, std::move(op), right);
        }
         return expr;
      }

      std::shared_ptr<Expr> comparison()
      {
        std:: shared_ptr<Expr> expr =  term();

        while (match(GREATER, GREATER_EQUAL, LESS, LESS_EQUAL)) {
        Token op = previous();
        std::shared_ptr<Expr> right = term();
         expr = std::make_shared<Binary>(expr, std::move(op), right);
        }
        return expr;

      }

      std::shared_ptr<Expr> term() {
    std::shared_ptr<Expr> expr = factor();

    while (match(MINUS, PLUS)) {
      Token op = previous();
      std::shared_ptr<Expr> right = factor();
      expr = std::make_shared<Binary>(expr, std::move(op), right);
    }

    return expr;
  }

      std::shared_ptr<Expr> factor() {
    std::shared_ptr<Expr> expr = unary();

    while (match(SLASH, STAR)) {
      Token op = previous();
      std::shared_ptr<Expr> right = unary();
      expr = std::make_shared<Binary>(expr, std::move(op), right);
    }

    return expr;
  }
  
     std::shared_ptr<Expr> unary() {
    if (match(BANG, MINUS)) {
      Token op = previous();
      std::shared_ptr<Expr> right = unary();
      return std::make_shared<Unary>(std::move(op), right);
    }

    return primary();
  }

  std::shared_ptr<Expr> primary() {
    if (match(FALSE)) return std::make_shared<Literal>(false);
    if (match(TRUE)) return std::make_shared<Literal>(true);
    if (match(NIL)) return std::make_shared<Literal>(nullptr);

    if (match(NUMBER, STRING)) {
      return std::make_shared<Literal>(previous().literal);
    }

    if (match(IDENTIFIER)) {
      return std::make_shared<Variable>(previous());
    }

    if (match(LEFT_PAREN)) {
      std::shared_ptr<Expr> expr = expression();
      consume(RIGHT_PAREN, "Expect ')' after expression.");
      return std::make_shared<Grouping>(expr);
    }

    throw error(peek(), "Expect expression.");
  }

  template <class... T>
  bool match(T... type) {
    assert((... && std::is_same_v<T, TokenType>));

    if ((... || check(type))) {
      advance();
      return true;
    }

    return false;
  }

  Token consume(TokenType type, std::string_view message) {
    if (check(type)) return advance();

    throw error(peek(), message);
  }

  bool check(TokenType type) {
    if (isAtEnd()) return false;
    return peek().type == type;
  }

  Token advance() {
    if (!isAtEnd()) ++current;
    return previous();
  }

  bool isAtEnd() {
    return peek().type == eof;
  }

  Token peek() {
    return tokens.at(current);
  }

  Token previous() {
    return tokens.at(current - 1);
  }

  ParseError error(const Token& token, std::string_view message) {
    ::error(token, message);
    return ParseError{""};
  }

  void synchronize() {
    advance();

    

      switch (peek().type) {
        case CLASS:
        case READ:
        case FOR:
        case IF:
        case WHILE:
        case SHOW:
        case RETURN:
          return;
      }

      advance();
    }
  };
