cmake_minimum_required(VERSION 3.0)
project(MiniJavaCompiler)

set(CMAKE_CXX_STANDARD 17)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

set(
    HEADERS
    ${MiniJavaCompiler_SOURCE_DIR}/driver.hh
    ${MiniJavaCompiler_SOURCE_DIR}/parser.hh
    )

BISON_TARGET(
    MyParser
    ${MiniJavaCompiler_SOURCE_DIR}/Parser/parser.y
    ${MiniJavaCompiler_SOURCE_DIR}/Parser/parser.cpp
    COMPILE_FLAGS "-W -Wconflicts-sr -Wconflicts-rr -Wother -Wprecedence --warnings=all --report=all --verbose"
    DEFINES_FILE ${MiniJavaCompiler_SOURCE_DIR}/Parser/parser.hh
)

FLEX_TARGET(
    MyScanner
    ${MiniJavaCompiler_SOURCE_DIR}/Parser/scanner.l
    ${MiniJavaCompiler_SOURCE_DIR}/Parser/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

add_executable(
    MiniJavaCompiler
    main.cpp
        Driver/driver.cpp
    ${BISON_MyParser_OUTPUTS}
    ${FLEX_MyScanner_OUTPUTS}
    Nodes/Nodes.h
    Nodes/NodesHeaders/Expressions/Add.h
    Nodes/NodesHeaders/Expressions/Mul.h
    Nodes/NodesHeaders/Expressions/Percent.h
    Nodes/NodesHeaders/Expressions/Div.h
    Nodes/NodesHeaders/Expressions/Equals.h
    Nodes/NodesHeaders/Statements/Assign.h
    Nodes/NodesHeaders/Expressions/Not.h
    Nodes/NodesHeaders/Expressions/Expression.h
    Nodes/NodesHeaders/Expressions/Number.h
    Nodes/NodesHeaders/Expressions/Subtract.h
    Nodes/NodesHeaders/Expressions/At.h
    Nodes/NodesHeaders/Expressions/NewArray.h
    Nodes/NodesHeaders/Expressions/Length.h
    Nodes/NodesHeaders/Expressions/Identifier.h
    Nodes/NodesHeaders/Expressions/This.h
    Nodes/NodesHeaders/Expressions/MethodInvocation.h
    Nodes/NodesHeaders/Expressions/Less.h
    Nodes/NodesHeaders/Expressions/More.h
    Nodes/NodesHeaders/Statements/Lvalue.h
    Nodes/NodesHeaders/Statements/Return.h
    Nodes/NodesHeaders/Statements/Print.h
    Nodes/NodesHeaders/Statements/While.h
    Nodes/NodesHeaders/Statements/If.h
    Nodes/NodesHeaders/Statements/Statements.h
    Nodes/NodesHeaders/Statements/Assert.h
    Nodes/NodesHeaders/Decls/Type.h
    Nodes/NodesHeaders/Decls/MethodDeclaration.h
    Nodes/NodesHeaders/Decls/Class.h
    Nodes/NodesHeaders/Program.h
    Nodes/NodesHeaders/Node.h
    Visitors/Visitor.h
    Nodes/NodesHeaders/Statements/Statement.h
    Nodes/NodesHeaders/Decls/VarDeclaration.h
    Visitors/Dumper.h
    Visitors/Impl/Dumper.cpp
    Nodes/NodesImpl/Program.cpp
    Nodes/NodesImpl/Decls/Class.cpp
    Nodes/NodesImpl/Decls/MethodDeclaration.cpp
    Nodes/NodesImpl/Decls/Type.cpp
    Nodes/NodesImpl/Decls/VarDeclaration.cpp
    Nodes/NodesImpl/Expressions/Add.cpp
    Nodes/NodesImpl/Expressions/At.cpp
    Nodes/NodesImpl/Expressions/Div.cpp
    Nodes/NodesImpl/Expressions/Equals.cpp
    Nodes/NodesImpl/Expressions/Identifier.cpp
    Nodes/NodesImpl/Expressions/Length.cpp
    Nodes/NodesImpl/Expressions/Less.cpp
    Nodes/NodesImpl/Expressions/MethodInvocation.cpp
    Nodes/NodesImpl/Expressions/More.cpp
    Nodes/NodesImpl/Expressions/Mul.cpp
    Nodes/NodesImpl/Expressions/NewArray.cpp
    Nodes/NodesImpl/Expressions/Not.cpp
    Nodes/NodesImpl/Expressions/Number.cpp
    Nodes/NodesImpl/Expressions/Percent.cpp
    Nodes/NodesImpl/Expressions/Subtract.cpp
    Nodes/NodesImpl/Expressions/This.cpp
    Nodes/NodesImpl/Statements/Assert.cpp
    Nodes/NodesImpl/Statements/Assign.cpp
    Nodes/NodesImpl/Statements/If.cpp
    Nodes/NodesImpl/Statements/Lvalue.cpp
    Nodes/NodesImpl/Statements/Print.cpp
    Nodes/NodesImpl/Statements/Return.cpp
    Nodes/NodesImpl/Statements/Statements.cpp
    Nodes/NodesImpl/Statements/While.cpp
    Nodes/NodesHeaders/Expressions/BinaryOp.h
    Nodes/NodesImpl/Expressions/BinaryOp.cpp
    Nodes/NodesHeaders/Decls/Formal.h
    Nodes/NodesImpl/Decls/Formal.cpp
    Nodes/NodesHeaders/Decls/MemberDeclaration.h
    Nodes/NodesHeaders/Expressions/New.h
    Nodes/NodesImpl/Expressions/New.cpp
    Nodes/NodesHeaders/Statements/Scope.h
    Nodes/NodesImpl/Statements/Scope.cpp
    Nodes/NodesHeaders/Expressions/Or.h
    Nodes/NodesHeaders/Expressions/And.h
    Nodes/NodesHeaders/Expressions/BooleanLiteral.h
    Nodes/NodesImpl/Expressions/Or.cpp
    Nodes/NodesImpl/Expressions/And.cpp
    Nodes/NodesImpl/Expressions/BooleanLiteral.cpp
    Visitors/Interpreter.h
    Visitors/AcceptRetType.h
    Visitors/Impl/Interpreter.cpp Visitors/SymbolTables/SymbolTableBuilder.h Visitors/SymbolTables/ProgramTable.h Visitors/SymbolTables/ClassTable.h Visitors/SymbolTables/ScopeTable.h Visitors/SymbolTables/Impl/ClassTable.cpp Visitors/SymbolTables/Impl/ProgramTable.cpp Visitors/SymbolTables/Impl/ScopeTable.cpp Visitors/SymbolTables/Impl/SymbolTableBuilder.cpp Visitors/SymbolTables/Symbol.h Nodes/NodesImpl/Expressions/Expression.cpp Nodes/NodesImpl/Node.cpp Visitors/Typer.h Visitors/Impl/Typer.cpp)

target_include_directories(MiniJavaCompiler PRIVATE ${MiniJavaCompiler_SOURCE_DIR})



