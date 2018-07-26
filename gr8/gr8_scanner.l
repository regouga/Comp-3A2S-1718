%option c++ prefix="gr8_scanner_" outfile="gr8_scanner.cpp"
%option stack noyywrap yylineno 8bit
%{ 
// make relevant includes before including the parser's tab file
#include <string>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include <cdk/ast/lvalue_node.h>
#include "gr8_parser.tab.h"

// don't change this
#define yyerror LexerError

int indentationLevel = 0;
int lineIndentation = 0;   
   
%}
%x X_NEWS X_COMMENT X_NEWS_SPECIAL X_NEWS_IGNORE X_INDENT
%s X_REGULAR



%% {setdebug();}

"!!".*                 ; /* ignore comments */

"small"                return tSMALL;
"huge"                 return tHUGE;
"news"                 return tNEWS;
"fake"                 return tFAKE;
"initially"            return tINITIALLY;

"use"                  return tUSE;
"public"               return tPUBLIC;
"define"               return tDEFINE;
"procedure"            return tPROCEDURE;
"function"             return tFUNCTION;
"on"                   return tON;
"as"                   return tAS;
"do"                   return tDO;
"uses"                 return tUSES;
"for"                  return tFOR;
"return"               return tRETURN;

"plus"                 return tPLUS;
"minus"                return tMINUS;
"times"                return tTIMES;
"over"                 return tOVER;
"modulus"              return tMODULUS;
"not"                  return tNOT;
"and"                  return tAND;
"or"                   return tOR;
"assign"               return tASSIGN;
"to"                   return tTO;
"cell"                 return tCELL;
"at"                   return tAT;
"above"                return tABOVE;
"below"                return tBELOW;
"equals"               return tEQUALS;
"input"                return tINPUT;

"if"                   return tIF; 
"else"                 return tELSE;
"then"                 return tTHEN;
"elsif"                return tELSIF;
"stop"                 return tSTOP;
"again"                return tAGAIN;
"tweet"                return tTWEET;
"post"                 return tPOST;
"sweeping"             return tSWEEPING;
"from"                 return tFROM;
"by"                   return tBY;
"read"                 return tREAD;
"objects"              return tOBJECTS; 

"apply"                return tAPPLY;

"}"                    return tCURLYBRACKET;
"{"                    return tCLOSEDCURLYBRACKET;

^[ \t]+                { yyless(0); yy_push_state(X_INDENT);}
<X_INDENT>" "          { lineIndentation++; }
<X_INDENT>"\t"         { lineIndentation = (lineIndentation + 8) & ~7; }
<X_INDENT,INITIAL><<EOF>>      { if(indentationLevel != 0){
                                    indentationLevel --;
                                    return tCLOSEDCURLYBRACKET;
                                }
                                yyterminate();
                              } 
<X_INDENT>.            {                        
                            if (lineIndentation < indentationLevel) {
                                indentationLevel--;
                                return tCLOSEDCURLYBRACKET;
                            }
                   
                            else if (lineIndentation > indentationLevel) {
                                indentationLevel++;
                                return tCURLYBRACKET;
                            }
                            
                            
                            else if (*yytext ==EOF) return tCLOSEDCURLYBRACKET;
                        
                            else BEGIN X_REGULAR;
                        }

<X_REGULAR>"\n"    { 
                        lineIndentation = 0; 
                        BEGIN X_INDENT; 
                   }



[A-Za-z][A-Za-z0-9_]*                   yylval.s = new std::string(yytext); return tIDENTIFIER;

\"                                      yy_push_state(X_NEWS); yylval.s = new std::string("");
<X_NEWS>\"[ ]\"                         *yylval.s += yytext + 3;
<X_NEWS>\"                              yy_pop_state(); return tNEWS;
<X_NEWS>\\\"                            *yylval.s += yytext + 1;
<X_NEWS>"~"                             yy_push_state(X_NEWS_SPECIAL);
<X_NEWS>.                               *yylval.s += yytext;
<X_NEWS>\n                              yyerror("newline in string");

<X_NEWS_SPECIAL>"0"                     yy_pop_state(); yy_pop_state(); yy_push_state(X_NEWS_IGNORE);
<X_NEWS_SPECIAL>[0-6]{1,3}              *yylval.s += new char(strtol(yytext, nullptr, 7)); yy_pop_state();
<X_NEWS_SPECIAL>"r"                     *yylval.s += "\r"; yy_pop_state();
<X_NEWS_SPECIAL>"t"                     *yylval.s += "\t"; yy_pop_state();
<X_NEWS_SPECIAL>\"                      *yylval.s += "\""; yy_pop_state();
<X_NEWS_SPECIAL>"~"                     *yylval.s += "\\"; yy_pop_state();
<X_NEWS_SPECIAL>"n"                     yyerror("newline in string"); yy_pop_state();

<X_NEWS_IGNORE>\\\"                     ;
<X_NEWS_IGNORE>\\\\                     ;
<X_NEWS_IGNORE>.|\n                     ;

"<<"                                    yy_push_state(X_COMMENT);
<X_COMMENT>"<<"                         yy_push_state(X_COMMENT);
<X_COMMENT>">>"                         yy_pop_state();
<X_COMMENT>.|\n                         ;

[1-9][0-9]*|0                           yylval.i = strtol(yytext, nullptr, 10); if (errno == ERANGE) yyerror("Overflow"); return tSMALL;
0[0-6]+                                 yylval.i = strtol(yytext, nullptr, 7);  if (errno == ERANGE) yyerror("Overflow"); return tSMALL; 

[1-9][0-9]*.[0-9]*                      yylval.i = strtol(yytext, nullptr, 10); if (errno == ERANGE) yyerror("Overflow"); return tHUGE;
[1-9][0-9]*.[0-9]*[eE][+-]?[0-9]+       yylval.i = strtol(yytext, nullptr, 10); if (errno == ERANGE) yyerror("Overflow"); return tHUGE;
[1-9][0-9]*[eE][+-]?[0-9]+              yylval.i = strtol(yytext, nullptr, 10); if (errno == ERANGE) yyerror("Overflow"); return tHUGE;
[e|E][+?|-][0-9]+                       yylval.i = strtol(yytext, nullptr, 10); if (errno == ERANGE) yyerror("Overflow"); return tHUGE;

[-()<>=+*/%;{}.]                        return *yytext;

[ \t]+                                ;
"..."                                   *yylval.s += "\\";
.                                       yyerror("Unknown character");


%%
