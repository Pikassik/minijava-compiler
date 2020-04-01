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
#line 18 "parser.y"

    #include "driver.hh"
    #include "location.hh"

    static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
        return scanner.ScanToken();
    }

#line 54 "/home/user/naive-minijava-interpreter/parser.cpp"


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
#line 145 "/home/user/naive-minijava-interpreter/parser.cpp"


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
      case 37: // "number"
      case 39: // SignedNumber
      case 40: // Expression
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 36: // "identifier"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
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
      case 37: // "number"
      case 39: // SignedNumber
      case 40: // Expression
        value.move< int > (YY_MOVE (that.value));
        break;

      case 36: // "identifier"
        value.move< std::string > (YY_MOVE (that.value));
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
      case 37: // "number"
      case 39: // SignedNumber
      case 40: // Expression
        value.copy< int > (that.value);
        break;

      case 36: // "identifier"
        value.copy< std::string > (that.value);
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
      case 37: // "number"
      case 39: // SignedNumber
      case 40: // Expression
        value.move< int > (that.value);
        break;

      case 36: // "identifier"
        value.move< std::string > (that.value);
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
    YYUSE (yytype);
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
      case 37: // "number"
      case 39: // SignedNumber
      case 40: // Expression
        yylhs.value.emplace< int > ();
        break;

      case 36: // "identifier"
        yylhs.value.emplace< std::string > ();
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
#line 87 "parser.y"
                              {}
#line 623 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 3:
#line 90 "parser.y"
                                                                                                 {/* pass */}
#line 629 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 4:
#line 93 "parser.y"
                      {/* pass */}
#line 635 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 5:
#line 94 "parser.y"
                      {/* pass */}
#line 641 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 6:
#line 97 "parser.y"
                                 {/* pass */}
#line 647 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 7:
#line 98 "parser.y"
                                 {/* pass */}
#line 653 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 8:
#line 101 "parser.y"
                          {/* pass */}
#line 659 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 9:
#line 104 "parser.y"
                                           { assert(yystack_[2].value.as < int > () != 0); }
#line 665 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 10:
#line 105 "parser.y"
                               {/* pass */}
#line 671 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 11:
#line 106 "parser.y"
                 {/* pass */}
#line 677 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 12:
#line 107 "parser.y"
                                                       { std::cout << yystack_[2].value.as < int > () << std::endl; }
#line 683 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 13:
#line 108 "parser.y"
                                           { driver.variables.at(yystack_[3].value.as < std::string > ()) = yystack_[1].value.as < int > (); }
#line 689 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 14:
#line 109 "parser.y"
                                                              { driver.arrays.at(yystack_[6].value.as < std::string > ()).at(yystack_[4].value.as < int > ()) = yystack_[1].value.as < int > (); }
#line 695 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 15:
#line 110 "parser.y"
                                                                    { driver.arrays.at(yystack_[7].value.as < std::string > ()).resize(yystack_[2].value.as < int > ()); }
#line 701 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 16:
#line 113 "parser.y"
                                                  {
  if (driver.variables.find(yystack_[1].value.as < std::string > ()) != driver.variables.end()) {
    std::cerr << "redefenition of variable: " << yystack_[1].value.as < std::string > () << std::endl;
    throw;
  }

  driver.variables[yystack_[1].value.as < std::string > ()] = 0;
}
#line 714 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 17:
#line 122 "parser.y"
                                                         {
  if (driver.arrays.find(yystack_[1].value.as < std::string > ()) != driver.arrays.end()) {
    std::cerr << "redefenition of array variable: " << yystack_[1].value.as < std::string > () << std::endl;
    throw;
  }

  driver.arrays[yystack_[1].value.as < std::string > ()] = std::vector<int>();
}
#line 727 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 18:
#line 135 "parser.y"
                                            { yylhs.value.as < int > () = yystack_[2].value.as < int > () && yystack_[0].value.as < int > (); }
#line 733 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 19:
#line 136 "parser.y"
                                            { yylhs.value.as < int > () = yystack_[2].value.as < int > () || yystack_[0].value.as < int > (); }
