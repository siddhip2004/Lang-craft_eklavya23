%{
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "y.tab.h"
int yylval;
%}

%%

[0-9]+(\.[0-9]+)? { yylval=atof(yytext);
                         return num; }
[()*/%+-]          { return yytext[0]; }
[ ] ;
[\n] { return 0; }
. { printf("Invalid Character : %c\n",yytext[0]);
    exit(0); }

%%

int yywrap(){
    return 1;
}