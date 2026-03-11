%{
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
int l=0,c=0,w=0,s=0,t=0,pos=0,neg=0,v=0,up=0,low=0;
%}

%%
\n {l++;c++;w++;}
[ \t] {s++;c++;if(yytext[0]=='\t')t++;}
[a-zA-Z]+ {
    c+=strlen(yytext);w++;
    if(strchr("aeiouAEIOU",yytext[0]))v++;
    if(isupper(yytext[0]))up++; else low++;
    if(strcmp(yytext,"int")==0||strcmp(yytext,"if")==0||strcmp(yytext,"main")==0||strcmp(yytext,"return")==0)
        printf("KEYWORD   : %s\n", yytext);
    else printf("IDENTIFIER: %s\n", yytext);
}
[0-9]+ {
    c+=strlen(yytext);
    int n=atoi(yytext);
    if(n>0)pos++; else if(n<0)neg++;
    printf("NUMBER    : %s\n", yytext);
}
[-+]?[0-9]+\.?[0-9]* {
    c+=strlen(yytext);
    float n=atof(yytext);
    if(n>0)pos++; else if(n<0)neg++;
    printf("FLOAT     : %s\n", yytext);
}
[+\-*/=<>!&|] {
    c++;
    printf("OPERATOR  : %s\n", yytext);
}
[;,.(){}] {
    c++;
    printf("SYMBOL    : %s\n", yytext);
}
. c++;
%%

int yywrap(){return 1;}

int main(){
    yyin=fopen("input.txt","r");
    printf("\n=== TOKEN LIST ===\n");
    yylex();
    printf("\nLines      : %d\n", l);
    printf("Words      : %d\n", w);
    printf("Characters : %d\n", c);
    printf("Spaces     : %d\n", s);
    printf("Tabs       : %d\n", t);
    printf("Positives  : %d\n", pos);
    printf("Negatives  : %d\n", neg);
    printf("Vowels     : %d\n", v);
    printf("Uppercase  : %d\n", up);
    printf("Lowercase  : %d\n", low);
    return 0;
}
