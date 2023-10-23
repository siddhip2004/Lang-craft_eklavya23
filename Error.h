#pragma once
#include<iostream>
#include<string_view>
#include"RunTimeError.h"
#include"Token.h"

inline bool hadError = false;
inline bool hadRuntimeError = false;

static void report( int line, string_view where, string_view message)
{
    cerr << "[line " << line << "] Error" << where << ": " <<message << "\n";
    hadError = true;
}

void error(const Token& token, string_view message)
{
    if(token.type == eof)
    {
        report(token.line, " at end", message);
    }

    else 
    {
        report(token.line, " at '" + token.lexeme + "'", message);
    }
}

void error(int line, string_view message) 
{
  report(line, "", message);
}

void runtimeError(const RuntimeError& error) 
{
    cerr << error.what() << "\n[line " << error.token.line << "]\n";
    hadRuntimeError = true;
}