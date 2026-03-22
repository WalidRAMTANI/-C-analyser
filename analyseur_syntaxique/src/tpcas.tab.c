/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/tpcas.y"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "compiler.h"
int yylex();
extern int yylineno;
int yyerror(char *msg) {
    fprintf(stderr, "%d: %s\n", yylineno, msg);
    return 1;
}
    extern FILE *yyin;
Node *ptr = NULL;

#line 86 "src/tpcas.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "tpcas.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TYPE = 3,                       /* TYPE  */
  YYSYMBOL_IDENT = 4,                      /* IDENT  */
  YYSYMBOL_VOID = 5,                       /* VOID  */
  YYSYMBOL_NUM = 6,                        /* NUM  */
  YYSYMBOL_CHARACTER = 7,                  /* CHARACTER  */
  YYSYMBOL_STRUCT = 8,                     /* STRUCT  */
  YYSYMBOL_WHILE = 9,                      /* WHILE  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_ELSE = 11,                      /* ELSE  */
  YYSYMBOL_RETURN = 12,                    /* RETURN  */
  YYSYMBOL_ORDER = 13,                     /* ORDER  */
  YYSYMBOL_ADDSUB = 14,                    /* ADDSUB  */
  YYSYMBOL_EQ = 15,                        /* EQ  */
  YYSYMBOL_DIVSTAR = 16,                   /* DIVSTAR  */
  YYSYMBOL_AND = 17,                       /* AND  */
  YYSYMBOL_OR = 18,                        /* OR  */
  YYSYMBOL_DOT = 19,                       /* DOT  */
  YYSYMBOL_20_ = 20,                       /* ';'  */
  YYSYMBOL_21_ = 21,                       /* '{'  */
  YYSYMBOL_22_ = 22,                       /* '}'  */
  YYSYMBOL_23_ = 23,                       /* ','  */
  YYSYMBOL_24_ = 24,                       /* '('  */
  YYSYMBOL_25_ = 25,                       /* ')'  */
  YYSYMBOL_26_ = 26,                       /* '='  */
  YYSYMBOL_27_ = 27,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 28,                  /* $accept  */
  YYSYMBOL_Prog = 29,                      /* Prog  */
  YYSYMBOL_DeclVars = 30,                  /* DeclVars  */
  YYSYMBOL_DeclarateursStruct = 31,        /* DeclarateursStruct  */
  YYSYMBOL_Declarateurs = 32,              /* Declarateurs  */
  YYSYMBOL_DeclFoncts = 33,                /* DeclFoncts  */
  YYSYMBOL_DeclFonct = 34,                 /* DeclFonct  */
  YYSYMBOL_EnTeteFonct = 35,               /* EnTeteFonct  */
  YYSYMBOL_Parametres = 36,                /* Parametres  */
  YYSYMBOL_ListTypVar = 37,                /* ListTypVar  */
  YYSYMBOL_Corps = 38,                     /* Corps  */
  YYSYMBOL_SuiteInstr = 39,                /* SuiteInstr  */
  YYSYMBOL_LValue = 40,                    /* LValue  */
  YYSYMBOL_Value = 41,                     /* Value  */
  YYSYMBOL_Instr = 42,                     /* Instr  */
  YYSYMBOL_Exp = 43,                       /* Exp  */
  YYSYMBOL_TB = 44,                        /* TB  */
  YYSYMBOL_FB = 45,                        /* FB  */
  YYSYMBOL_M = 46,                         /* M  */
  YYSYMBOL_E = 47,                         /* E  */
  YYSYMBOL_T = 48,                         /* T  */
  YYSYMBOL_F = 49,                         /* F  */
  YYSYMBOL_Arguments = 50,                 /* Arguments  */
  YYSYMBOL_ListExp = 51                    /* ListExp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   159

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  28
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  140

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   274


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    27,     2,     2,     2,     2,     2,     2,
      24,    25,     2,     2,    23,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    20,
       2,    26,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    21,     2,    22,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    30,    30,    39,    46,    54,    62,    66,    73,    81,
      85,    89,    95,    96,   100,   108,   114,   120,   130,   131,
     132,   136,   141,   147,   153,   163,   171,   172,   177,   182,
     188,   193,   197,   202,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   219,   220,   224,   225,   229,   230,   234,
     235,   239,   240,   244,   245,   249,   250,   251,   252,   253,
     254,   255,   260,   261,   265,   266
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TYPE", "IDENT",
  "VOID", "NUM", "CHARACTER", "STRUCT", "WHILE", "IF", "ELSE", "RETURN",
  "ORDER", "ADDSUB", "EQ", "DIVSTAR", "AND", "OR", "DOT", "';'", "'{'",
  "'}'", "','", "'('", "')'", "'='", "'!'", "$accept", "Prog", "DeclVars",
  "DeclarateursStruct", "Declarateurs", "DeclFoncts", "DeclFonct",
  "EnTeteFonct", "Parametres", "ListTypVar", "Corps", "SuiteInstr",
  "LValue", "Value", "Instr", "Exp", "TB", "FB", "M", "E", "T", "F",
  "Arguments", "ListExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-79)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-34)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -79,     3,    81,   -79,    11,    15,    17,    87,   -79,     4,
      25,    68,    34,     7,    30,    74,   -79,   -79,   -79,    95,
     -79,    75,    95,    92,   -79,    85,    25,   107,    63,   110,
     -79,   114,    62,    98,   -79,    94,    95,    24,   -79,    92,
     116,   118,    31,   -79,   119,   -79,    96,   -79,    99,   116,
     121,   106,   -79,    10,    82,   103,   104,     2,   -79,   -79,
     -79,     6,   105,   111,   -79,   -79,   125,   128,   -79,    89,
     116,   -79,     6,     6,     6,    83,   -79,   -79,     6,   -79,
       6,     6,   -79,    49,   117,   120,   123,   124,   126,   -79,
      52,    29,     6,   129,   -79,   133,   -79,    90,   122,   127,
     130,    32,    45,     6,   -79,    50,   -79,     6,   -79,     6,
       6,     6,     6,     6,   -79,   -79,    97,   131,   -79,   -79,
     134,     6,    73,    73,   132,   136,   117,   120,   123,   124,
     126,   -79,   -79,   -79,   122,   -79,   135,   137,    73,   -79
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       6,     0,     0,     1,     0,     0,     0,     2,    13,     0,
      11,     0,     0,     0,     0,     0,    12,     6,    14,    20,
       3,     0,    20,    11,     9,     0,     0,     0,    27,     0,
      18,     0,     0,    19,    10,     0,    20,     0,     4,     0,
       0,     0,     0,    23,     0,    15,     0,    16,     0,     0,
       0,     0,    11,     0,    29,     0,     0,     0,    42,    27,
      25,     0,     0,     0,    26,    24,     0,     0,    17,     0,
       0,     5,    63,     0,     0,    29,    58,    59,     0,    40,
       0,     0,    61,     0,    44,    46,    48,    50,    52,    54,
       0,     0,     0,     0,    21,     0,     7,     0,    64,     0,
      62,     0,     0,    63,    55,     0,    56,     0,    39,     0,
       0,     0,     0,     0,    41,    31,     0,    28,    22,     8,
      30,     0,     0,     0,     0,    57,    43,    45,    47,    49,
      51,    53,    34,    38,    65,    37,    35,    60,     0,    36
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -79,   -79,   141,   -79,   -11,   -79,   138,   -79,     1,   -79,
     -79,    80,   -42,   -79,   -78,   -56,    36,    35,    37,    38,
      39,   -74,    56,   -79
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    37,    11,     7,     8,     9,    32,    33,
      18,    42,    82,    63,    64,    98,    84,    85,    86,    87,
      88,    89,    99,   100
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      62,    83,    25,     3,   104,    91,    75,   106,    76,    77,
      75,    23,    76,    77,    52,    10,    78,   101,   102,    12,
      78,    13,    79,    35,   105,    17,    80,    49,    24,    81,
      80,    24,    50,    81,    26,    54,   116,    48,    69,   131,
      55,    56,    25,    57,   135,   136,    51,   107,    62,    19,
     107,    58,    59,    60,   115,    61,    54,   122,    22,    97,
     139,    55,    56,   107,    57,   134,    40,   107,   107,   108,
     123,    41,    58,    59,   114,   125,    61,    54,    27,    34,
      62,    62,    55,    56,     4,    57,     5,    45,    20,     6,
      14,    21,     5,    58,    59,    15,    62,    61,    29,    66,
      30,   -33,   -33,    31,    67,    38,    72,   103,    21,    96,
     119,    39,    21,    21,    43,   107,    36,   132,    44,    47,
      52,    46,    53,    65,    68,    70,    71,    73,    74,    94,
      93,    92,    95,   117,   109,   110,   111,   118,   112,    90,
     107,     0,   113,   126,   127,    16,   138,   128,     0,   129,
     -32,   130,   120,   121,   133,   -31,   -30,   137,    28,   124
};

static const yytype_int16 yycheck[] =
{
      42,    57,    13,     0,    78,    61,     4,    81,     6,     7,
       4,     4,     6,     7,     4,     4,    14,    73,    74,     4,
      14,     4,    20,    22,    80,    21,    24,     3,    21,    27,
      24,    21,     8,    27,     4,     4,    92,    36,    49,   113,
       9,    10,    53,    12,   122,   123,    22,    18,    90,    24,
      18,    20,    21,    22,    25,    24,     4,    25,    24,    70,
     138,     9,    10,    18,    12,   121,     3,    18,    18,    20,
      25,     8,    20,    21,    22,    25,    24,     4,     4,     4,
     122,   123,     9,    10,     3,    12,     5,    25,    20,     8,
       3,    23,     5,    20,    21,     8,   138,    24,     3,     3,
       5,    19,    19,     8,     8,    20,    24,    24,    23,    20,
      20,     4,    23,    23,     4,    18,    24,    20,     4,    25,
       4,    23,     4,     4,    25,     4,    20,    24,    24,     4,
      19,    26,     4,     4,    17,    15,    13,     4,    14,    59,
      18,    -1,    16,   107,   109,     7,    11,   110,    -1,   111,
      19,   112,    25,    23,    20,    19,    19,    25,    17,   103
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    29,    30,     0,     3,     5,     8,    33,    34,    35,
       4,    32,     4,     4,     3,     8,    34,    21,    38,    24,
      20,    23,    24,     4,    21,    32,     4,     4,    30,     3,
       5,     8,    36,    37,     4,    36,    24,    31,    20,     4,
       3,     8,    39,     4,     4,    25,    23,    25,    36,     3,
       8,    22,     4,     4,     4,     9,    10,    12,    20,    21,
      22,    24,    40,    41,    42,     4,     3,     8,    25,    32,
       4,    20,    24,    24,    24,     4,     6,     7,    14,    20,
      24,    27,    40,    43,    44,    45,    46,    47,    48,    49,
      39,    43,    26,    19,     4,     4,    20,    32,    43,    50,
      51,    43,    43,    24,    49,    43,    49,    18,    20,    17,
      15,    13,    14,    16,    22,    25,    43,     4,     4,    20,
      25,    23,    25,    25,    50,    25,    44,    45,    46,    47,
      48,    49,    20,    20,    43,    42,    42,    25,    11,    42
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    28,    29,    30,    30,    30,    30,    31,    31,    31,
      32,    32,    33,    33,    34,    35,    35,    35,    36,    36,
      36,    37,    37,    37,    37,    38,    39,    39,    40,    40,
      41,    41,    41,    41,    42,    42,    42,    42,    42,    42,
      42,    42,    42,    43,    43,    44,    44,    45,    45,    46,
      46,    47,    47,    48,    48,    49,    49,    49,    49,    49,
      49,    49,    50,    50,    51,    51
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     4,     5,     7,     0,     4,     5,     0,
       3,     1,     2,     1,     2,     5,     5,     6,     1,     1,
       0,     4,     5,     2,     3,     4,     2,     0,     3,     1,
       4,     3,     3,     1,     4,     5,     7,     5,     5,     3,
       2,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     2,     2,     3,     1,     1,
       4,     1,     1,     0,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Prog: DeclVars DeclFoncts  */
