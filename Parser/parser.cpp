// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "parser.hh"


// Unqualified %code blocks.
#line 25 "/home/user/minijava-compiler/Parser/parser.y"

    #include <Driver/driver.hh>
    #include "location.hh"

    static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
        return scanner.ScanToken();
    }

#line 54 "/home/user/minijava-compiler/Parser/parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 145 "/home/user/minijava-compiler/Parser/parser.cpp"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  parser::parser (Scanner &scanner_yyarg, Driver &driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_number_type
  parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 44: // "number"
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 49: // ClassMembers
        value.YY_MOVE_OR_COPY< pair<vector<ptr<MethodDeclaration>>, vector<ptr<VarDeclaration>>> > (YY_MOVE (that.value));
        break;

      case 65: // BooleanLiteral
        value.YY_MOVE_OR_COPY< ptr<BooleanLiteral> > (YY_MOVE (that.value));
        break;

      case 47: // MainClassDeclaration
      case 48: // ClassDeclaration
        value.YY_MOVE_OR_COPY< ptr<Class> > (YY_MOVE (that.value));
        break;

      case 64: // Expression
        value.YY_MOVE_OR_COPY< ptr<Expression> > (YY_MOVE (that.value));
        break;

      case 63: // Lvalue
        value.YY_MOVE_OR_COPY< ptr<Lvalue> > (YY_MOVE (that.value));
        break;

      case 50: // MethodDeclaration
        value.YY_MOVE_OR_COPY< ptr<MethodDeclaration> > (YY_MOVE (that.value));
        break;

      case 61: // MethodInvocation
        value.YY_MOVE_OR_COPY< ptr<MethodInvocation> > (YY_MOVE (that.value));
        break;

      case 66: // SignedNumber
        value.YY_MOVE_OR_COPY< ptr<Number> > (YY_MOVE (that.value));
        break;

      case 46: // Program
        value.YY_MOVE_OR_COPY< ptr<Program> > (YY_MOVE (that.value));
        break;

      case 59: // Scope
        value.YY_MOVE_OR_COPY< ptr<Scope> > (YY_MOVE (that.value));
        break;

      case 60: // Statement
        value.YY_MOVE_OR_COPY< ptr<Statement> > (YY_MOVE (that.value));
        break;

      case 54: // Type
      case 55: // SimpleType
      case 56: // ArrayType
        value.YY_MOVE_OR_COPY< ptr<Type> > (YY_MOVE (that.value));
        break;

      case 51: // VarDeclaration
      case 52: // VarDeclarationStmt
        value.YY_MOVE_OR_COPY< ptr<VarDeclaration> > (YY_MOVE (that.value));
        break;

      case 43: // "identifier"
      case 57: // TypeId
        value.YY_MOVE_OR_COPY< string > (YY_MOVE (that.value));
        break;

      case 62: // MethodArgs
        value.YY_MOVE_OR_COPY< vector<ptr<Expression>> > (YY_MOVE (that.value));
        break;

      case 58: // Statements
        value.YY_MOVE_OR_COPY< vector<ptr<Statement>> > (YY_MOVE (that.value));
        break;

      case 53: // Formals
        value.YY_MOVE_OR_COPY< vector<ptr<VarDeclaration>> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 44: // "number"
        value.move< int > (YY_MOVE (that.value));
        break;

      case 49: // ClassMembers
        value.move< pair<vector<ptr<MethodDeclaration>>, vector<ptr<VarDeclaration>>> > (YY_MOVE (that.value));
        break;

      case 65: // BooleanLiteral
        value.move< ptr<BooleanLiteral> > (YY_MOVE (that.value));
        break;

      case 47: // MainClassDeclaration
      case 48: // ClassDeclaration
        value.move< ptr<Class> > (YY_MOVE (that.value));
        break;

      case 64: // Expression
        value.move< ptr<Expression> > (YY_MOVE (that.value));
        break;

      case 63: // Lvalue
        value.move< ptr<Lvalue> > (YY_MOVE (that.value));
        break;

      case 50: // MethodDeclaration
        value.move< ptr<MethodDeclaration> > (YY_MOVE (that.value));
        break;

      case 61: // MethodInvocation
        value.move< ptr<MethodInvocation> > (YY_MOVE (that.value));
        break;

      case 66: // SignedNumber
        value.move< ptr<Number> > (YY_MOVE (that.value));
        break;

      case 46: // Program
        value.move< ptr<Program> > (YY_MOVE (that.value));
        break;

      case 59: // Scope
        value.move< ptr<Scope> > (YY_MOVE (that.value));
        break;

      case 60: // Statement
        value.move< ptr<Statement> > (YY_MOVE (that.value));
        break;

      case 54: // Type
      case 55: // SimpleType
      case 56: // ArrayType
        value.move< ptr<Type> > (YY_MOVE (that.value));
        break;

      case 51: // VarDeclaration
      case 52: // VarDeclarationStmt
        value.move< ptr<VarDeclaration> > (YY_MOVE (that.value));
        break;

      case 43: // "identifier"
      case 57: // TypeId
        value.move< string > (YY_MOVE (that.value));
        break;

      case 62: // MethodArgs
        value.move< vector<ptr<Expression>> > (YY_MOVE (that.value));
        break;

      case 58: // Statements
        value.move< vector<ptr<Statement>> > (YY_MOVE (that.value));
        break;

      case 53: // Formals
        value.move< vector<ptr<VarDeclaration>> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 44: // "number"
        value.copy< int > (that.value);
        break;

      case 49: // ClassMembers
        value.copy< pair<vector<ptr<MethodDeclaration>>, vector<ptr<VarDeclaration>>> > (that.value);
        break;

      case 65: // BooleanLiteral
        value.copy< ptr<BooleanLiteral> > (that.value);
        break;

      case 47: // MainClassDeclaration
      case 48: // ClassDeclaration
        value.copy< ptr<Class> > (that.value);
        break;

      case 64: // Expression
        value.copy< ptr<Expression> > (that.value);
        break;

      case 63: // Lvalue
        value.copy< ptr<Lvalue> > (that.value);
        break;

      case 50: // MethodDeclaration
        value.copy< ptr<MethodDeclaration> > (that.value);
        break;

      case 61: // MethodInvocation
        value.copy< ptr<MethodInvocation> > (that.value);
        break;

      case 66: // SignedNumber
        value.copy< ptr<Number> > (that.value);
        break;

      case 46: // Program
        value.copy< ptr<Program> > (that.value);
        break;

      case 59: // Scope
        value.copy< ptr<Scope> > (that.value);
        break;

      case 60: // Statement
        value.copy< ptr<Statement> > (that.value);
        break;

      case 54: // Type
      case 55: // SimpleType
      case 56: // ArrayType
        value.copy< ptr<Type> > (that.value);
        break;

      case 51: // VarDeclaration
      case 52: // VarDeclarationStmt
        value.copy< ptr<VarDeclaration> > (that.value);
        break;

      case 43: // "identifier"
      case 57: // TypeId
        value.copy< string > (that.value);
        break;

      case 62: // MethodArgs
        value.copy< vector<ptr<Expression>> > (that.value);
        break;

      case 58: // Statements
        value.copy< vector<ptr<Statement>> > (that.value);
        break;

      case 53: // Formals
        value.copy< vector<ptr<VarDeclaration>> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 44: // "number"
        value.move< int > (that.value);
        break;

      case 49: // ClassMembers
        value.move< pair<vector<ptr<MethodDeclaration>>, vector<ptr<VarDeclaration>>> > (that.value);
        break;

      case 65: // BooleanLiteral
        value.move< ptr<BooleanLiteral> > (that.value);
        break;

      case 47: // MainClassDeclaration
      case 48: // ClassDeclaration
        value.move< ptr<Class> > (that.value);
        break;

      case 64: // Expression
        value.move< ptr<Expression> > (that.value);
        break;

      case 63: // Lvalue
        value.move< ptr<Lvalue> > (that.value);
        break;

      case 50: // MethodDeclaration
        value.move< ptr<MethodDeclaration> > (that.value);
        break;

      case 61: // MethodInvocation
        value.move< ptr<MethodInvocation> > (that.value);
        break;

      case 66: // SignedNumber
        value.move< ptr<Number> > (that.value);
        break;

      case 46: // Program
        value.move< ptr<Program> > (that.value);
        break;

      case 59: // Scope
        value.move< ptr<Scope> > (that.value);
        break;

      case 60: // Statement
        value.move< ptr<Statement> > (that.value);
        break;

      case 54: // Type
      case 55: // SimpleType
      case 56: // ArrayType
        value.move< ptr<Type> > (that.value);
        break;

      case 51: // VarDeclaration
      case 52: // VarDeclarationStmt
        value.move< ptr<VarDeclaration> > (that.value);
        break;

      case 43: // "identifier"
      case 57: // TypeId
        value.move< string > (that.value);
        break;

      case 62: // MethodArgs
        value.move< vector<ptr<Expression>> > (that.value);
        break;

      case 58: // Statements
        value.move< vector<ptr<Statement>> > (that.value);
        break;

      case 53: // Formals
        value.move< vector<ptr<VarDeclaration>> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
      case 43: // "identifier"
