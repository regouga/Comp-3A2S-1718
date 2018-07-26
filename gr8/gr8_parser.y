%{
//-- don't change *any* of these: if you do, you'll break the compiler.
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE               compiler->scanner()->lineno()
#define yylex()            compiler->scanner()->scan()
#define yyerror(s)         compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
//-- don't change *any* of these --- END!
%}

%union {
  int                   i;	                 /* integer value */
  std::string          *s;	                 /* symbol name or string literal */
  cdk::basic_node      *node;	             /* node pointer */
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression;          /* expression nodes */
  cdk::lvalue_node     *lvalue;
  basic_type           *basic;
  gr8::block_node      *block;
};

%token <i> tSMALL
%token <d> tHUGE
%token <s> tIDENTIFIER tNEWS
%token tNEWS tFAKE tINITIALLY tUSE tPUBLIC tDEFINE tPROCEDURE tFUNCTION tON tAS tDO tUSES tFOR tRETURN tPLUS tMINUS tTIMES tOVER tMODULUS tNOT tAND tOR tASSIGN tTO tCELL tAT tABOVE tBELOW tEQUALS tINPUT tIF tELSE tTHEN tELSIF tSTOP tAGAIN tPOST tTWEET tSWEEPING tFROM tBY tREAD tOBJECTS tCURLYBRACKET tCLOSEDCURLYBRACKET

%nonassoc tIF
%nonassoc tELSE tELSIF

%left tOR
%left tAND
%nonassoc tNOT
%left tEQUALS
%left tBELOW tABOVE
%left tPLUS tMINUS
%left tTIMES tOVER tMODULUS
%nonassoc tUNARY
%nonassoc '?' tOBJECTS
%nonassoc '(' ')'

%type <node>  func func_invoc var var_bloco decl decl_bloco instr condinstr interinstr
%type <sequence> vars decls decls_bloco instrs  exprs
%type <expression> expr  attrb
%type <lvalue> lval
%type <basic> tipo fakeIT hugeIT smallIT
%type <block> bloco

%{
//-- The rules below will be included in yyparse, the main parsing function.
%}
%%

file: decls                                              { compiler->ast($1); }
    |
    ;
    
decls: decl                                                 { $$ = new cdk::sequence_node(LINE, $1); }                                                   
     | decls decl                                           { $$ = new cdk::sequence_node(LINE, $2, $1); } 
     ;
     
decl: var  ';'                                              { $$ = $1; }
    | func                                                  { $$ = $1; }
    | func_invoc ';'                                        { $$ = $1; }
    ;

decls_bloco: decl_bloco                                     { $$ = new cdk::sequence_node(LINE, $1); }                                                   
           | decls_bloco decl_bloco                         { $$ = new cdk::sequence_node(LINE, $2, $1); } 
           ;
     
decl_bloco: var_bloco ';'                                      { $$ = $1; }
          | func_invoc ';'                                     { $$ = $1; }
          ;
    
    
var: tUSE tipo tIDENTIFIER                                  { $$ = new gr8::var_declaration_node(LINE, $2, false, true, $3, nullptr); }
   | tUSE tipo tIDENTIFIER '(' tINITIALLY expr ')'          { $$ = new gr8::var_declaration_node(LINE, $2, false, true, $3, $6); } 
   | tPUBLIC tipo tIDENTIFIER '(' tINITIALLY expr ')'       { $$ = new gr8::var_declaration_node(LINE, $2, true, false, $3, $6); } 
   | tPUBLIC tipo tIDENTIFIER                               { $$ = new gr8::var_declaration_node(LINE, $2, true, false, $3, nullptr); } 
   | var_bloco                                              { $$ = new cdk::sequence_node(LINE);}
   ;
    
var_bloco: tipo tIDENTIFIER                                       { $$ = new gr8::var_declaration_node(LINE, $1, false, false, $2, nullptr); } 
         | tipo tIDENTIFIER '(' tINITIALLY expr ')'               { $$ = new gr8::var_declaration_node(LINE, $1, false, false, $2, $5); } 
         ;