#line 30 "src/tpcas.y"
                          {
        (yyval.node) = makeNode(NODE_Prog, NULL);
        addChild((yyval.node), (yyvsp[-1].node));
        addChild((yyval.node), (yyvsp[0].node));
        ptr = (yyval.node);
    }
#line 1214 "src/tpcas.tab.c"
    break;

  case 3: /* DeclVars: DeclVars TYPE Declarateurs ';'  */
#line 39 "src/tpcas.y"
                                     {
        Node *var = makeNode(NODE_VAR_DECL, NULL);
        addChild(var, makeNode(NODE_TYPE, (yyvsp[-2].text)));
        addChild(var, (yyvsp[-1].node));
        addChild((yyvsp[-3].node), var);
        (yyval.node) = (yyvsp[-3].node);
    }
#line 1226 "src/tpcas.tab.c"
    break;

  case 4: /* DeclVars: DeclVars STRUCT IDENT Declarateurs ';'  */
#line 46 "src/tpcas.y"
                                             {
        Node *var = makeNode(NODE_VAR_DECL, NULL);
        addChild(var, makeNode(NODE_STRUCT, (yyvsp[-3].text)));
        addChild(var, makeNode(NODE_IDENT, (yyvsp[-2].text)));
        addChild(var, (yyvsp[-1].node));
        addChild((yyvsp[-4].node), var);
        (yyval.node) = (yyvsp[-4].node);
    }