#line 111 "/home/user/minijava-compiler/Parser/parser.y"
                 { /* yyo << $$; */ }
#line 650 "/home/user/minijava-compiler/Parser/parser.cpp"
        break;

      case 44: // "number"
#line 111 "/home/user/minijava-compiler/Parser/parser.y"
                 { /* yyo << $$; */ }
#line 656 "/home/user/minijava-compiler/Parser/parser.cpp"
        break;

      case 46: // Program
#line 111 "/home/user/minijava-compiler/Parser/parser.y"
                 { /* yyo << $$; */ }
#line 662 "/home/user/minijava-compiler/Parser/parser.cpp"
        break;

      case 47: // MainClassDeclaration
#line 111 "/home/user/minijava-compiler/Parser/parser.y"
                 { /* yyo << $$; */ }
#line 668 "/home/user/minijava-compiler/Parser/parser.cpp"
        break;

      case 48: // ClassDeclaration
#line 111 "/home/user/minijava-compiler/Parser/parser.y"
                 { /* yyo << $$; */ }
#line 674 "/home/user/minijava-compiler/Parser/parser.cpp"
        break;

      case 49: // ClassMembers
#line 111 "/home/user/minijava-compiler/Parser/parser.y"
                 { /* yyo << $$; */ }
#line 680 "/home/user/minijava-compiler/Parser/parser.cpp"
        break;

      case 50: // MethodDeclaration
#line 111 "/home/user/minijava-compiler/Parser/parser.y"
                 { /* yyo << $$; */ }
#line 686 "/home/user/minijava-compiler/Parser/parser.cpp"
        break;

      case 51: // VarDeclaration
#line 111 "/home/user/minijava-compiler/Parser/parser.y"
                 { /* yyo << $$; */ }
#line 692 "/home/user/minijava-compiler/Parser/parser.cpp"
        break;

      case 52: // VarDeclarationStmt
#line 111 "/home/user/minijava-compiler/Parser/parser.y"
                 { /* yyo << $$; */ }
#line 698 "/home/user/minijava-compiler/Parser/parser.cpp"
        break;

      case 53: // Formals
#line 111 "/home/user/minijava-compiler/Parser/parser.y"
                 { /* yyo << $$; */ }