func: tUSE tipo tFUNCTION  tIDENTIFIER                              { $$ = new gr8::func_declaration_node(LINE, $2, false, true, $4, nullptr); }      
    | tUSE tipo tFUNCTION tIDENTIFIER tUSES vars                    { $$ = new gr8::func_declaration_node(LINE, $2, false, true, $4, $6); } 
    | tUSE tPROCEDURE tIDENTIFIER                                   { $$ = new gr8::func_declaration_node(LINE, new basic_type(0, basic_type::TYPE_VOID), false, true, $3, nullptr); } 
    | tUSE tPROCEDURE tIDENTIFIER tUSES vars                        { $$ = new gr8::func_declaration_node(LINE, new basic_type(0, basic_type::TYPE_VOID), false, true, $3, $5); } 
    | tPUBLIC tipo tFUNCTION tIDENTIFIER                            { $$ = new gr8::func_declaration_node(LINE, $2, true, false, $4, nullptr); }   
    | tPUBLIC tipo tFUNCTION tIDENTIFIER tUSES vars                 { $$ = new gr8::func_declaration_node(LINE, $2, true, false, $4, $6); } 
    | tPUBLIC tPROCEDURE tIDENTIFIER                                { $$ = new gr8::func_declaration_node(LINE, new basic_type(0, basic_type::TYPE_VOID), true, false, $3, nullptr); } 
    | tPUBLIC tPROCEDURE tIDENTIFIER tUSES vars                     { $$ = new gr8::func_declaration_node(LINE, new basic_type(0, basic_type::TYPE_VOID), true, false, $3, $5); } 
    | tDEFINE tipo tFUNCTION tIDENTIFIER tON vars tAS bloco         { $$ = new gr8::func_body_node(LINE, false, $2, $4, $6, nullptr, $8); } 
    | tDEFINE tipo tFUNCTION tIDENTIFIER tAS bloco                  { $$ = new gr8::func_body_node(LINE, false, $2, $4, nullptr, nullptr, $6); } 
    | tDEFINE tPROCEDURE tIDENTIFIER tON vars tAS bloco             { $$ = new gr8::func_body_node(LINE, false, new basic_type(0, basic_type::TYPE_VOID), $3, $5, nullptr, $7); } 
    | tDEFINE tPROCEDURE tIDENTIFIER tAS bloco                      { $$ = new gr8::func_body_node(LINE, false, new basic_type(0, basic_type::TYPE_VOID), $3, nullptr, nullptr, $5); } 
    | tDEFINE tPUBLIC tipo tFUNCTION tIDENTIFIER tON vars tAS bloco { $$ = new gr8::func_body_node(LINE, true, $3, $5, $7, nullptr, $9); } 
    | tDEFINE tPUBLIC tipo tFUNCTION tIDENTIFIER tAS bloco          { $$ = new gr8::func_body_node(LINE, true, $3, $5, nullptr, nullptr, $7); } 
    | tDEFINE tPUBLIC tPROCEDURE tIDENTIFIER tON vars tAS bloco     { $$ = new gr8::func_body_node(LINE, true, new basic_type(0, basic_type::TYPE_VOID), $4, $6, nullptr, $8); } 
    | tDEFINE tPUBLIC tPROCEDURE tIDENTIFIER tAS bloco              { $$ = new gr8::func_body_node(LINE, true, new basic_type(0, basic_type::TYPE_VOID), $4, nullptr, nullptr, $6); }
    | tUSE vars tFOR tIDENTIFIER                                    { $$ = new gr8::func_invocation_node(LINE, $4, $2);}
    | func_invoc                                                    { $$ = new cdk::sequence_node(LINE);}
    ;

func_invoc: tDO tIDENTIFIER                                               { $$ = new gr8::func_invocation_node(LINE, $2, nullptr);}
          | tUSE exprs tFOR tIDENTIFIER                                   { $$ = new gr8::func_invocation_node(LINE, $4, $2);}  
          ;
vars: var                                                                   { $$ = new cdk::sequence_node(LINE, $1); }   
    | vars "," var                                                          { $$ = new cdk::sequence_node(LINE, $3, $1); }  
    ;
    
tipo: tSMALL smallIT tFAKE                                                  { $$ = new basic_type(4, basic_type::TYPE_POINTER); }
    | tSMALL tFAKE                                                          { $$ = new basic_type(4, basic_type::TYPE_POINTER); }
    | tSMALL                                                                { $$ = new basic_type(4, basic_type::TYPE_INT); }
    | tHUGE hugeIT tFAKE                                                    { $$ = new basic_type(4, basic_type::TYPE_POINTER); }
    | tHUGE tFAKE                                                           { $$ = new basic_type(4, basic_type::TYPE_POINTER); }
    | tHUGE                                                                 { $$ = new basic_type(8, basic_type::TYPE_DOUBLE); }
    | fakeIT tNEWS                                                          { $$ = new basic_type(4, basic_type::TYPE_POINTER); }
    | tFAKE tNEWS                                                           { $$ = new basic_type(4, basic_type::TYPE_POINTER); }
    | tNEWS                                                                 { $$ = new basic_type(4, basic_type::TYPE_STRING); }
    ;
    
fakeIT: fakeIT tFAKE                                                        { $$ = new basic_type(4, basic_type::TYPE_POINTER); }   
      ;
      
smallIT: smallIT tSMALL                                                     { $$ = new basic_type(4, basic_type::TYPE_INT); }   
       ;
       
hugeIT: hugeIT tHUGE                                                        { $$ = new basic_type(8, basic_type::TYPE_DOUBLE);}   
      ;
      
bloco: tCURLYBRACKET decls_bloco instrs tCLOSEDCURLYBRACKET                 { $$ = new gr8::block_node(LINE, $2, $3); }
     |tCURLYBRACKET decls_bloco tCLOSEDCURLYBRACKET                         { $$ = new gr8::block_node(LINE, $2, nullptr); }
     |tCURLYBRACKET instrs tCLOSEDCURLYBRACKET                              { $$ = new gr8::block_node(LINE, nullptr, $2); }
     ;