#line 1239 "src/tpcas.tab.c"
    break;

  case 5: /* DeclVars: DeclVars STRUCT IDENT '{' DeclarateursStruct '}' ';'  */
#line 54 "src/tpcas.y"
                                                           {
        Node *var = makeNode(NODE_STRUCT_DEF, NULL);
        addChild(var, makeNode(NODE_STRUCT, (yyvsp[-5].text)));
        addChild(var, makeNode(NODE_IDENT, (yyvsp[-4].text)));
        addChild(var, (yyvsp[-2].node));
        addChild((yyvsp[-6].node), var);
        (yyval.node) = (yyvsp[-6].node);
    }
#line 1252 "src/tpcas.tab.c"
    break;

  case 6: /* DeclVars: %empty  */
#line 62 "src/tpcas.y"
                  { (yyval.node) = makeNode(NODE_DeclVars, NULL); }
#line 1258 "src/tpcas.tab.c"
    break;

  case 7: /* DeclarateursStruct: DeclarateursStruct TYPE Declarateurs ';'  */
#line 66 "src/tpcas.y"
                                               {
        Node *decl = makeNode(NODE_VAR_DECL, NULL);
        addChild(decl, makeNode(NODE_TYPE, (yyvsp[-2].text)));
        addChild(decl, (yyvsp[-1].node));
        addChild((yyvsp[-3].node), decl);
        (yyval.node) = (yyvsp[-3].node);
    }