#line 704 "/home/user/minijava-compiler/Parser/parser.cpp"
        break;

      case 54: // Type
#line 111 "/home/user/minijava-compiler/Parser/parser.y"
                 { /* yyo << $$; */ }
#line 710 "/home/user/minijava-compiler/Parser/parser.cpp"
        break;

      case 55: // SimpleType
#line 111 "/home/user/minijava-compiler/Parser/parser.y"
                 { /* yyo << $$; */ }
#line 716 "/home/user/minijava-compiler/Parser/parser.cpp"
        break;

      case 56: // ArrayType
#line 111 "/home/user/minijava-compiler/Parser/parser.y"
                 { /* yyo << $$; */ }
#line 722 "/home/user/minijava-compiler/Parser/parser.cpp"
        break;

      case 57: // TypeId
#line 111 "/home/user/minijava-compiler/Parser/parser.y"
                 { /* yyo << $$; */ }
#line 728 "/home/user/minijava-compiler/Parser/parser.cpp"
        break;

      case 58: // Statements
#line 111 "/home/user/minijava-compiler/Parser/parser.y"
                 { /* yyo << $$; */ }
#line 734 "/home/user/minijava-compiler/Parser/parser.cpp"
        break;

      case 59: // Scope
#line 111 "/home/user/minijava-compiler/Parser/parser.y"
                 { /* yyo << $$; */ }
#line 740 "/home/user/minijava-compiler/Parser/parser.cpp"
        break;

      case 60: // Statement
#line 111 "/home/user/minijava-compiler/Parser/parser.y"
                 { /* yyo << $$; */ }
#line 746 "/home/user/minijava-compiler/Parser/parser.cpp"
        break;

      case 61: // MethodInvocation
#line 111 "/home/user/minijava-compiler/Parser/parser.y"
                 { /* yyo << $$; */ }
#line 752 "/home/user/minijava-compiler/Parser/parser.cpp"
        break;

      case 62: // MethodArgs
#line 111 "/home/user/minijava-compiler/Parser/parser.y"
                 { /* yyo << $$; */ }
#line 758 "/home/user/minijava-compiler/Parser/parser.cpp"
        break;

      case 63: // Lvalue
#line 111 "/home/user/minijava-compiler/Parser/parser.y"
                 { /* yyo << $$; */ }
#line 764 "/home/user/minijava-compiler/Parser/parser.cpp"
        break;

      case 64: // Expression
#line 111 "/home/user/minijava-compiler/Parser/parser.y"
                 { /* yyo << $$; */ }
#line 770 "/home/user/minijava-compiler/Parser/parser.cpp"
        break;

      case 65: // BooleanLiteral
#line 111 "/home/user/minijava-compiler/Parser/parser.y"
                 { /* yyo << $$; */ }
#line 776 "/home/user/minijava-compiler/Parser/parser.cpp"
        break;

      case 66: // SignedNumber
#line 111 "/home/user/minijava-compiler/Parser/parser.y"
                 { /* yyo << $$; */ }
#line 782 "/home/user/minijava-compiler/Parser/parser.cpp"
        break;

      default:
        break;
    }
    yyo << ')';
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (scanner, driver));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 44: // "number"
        yylhs.value.emplace< int > ();
        break;

      case 49: // ClassMembers
        yylhs.value.emplace< pair<vector<ptr<MethodDeclaration>>, vector<ptr<VarDeclaration>>> > ();
        break;

      case 65: // BooleanLiteral
        yylhs.value.emplace< ptr<BooleanLiteral> > ();
        break;

      case 47: // MainClassDeclaration
      case 48: // ClassDeclaration
        yylhs.value.emplace< ptr<Class> > ();
        break;

      case 64: // Expression
        yylhs.value.emplace< ptr<Expression> > ();
        break;

      case 63: // Lvalue
        yylhs.value.emplace< ptr<Lvalue> > ();
        break;

      case 50: // MethodDeclaration
        yylhs.value.emplace< ptr<MethodDeclaration> > ();
        break;

      case 61: // MethodInvocation
        yylhs.value.emplace< ptr<MethodInvocation> > ();
        break;

      case 66: // SignedNumber
        yylhs.value.emplace< ptr<Number> > ();
        break;

      case 46: // Program
        yylhs.value.emplace< ptr<Program> > ();
        break;

      case 59: // Scope
        yylhs.value.emplace< ptr<Scope> > ();
        break;

      case 60: // Statement
        yylhs.value.emplace< ptr<Statement> > ();
        break;

      case 54: // Type
      case 55: // SimpleType
      case 56: // ArrayType
        yylhs.value.emplace< ptr<Type> > ();
        break;

      case 51: // VarDeclaration
      case 52: // VarDeclarationStmt
        yylhs.value.emplace< ptr<VarDeclaration> > ();
        break;

      case 43: // "identifier"
      case 57: // TypeId
        yylhs.value.emplace< string > ();
        break;

      case 62: // MethodArgs
        yylhs.value.emplace< vector<ptr<Expression>> > ();
        break;

      case 58: // Statements
        yylhs.value.emplace< vector<ptr<Statement>> > ();
        break;

      case 53: // Formals
        yylhs.value.emplace< vector<ptr<VarDeclaration>> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 125 "/home/user/minijava-compiler/Parser/parser.y"
                              {
  yylhs.value.as < ptr<Program> > () = make_shared<Program>(vector<ptr<Class>>{yystack_[0].value.as < ptr<Class> > ()});
  driver.program = yylhs.value.as < ptr<Program> > ();
}
#line 1103 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 3:
#line 129 "/home/user/minijava-compiler/Parser/parser.y"
                                  {
  yystack_[1].value.as < ptr<Program> > ()->classes.push_back(yystack_[0].value.as < ptr<Class> > ());
  yylhs.value.as < ptr<Program> > () = move(yystack_[1].value.as < ptr<Program> > ());
}
#line 1112 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 4:
#line 135 "/home/user/minijava-compiler/Parser/parser.y"
                                                                                                 {
  yylhs.value.as < ptr<Class> > () = make_shared<Class>(
    yystack_[9].value.as < string > (),
    vector<ptr<MethodDeclaration>>(
      {make_shared<MethodDeclaration>(make_shared<Type>("void"), "main", vector<ptr<VarDeclaration>>(), yystack_[1].value.as < ptr<Scope> > ())}
    ),
    vector<ptr<VarDeclaration>>()
  );
}
#line 1126 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 5:
#line 146 "/home/user/minijava-compiler/Parser/parser.y"
                                                            {
  yylhs.value.as < ptr<Class> > () = make_shared<Class>(yystack_[3].value.as < string > (), move(yystack_[1].value.as < pair<vector<ptr<MethodDeclaration>>, vector<ptr<VarDeclaration>>> > ().first), move(yystack_[1].value.as < pair<vector<ptr<MethodDeclaration>>, vector<ptr<VarDeclaration>>> > ().second));
}
#line 1134 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 6:
#line 149 "/home/user/minijava-compiler/Parser/parser.y"
                                                                                   {
  yylhs.value.as < ptr<Class> > () = make_shared<Class>(yystack_[5].value.as < string > (), yystack_[3].value.as < string > (), move(yystack_[1].value.as < pair<vector<ptr<MethodDeclaration>>, vector<ptr<VarDeclaration>>> > ().first), move(yystack_[1].value.as < pair<vector<ptr<MethodDeclaration>>, vector<ptr<VarDeclaration>>> > ().second));
}
#line 1142 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 7:
#line 154 "/home/user/minijava-compiler/Parser/parser.y"
                     { yylhs.value.as < pair<vector<ptr<MethodDeclaration>>, vector<ptr<VarDeclaration>>> > () = pair<vector<ptr<MethodDeclaration>>, vector<ptr<VarDeclaration>>>(); }
