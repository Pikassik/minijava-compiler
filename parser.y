%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    class Scanner;
    class Driver;
}

%define parse.trace
%define parse.error verbose

%code {
    #include "driver.hh"
    #include "location.hh"

    static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
        return scanner.ScanToken();
    }
}

%lex-param { Scanner &scanner }
%lex-param { Driver &driver }
%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%locations

%define api.token.prefix {TOK_}

%token
    END 0 "end of file"
    NEW "new"
    CLASS "class"
    PUBLIC "public"
    STATIC "static"
    VOID "void"
    MAIN "main"
    LCURLPAREN "{"
    RCURLPAREN "}"
    SEMICOLON ";"
    LENGTH "length"
    PRINT "System.out.println"
    ASSERT "assert"
    INT "int"
    BOOLEAN "boolean"
    LSQPAREN "["
    RSQPAREN "]"
    ASSIGN "="
    EXCL "!"
    AND "&&"
    OR "||"
    LESS "<"
    MORE ">"
    EQUAL "=="
    MINUS "-"
    PLUS "+"
    STAR "*"
    SLASH "/"
    PERC "%"
    DOT "."
    LPAREN "("
    RPAREN ")"
    TRUE "true"
    FALSE "false"
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"


%nterm <int> SignedNumber
%nterm <int> Expression

%left        "&&" "||" "<" ">" "=="
%left        "-" "+"
%left        "*" "/" "%"
%precedence  "!"

%%
%start Program;
Program: MainClassDeclaration {}
;

MainClassDeclaration: "class" "identifier" "{" "public" "static" "void" "main" "(" ")" Scope "}" {/* pass */}
;

SimpleType: "int"     {/* pass */}
          | "boolean" {/* pass */}
;

Statements: %empty               {/* pass */}
          | Statements Statement {/* pass */}
;

Scope: "{" Statements "}" {/* pass */}
;

Statement: "assert" "(" Expression ")" ";" { assert($3 != 0); }
         | LocalVarDeclaration {/* pass */}
         | Scope {/* pass */}
         | "System.out.println" "(" Expression ")" ";" { std::cout << $3 << std::endl; }
         | "identifier" "=" Expression ";" { driver.variables.at($1) = $3; }
         | "identifier" "[" Expression "]" "=" Expression ";" { driver.arrays.at($1).at($3) = $6; }
         | "identifier" "=" "new" SimpleType "[" Expression "]" ";" { driver.arrays.at($1).resize($6); }
;

LocalVarDeclaration: SimpleType  "identifier" ";" {
  if (driver.variables.find($2) != driver.variables.end()) {
    std::cerr << "redefenition of variable: " << $2 << std::endl;
    throw;
  }

  driver.variables[$2] = 0;
}

                   | SimpleType "[" "]" "identifier" ";" {
  if (driver.arrays.find($4) != driver.arrays.end()) {
    std::cerr << "redefenition of array variable: " << $4 << std::endl;
    throw;
  }

  driver.arrays[$4] = std::vector<int>();
}
;


;

Expression: Expression "&&" Expression      { $$ = $1 && $3; }
          | Expression "||" Expression      { $$ = $1 || $3; }
          | Expression "<"  Expression      { $$ = $1 <  $3; }
          | Expression ">"  Expression      { $$ = $1 >  $3; }
          | Expression "==" Expression      { $$ = $1 == $3; }
          | Expression "+"  Expression      { $$ = $1 +  $3; }
          | Expression "-"  Expression      { $$ = $1 -  $3; }
          | Expression "*"  Expression      { $$ = $1 *  $3; }
          | Expression "/"  Expression      { $$ = $1 /  $3; }
          | Expression "%"  Expression      { $$ = $1 %  $3; }
          | "identifier" "[" Expression "]" { $$ = driver.arrays.at($1).at($3); }
          | "identifier" "." "length"       { $$ = driver.arrays.at($1).size(); }
          | "!" Expression                  { $$ = !$2; }
          | "(" Expression ")"              { $$ = $2; }
          | "identifier"                    { $$ = driver.variables.at($1); }
          | SignedNumber                    { $$ = $1; }
;

SignedNumber: "true"       { $$ = 1; }
            | "false"      { $$ = 0; }
            | "number"     { $$ = $1; }
            | "-" "number" { $$ = -$2; }

%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