#line 1270 "src/tpcas.tab.c"
    break;

  case 8: /* DeclarateursStruct: DeclarateursStruct STRUCT IDENT Declarateurs ';'  */
#line 73 "src/tpcas.y"
                                                       {
        Node *decl = makeNode(NODE_VAR_DECL, NULL);
        addChild(decl, makeNode(NODE_STRUCT, (yyvsp[-3].text)));
        addChild(decl, makeNode(NODE_IDENT, (yyvsp[-2].text)));
        addChild(decl, (yyvsp[-1].node));
        addChild((yyvsp[-4].node), decl);
        (yyval.node) = (yyvsp[-4].node);
    }
#line 1283 "src/tpcas.tab.c"
    break;

  case 9: /* DeclarateursStruct: %empty  */
#line 81 "src/tpcas.y"
                  { (yyval.node) = makeNode(NODE_DeclarateursStruct, NULL); }
#line 1289 "src/tpcas.tab.c"
    break;

  case 10: /* Declarateurs: Declarateurs ',' IDENT  */
#line 85 "src/tpcas.y"
                             {
        addSibling((yyvsp[-2].node), makeNode(NODE_IDENT, (yyvsp[0].text)));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1298 "src/tpcas.tab.c"
    break;

  case 11: /* Declarateurs: IDENT  */
#line 89 "src/tpcas.y"
            {
        (yyval.node) = makeNode(NODE_IDENT, (yyvsp[0].text));
    }
#line 1306 "src/tpcas.tab.c"
    break;

  case 12: /* DeclFoncts: DeclFoncts DeclFonct  */
#line 95 "src/tpcas.y"
                           { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 1312 "src/tpcas.tab.c"
    break;

  case 13: /* DeclFoncts: DeclFonct  */
#line 96 "src/tpcas.y"
                { (yyval.node) = makeNode(NODE_DeclFoncts, NULL); addChild((yyval.node), (yyvsp[0].node)); }
#line 1318 "src/tpcas.tab.c"
    break;

  case 14: /* DeclFonct: EnTeteFonct Corps  */
#line 100 "src/tpcas.y"
                        {
        (yyval.node) = makeNode(NODE_DeclFonct, NULL);
        addChild((yyval.node), (yyvsp[-1].node));
        addChild((yyval.node), (yyvsp[0].node));
    }
#line 1328 "src/tpcas.tab.c"
    break;

  case 15: /* EnTeteFonct: TYPE IDENT '(' Parametres ')'  */
#line 108 "src/tpcas.y"
                                    {
        (yyval.node) = makeNode(NODE_EnTeteFonct, NULL);
        addChild((yyval.node), makeNode(NODE_TYPE, (yyvsp[-4].text)));
        addChild((yyval.node), makeNode(NODE_IDENT, (yyvsp[-3].text)));
        addChild((yyval.node), (yyvsp[-1].node));
      }
#line 1339 "src/tpcas.tab.c"
    break;

  case 16: /* EnTeteFonct: VOID IDENT '(' Parametres ')'  */
#line 114 "src/tpcas.y"
                                    {
        (yyval.node) = makeNode(NODE_EnTeteFonct, NULL);
        addChild((yyval.node), makeNode(NODE_VOID, (yyvsp[-4].text)));
        addChild((yyval.node), makeNode(NODE_IDENT, (yyvsp[-3].text)));
        addChild((yyval.node), (yyvsp[-1].node));
      }
#line 1350 "src/tpcas.tab.c"
    break;

  case 17: /* EnTeteFonct: STRUCT IDENT IDENT '(' Parametres ')'  */
#line 120 "src/tpcas.y"
                                            {
        (yyval.node) = makeNode(NODE_EnTeteFonct, NULL);
        addChild((yyval.node), makeNode(NODE_STRUCT, (yyvsp[-5].text)));
        addChild((yyval.node), makeNode(NODE_IDENT, (yyvsp[-4].text)));
        addChild((yyval.node), makeNode(NODE_IDENT, (yyvsp[-3].text)));
        addChild((yyval.node), (yyvsp[-1].node));
      }
#line 1362 "src/tpcas.tab.c"
    break;

  case 18: /* Parametres: VOID  */
#line 130 "src/tpcas.y"
           { (yyval.node) = makeNode(NODE_Parametres, NULL); addChild((yyval.node), makeNode(NODE_VOID, (yyvsp[0].text))); }
#line 1368 "src/tpcas.tab.c"
    break;

  case 19: /* Parametres: ListTypVar  */
#line 131 "src/tpcas.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1374 "src/tpcas.tab.c"
    break;

  case 20: /* Parametres: %empty  */
#line 132 "src/tpcas.y"
                  { (yyval.node) = makeNode(NODE_Parametres, NULL); }
#line 1380 "src/tpcas.tab.c"
    break;

  case 21: /* ListTypVar: ListTypVar ',' TYPE IDENT  */
#line 136 "src/tpcas.y"
                                {
        addChild((yyvsp[-3].node), makeNode(NODE_TYPE, (yyvsp[-1].text)));
        addChild((yyvsp[-3].node), makeNode(NODE_IDENT, (yyvsp[0].text)));
        (yyval.node) = (yyvsp[-3].node);
    }
#line 1390 "src/tpcas.tab.c"
    break;

  case 22: /* ListTypVar: ListTypVar ',' STRUCT IDENT IDENT  */
#line 141 "src/tpcas.y"
                                        {
        addChild((yyvsp[-4].node), makeNode(NODE_STRUCT, (yyvsp[-2].text)));
        addChild((yyvsp[-4].node), makeNode(NODE_IDENT, (yyvsp[-1].text)));
        addChild((yyvsp[-4].node), makeNode(NODE_IDENT, (yyvsp[0].text)));
        (yyval.node) = (yyvsp[-4].node);
    }
#line 1401 "src/tpcas.tab.c"
    break;

  case 23: /* ListTypVar: TYPE IDENT  */
#line 147 "src/tpcas.y"
                 {
        Node *list = makeNode(NODE_ListTypVar, NULL);
        addChild(list, makeNode(NODE_TYPE, (yyvsp[-1].text)));
        addChild(list, makeNode(NODE_IDENT, (yyvsp[0].text)));
        (yyval.node) = list;
    }
#line 1412 "src/tpcas.tab.c"
    break;

  case 24: /* ListTypVar: STRUCT IDENT IDENT  */
#line 153 "src/tpcas.y"
                         {
        Node *list = makeNode(NODE_ListTypVar, NULL);
        addChild(list, makeNode(NODE_STRUCT, (yyvsp[-2].text)));
        addChild(list, makeNode(NODE_IDENT, (yyvsp[-1].text)));
        addChild(list, makeNode(NODE_IDENT, (yyvsp[0].text)));
        (yyval.node) = list;
    }
#line 1424 "src/tpcas.tab.c"
    break;

  case 25: /* Corps: '{' DeclVars SuiteInstr '}'  */
#line 163 "src/tpcas.y"
                                  {
        (yyval.node) = makeNode(NODE_Corps, NULL);
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[-1].node));
    }