#line 1148 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 8:
#line 155 "/home/user/minijava-compiler/Parser/parser.y"
                                             {
  yystack_[1].value.as < pair<vector<ptr<MethodDeclaration>>, vector<ptr<VarDeclaration>>> > ().first.push_back(yystack_[0].value.as < ptr<MethodDeclaration> > ());  // methods.push
  yylhs.value.as < pair<vector<ptr<MethodDeclaration>>, vector<ptr<VarDeclaration>>> > () = move(yystack_[1].value.as < pair<vector<ptr<MethodDeclaration>>, vector<ptr<VarDeclaration>>> > ());
}
#line 1157 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 9:
#line 159 "/home/user/minijava-compiler/Parser/parser.y"
                                              {
  yystack_[1].value.as < pair<vector<ptr<MethodDeclaration>>, vector<ptr<VarDeclaration>>> > ().second.push_back(yystack_[0].value.as < ptr<VarDeclaration> > ()); // fields.push
  yylhs.value.as < pair<vector<ptr<MethodDeclaration>>, vector<ptr<VarDeclaration>>> > () = move(yystack_[1].value.as < pair<vector<ptr<MethodDeclaration>>, vector<ptr<VarDeclaration>>> > ());
}
#line 1166 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 10:
#line 165 "/home/user/minijava-compiler/Parser/parser.y"
                                                                    {
  yylhs.value.as < ptr<MethodDeclaration> > () = make_shared<MethodDeclaration>(yystack_[5].value.as < ptr<Type> > (), yystack_[4].value.as < string > (), move(yystack_[2].value.as < vector<ptr<VarDeclaration>> > ()), yystack_[0].value.as < ptr<Scope> > ());
}
#line 1174 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 11:
#line 170 "/home/user/minijava-compiler/Parser/parser.y"
                                  { yylhs.value.as < ptr<VarDeclaration> > () = make_shared<VarDeclaration>(yystack_[1].value.as < ptr<Type> > (), yystack_[0].value.as < string > ()); }
#line 1180 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 12:
#line 172 "/home/user/minijava-compiler/Parser/parser.y"
                { yylhs.value.as < vector<ptr<VarDeclaration>> > () = vector<ptr<VarDeclaration>>(); }
#line 1186 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 13:
#line 173 "/home/user/minijava-compiler/Parser/parser.y"
                        { yylhs.value.as < vector<ptr<VarDeclaration>> > () = vector<ptr<VarDeclaration>>{yystack_[0].value.as < ptr<VarDeclaration> > ()}; }
#line 1192 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 14:
#line 174 "/home/user/minijava-compiler/Parser/parser.y"
                                    {
  yystack_[2].value.as < vector<ptr<VarDeclaration>> > ().push_back(yystack_[0].value.as < ptr<VarDeclaration> > ());
  yylhs.value.as < vector<ptr<VarDeclaration>> > () = move(yystack_[2].value.as < vector<ptr<VarDeclaration>> > ());
}
#line 1201 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 15:
#line 180 "/home/user/minijava-compiler/Parser/parser.y"
                 { yylhs.value.as < ptr<Type> > () = yystack_[0].value.as < ptr<Type> > (); }
#line 1207 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 16:
#line 181 "/home/user/minijava-compiler/Parser/parser.y"
                 { yylhs.value.as < ptr<Type> > () = yystack_[0].value.as < ptr<Type> > (); }
#line 1213 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 17:
#line 184 "/home/user/minijava-compiler/Parser/parser.y"
                  { yylhs.value.as < ptr<Type> > () = make_shared<Type>("int", false); }