#line 739 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 20:
#line 137 "parser.y"
                                            { yylhs.value.as < int > () = yystack_[2].value.as < int > () <  yystack_[0].value.as < int > (); }
#line 745 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 21:
#line 138 "parser.y"
                                            { yylhs.value.as < int > () = yystack_[2].value.as < int > () >  yystack_[0].value.as < int > (); }
#line 751 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 22:
#line 139 "parser.y"
                                            { yylhs.value.as < int > () = yystack_[2].value.as < int > () == yystack_[0].value.as < int > (); }
#line 757 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 23:
#line 140 "parser.y"
                                            { yylhs.value.as < int > () = yystack_[2].value.as < int > () +  yystack_[0].value.as < int > (); }
#line 763 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 24:
#line 141 "parser.y"
                                            { yylhs.value.as < int > () = yystack_[2].value.as < int > () -  yystack_[0].value.as < int > (); }
#line 769 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 25:
#line 142 "parser.y"
                                            { yylhs.value.as < int > () = yystack_[2].value.as < int > () *  yystack_[0].value.as < int > (); }
#line 775 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 26:
#line 143 "parser.y"
                                            { yylhs.value.as < int > () = yystack_[2].value.as < int > () /  yystack_[0].value.as < int > (); }
#line 781 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 27:
#line 144 "parser.y"
                                            { yylhs.value.as < int > () = yystack_[2].value.as < int > () %  yystack_[0].value.as < int > (); }
#line 787 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 28:
#line 145 "parser.y"
                                            { yylhs.value.as < int > () = driver.arrays.at(yystack_[3].value.as < std::string > ()).at(yystack_[1].value.as < int > ()); }
#line 793 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 29:
#line 146 "parser.y"
                                            { yylhs.value.as < int > () = driver.arrays.at(yystack_[2].value.as < std::string > ()).size(); }
#line 799 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 30:
#line 147 "parser.y"
                                            { yylhs.value.as < int > () = !yystack_[0].value.as < int > (); }
#line 805 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 31:
#line 148 "parser.y"
                                            { yylhs.value.as < int > () = yystack_[1].value.as < int > (); }
#line 811 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 32:
#line 149 "parser.y"
                                            { yylhs.value.as < int > () = driver.variables.at(yystack_[0].value.as < std::string > ()); }
#line 817 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 33:
#line 150 "parser.y"
                                            { yylhs.value.as < int > () = yystack_[0].value.as < int > (); }
#line 823 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 34:
#line 153 "parser.y"
                           { yylhs.value.as < int > () = 1; }
#line 829 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 35:
#line 154 "parser.y"
                           { yylhs.value.as < int > () = 0; }
#line 835 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 36:
#line 155 "parser.y"
                           { yylhs.value.as < int > () = yystack_[0].value.as < int > (); }
#line 841 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;

  case 37:
#line 156 "parser.y"
                           { yylhs.value.as < int > () = -yystack_[0].value.as < int > (); }
#line 847 "/home/user/naive-minijava-interpreter/parser.cpp"
    break;