#line 1434 "src/tpcas.tab.c"
    break;

  case 26: /* SuiteInstr: SuiteInstr Instr  */
#line 171 "src/tpcas.y"
                       { addChild((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 1440 "src/tpcas.tab.c"
    break;

  case 27: /* SuiteInstr: %empty  */
#line 172 "src/tpcas.y"
                  { (yyval.node) = makeNode(NODE_SuiteInstr, NULL); }
#line 1446 "src/tpcas.tab.c"
    break;

  case 28: /* LValue: Value DOT IDENT  */
#line 177 "src/tpcas.y"
                      { 
        (yyval.node) = makeNode(NODE_DOT, NULL);
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), makeNode(NODE_IDENT, (yyvsp[0].text)));
     }
#line 1456 "src/tpcas.tab.c"
    break;

  case 29: /* LValue: IDENT  */
#line 182 "src/tpcas.y"
            {
        (yyval.node) = makeNode(NODE_IDENT, (yyvsp[0].text)); 
    }
#line 1464 "src/tpcas.tab.c"
    break;

  case 30: /* Value: IDENT '(' Arguments ')'  */
#line 188 "src/tpcas.y"
                              {
        (yyval.node) = makeNode(NODE_IDENT, (yyvsp[-3].text));
        addChild((yyval.node), (yyvsp[-1].node));
    }
#line 1473 "src/tpcas.tab.c"
    break;

  case 31: /* Value: '(' Exp ')'  */
#line 194 "src/tpcas.y"
    {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1481 "src/tpcas.tab.c"
    break;

  case 32: /* Value: Value DOT IDENT  */
#line 197 "src/tpcas.y"
                      {
        (yyval.node) = makeNode(NODE_DOT, NULL);
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), makeNode(NODE_IDENT, (yyvsp[0].text)));
    }
