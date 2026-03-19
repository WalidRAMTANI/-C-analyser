%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "tpcas.tab.h"
%}

%option yylineno

%%
"int"           { yylval.text = strdup(yytext); return TYPE; }
"char"          { yylval.text = strdup(yytext); return TYPE; }
"void"          { yylval.text = strdup(yytext); return VOID; }
"struct"        { yylval.text = strdup(yytext); return STRUCT; }
"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"return"        { return RETURN; }

[a-zA-Z_][a-zA-Z0-9_]*  { yylval.text = strdup(yytext); return IDENT; }

[0-9]+          { yylval.text = strdup(yytext); return NUM; }

\'([^\\\']|\\.)\'   { yylval.text = strdup(yytext); return CHARACTER; }
\'([^\\\']|\\.)+\'   {
    fprintf(stderr, "%d: caractère littéral mal formé (plusieurs caractères entre quotes)\n", yylineno);
    exit(1);
}

"+"             { yylval.text = strdup(yytext); return ADDSUB; }
"-"             { yylval.text = strdup(yytext); return ADDSUB; }
"*"             { yylval.text = strdup(yytext); return DIVSTAR; }
"/"             { yylval.text = strdup(yytext); return DIVSTAR; }
"%"             { yylval.text = strdup(yytext); return DIVSTAR; }
"<="            { yylval.text = strdup(yytext); return ORDER; }
">="            { yylval.text = strdup(yytext); return ORDER; }
"<"             { yylval.text = strdup(yytext); return ORDER; }
">"             { yylval.text = strdup(yytext); return ORDER; }

"=="            { yylval.text = strdup(yytext); return EQ; }
"!="            { yylval.text = strdup(yytext); return EQ; }

"&&"            { yylval.text = strdup(yytext); return AND; }
"||"            { yylval.text = strdup(yytext); return OR; }

\.              { yylval.text = strdup(yytext); return DOT; }

[ \t\r]+        { }
\n              { }

"//"[^\n]*      { }
"/*"([^*]|\*+[^*/])*\*+"/"  { }

[(){};,=!]      { return yytext[0]; }

.               { }
<<EOF>> {
    return 0;
}
%%

int yywrap() {
    return 1;
}
