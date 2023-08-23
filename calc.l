   

%{
    #include <stdio.h>
    #include "calc.tab.h"
    #include <stdlib.h>
     int yylval;
%}
%%
"+" { return plus; }
"-" { return minus; }
"*" { return mult; }
"/" { return divi; }
"=" {return equal;}

[0-9]+ { yylval = atoi(yytext); 
         return num; }

[ \t] { }

. { printf("wrong input %c\n", *yytext); 
    exit(0);}

 %%

 int yywrap(){
    return 1;
}