#line 1491 "src/tpcas.tab.c"
    break;

  case 33: /* Value: IDENT  */
#line 202 "src/tpcas.y"
           {
        (yyval.node) = makeNode(NODE_IDENT, (yyvsp[0].text)); 
    }
#line 1499 "src/tpcas.tab.c"
    break;

  case 34: /* Instr: LValue '=' Exp ';'  */
#line 207 "src/tpcas.y"
                         { (yyval.node) = makeNode(NODE_ASSIGN, NULL); addChild((yyval.node), (yyvsp[-3].node)); addChild((yyval.node), (yyvsp[-1].node));  }
#line 1505 "src/tpcas.tab.c"
    break;

  case 35: /* Instr: IF '(' Exp ')' Instr  */
#line 208 "src/tpcas.y"
                           { (yyval.node) = makeNode(NODE_IF, NULL); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node));}
#line 1511 "src/tpcas.tab.c"
    break;

  case 36: /* Instr: IF '(' Exp ')' Instr ELSE Instr  */
#line 209 "src/tpcas.y"
                                      { (yyval.node) = makeNode(NODE_IF, NULL); addChild((yyval.node), (yyvsp[-4].node)); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node));}
#line 1517 "src/tpcas.tab.c"
    break;

  case 37: /* Instr: WHILE '(' Exp ')' Instr  */
#line 210 "src/tpcas.y"
                              { (yyval.node) = makeNode(NODE_WHILE, NULL); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node));  }
#line 1523 "src/tpcas.tab.c"
    break;

  case 38: /* Instr: IDENT '(' Arguments ')' ';'  */
#line 211 "src/tpcas.y"
                                  { (yyval.node) = makeNode(NODE_CALL_FUNCTION, NULL); addChild((yyval.node), makeNode(NODE_IDENT, (yyvsp[-4].text))); addChild((yyval.node), (yyvsp[-2].node)); }
#line 1529 "src/tpcas.tab.c"
    break;

  case 39: /* Instr: RETURN Exp ';'  */
