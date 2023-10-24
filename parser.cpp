#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<array>
#include<exception>
#include"Token.h"
#include"TokenType.h"
#include"Stmt.h"


using namespace std;

class Parser
{
  
    class  ParserError : public exception{};

    private: static vector<Token> tokens;
    private: int current = 0;

    Parser(vector<Token> tokens) {
    this->tokens = tokens;
    }

     //vector<

     vector<Stmt> parse()
     {
       vector<Stmt> statements;
       while(!isAtEnd())
       {
         statements.push_back(declaration());
       }

       return statements;
     }

     private: Expr expression()
     {
      return assignment();
     }

     private: Stmt declaration()
     {
      try
      {
         if(match(FUN))
         {
            return function("function");
         }

         if(match(CLASS))
         {
            return classDeclaration();
         }

         if(match(VAR))
         {
            return varDeclaration();
         }

         else 
         {
            return statement();
         }
      }

      catch (ParserError error) {
      synchronize();
      return null;
    }
     }
 private: Token consume(TokenType type, string message)
     private: Stmt classDeclaration()
     {
      Token name = consume(IDENTIFIER, "Except class name.");
      //Expr .Variable superclass = null;
      if(match(LESS))
      {
         consume(IDENTIFIER, "Expect superclass name.");
         //superclass = new Expr.variable(previous());
      }

      consume(LEFT_BRACE, "Expect '{' before class body.");

      //vector<Stmt.Function> methods;
      while(!check(RIGHT_BRACE) && !isAtEnd())
      {
         methods.push_back(function("method"));
      }

      consume(RIGHT_BRACE, "Expect '}' after class body.");

      //return new Stmt.Class(name, superclass, methods);
     }

     private: Stmt statement() {

    if (match(FOR)) return forStatement();

    if (match(IF)) return ifStatement();

    if (match(PRINT)) return printStatement();

    if (match(RETURN)) return returnStatement();

    if (match(WHILE)) return whileStatement();

    //if (match(LEFT_BRACE)) return new Stmt.Block(block());

    return expressionStatement();
  }

    //HOW TO CHECK FOR INDENTATION???

  private: Stmt forStatement() {
    consume(LEFT_PAREN, "Expect '(' after 'for'.");


    Stmt initializer;
    //if (match(COLON)) 
    {
      initializer = NULL;
    }
     else if (match(VAR)) {
      initializer = varDeclaration();
    } 
    else {
      initializer = expressionStatement();
    }

     /*Expr condition = NULL;
    if (!check(COLON)) {
      condition = expression();
    }
    consume(COLON, "Expect ':' after loop condition.");*/

    Expr increment = NULL;
    if (!check(RIGHT_PAREN)) {
      increment = expression();
    }
    consume(RIGHT_PAREN, "Expect ')' after for clauses.");

    Stmt body = statement();


    if (increment != NULL) {
      //body = new Stmt.Block(
          //Arrays.asList(
              //body,
              //new Stmt.Expression(increment)));
    }

    if (condition == NULL) {
      condition = new Expr.Literal(true);
    }
    body = new Stmt.While(condition, body);

    if (initializer != NULL) {
      //body = new Stmt.Block(Arrays.asList(initializer, body));
    }
    return body;
}

private: Stmt ifStatement() {
    consume(LEFT_PAREN, "Expect '(' after 'if'.");
    Expr condition = expression();
    consume(RIGHT_PAREN, "Expect ')' after if condition."); 

    Stmt thenBranch = statement();
    Stmt elseBranch = NULL;
    if (match(ELSE)) {
      elseBranch = statement();
    }
    
    return new Stmt*.If(condition, thenBranch, elseBranch);
  }

  // From line 204 to 216, will not come, since no semicolon??

  private: Stmt varDeclaration() {
    Token name = consume(IDENTIFIER, "Expect variable name.");

    Expr initializer = NULL;
    if (match(EQUAL)) {
      initializer = expression();
    }

    //consume(SEMICOLON, "Expect ';' after variable declaration.");
    //return new Stmt.Var(name, initializer);
  }

  private Stmt whileStatement() {
    consume(LEFT_PAREN, "Expect '(' after 'while'.");
    Expr condition = expression();
    consume(RIGHT_PAREN, "Expect ')' after condition.");
    Stmt body = statement();

    return new Stmt.While(condition, body);
  }

  // From line 246 to 250, will not come, since no semicolon??

  private: Stmt.Function function(string kind) {
    Token name = consume(IDENTIFIER, "Expect " + kind + " name.");

    consume(LEFT_PAREN, "Expect '(' after " + kind + " name.");
    vector<Token> parameters;
    if (!check(RIGHT_PAREN)) {
      do {
        if (parameters.size() >= 255) {
          error(peek(), "Can't have more than 255 parameters.");
        }

        parameters.push_back(
            consume(IDENTIFIER, "Expect parameter name."));
      } while (match(COMMA));
    }
    consume(RIGHT_PAREN, "Expect ')' after parameters.");

    consume(LEFT_BRACE, "Expect '{' before " + kind + " body.");
    vector<Stmt> body = block();
    return new Stmt.Function(name, parameters, body);

  }

