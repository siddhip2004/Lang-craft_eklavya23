%{
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
%}

%token num
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

%%

ArithmeticExpression : E{
    printf("\nResult : %d\n", $$);
    return 0;
};
E : '('E')' {$$ = $2;}
|E'*'E {$$ = $1 * $3;}
|E'/'E {$$ = $1 / $3;}
|E'%'E {$$ = $1 % $3;}
|E'+'E {$$ = $1 + $3;}
|E'-'E {$$ = $1 - $3;}
|num {$$ = $1;}
;

%%

int main(void){
    printf("Enter the Operation : ");
    yyparse();
}

void yyerror(){
    printf("Invalid Expression\n");
    exit(0);
}