#line 212 "src/tpcas.y"
                     { (yyval.node) = makeNode(NODE_RETURN, NULL); addChild((yyval.node), (yyvsp[-1].node)); }
#line 1535 "src/tpcas.tab.c"
    break;

  case 40: /* Instr: RETURN ';'  */
#line 213 "src/tpcas.y"
                 { (yyval.node) = makeNode(NODE_RETURN, NULL); }
#line 1541 "src/tpcas.tab.c"
    break;

  case 41: /* Instr: '{' SuiteInstr '}'  */
#line 214 "src/tpcas.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 1547 "src/tpcas.tab.c"
    break;

  case 42: /* Instr: ';'  */
#line 215 "src/tpcas.y"
          { (yyval.node) = makeNode(NODE_EMPTY, NULL); }
#line 1553 "src/tpcas.tab.c"
    break;

  case 43: /* Exp: Exp OR TB  */
#line 219 "src/tpcas.y"
                { (yyval.node) = makeNode(NODE_OR, (yyvsp[-1].text)); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 1559 "src/tpcas.tab.c"
    break;

  case 44: /* Exp: TB  */
#line 220 "src/tpcas.y"
         { (yyval.node) = (yyvsp[0].node); }
#line 1565 "src/tpcas.tab.c"
    break;

  case 45: /* TB: TB AND FB  */
#line 224 "src/tpcas.y"
                { (yyval.node) = makeNode(NODE_AND, (yyvsp[-1].text)); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 1571 "src/tpcas.tab.c"
    break;

  case 46: /* TB: FB  */
#line 225 "src/tpcas.y"
         { (yyval.node) = (yyvsp[0].node); }
#line 1577 "src/tpcas.tab.c"
    break;

  case 47: /* FB: FB EQ M  */
#line 229 "src/tpcas.y"
              { (yyval.node) = makeNode(NODE_EQ, (yyvsp[-1].text)); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 1583 "src/tpcas.tab.c"
    break;

  case 48: /* FB: M  */
#line 230 "src/tpcas.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1589 "src/tpcas.tab.c"
    break;

  case 49: /* M: M ORDER E  */
#line 234 "src/tpcas.y"
                { (yyval.node) = makeNode(NODE_ORDER, (yyvsp[-1].text)); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 1595 "src/tpcas.tab.c"
    break;

  case 50: /* M: E  */
#line 235 "src/tpcas.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1601 "src/tpcas.tab.c"
    break;

  case 51: /* E: E ADDSUB T  */
#line 239 "src/tpcas.y"
                 { (yyval.node) = makeNode(NODE_ADDSUB, (yyvsp[-1].text)); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node));  }
#line 1607 "src/tpcas.tab.c"
    break;

  case 52: /* E: T  */
#line 240 "src/tpcas.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1613 "src/tpcas.tab.c"
    break;

  case 53: /* T: T DIVSTAR F  */
#line 244 "src/tpcas.y"
                  { (yyval.node) = makeNode(NODE_DIVSTAR, (yyvsp[-1].text)); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 1619 "src/tpcas.tab.c"
    break;

  case 54: /* T: F  */
#line 245 "src/tpcas.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1625 "src/tpcas.tab.c"
    break;

  case 55: /* F: ADDSUB F  */
#line 249 "src/tpcas.y"
               { (yyval.node) = makeNode(NODE_UNARY, (yyvsp[-1].text)); addChild((yyval.node), (yyvsp[0].node)); }
#line 1631 "src/tpcas.tab.c"
    break;

  case 56: /* F: '!' F  */
#line 250 "src/tpcas.y"
            { (yyval.node) = makeNode(NODE_NOT, NULL); addChild((yyval.node), (yyvsp[0].node)); }
#line 1637 "src/tpcas.tab.c"
    break;

  case 57: /* F: '(' Exp ')'  */
#line 251 "src/tpcas.y"
                  { (yyval.node) = (yyvsp[-1].node); }
#line 1643 "src/tpcas.tab.c"
    break;

  case 58: /* F: NUM  */
#line 252 "src/tpcas.y"
          { (yyval.node) = makeNode(NODE_NUM, (yyvsp[0].text)); }
#line 1649 "src/tpcas.tab.c"
    break;

  case 59: /* F: CHARACTER  */
#line 253 "src/tpcas.y"
                { (yyval.node) = makeNode(NODE_CHARACTER, (yyvsp[0].text)); }
#line 1655 "src/tpcas.tab.c"
    break;

  case 60: /* F: IDENT '(' Arguments ')'  */
#line 254 "src/tpcas.y"
                              {  (yyval.node) = makeNode(NODE_CALL_FUNCTION, NULL); addChild((yyval.node), makeNode(NODE_IDENT, (yyvsp[-3].text))); addChild((yyval.node), (yyvsp[-1].node)); }
#line 1661 "src/tpcas.tab.c"
    break;

  case 61: /* F: LValue  */
#line 255 "src/tpcas.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 1667 "src/tpcas.tab.c"
    break;

  case 62: /* Arguments: ListExp  */
#line 260 "src/tpcas.y"
              { (yyval.node) = makeNode(NODE_Arguments, NULL); addChild((yyval.node), (yyvsp[0].node)); }
#line 1673 "src/tpcas.tab.c"
    break;

  case 63: /* Arguments: %empty  */
#line 261 "src/tpcas.y"
                  { (yyval.node) = makeNode(NODE_Arguments, NULL); }
#line 1679 "src/tpcas.tab.c"
    break;

  case 64: /* ListExp: Exp  */
#line 265 "src/tpcas.y"
          { (yyval.node) = makeNode(NODE_ListExp, NULL); addChild((yyval.node), (yyvsp[0].node)); }
#line 1685 "src/tpcas.tab.c"
    break;

  case 65: /* ListExp: ListExp ',' Exp  */
#line 266 "src/tpcas.y"
                      { addChild((yyval.node), (yyvsp[0].node)); }
#line 1691 "src/tpcas.tab.c"
    break;


#line 1695 "src/tpcas.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 269 "src/tpcas.y"

    

void print_usage(char *prog_name) {
    printf("Usage: %s [OPTIONS] [FILE.tpc]\n", prog_name);
    printf("Analyseur syntaxique pour le langage TPC\n\n");
    printf("Options:\n");
    printf("  -t, --tree        Affiche l'arbre abstrait sur la sortie standard\n");
    printf("  -h, --help        Affiche cette aide et termine l'exécution\n\n");
    printf("\nValeurs de retour:\n");
    printf("  0  Aucune erreur lexicale ni syntaxique\n");
    printf("  1  Erreur lexicale ou syntaxique détectée\n");
    printf("  2+ Autres erreurs (ligne de commande, mémoire, etc.)\n");
}
    
int main(int argc, char **argv) {
    int show_tree = 0;
    int noption = 1;
    char *input_file = NULL;
    if(argc < 2){
        fprintf(stderr, "Utilisez -h ou --help pour plus d'informations\n");
        return 2;
    }
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "-help") == 0){
            print_usage(argv[0]);
            return 0;
        }
        if(strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "-tree") == 0){
            show_tree = 1
            ;
            noption++;
        }
    }
    if(noption < argc){
        input_file = argv[noption];
        yyin = fopen(input_file, "r");
        if (!yyin) {
            fprintf(stderr, "Erreur: impossible d'ouvrir le fichier '%s'\n", input_file);
            return 2;
        }
    }
    yylineno = 1;
    int result = yyparse();
    if (result != 0) {
        fprintf(stderr, "Analyse terminée \n");
        deleteTree(ptr);
        return 1;
        }
    if (show_tree) {
        printf("=== Arbre abstrait ===\n");
        generateTreePDF(ptr);
        printTree(ptr);
        
    }
    extern struct table_symbole globalTable[100];
    extern int size;
    // ----- - tp5 partie 2 -----
    FILE *fp = fopen("_anonymous.asm", "w");
    // ----- - tp5 partie 2 -----
    fill_global_symbol_table(ptr, globalTable, fp);
    print_global_symbol_table(globalTable, size);
    // ----- TDC6 Exercice 1 : Vérification des déclarations -----
    check_all_declarations(ptr, globalTable, size);
    // ----- - tp5 partie 2 -----
    parcours_instruction(ptr, globalTable, fp);
    fprintf(fp, "mov rdi, format\n");
    fprintf(fp, "mov rsi, rbx\n");
    fprintf(fp, "xor rax, rax\n");
    fprintf(fp, "call printf\n");
    fprintf(fp, "mov rax, 60\n");
    fprintf(fp, "xor rdi, rdi\n");
    fprintf(fp, "syscall\n");
    fclose(fp);
    // ----- - tp5 partie 3 -----
    deleteTree(ptr);
    return result;
}