#line 1219 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 18:
#line 185 "/home/user/minijava-compiler/Parser/parser.y"
                      { yylhs.value.as < ptr<Type> > () = make_shared<Type>("boolean", false); }
#line 1225 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 19:
#line 186 "/home/user/minijava-compiler/Parser/parser.y"
                   { yylhs.value.as < ptr<Type> > () = make_shared<Type>("void", false); }
#line 1231 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 20:
#line 187 "/home/user/minijava-compiler/Parser/parser.y"
                   { yylhs.value.as < ptr<Type> > () = make_shared<Type>(yystack_[0].value.as < string > (), false); }
#line 1237 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 21:
#line 190 "/home/user/minijava-compiler/Parser/parser.y"
                              {
  yystack_[2].value.as < ptr<Type> > ()->is_array = true;
  yylhs.value.as < ptr<Type> > () = yystack_[2].value.as < ptr<Type> > ();
}
#line 1246 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 22:
#line 196 "/home/user/minijava-compiler/Parser/parser.y"
                     { yylhs.value.as < string > () = yystack_[0].value.as < string > (); }
#line 1252 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 23:
#line 199 "/home/user/minijava-compiler/Parser/parser.y"
                   { yylhs.value.as < vector<ptr<Statement>> > () = vector<ptr<Statement>>(); }
#line 1258 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 24:
#line 200 "/home/user/minijava-compiler/Parser/parser.y"
                                 {
  yystack_[1].value.as < vector<ptr<Statement>> > ().push_back(yystack_[0].value.as < ptr<Statement> > ());
  yylhs.value.as < vector<ptr<Statement>> > () = yystack_[1].value.as < vector<ptr<Statement>> > ();
}
#line 1267 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 25:
#line 206 "/home/user/minijava-compiler/Parser/parser.y"
                          { yylhs.value.as < ptr<Scope> > () = make_shared<Scope>(yystack_[1].value.as < vector<ptr<Statement>> > ()); }
#line 1273 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 26:
#line 209 "/home/user/minijava-compiler/Parser/parser.y"
                                           { yylhs.value.as < ptr<Statement> > () = make_shared<Assert>(yystack_[2].value.as < ptr<Expression> > ()); }
#line 1279 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 27:
#line 210 "/home/user/minijava-compiler/Parser/parser.y"
                              { yylhs.value.as < ptr<Statement> > () = yystack_[0].value.as < ptr<VarDeclaration> > (); }
#line 1285 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 28:
#line 211 "/home/user/minijava-compiler/Parser/parser.y"
                 { yylhs.value.as < ptr<Statement> > () = yystack_[0].value.as < ptr<Scope> > (); }
#line 1291 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 29:
#line 212 "/home/user/minijava-compiler/Parser/parser.y"
                                             { yylhs.value.as < ptr<Statement> > () = make_shared<If>(yystack_[2].value.as < ptr<Expression> > (), yystack_[0].value.as < ptr<Statement> > ()); }
#line 1297 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 30:
#line 213 "/home/user/minijava-compiler/Parser/parser.y"
                                                              { yylhs.value.as < ptr<Statement> > () = make_shared<If>(yystack_[4].value.as < ptr<Expression> > (), yystack_[2].value.as < ptr<Statement> > (), yystack_[0].value.as < ptr<Statement> > ()); }
#line 1303 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 31:
#line 214 "/home/user/minijava-compiler/Parser/parser.y"
                                                { yylhs.value.as < ptr<Statement> > () = make_shared<While>(yystack_[2].value.as < ptr<Expression> > (), yystack_[0].value.as < ptr<Statement> > ()); }
#line 1309 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 32:
#line 215 "/home/user/minijava-compiler/Parser/parser.y"
                                                       { yylhs.value.as < ptr<Statement> > () = make_shared<Print>(yystack_[2].value.as < ptr<Expression> > ()); }
#line 1315 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 33:
#line 216 "/home/user/minijava-compiler/Parser/parser.y"
                                     { yylhs.value.as < ptr<Statement> > () = make_shared<Assign>(yystack_[3].value.as < ptr<Lvalue> > (), yystack_[1].value.as < ptr<Expression> > ()); }
#line 1321 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 34:
#line 217 "/home/user/minijava-compiler/Parser/parser.y"
                                   { yylhs.value.as < ptr<Statement> > () = make_shared<Return>(yystack_[1].value.as < ptr<Expression> > ()); }
#line 1327 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 35:
#line 218 "/home/user/minijava-compiler/Parser/parser.y"
                                { yylhs.value.as < ptr<Statement> > () = yystack_[1].value.as < ptr<MethodInvocation> > (); }
#line 1333 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 36:
#line 221 "/home/user/minijava-compiler/Parser/parser.y"
                                       { yylhs.value.as < ptr<VarDeclaration> > () = yystack_[1].value.as < ptr<VarDeclaration> > (); }
#line 1339 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 37:
#line 224 "/home/user/minijava-compiler/Parser/parser.y"
                                                                 { yylhs.value.as < ptr<MethodInvocation> > () = make_shared<MethodInvocation>(yystack_[5].value.as < ptr<Expression> > (), yystack_[3].value.as < string > (), yystack_[1].value.as < vector<ptr<Expression>> > ()); }
#line 1345 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 38:
#line 227 "/home/user/minijava-compiler/Parser/parser.y"
                   { yylhs.value.as < vector<ptr<Expression>> > () = vector<ptr<Expression>>(); }
#line 1351 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 39:
#line 228 "/home/user/minijava-compiler/Parser/parser.y"
                       { yylhs.value.as < vector<ptr<Expression>> > ().push_back(yystack_[0].value.as < ptr<Expression> > ()); }