instrs: instr                                                               { $$ = new cdk::sequence_node(LINE, $1); }                        
      | instrs instr                                                        { $$ = new cdk::sequence_node(LINE, $2, $1); }
      ;
      
instr: expr                                                                 { $$ = new cdk::sequence_node(LINE, $1); }                                                               
     | tTWEET expr                                                          { $$ = new gr8::print_node(LINE, $2, true); } 
     | tPOST expr                                                           { $$ = new gr8::print_node(LINE, $2, false); } 
     | tAGAIN                                                               { $$ = new gr8::again_node(LINE, nullptr); } 
     | tAGAIN tSMALL                                                        { $$ = new gr8::again_node(LINE, new cdk::integer_node(LINE, $2)); } 
     | tSTOP tSMALL                                                         { $$ = new gr8::stop_node(LINE, new cdk::integer_node(LINE, $2)); } 
     | tSTOP                                                                { $$ = new gr8::stop_node(LINE, nullptr); }     
     | tRETURN expr                                                         { $$ = new gr8::return_node(LINE, $2); } 
     | tRETURN                                                              { $$ = new gr8::return_node(LINE, nullptr); }
     | tIF condinstr                                                        { $$ = $2; }    
     | interinstr                                                           { $$ = $1; }    
     | bloco                                                                { $$ = $1; }
     | tREAD                                                                { $$ = new gr8::read_node(LINE); }
     | attrb                                                                { $$ = $1; }
     | tAPPLY tIDENTIFIER tTO expr tFROM expr tTO expr                      { $$ = new gr8::apply_node(LINE, $2, $4, $6, $8);}
     ;
     
     
attrb: tASSIGN expr tTO lval                                                { $$ = new cdk::assignment_node(LINE, $4, $2); }
     ;
     
condinstr: tIF expr tTHEN bloco tELSE condinstr                             { $$ = new gr8::if_else_node(LINE, $2, $4, $6); }
         | tIF expr tTHEN bloco tELSE bloco                                 { $$ = new gr8::if_else_node(LINE, $2, $4, $6); }
         | tIF expr tTHEN bloco                                             { $$ = new gr8::if_node(LINE, $2, $4); }
         ;
         
      
interinstr: tSWEEPING lval tFROM expr tTO expr tBY expr tDO bloco           { $$ = new gr8::sweeping_node(LINE, $4, $6, $8, $10, $2); }    
          | tSWEEPING lval tFROM expr tTO expr tDO bloco                    { $$ = new gr8::sweeping_node(LINE, $4, $6, nullptr, $8, $2); }   
          ;
          
          
expr : tSMALL                             { $$ = new cdk::integer_node(LINE, $1); }
     | tNEWS                              { $$ = new cdk::string_node(LINE, $1); }
     | tPLUS expr %prec tUNARY            { $$ = new gr8::identity_node(LINE, $2); }
     | tMINUS expr %prec tUNARY           { $$ = new cdk::neg_node(LINE, $2); }
     | expr tPLUS expr	                  { $$ = new cdk::add_node(LINE, $1, $3); }
     | expr tMINUS expr	                  { $$ = new cdk::sub_node(LINE, $1, $3); }
     | expr tTIMES expr	                  { $$ = new cdk::mul_node(LINE, $1, $3); }
     | expr tOVER expr	                  { $$ = new cdk::div_node(LINE, $1, $3); }
     | expr tMODULUS expr	              { $$ = new cdk::mod_node(LINE, $1, $3); }
     | expr tBELOW expr	                  { $$ = new cdk::lt_node(LINE, $1, $3); }
     | expr tABOVE expr	                  { $$ = new cdk::gt_node(LINE, $1, $3); }
     | expr tEQUALS expr	              { $$ = new cdk::eq_node(LINE, $1, $3); }
     | tNOT expr	                      { $$ = new cdk::not_node(LINE, $2); }
     | expr tAND expr	                  { $$ = new cdk::and_node(LINE, $1, $3); }
     | expr tOR expr	                  { $$ = new cdk::or_node(LINE, $1, $3); }
     | '(' expr ')'                       { $$ = $2; }
     | lval                               { $$ = new cdk::rvalue_node(LINE, $1); }  //FIXME TODO
     | lval tEQUALS expr                  { $$ = new cdk::assignment_node(LINE, $1, $3); }
     | expr tOBJECTS %prec tUNARY         { $$ = new gr8::mem_alloc_node(LINE, $1); }
     | lval '?'                           { $$ = new gr8::mem_address_node(LINE, $1);}
     ;

exprs: expr                               { $$ = new cdk::sequence_node(LINE, $1); }  
     | exprs ',' expr                     { $$ = new cdk::sequence_node(LINE, $3, $1); }  
     ;
lval : tIDENTIFIER                        { $$ = new cdk::identifier_node(LINE, $1); }
     | tCELL expr tAT expr                { $$ = new gr8::indexing_node(LINE, $4, $2); }  
     ;

%%
