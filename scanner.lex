%{
#include <stdio.h>
#include<cstdio>
#include <stdlib.h>
#include <string.h>
#include "hw5_aux.hpp"
#include "hw5_output.hpp"
#include "parser.tab.hpp"
#define MAX_LEN (1024)

int line_num = 1;
char string_buf[MAX_LEN];
char *string_buf_ptr;
long result;

%}
whitespace ([\t\n\r ])
%option yylineno
%option noyywrap

%%

"void"                        {return VOID;}
"int"                         {return INT;}
"byte"                        {return BYTE;}
"b"                           {return B;}
"bool"                        {return BOOL;}
"and"                         {return AND;}
"or"                          {return OR;}
"not"                         {return NOT;}
"true"                        {return TRUE;}
"false"                       {return FALSE;}
"return"                      {return RETURN;}
"if"                          {return IF;}
"else"                        {return ELSE;}
"while"                       {return WHILE;}
"break"                       {return BREAK;}
"continue"                    {return CONTINUE;}
";"                           {return SC;}
","                           {return COMMA;}
"("                           {return LPAREN;}
")"                           {return RPAREN;}
"{"                           {return LBRACE;}
"}"                           {return RBRACE;}
"="                           {return ASSIGN;}
"=="|"!="                     { yylval = new EqOp(yytext); return EQOP;}
"<"|">"|"<="|">="             { yylval = new RelOp(yytext); return RELOP;}
"+"|"-"                       { yylval = new BinOp(yytext); return BINOP;}
"*"|"/"                       { yylval = new MulOp(yytext); return MULTIOP;}
[a-zA-Z][a-zA-Z0-9]*          { yylval = new Id(yytext); return ID;}
0|[1-9][0-9]*                 { yylval = new Num(yytext); return NUM;}
\"([^\n\r\"\\]|\\[rnt"\\])+\" { yylval = new String(yytext); return STRING;}
"//"[^\r\n]*[\r|\n|\r\n]? ;
{whitespace} ;
.                             {output::errorLex(yylineno);exit(0);}

%%
