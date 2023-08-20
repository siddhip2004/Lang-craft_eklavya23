%{
    #include <stdio.h>
%}

%token plus minus num equal div mult

%start input

//%left plus minus
%left Div mult plus minus

%%
input : 
        | input line {printf("result is %d", $2);}
        ;
line : equal
        | exp equal
        ;
exp : num
        | exp plus exp {$$ = $1 + $3;}
        | exp minus exp {$$ = $1 - $3;}
        | exp mult exp {$$ = $1 * $3;}
        | exp Div exp {
                       if($3 == 0)
                       {printf("cannot divide\n");}
                       else
                       {
                        $$ = $1/$3
                       }
                      }

        ;

%%
void yyerror(char *s)
{
    printf("Error occured");
}



int main()
{
    yyparse();
}

