#pragma once

#include<any>
#include<iostream>
#include<string>
#include<vector>
#include"Token.h"
#include<memory>
#include<utility>

using namespace std;

struct Binary;
struct Grouping;
struct Literal;
struct Unary;

struct ExprVisitor {
  virtual any visitBinaryExpr (shared_ptr<Binary> expr) = 0;
  virtual any visitGroupingExpr (shared_ptr<Grouping> expr) = 0;
  virtual any visitLiteralExpr (shared_ptr<Literal> expr) = 0;
  virtual any visitUnaryExpr (shared_ptr<Unary> expr) = 0;
  virtual ~ExprVisitor() = default;
};

struct Expr 
{
  virtual any accept(ExprVisitor& visitor) = 0;
};

struct Binary: Expr, public enable_shared_from_this<Binary> 
{
  Binary(shared_ptr<Expr> left, Token op, shared_ptr<Expr> right)
    : left{move(left)}, op{move(op)}, right{move(right)}
  {}

  any accept(ExprVisitor& visitor) override 
  {
    return visitor.visitBinaryExpr(shared_from_this());
  }

  const shared_ptr<Expr> left;
  const Token op;
  const shared_ptr<Expr> right;
};

struct Grouping: Expr, public enable_shared_from_this<Grouping> 
{
  Grouping(shared_ptr<Expr> expression)
    : expression{move(expression)}
  {}

  any accept(ExprVisitor& visitor) override 
  {
    return visitor.visitGroupingExpr(shared_from_this());
  }

  const shared_ptr<Expr> expression;
};

struct Literal: Expr, public enable_shared_from_this<Literal> 
{
  Literal(any value)
    : value{move(value)}
  {}

  any accept(ExprVisitor& visitor) override 
  {
    return visitor.visitLiteralExpr(shared_from_this());
  }

  const any value;
};

struct Unary: Expr, public enable_shared_from_this<Unary> 
{
  Unary(Token op, shared_ptr<Expr> right)
    : op{move(op)}, right{move(right)}
  {}

  any accept(ExprVisitor& visitor) override 
  {
    return visitor.visitUnaryExpr(shared_from_this());
  }

  const Token op;
  const shared_ptr<Expr> right;
};