#line 851 "/home/user/naive-minijava-interpreter/parser.cpp"

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


  const signed char parser::yypact_ninf_ = -33;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
       4,   -32,    17,   -33,    31,   -33,    19,    47,    48,    46,
      38,    36,    62,   -33,    63,     0,   -33,   -33,    40,    42,
     -33,   -33,     2,   -14,   -33,   -33,   -33,    68,    68,    68,
      15,    58,    64,    68,    52,    68,   -33,   -33,   -11,   -33,
     -33,    85,    98,   111,    -4,    37,    41,   -33,   -33,   -33,
     121,    68,    78,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    80,    81,    74,    79,   -33,    84,   -33,
     134,   -33,    16,    16,    16,    16,    16,     9,     9,   -33,
     -33,   -33,   -33,   -33,    68,    68,   -33,   -33,    57,   147,
     -33,    86,   -33
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     2,     0,     1,     0,     0,     0,     0,
       0,     0,     0,     6,     0,     0,     3,     8,     0,     0,
       4,     5,     0,     0,    11,     7,    10,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,    35,    32,    36,
      33,     0,     0,     0,     0,     0,     0,    16,    30,    37,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    13,     0,    31,
       0,    29,    18,    19,    20,    21,    22,    24,    23,    25,
      26,    27,    12,     9,     0,     0,    17,    28,     0,     0,
      14,     0,    15
  };

  const signed char
  parser::yypgoto_[] =
  {
     -33,   -33,   -28,   -33,   -33,    54,   -33,   101,   -33,   -33
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,    40,    41,     2,     3,    23,    15,    14,    25,    26
  };

  const signed char
  parser::yytable_[] =
  {
      42,    43,    45,    31,     4,    48,    51,    50,     1,    13,
      17,    20,    21,    18,    19,    20,    21,     5,    44,    29,
      52,    30,    32,    70,     7,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    33,    22,    60,    61,    62,
       6,    34,    58,    59,    60,    61,    62,    35,    67,    36,
      37,    38,    39,     8,    10,     9,    88,    89,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    90,    12,
      11,    13,    27,    16,    28,    47,    46,    68,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    33,    49,
      71,    82,    83,    84,    34,    86,    85,    92,    66,     0,
      35,     0,    36,    37,    38,    39,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    24,     0,    63,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    65,
       0,    64,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    87,     0,    69,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    91,     0,     0,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62
  };

  const signed char
  parser::yycheck_[] =
  {
      28,    29,    30,    17,    36,    33,    17,    35,     4,     9,
      10,    15,    16,    13,    14,    15,    16,     0,     3,    17,
      31,    19,    36,    51,     5,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    20,    36,    28,    29,    30,
       9,    26,    26,    27,    28,    29,    30,    32,    11,    34,
      35,    36,    37,     6,     8,     7,    84,    85,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    11,    33,
      32,     9,    32,    10,    32,    11,    18,    36,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    20,    37,
      12,    11,    11,    19,    26,    11,    17,    11,    44,    -1,
      32,    -1,    34,    35,    36,    37,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    15,    -1,    33,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    18,
      -1,    33,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    18,    -1,    33,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    18,    -1,    -1,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30
  };

  const signed char
  parser::yystos_[] =
  {
       0,     4,    41,    42,    36,     0,     9,     5,     6,     7,
       8,    32,    33,     9,    45,    44,    10,    10,    13,    14,
      15,    16,    36,    43,    45,    46,    47,    32,    32,    17,
      19,    17,    36,    20,    26,    32,    34,    35,    36,    37,
      39,    40,    40,    40,     3,    40,    18,    11,    40,    37,
      40,    17,    31,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    33,    33,    18,    43,    11,    36,    33,
      40,    12,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    11,    11,    19,    17,    11,    18,    40,    40,
      11,    18,    11
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    38,    41,    42,    43,    43,    44,    44,    45,    46,
      46,    46,    46,    46,    46,    46,    47,    47,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    39,    39,    39,    39
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,    11,     1,     1,     0,     2,     3,     5,
       1,     1,     5,     4,     7,     8,     3,     5,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     4,     3,
       2,     3,     1,     1,     1,     1,     1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"new\"", "\"class\"",
  "\"public\"", "\"static\"", "\"void\"", "\"main\"", "\"{\"", "\"}\"",
  "\";\"", "\"length\"", "\"System.out.println\"", "\"assert\"", "\"int\"",
  "\"boolean\"", "\"[\"", "\"]\"", "\"=\"", "\"!\"", "\"&&\"", "\"||\"",
  "\"<\"", "\">\"", "\"==\"", "\"-\"", "\"+\"", "\"*\"", "\"/\"", "\"%\"",
  "\".\"", "\"(\"", "\")\"", "\"true\"", "\"false\"", "\"identifier\"",
  "\"number\"", "$accept", "SignedNumber", "Expression", "Program",
  "MainClassDeclaration", "SimpleType", "Statements", "Scope", "Statement",
  "LocalVarDeclaration", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,    87,    87,    90,    93,    94,    97,    98,   101,   104,
     105,   106,   107,   108,   109,   110,   113,   122,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   153,   154,   155,   156
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
#line 1306 "/home/user/naive-minijava-interpreter/parser.cpp"

#line 158 "parser.y"


void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