#line 1357 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 40:
#line 229 "/home/user/minijava-compiler/Parser/parser.y"
                                      {
  yystack_[2].value.as < vector<ptr<Expression>> > ().push_back(yystack_[0].value.as < ptr<Expression> > ());
  yylhs.value.as < vector<ptr<Expression>> > () = move(yystack_[2].value.as < vector<ptr<Expression>> > ());
}
#line 1366 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 41:
#line 235 "/home/user/minijava-compiler/Parser/parser.y"
                     { yylhs.value.as < ptr<Lvalue> > () = make_shared<Lvalue>(yystack_[0].value.as < string > ()); }
#line 1372 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 42:
#line 236 "/home/user/minijava-compiler/Parser/parser.y"
                                        { yylhs.value.as < ptr<Lvalue> > () = make_shared<Lvalue>(yystack_[3].value.as < string > (), yystack_[1].value.as < ptr<Expression> > ()); }
#line 1378 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 43:
#line 239 "/home/user/minijava-compiler/Parser/parser.y"
                   { yylhs.value.as < ptr<Expression> > () = make_shared<This>(); }
#line 1384 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 44:
#line 240 "/home/user/minijava-compiler/Parser/parser.y"
                             { yylhs.value.as < ptr<Expression> > () = yystack_[0].value.as < ptr<MethodInvocation> > (); }
#line 1390 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 45:
#line 241 "/home/user/minijava-compiler/Parser/parser.y"
                                       { yylhs.value.as < ptr<Expression> > () = make_shared<Mul>(yystack_[2].value.as < ptr<Expression> > (), yystack_[0].value.as < ptr<Expression> > ()); }
#line 1396 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 46:
#line 242 "/home/user/minijava-compiler/Parser/parser.y"
                                       { yylhs.value.as < ptr<Expression> > () = make_shared<Add>(yystack_[2].value.as < ptr<Expression> > (), yystack_[0].value.as < ptr<Expression> > ()); }
#line 1402 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 47:
#line 243 "/home/user/minijava-compiler/Parser/parser.y"
                                       { yylhs.value.as < ptr<Expression> > () = make_shared<Less>(yystack_[2].value.as < ptr<Expression> > (), yystack_[0].value.as < ptr<Expression> > ()); }
#line 1408 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 48:
#line 244 "/home/user/minijava-compiler/Parser/parser.y"
                                       { yylhs.value.as < ptr<Expression> > () = make_shared<More>(yystack_[2].value.as < ptr<Expression> > (), yystack_[0].value.as < ptr<Expression> > ()); }
#line 1414 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 49:
#line 245 "/home/user/minijava-compiler/Parser/parser.y"
                                       { yylhs.value.as < ptr<Expression> > () = make_shared<Equals>(yystack_[2].value.as < ptr<Expression> > (), yystack_[0].value.as < ptr<Expression> > ()); }
#line 1420 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 50:
#line 246 "/home/user/minijava-compiler/Parser/parser.y"
                                       { yylhs.value.as < ptr<Expression> > () = make_shared<Add>(yystack_[2].value.as < ptr<Expression> > (), yystack_[0].value.as < ptr<Expression> > ()); }
#line 1426 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 51:
#line 247 "/home/user/minijava-compiler/Parser/parser.y"
                                       { yylhs.value.as < ptr<Expression> > () = make_shared<Subtract>(yystack_[2].value.as < ptr<Expression> > (), yystack_[0].value.as < ptr<Expression> > ()); }
#line 1432 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 52:
#line 248 "/home/user/minijava-compiler/Parser/parser.y"
                                       { yylhs.value.as < ptr<Expression> > () = make_shared<Mul>(yystack_[2].value.as < ptr<Expression> > (), yystack_[0].value.as < ptr<Expression> > ()); }
#line 1438 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 53:
#line 249 "/home/user/minijava-compiler/Parser/parser.y"
                                       { yylhs.value.as < ptr<Expression> > () = make_shared<Div>(yystack_[2].value.as < ptr<Expression> > (), yystack_[0].value.as < ptr<Expression> > ()); }
#line 1444 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 54:
#line 250 "/home/user/minijava-compiler/Parser/parser.y"
                                       { yylhs.value.as < ptr<Expression> > () = make_shared<Percent>(yystack_[2].value.as < ptr<Expression> > (), yystack_[0].value.as < ptr<Expression> > ()); }
#line 1450 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 55:
#line 251 "/home/user/minijava-compiler/Parser/parser.y"
                                          { yylhs.value.as < ptr<Expression> > () = make_shared<At>(yystack_[3].value.as < ptr<Expression> > (), yystack_[1].value.as < ptr<Expression> > ()); }
#line 1456 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 56:
#line 252 "/home/user/minijava-compiler/Parser/parser.y"
                                    { yylhs.value.as < ptr<Expression> > () = make_shared<Length>(yystack_[2].value.as < ptr<Expression> > ()); }
#line 1462 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 57:
#line 253 "/home/user/minijava-compiler/Parser/parser.y"
                                                { yylhs.value.as < ptr<Expression> > () = make_shared<NewArray>(yystack_[3].value.as < ptr<Type> > (), yystack_[1].value.as < ptr<Expression> > ()); yylhs.value.as < ptr<Expression> > ()->type->is_array = true; }
#line 1468 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 58:
#line 254 "/home/user/minijava-compiler/Parser/parser.y"
                                 { yylhs.value.as < ptr<Expression> > () = make_shared<New>(yystack_[2].value.as < string > ()); }
#line 1474 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 59:
#line 255 "/home/user/minijava-compiler/Parser/parser.y"
                           { yylhs.value.as < ptr<Expression> > () = make_shared<Not>(yystack_[0].value.as < ptr<Expression> > ()); }
#line 1480 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 60:
#line 256 "/home/user/minijava-compiler/Parser/parser.y"
                               { yylhs.value.as < ptr<Expression> > () = yystack_[1].value.as < ptr<Expression> > (); }