  private: vector<Stmt> block() {
    vector<Stmt> statements;

    while (!check(RIGHT_BRACE) && !isAtEnd()) {
      statements.push_back(declaration());
    }

    consume(RIGHT_BRACE, "Expect '}' after block.");
    return statements;
  }

  /*private: Expr assignment() {

    Expr expr = or();


    if (match(EQUAL)) {
      Token equals = previous();
      Expr value = assignment();

      if (expr instanceof Expr.Variable) {
        Token name = ((Expr.Variable)expr).name;
        return new Expr.Assign(name, value);

      } else if (expr instanceof Expr.Get) {
        Expr.Get get = (Expr.Get)expr;
        return new Expr.Set(get.object, get.name, value);

      }

      error(equals, "Invalid assignment target."); // [no-throw]
    }
    return expr;
    }*/

private: Expr or() {
    Expr expr = and();

    while (match(OR)) {
      Token operator = previous();
      Expr right = and();
      expr = new Expr.Logical(expr, operator, right);
    }

    return expr;
  }

private: Expr and() {
    Expr expr = equality();

    while (match(AND)) {
      Token operator = previous();
      Expr right = equality();
      expr = new Expr.Logical(expr, operator, right);
    }

    return expr;
  }

private: Expr comparison() {
    Expr expr = term();

    while (match(GREATER, GREATER_EQUAL, LESS, LESS_EQUAL)) {
      Token operator = previous();
      Expr right = term();
      expr = new Expr.Binary(expr, operator, right);
    }

    return expr;
  }
  
private: Expr term() {
    Expr expr = factor();

    while (match(MINUS, PLUS)) {
      Token operator = previous();
      Expr right = factor();
      expr = new Expr.Binary(expr, operator, right);
    }

    return expr;
}
private: Expr factor() {
    Expr expr = unary();

    while (match(SLASH, STAR)) {
      Token operator = previous();
      Expr right = unary();
      expr = new Expr.Binary(expr, operator, right);
    }

    return expr;
  }

private: Expr unary() {
    if (match(BANG, MINUS)) {
      Token operator = previous();
      Expr right = unary();
      return new Expr.Unary(operator, right);
    }

 return call();
}

private: Expr finishCall(Expr callee) {
    vector<Expr> arguments ;
    if (!check(RIGHT_PAREN)) {private: Token consume(TokenType type, string message)
      do {

        if (arguments.size() >= 255) {
          error(peek(), "Can't have more than 255 arguments.");
        }

        arguments.push_back(expression());
      } while (match(COMMA));
    }

    Token paren = consume(RIGHT_PAREN,
                          "Expect ')' after arguments.");

    return new Expr.Call(callee, paren, arguments);
  }
/*private Expr call() {
    Expr expr = primary();

    while (true) { 
      if (match(LEFT_PAREN)) {
        expr = finishCall(expr);

      } else if (match(DOT)) {
        Token name = consume(IDENTIFIER,
            "Expect property name after '.'.");
        expr = new Expr.Get(expr, name);

      } else {
        break;
      }
    }

    return expr;
  }*/

private: Expr primary() {
    if (match(FALSE)) return new Expr.Literal(false);
    if (match(TRUE)) return new Expr.Literal(true);
    if (match(NULL)) return new Expr.Literal(NULL);

    if (match(NUMBER, STRING)) {
      return new Expr.Literal(previous().literal);
    }


    /*if (match(SUPER)) {
      Token keyword = previous();
      consume(DOT, "Expect '.' after 'super'.");
      Token method = consume(IDENTIFIER,
          "Expect superclass method name.");
      return new Expr.Super(keyword, method);
    }*/


    if (match(THIS)) 
    {return new Expr.This(previous());}

    if (match(IDENTIFIER)) {
      return new Expr.Variable(previous());
    }

    if (match(LEFT_PAREN)) {
      Expr expr = expression();
      consume(RIGHT_PAREN, "Expect ')' after expression.");
      return new Expr.Grouping(expr);
    }

    throw error(peek(), "Expect expression.");

  }

  private: 
  bool match(TokenType types) {
    //for (TokenType type : types) 
    {
      if (check(type)) {
        advance();
        return true;
      }
    }

    return false;
  }

  private: Token consume(TokenType type, string message) {
    if (check(type)) return advance();

    throw error(peek(), message);
  }

 private: bool check(TokenType type) {
    if (isAtEnd()) return false;
    return peek().type == type;
  }
/*private: Token previous() {
    return tokens[current - 1];
  }*/

  private: Token advance() {
    if (!isAtEnd()) current++;
    return previous();
  }
  
  private: bool isAtEnd() {
    return peek().type == eof;
  }

private: Token peek() {
    return tokens[current];
  }

private: Token previous() {
    return tokens[current - 1];
  }
private: ParseError error(Token token, String message) {
    error(token, message);
    return new ParserError();
  }

private: void synchronize() {
    advance();

    while (!isAtEnd()) {
      if (previous().type == SEMICOLON) return;

      switch (peek().type) {
        case CLASS:
        case FUN:
        case VAR:
        case FOR:
        case IF:
        case WHILE:
        case PRINT:
        case RETURN:
          return;
      }

      advance();
    }
  }

};
