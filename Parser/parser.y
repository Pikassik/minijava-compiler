%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    #include <Nodes/Nodes.h>
    class Scanner;
    class Driver;

    using namespace node;
    using namespace std;

    template <typename T>
    using ptr = shared_ptr<T>;
}

%define parse.trace
%define parse.error verbose

%code {
    #include <Driver/driver.hh>
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
    RETURN "return"
    CLASS "class"
    PUBLIC "public"
    STATIC "static"
    VOID "void"
    MAIN "main"
    EXTENDS "extends"
    ELSE "else"
    IF "if"
    WHILE "while"
    THIS "this"
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
    COMMA ","
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

%token <string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%nterm <ptr<Program>> Program
%nterm <ptr<Class>> MainClassDeclaration
%nterm <ptr<Class>> ClassDeclaration
%nterm <pair<vector<ptr<MethodDeclaration>>, vector<ptr<VarDeclaration>>>> ClassMembers
%nterm <ptr<MethodDeclaration>> MethodDeclaration
%nterm <ptr<VarDeclaration>> VarDeclaration
%nterm <ptr<VarDeclaration>> VarDeclarationStmt
%nterm <vector<ptr<VarDeclaration>>> Formals
%nterm <ptr<Type>> Type
%nterm <ptr<Type>> SimpleType
%nterm <ptr<Type>> ArrayType
%nterm <string> TypeId
%nterm <vector<ptr<Statement>>> Statements
%nterm <ptr<Scope>> Scope
%nterm <ptr<Statement>> Statement
%nterm <ptr<MethodInvocation>> MethodInvocation
%nterm <vector<ptr<Expression>>> MethodArgs
%nterm <ptr<Lvalue>> Lvalue
%nterm <ptr<Expression>> Expression
%nterm <ptr<BooleanLiteral>> BooleanLiteral
%nterm <ptr<Number>> SignedNumber

%printer { /* yyo << $$; */ } <*>;

%precedence  "["
%right       "="
%left        "&&" "||" "<" ">" "=="
%left        "-" "+"
%left        "*" "/" "%"
%precedence  "!"
%left        "."
%precedence  ")"
%precedence  "else"

%%
%start Program;
Program: MainClassDeclaration {
  $$ = make_shared<Program>(vector<ptr<Class>>{$1});
  driver.program = $$;
}
       | Program ClassDeclaration {
  $1->classes.push_back($2);
  $$ = move($1);
}
;

MainClassDeclaration: "class" "identifier" "{" "public" "static" "void" "main" "(" ")" Scope "}" {
  $$ = make_shared<Class>(
    $2,
    vector<ptr<MethodDeclaration>>(
      {make_shared<MethodDeclaration>(make_shared<Type>("void"), "main", vector<ptr<VarDeclaration>>(), $10)}
    ),
    vector<ptr<VarDeclaration>>()
  );
}
;

ClassDeclaration: "class" "identifier" "{" ClassMembers "}" {
  $$ = make_shared<Class>($2, move($4.first), move($4.second));
}
                | "class" "identifier" "extends" "identifier" "{" ClassMembers "}" {
  $$ = make_shared<Class>($2, $4, move($6.first), move($6.second));
}
;

ClassMembers: %empty { $$ = pair<vector<ptr<MethodDeclaration>>, vector<ptr<VarDeclaration>>>(); }
            | ClassMembers MethodDeclaration {
  $1.first.push_back($2);  // methods.push
  $$ = move($1);
}
            | ClassMembers VarDeclarationStmt {
  $1.second.push_back($2); // fields.push
  $$ = move($1);
}
;

MethodDeclaration: "public" Type "identifier" "(" Formals ")" Scope {
  $$ = make_shared<MethodDeclaration>($2, $3, move($5), $7);
}
;

VarDeclaration: Type "identifier" { $$ = make_shared<VarDeclaration>($1, $2); }

Formals: %empty { $$ = vector<ptr<VarDeclaration>>(); }
       | VarDeclaration { $$ = vector<ptr<VarDeclaration>>{$1}; }
       | Formals "," VarDeclaration {
  $1.push_back($3);
  $$ = move($1);
}
;

Type: SimpleType { $$ = $1; }
    | ArrayType  { $$ = $1; }
;

SimpleType: "int" { $$ = make_shared<Type>("int", false); }
          | "boolean" { $$ = make_shared<Type>("boolean", false); }
          | "void" { $$ = make_shared<Type>("void", false); }
          | TypeId { $$ = make_shared<Type>($1, false); }
;

ArrayType: SimpleType "[" "]" {
  $1->is_array = true;
  $$ = $1;
}
;

TypeId: "identifier" { $$ = $1; }
;

Statements: %empty { $$ = vector<ptr<Statement>>(); }
          | Statements Statement {
  $1.push_back($2);
  $$ = $1;
}
;

Scope: "{" Statements "}" { $$ = make_shared<Scope>($2); }
;

Statement: "assert" "(" Expression ")" ";" { $$ = make_shared<Assert>($3); }
         | VarDeclarationStmt { $$ = $1; }
         | Scope { $$ = $1; }
         | "if" "(" Expression ")" Statement { $$ = make_shared<If>($3, $5); }
         | "if" "(" Expression ")" Statement "else" Statement { $$ = make_shared<If>($3, $5, $7); }
         | "while" "(" Expression ")" Statement { $$ = make_shared<While>($3, $5); }
         | "System.out.println" "(" Expression ")" ";" { $$ = make_shared<Print>($3); }
         | Lvalue "=" Expression ";" { $$ = make_shared<Assign>($1, $3); }
         | "return" Expression ";" { $$ = make_shared<Return>($2); }
         | MethodInvocation ";" { $$ = $1; }
;

VarDeclarationStmt: VarDeclaration ";" { $$ = $1; }
;

MethodInvocation: Expression "." "identifier" "(" MethodArgs ")" { $$ = make_shared<MethodInvocation>($1, $3, $5); }
;

MethodArgs: %empty { $$ = vector<ptr<Expression>>(); }
          | Expression { $$.push_back($1); }
          | MethodArgs "," Expression {
  $1.push_back($3);
  $$ = move($1);
}
;

Lvalue: "identifier" { $$ = make_shared<Lvalue>($1); }
      | "identifier" "[" Expression "]" { $$ = make_shared<Lvalue>($1, $3); }
;

Expression: "this" { $$ = make_shared<This>(); }
          | MethodInvocation { $$ = $1; }
          | Expression "&&" Expression { $$ = make_shared<Mul>($1, $3); }
          | Expression "||" Expression { $$ = make_shared<Add>($1, $3); }
          | Expression "<"  Expression { $$ = make_shared<Less>($1, $3); }
          | Expression ">"  Expression { $$ = make_shared<More>($1, $3); }
          | Expression "==" Expression { $$ = make_shared<Equals>($1, $3); }
          | Expression "+"  Expression { $$ = make_shared<Add>($1, $3); }
          | Expression "-"  Expression { $$ = make_shared<Subtract>($1, $3); }
          | Expression "*"  Expression { $$ = make_shared<Mul>($1, $3); }
          | Expression "/"  Expression { $$ = make_shared<Div>($1, $3); }
          | Expression "%"  Expression { $$ = make_shared<Percent>($1, $3); }
          | Expression "[" Expression "]" { $$ = make_shared<At>($1, $3); }
          | Expression "." "length" { $$ = make_shared<Length>($1); }
          | "new" SimpleType "[" Expression "]" { $$ = make_shared<NewArray>($2, $4); $$->type->is_array = true; }
          | "new" TypeId "(" ")" { $$ = make_shared<New>($2); }
          | "!" Expression { $$ = make_shared<Not>($2); }
          | "(" Expression ")" { $$ = $2; }
          | "identifier" { $$ = make_shared<Identifier>($1); }
          | SignedNumber { $$ = $1; }
          | BooleanLiteral { $$ = $1; }
;

BooleanLiteral: "true" { $$ = make_shared<BooleanLiteral>(true); }
              | "false" { $$ = make_shared<BooleanLiteral>(false); }
;

SignedNumber: "number"     { $$ = make_shared<Number>($1); }
            | "-" "number" { $$ = make_shared<Number>(-$2); }
;

%%

void
yy::parser::error(const location_type& l, const string& m)
{
  cerr << l << ": " << m << '\n';
}