#line 1486 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 61:
#line 257 "/home/user/minijava-compiler/Parser/parser.y"
                         { yylhs.value.as < ptr<Expression> > () = make_shared<Identifier>(yystack_[0].value.as < string > ()); }
#line 1492 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 62:
#line 258 "/home/user/minijava-compiler/Parser/parser.y"
                         { yylhs.value.as < ptr<Expression> > () = yystack_[0].value.as < ptr<Number> > (); }
#line 1498 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 63:
#line 259 "/home/user/minijava-compiler/Parser/parser.y"
                           { yylhs.value.as < ptr<Expression> > () = yystack_[0].value.as < ptr<BooleanLiteral> > (); }
#line 1504 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 64:
#line 262 "/home/user/minijava-compiler/Parser/parser.y"
                       { yylhs.value.as < ptr<BooleanLiteral> > () = make_shared<BooleanLiteral>(true); }
#line 1510 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 65:
#line 263 "/home/user/minijava-compiler/Parser/parser.y"
                        { yylhs.value.as < ptr<BooleanLiteral> > () = make_shared<BooleanLiteral>(false); }
#line 1516 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 66:
#line 266 "/home/user/minijava-compiler/Parser/parser.y"
                           { yylhs.value.as < ptr<Number> > () = make_shared<Number>(yystack_[0].value.as < int > ()); }
#line 1522 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;

  case 67:
#line 267 "/home/user/minijava-compiler/Parser/parser.y"
                           { yylhs.value.as < ptr<Number> > () = make_shared<Number>(-yystack_[0].value.as < int > ()); }
#line 1528 "/home/user/minijava-compiler/Parser/parser.cpp"
    break;


