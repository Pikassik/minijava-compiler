%{
    #include <cerrno>
    #include <climits>
    #include <cstdlib>
    #include <cstring> // strerror
    #include <string>
    #include <iostream>
    #include <Driver/driver.hh>
    #include "parser.hh"
%}

%option noyywrap nounput noinput batch debug

%option c++
%option yyclass="Scanner"
%option yylineno

%{
  // A number symbol corresponding to the value in S.
  yy::parser::symbol_type make_NUMBER(
    const std::string &s,
    const yy::parser::location_type& loc
  );
%}

id    [a-zA-Z][a-zA-Z_0-9]*
int   [0-9]+
blank [ \t\r]
comment \/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+\/
linecomment \/\/.*

%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  {loc.columns (yyleng);\
                            prev_current_yylineno = current_yylineno;\
                            current_yylineno = yylineno; };
%}
%%
%{
  // A handy shortcut to the location held by the driver.
  yy::location& loc = driver.location;
  // Code run each time yylex is called.
  loc.step();

  int prev_current_yylineno = yylineno;
  int current_yylineno = yylineno;
%}


{comment}     {loc.lines(yylineno - prev_current_yylineno); loc.step ();}
{linecomment} loc.lines(1); loc.step ();

{blank}+      loc.step ();
\n+           loc.lines (yyleng); loc.step ();

"class"               return yy::parser::make_CLASS      (loc);
"length"              return yy::parser::make_LENGTH     (loc);
"new"                 return yy::parser::make_NEW        (loc);
"extends"             return yy::parser::make_EXTENDS    (loc);
"public"              return yy::parser::make_PUBLIC     (loc);
"static"              return yy::parser::make_STATIC     (loc);
"main"                return yy::parser::make_MAIN       (loc);
"void"                return yy::parser::make_VOID       (loc);
"int"                 return yy::parser::make_INT        (loc);
"boolean"             return yy::parser::make_BOOLEAN    (loc);
"else"                return yy::parser::make_ELSE       (loc);
"if"                  return yy::parser::make_IF         (loc);
"while"               return yy::parser::make_WHILE      (loc);
"this"                return yy::parser::make_THIS       (loc);
"{"                   return yy::parser::make_LCURLPAREN (loc);
"}"                   return yy::parser::make_RCURLPAREN (loc);
";"                   return yy::parser::make_SEMICOLON  (loc);
"System.out.println"  return yy::parser::make_PRINT      (loc);
"assert"              return yy::parser::make_ASSERT     (loc);
"["                   return yy::parser::make_LSQPAREN   (loc);
"]"                   return yy::parser::make_RSQPAREN   (loc);
"."                   return yy::parser::make_DOT        (loc);
","                   return yy::parser::make_COMMA      (loc);
"="                   return yy::parser::make_ASSIGN     (loc);
"!"                   return yy::parser::make_EXCL       (loc);
"&&"                  return yy::parser::make_AND        (loc);
"||"                  return yy::parser::make_OR         (loc);
"<"                   return yy::parser::make_LESS       (loc);
">"                   return yy::parser::make_MORE       (loc);
"=="                  return yy::parser::make_EQUAL      (loc);
"-"                   return yy::parser::make_MINUS      (loc);
"+"                   return yy::parser::make_PLUS       (loc);
"*"                   return yy::parser::make_STAR       (loc);
"/"                   return yy::parser::make_SLASH      (loc);
"%"                   return yy::parser::make_PERC       (loc);
"("                   return yy::parser::make_LPAREN     (loc);
")"                   return yy::parser::make_RPAREN     (loc);
"true"                return yy::parser::make_TRUE       (loc);
"false"               return yy::parser::make_FALSE      (loc);

{int}                 return make_NUMBER(yytext, loc);
{id}                  return yy::parser::make_IDENTIFIER(yytext, loc);
.          {
                throw yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext));
           }
<<EOF>>    return yy::parser::make_END (loc);
%%

yy::parser::symbol_type make_NUMBER(
  const std::string &s,
  const yy::parser::location_type& loc
) {
  errno = 0;
  long n = strtol(s.c_str(), NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE))
    throw yy::parser::syntax_error(loc, "integer is out of range: " + s);
  return yy::parser::make_NUMBER((int) n, loc);
}