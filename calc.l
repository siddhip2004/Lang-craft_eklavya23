   

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

[0-9]+ { yylval = atoi(yytext); return num; }

[ \t] { /* ignore whitespace */ }
. { printf("wrong input %c\n", *yytext); }
%%
int main()
{
int tok;
while(tok = yylex()) {
printf("%d", tok);
if(tok == num) printf(" = %d\n", yylval);
else printf("\n");
}
return 0;
}