#line 1532 "/home/user/minijava-compiler/Parser/parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -118;

  const signed char parser::yytable_ninf_ = -42;

  const short
  parser::yypact_[] =
  {
      15,   -20,     9,  -118,    21,  -118,    11,  -118,    49,    47,
      58,    20,  -118,    66,    64,    13,    71,  -118,    -5,  -118,
    -118,  -118,  -118,  -118,  -118,    68,  -118,    43,    67,  -118,
    -118,    48,    45,    51,  -118,  -118,    79,    52,  -118,    65,
    -118,    76,    -5,  -118,    89,  -118,   -12,    56,  -118,    -5,
      76,    -5,   118,    69,    70,  -118,  -118,    75,    77,   118,
      63,   118,  -118,  -118,   -19,  -118,  -118,  -118,  -118,   105,
      97,   303,  -118,  -118,  -118,  -118,    92,    85,  -118,  -118,
     135,   118,   118,   118,   118,    95,  -118,   173,   118,  -118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   -16,   118,    90,  -118,   189,   205,   221,   237,
    -118,   255,   157,   271,   309,   309,   309,   309,   309,    91,
      91,    95,    95,    95,  -118,    96,   287,  -118,    98,    98,
     117,   119,  -118,  -118,  -118,   118,  -118,   127,  -118,  -118,
    -118,    33,   303,    98,   118,  -118,  -118,   303
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     2,     0,     1,     0,     3,     0,     0,
       0,     0,     7,     0,     0,     0,     0,     7,     0,    19,
       5,    17,    18,    22,     8,     0,     9,     0,    15,    16,
      20,     0,     0,     0,    36,    11,     0,     0,     6,     0,
      21,     0,    12,    23,     0,    13,     0,     0,     4,     0,
       0,     0,     0,     0,     0,    43,    25,     0,     0,     0,
       0,     0,    64,    65,    61,    66,    27,    28,    24,    44,
       0,     0,    63,    62,    14,    10,     0,    20,    61,    44,
       0,     0,     0,     0,     0,    59,    67,     0,     0,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,     0,     0,     0,     0,
      60,     0,     0,     0,    45,    46,    47,    48,    49,    51,
      50,    52,    53,    54,    56,     0,     0,    58,     0,     0,
       0,     0,    42,    33,    55,    38,    57,    29,    31,    32,
      26,     0,    39,     0,     0,    37,    30,    40
  };

  const short
  parser::yypgoto_[] =
  {
    -118,  -118,  -118,  -118,   126,  -118,   -24,   -10,  -118,   128,
      93,  -118,    99,  -118,   -35,  -117,   -47,  -118,  -118,   -51,
    -118,  -118
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     2,     3,     7,    15,    24,    25,    66,    46,    27,
      28,    29,    30,    47,    67,    68,    79,   141,    70,    71,
      72,    73
  };

  const short
  parser::yytable_[] =
  {
      69,    80,   124,    19,    88,    26,    44,   -41,    85,     5,
      87,   137,   138,    49,     6,    75,    21,    22,    45,    18,
       1,    19,    26,     4,   -22,    74,   146,   125,    50,    20,
     106,   107,   108,   109,    21,    22,     8,   111,    23,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,    18,   126,    19,     9,    10,    23,    11,   144,    51,
      52,    38,    12,    14,    19,    13,    21,    22,    53,    54,
      55,    43,    56,   145,    16,    57,    58,    21,    22,    17,
      31,    69,    69,    59,   142,    34,    35,    37,    23,    60,
      36,    43,    41,   147,    39,    61,    69,    62,    63,    64,
      65,    51,    52,    40,    42,    48,    19,    86,    81,    82,
      53,    54,    55,    43,    83,   103,    84,    57,    58,    21,
      22,    51,    89,    90,   104,    59,    99,   100,   101,   102,
     127,    60,    55,   102,   139,   135,   140,    61,   143,    62,
      63,    64,    65,    32,    76,    59,    33,     0,     0,     0,
      77,    60,   105,     0,     0,     0,     0,    61,    91,    62,
      63,    78,    65,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   133,     0,     0,     0,     0,     0,
      91,     0,     0,     0,     0,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,    91,     0,     0,     0,
       0,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,    91,   110,     0,     0,     0,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,    91,   128,
       0,     0,     0,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,    91,   129,     0,     0,     0,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
      91,   130,     0,     0,     0,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,     0,   131,    91,   132,
       0,     0,     0,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,    91,   134,     0,     0,     0,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
      91,   136,     0,     0,     0,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,    91,     0,     0,     0,
       0,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,    97,    98,    99,   100,   101,   102
  };

  const short
  parser::yycheck_[] =
  {
      47,    52,    18,     8,    23,    15,    41,    26,    59,     0,
      61,   128,   129,    25,     5,    50,    21,    22,    42,     6,
       5,     8,    32,    43,    43,    49,   143,    43,    40,    16,
      81,    82,    83,    84,    21,    22,    15,    88,    43,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,     6,   103,     8,    43,     6,    43,    10,    25,     3,
       4,    16,    15,    43,     8,     7,    21,    22,    12,    13,
      14,    15,    16,    40,     8,    19,    20,    21,    22,    15,
       9,   128,   129,    27,   135,    17,    43,    39,    43,    33,
      23,    15,    40,   144,    43,    39,   143,    41,    42,    43,
      44,     3,     4,    24,    39,    16,     8,    44,    39,    39,
      12,    13,    14,    15,    39,    23,    39,    19,    20,    21,
      22,     3,    17,    26,    39,    27,    35,    36,    37,    38,
      40,    33,    14,    38,    17,    39,    17,    39,    11,    41,
      42,    43,    44,    17,    51,    27,    18,    -1,    -1,    -1,
      51,    33,    17,    -1,    -1,    -1,    -1,    39,    23,    41,
      42,    43,    44,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    17,    -1,    -1,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    23,    -1,    -1,    -1,
      -1,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    23,    40,    -1,    -1,    -1,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    23,    40,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    23,    40,    -1,    -1,    -1,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      23,    40,    -1,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    40,    23,    24,
      -1,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    23,    24,    -1,    -1,    -1,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      23,    24,    -1,    -1,    -1,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    23,    -1,    -1,    -1,
      -1,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    33,    34,    35,    36,    37,    38
  };

  const signed char
  parser::yystos_[] =
  {
       0,     5,    46,    47,    43,     0,     5,    48,    15,    43,
       6,    10,    15,     7,    43,    49,     8,    15,     6,     8,
      16,    21,    22,    43,    50,    51,    52,    54,    55,    56,
      57,     9,    49,    54,    17,    43,    23,    39,    16,    43,
      24,    40,    39,    15,    59,    51,    53,    58,    16,    25,
      40,     3,     4,    12,    13,    14,    16,    19,    20,    27,
      33,    39,    41,    42,    43,    44,    52,    59,    60,    61,
      63,    64,    65,    66,    51,    59,    55,    57,    43,    61,
      64,    39,    39,    39,    39,    64,    44,    64,    23,    17,
      26,    23,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    23,    39,    17,    64,    64,    64,    64,
      40,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    18,    43,    64,    40,    40,    40,
      40,    40,    24,    17,    24,    39,    24,    60,    60,    17,
      17,    62,    64,    11,    25,    40,    60,    64
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    45,    46,    46,    47,    48,    48,    49,    49,    49,
      50,    51,    53,    53,    53,    54,    54,    55,    55,    55,
      55,    56,    57,    58,    58,    59,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    52,    61,    62,    62,
      62,    63,    63,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    65,    65,    66,    66
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,    11,     5,     7,     0,     2,     2,
       7,     2,     0,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     1,     0,     2,     3,     5,     1,     1,     5,
       7,     5,     5,     4,     3,     2,     2,     6,     0,     1,
       3,     1,     4,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     3,     5,     4,     2,
       3,     1,     1,     1,     1,     1,     1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"new\"", "\"return\"",
  "\"class\"", "\"public\"", "\"static\"", "\"void\"", "\"main\"",
  "\"extends\"", "\"else\"", "\"if\"", "\"while\"", "\"this\"", "\"{\"",
  "\"}\"", "\";\"", "\"length\"", "\"System.out.println\"", "\"assert\"",
  "\"int\"", "\"boolean\"", "\"[\"", "\"]\"", "\",\"", "\"=\"", "\"!\"",
  "\"&&\"", "\"||\"", "\"<\"", "\">\"", "\"==\"", "\"-\"", "\"+\"",
  "\"*\"", "\"/\"", "\"%\"", "\".\"", "\"(\"", "\")\"", "\"true\"",
  "\"false\"", "\"identifier\"", "\"number\"", "$accept", "Program",
  "MainClassDeclaration", "ClassDeclaration", "ClassMembers",
  "MethodDeclaration", "VarDeclaration", "VarDeclarationStmt", "Formals",
  "Type", "SimpleType", "ArrayType", "TypeId", "Statements", "Scope",
  "Statement", "MethodInvocation", "MethodArgs", "Lvalue", "Expression",
  "BooleanLiteral", "SignedNumber", YY_NULLPTR
  };

#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   125,   125,   129,   135,   146,   149,   154,   155,   159,
     165,   170,   172,   173,   174,   180,   181,   184,   185,   186,
     187,   190,   196,   199,   200,   206,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   221,   224,   227,   228,
     229,   235,   236,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   262,   263,   266,   267
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 2053 "/home/user/minijava-compiler/Parser/parser.cpp"

#line 270 "/home/user/minijava-compiler/Parser/parser.y"


void
yy::parser::error(const location_type& l, const string& m)
{
  cerr << l << ": " << m << '\n';
}
