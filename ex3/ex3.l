%{
#include <math.h>
%}

DIGIT [0-9]
ID [a-z][a-z0-9]*

%%
int|main|return|if {printf("keyword %s\n", yytext);}
{DIGIT}+"."{DIGIT}+ {printf("float %s\n", yytext);}
{DIGIT}+ {printf("int %s\n", yytext);}
{ID} {printf("id %s\n", yytext);}
"+"|"-"|"*"|"/" {printf("op %s\n", yytext);}
";"|"," {printf("sym %s\n", yytext);}
[ \t\n]+ /* ignore whitespace */
. {printf("err '%s'\n", yytext);}
%%

int yywrap(){return 1;}

int main(){
  yyin = fopen("input.txt","r");
  yylex();
  return 0;
}
