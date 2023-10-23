#pragma once
#include<iostream>
#include<string>
#include<cstring>
#include<map>
#include<vector>
//#include"Stmt.h"
#include"Expr.h"
#include<stdexcept>
#include<memory>
#include"RunTimeError.h"
#include<any>


using namespace std;

class Interpreter : public ExprVisitor
{
  public:

  void interpret(shared_ptr<Expr> expression)
  {
    try 
    {
       any value = evaluate (expression);
       cout<< stringify(value)<<endl;     
    }

    catch(RuntimeError error)
    {
      runtimeError(error);
    }
  }

  private:

  any evaluate(shared_ptr<Expr> expr)
  {
    return expr-> accept(*this);
  }

  public:
   
   any visitBinaryExpr(shared_ptr<Binary> expr) override 
   {
     any left = evaluate(expr->left);
     any right = evaluate(expr-> right);

     switch(expr-> op.type)
     {
       case BANG_EQUAL: return !isEqual(left,right);

       case EQUAL_EQUAL: return isEqual(left, right);

       case GREATER:
       checkNumberOperands(expr->op, left, right);
       return any_cast<double>(left) > 
              any_cast<double>(right);
        
       case LESS:
       checkNumberOperands(expr->op, left, right);
       return std::any_cast<double>(left) <
               std::any_cast<double>(right);

       case GREATER_EQUAL:
        checkNumberOperands(expr->op, left, right);
        return std::any_cast<double>(left) >=
               std::any_cast<double>(right);

       case LESS_EQUAL:
        checkNumberOperands(expr->op, left, right);
        return std::any_cast<double>(left) <=
               std::any_cast<double>(right);

       case MINUS:
        checkNumberOperands(expr->op, left, right);
        return std::any_cast<double>(left) -
               std::any_cast<double>(right);

      case PLUS:
        if (left.type() == typeid(double) &&
            right.type() == typeid(double)) 
        {
          return any_cast<double>(left) +
                 any_cast<double>(right);
        }

        if (left.type() == typeid(std::string) &&
            right.type() == typeid(std::string)) 
        {
          return any_cast<std::string>(left) +
                 any_cast<std::string>(right);
        }

        throw RuntimeError{expr->op,
            "Operands must be either two numbers or two strings."};

      case SLASH:
        checkNumberOperands(expr->op, left, right);
        return any_cast<double>(left) /
               any_cast<double>(right);

      case STAR:
        checkNumberOperands(expr->op, left, right);
        return std::any_cast<double>(left) *
               std::any_cast<double>(right);

     }

     return {};
   }

   any visitGroupingExpr(
     shared_ptr<Grouping> expr) override {
    return evaluate(expr->expression);
  }

   

};