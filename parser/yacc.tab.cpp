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
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"

/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "ast.h"
#include "yacc.tab.h"
#include <iostream>
#include <memory>

int yylex(YYSTYPE *yylval, YYLTYPE *yylloc);

void yyerror(YYLTYPE *locp, const char* s) {
    std::cerr << "Parser Error at line " << locp->first_line << " column " << locp->first_column << ": " << s << std::endl;
}

using namespace njudb;
using namespace ast;

#line 97 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"

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

#include "yacc.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_EXPLAIN = 3,                    /* EXPLAIN  */
  YYSYMBOL_SHOW = 4,                       /* SHOW  */
  YYSYMBOL_TABLES = 5,                     /* TABLES  */
  YYSYMBOL_CREATE = 6,                     /* CREATE  */
  YYSYMBOL_TABLE = 7,                      /* TABLE  */
  YYSYMBOL_DROP = 8,                       /* DROP  */
  YYSYMBOL_DESC = 9,                       /* DESC  */
  YYSYMBOL_INSERT = 10,                    /* INSERT  */
  YYSYMBOL_INTO = 11,                      /* INTO  */
  YYSYMBOL_VALUES = 12,                    /* VALUES  */
  YYSYMBOL_DELETE = 13,                    /* DELETE  */
  YYSYMBOL_FROM = 14,                      /* FROM  */
  YYSYMBOL_OPEN = 15,                      /* OPEN  */
  YYSYMBOL_DATABASE = 16,                  /* DATABASE  */
  YYSYMBOL_ON = 17,                        /* ON  */
  YYSYMBOL_ASC = 18,                       /* ASC  */
  YYSYMBOL_AS = 19,                        /* AS  */
  YYSYMBOL_ORDER = 20,                     /* ORDER  */
  YYSYMBOL_GROUP = 21,                     /* GROUP  */
  YYSYMBOL_BY = 22,                        /* BY  */
  YYSYMBOL_SUM = 23,                       /* SUM  */
  YYSYMBOL_AVG = 24,                       /* AVG  */
  YYSYMBOL_MAX = 25,                       /* MAX  */
  YYSYMBOL_MIN = 26,                       /* MIN  */
  YYSYMBOL_COUNT = 27,                     /* COUNT  */
  YYSYMBOL_IN = 28,                        /* IN  */
  YYSYMBOL_STATIC_CHECKPOINT = 29,         /* STATIC_CHECKPOINT  */
  YYSYMBOL_USING = 30,                     /* USING  */
  YYSYMBOL_LOOP = 31,                      /* LOOP  */
  YYSYMBOL_MERGE = 32,                     /* MERGE  */
  YYSYMBOL_INDEX_BPTREE = 33,              /* INDEX_BPTREE  */
  YYSYMBOL_HASH_KWD = 34,                  /* HASH_KWD  */
  YYSYMBOL_WHERE = 35,                     /* WHERE  */
  YYSYMBOL_HAVING = 36,                    /* HAVING  */
  YYSYMBOL_UPDATE = 37,                    /* UPDATE  */
  YYSYMBOL_SET = 38,                       /* SET  */
  YYSYMBOL_SELECT = 39,                    /* SELECT  */
  YYSYMBOL_INT = 40,                       /* INT  */
  YYSYMBOL_CHAR = 41,                      /* CHAR  */
  YYSYMBOL_FLOAT = 42,                     /* FLOAT  */
  YYSYMBOL_BOOL = 43,                      /* BOOL  */
  YYSYMBOL_INDEX = 44,                     /* INDEX  */
  YYSYMBOL_AND = 45,                       /* AND  */
  YYSYMBOL_JOIN = 46,                      /* JOIN  */
  YYSYMBOL_INNER = 47,                     /* INNER  */
  YYSYMBOL_OUTER = 48,                     /* OUTER  */
  YYSYMBOL_EXIT = 49,                      /* EXIT  */
  YYSYMBOL_HELP = 50,                      /* HELP  */
  YYSYMBOL_TXN_BEGIN = 51,                 /* TXN_BEGIN  */
  YYSYMBOL_TXN_COMMIT = 52,                /* TXN_COMMIT  */
  YYSYMBOL_TXN_ABORT = 53,                 /* TXN_ABORT  */
  YYSYMBOL_TXN_ROLLBACK = 54,              /* TXN_ROLLBACK  */
  YYSYMBOL_ORDER_BY = 55,                  /* ORDER_BY  */
  YYSYMBOL_ENABLE_NESTLOOP = 56,           /* ENABLE_NESTLOOP  */
  YYSYMBOL_ENABLE_SORTMERGE = 57,          /* ENABLE_SORTMERGE  */
  YYSYMBOL_STORAGE = 58,                   /* STORAGE  */
  YYSYMBOL_PAX = 59,                       /* PAX  */
  YYSYMBOL_NARY = 60,                      /* NARY  */
  YYSYMBOL_LIMIT = 61,                     /* LIMIT  */
  YYSYMBOL_LEQ = 62,                       /* LEQ  */
  YYSYMBOL_NEQ = 63,                       /* NEQ  */
  YYSYMBOL_GEQ = 64,                       /* GEQ  */
  YYSYMBOL_T_EOF = 65,                     /* T_EOF  */
  YYSYMBOL_IDENTIFIER = 66,                /* IDENTIFIER  */
  YYSYMBOL_VALUE_STRING = 67,              /* VALUE_STRING  */
  YYSYMBOL_VALUE_INT = 68,                 /* VALUE_INT  */
  YYSYMBOL_VALUE_FLOAT = 69,               /* VALUE_FLOAT  */
  YYSYMBOL_VALUE_BOOL = 70,                /* VALUE_BOOL  */
  YYSYMBOL_71_ = 71,                       /* ';'  */
  YYSYMBOL_72_ = 72,                       /* '('  */
  YYSYMBOL_73_ = 73,                       /* ')'  */
  YYSYMBOL_74_ = 74,                       /* '='  */
  YYSYMBOL_75_ = 75,                       /* ','  */
  YYSYMBOL_76_ = 76,                       /* '.'  */
  YYSYMBOL_77_ = 77,                       /* '*'  */
  YYSYMBOL_78_ = 78,                       /* '<'  */
  YYSYMBOL_79_ = 79,                       /* '>'  */
  YYSYMBOL_YYACCEPT = 80,                  /* $accept  */
  YYSYMBOL_start = 81,                     /* start  */
  YYSYMBOL_stmt = 82,                      /* stmt  */
  YYSYMBOL_txnStmt = 83,                   /* txnStmt  */
  YYSYMBOL_logStmt = 84,                   /* logStmt  */
  YYSYMBOL_dbStmt = 85,                    /* dbStmt  */
  YYSYMBOL_indexStmt = 86,                 /* indexStmt  */
  YYSYMBOL_ddl = 87,                       /* ddl  */
  YYSYMBOL_optStorageModel = 88,           /* optStorageModel  */
  YYSYMBOL_dml = 89,                       /* dml  */
  YYSYMBOL_selectStmt = 90,                /* selectStmt  */
  YYSYMBOL_optLimit = 91,                  /* optLimit  */
  YYSYMBOL_fieldList = 92,                 /* fieldList  */
  YYSYMBOL_colNameList = 93,               /* colNameList  */
  YYSYMBOL_field = 94,                     /* field  */
  YYSYMBOL_type = 95,                      /* type  */
  YYSYMBOL_valueList = 96,                 /* valueList  */
  YYSYMBOL_value = 97,                     /* value  */
  YYSYMBOL_colListWithoutAlias = 98,       /* colListWithoutAlias  */
  YYSYMBOL_optGroupByClause = 99,          /* optGroupByClause  */
  YYSYMBOL_condition = 100,                /* condition  */
  YYSYMBOL_optWhereClause = 101,           /* optWhereClause  */
  YYSYMBOL_optUsingIndexClause = 102,      /* optUsingIndexClause  */
  YYSYMBOL_optUsingJoinClause = 103,       /* optUsingJoinClause  */
  YYSYMBOL_conditionAgg = 104,             /* conditionAgg  */
  YYSYMBOL_optHavingClause = 105,          /* optHavingClause  */
  YYSYMBOL_havingClause = 106,             /* havingClause  */
  YYSYMBOL_whereClause = 107,              /* whereClause  */
  YYSYMBOL_col = 108,                      /* col  */
  YYSYMBOL_aggCol = 109,                   /* aggCol  */
  YYSYMBOL_colList = 110,                  /* colList  */
  YYSYMBOL_optAlias = 111,                 /* optAlias  */
  YYSYMBOL_op = 112,                       /* op  */
  YYSYMBOL_expr = 113,                     /* expr  */
  YYSYMBOL_setClauses = 114,               /* setClauses  */
  YYSYMBOL_setClause = 115,                /* setClause  */
  YYSYMBOL_selector = 116,                 /* selector  */
  YYSYMBOL_table = 117,                    /* table  */
  YYSYMBOL_tableList = 118,                /* tableList  */
  YYSYMBOL_opt_order_clause = 119,         /* opt_order_clause  */
  YYSYMBOL_order_clause = 120,             /* order_clause  */
  YYSYMBOL_opt_asc_desc = 121,             /* opt_asc_desc  */
  YYSYMBOL_tbName = 122,                   /* tbName  */
  YYSYMBOL_colName = 123                   /* colName  */
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

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  55
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   236

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  122
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  229

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   325


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      72,    73,    77,     2,    75,     2,    76,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    71,
      78,    74,    79,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    75,    75,    81,    86,    91,    96,   104,   105,   106,
     107,   108,   109,   110,   114,   118,   122,   126,   133,   139,
     143,   147,   154,   158,   164,   168,   172,   176,   180,   187,
     188,   190,   195,   199,   203,   207,   214,   221,   225,   229,
     233,   240,   244,   251,   258,   262,   266,   270,   277,   281,
     288,   292,   296,   300,   305,   311,   315,   322,   323,   330,
     334,   338,   342,   350,   351,   358,   359,   360,   363,   364,
     366,   368,   372,   380,   381,   387,   391,   395,   399,   407,
     411,   418,   422,   429,   433,   437,   441,   445,   449,   457,
     462,   467,   472,   480,   484,   488,   492,   496,   500,   504,
     508,   515,   519,   526,   530,   537,   544,   548,   552,   556,
     560,   564,   568,   575,   579,   586,   590,   594,   601,   602,
     603,   606,   608
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "EXPLAIN", "SHOW",
  "TABLES", "CREATE", "TABLE", "DROP", "DESC", "INSERT", "INTO", "VALUES",
  "DELETE", "FROM", "OPEN", "DATABASE", "ON", "ASC", "AS", "ORDER",
  "GROUP", "BY", "SUM", "AVG", "MAX", "MIN", "COUNT", "IN",
  "STATIC_CHECKPOINT", "USING", "LOOP", "MERGE", "INDEX_BPTREE",
  "HASH_KWD", "WHERE", "HAVING", "UPDATE", "SET", "SELECT", "INT", "CHAR",
  "FLOAT", "BOOL", "INDEX", "AND", "JOIN", "INNER", "OUTER", "EXIT",
  "HELP", "TXN_BEGIN", "TXN_COMMIT", "TXN_ABORT", "TXN_ROLLBACK",
  "ORDER_BY", "ENABLE_NESTLOOP", "ENABLE_SORTMERGE", "STORAGE", "PAX",
  "NARY", "LIMIT", "LEQ", "NEQ", "GEQ", "T_EOF", "IDENTIFIER",
  "VALUE_STRING", "VALUE_INT", "VALUE_FLOAT", "VALUE_BOOL", "';'", "'('",
  "')'", "'='", "','", "'.'", "'*'", "'<'", "'>'", "$accept", "start",
  "stmt", "txnStmt", "logStmt", "dbStmt", "indexStmt", "ddl",
  "optStorageModel", "dml", "selectStmt", "optLimit", "fieldList",
  "colNameList", "field", "type", "valueList", "value",
  "colListWithoutAlias", "optGroupByClause", "condition", "optWhereClause",
  "optUsingIndexClause", "optUsingJoinClause", "conditionAgg",
  "optHavingClause", "havingClause", "whereClause", "col", "aggCol",
  "colList", "optAlias", "op", "expr", "setClauses", "setClause",
  "selector", "table", "tableList", "opt_order_clause", "order_clause",
  "opt_asc_desc", "tbName", "colName", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-141)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-122)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      80,    99,    27,    97,    -1,   -49,     9,    13,    17,   -49,
      21,  -141,  -141,  -141,  -141,  -141,  -141,  -141,    36,   -29,
    -141,  -141,  -141,  -141,  -141,  -141,  -141,     1,  -141,    46,
     -49,    19,  -141,   -49,   -49,   -49,  -141,  -141,   -49,   -49,
      25,    41,    22,    30,    34,    38,    52,    49,  -141,    78,
      78,    53,   126,    63,  -141,  -141,  -141,  -141,   -49,    71,
    -141,   127,  -141,   137,   143,   133,  -141,   103,   122,   122,
     122,   122,   -59,   103,  -141,  -141,    26,   -58,   103,  -141,
     103,   -49,   -49,   117,   122,  -141,  -141,   -20,  -141,   116,
     118,   119,   120,   121,   124,   128,  -141,    78,    78,   156,
    -141,   -11,   125,  -141,    47,  -141,   136,   130,  -141,   113,
    -141,   153,    37,   103,  -141,   113,  -141,  -141,  -141,  -141,
    -141,  -141,  -141,  -141,   131,   -58,   178,   -49,   154,   157,
     147,   103,  -141,   134,  -141,  -141,  -141,   103,  -141,  -141,
    -141,  -141,    62,  -141,   122,   135,  -141,  -141,  -141,  -141,
    -141,  -141,    95,  -141,  -141,  -141,  -141,   186,   173,  -141,
     -49,   -49,   138,  -141,  -141,   142,   111,  -141,  -141,   113,
    -141,    79,   156,  -141,  -141,  -141,   122,    26,   181,  -141,
    -141,   -47,   140,   184,   103,  -141,   144,   112,   145,   146,
    -141,  -141,  -141,   170,    96,     7,   199,  -141,  -141,  -141,
      42,  -141,  -141,  -141,  -141,  -141,   122,    26,   113,  -141,
    -141,  -141,   198,   161,  -141,  -141,  -141,  -141,  -141,  -141,
      10,   155,  -141,  -141,  -141,  -141,   122,  -141,   146
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      13,    13,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     5,     4,    14,    15,    16,    17,     6,     0,     0,
      10,    12,     7,    11,     8,     9,    35,     0,    19,    23,
       0,     0,    18,     0,     0,     0,   121,    26,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   122,   106,    94,
      94,   107,     0,     0,    82,     1,     2,     3,     0,     0,
      20,     0,    25,     0,     0,    63,    21,     0,     0,     0,
       0,     0,     0,     0,    89,    90,     0,     0,     0,    22,
       0,     0,     0,     0,     0,    33,   122,    63,   103,     0,
       0,     0,     0,     0,     0,     0,    93,    94,    94,     0,
     113,    63,   108,    81,     0,    39,     0,     0,    28,    54,
      79,    64,     0,     0,    34,    54,    84,    85,    86,    87,
      88,    83,    91,    92,     0,     0,    57,     0,     0,     0,
      29,     0,    44,     0,    47,    45,    43,     0,    52,    50,
      51,    53,     0,    48,     0,     0,    99,    98,   100,    95,
      96,    97,    54,   104,   105,   109,   114,     0,    73,   110,
       0,     0,     0,    24,    40,     0,     0,    41,    32,    54,
      80,    54,     0,   101,   102,    59,     0,     0,    68,   111,
     112,     0,     0,    65,     0,    49,     0,     0,     0,    58,
      55,    75,    76,    74,     0,     0,   116,    31,    30,    46,
       0,    27,    42,    61,    62,    60,     0,     0,    54,    69,
      70,    71,     0,    38,    66,    67,    56,    77,    78,    72,
     120,     0,    36,   119,   118,   115,     0,    37,   117
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -141,  -141,   223,  -141,  -141,  -141,  -141,  -141,  -141,  -141,
     -90,  -141,  -141,  -141,    94,  -141,    55,  -112,     2,  -141,
    -140,   -76,  -141,  -141,    20,  -141,  -141,  -141,   -10,    -8,
    -141,   -28,    35,  -141,  -141,   123,  -141,   105,  -141,  -141,
    -141,  -141,    -4,   -57
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    18,    19,    20,    21,    22,    23,    24,   163,    25,
      26,   222,   104,   166,   105,   136,   142,   143,   189,   158,
     110,    85,   201,   196,   192,   178,   193,   111,   112,   194,
      51,    74,   152,   175,    87,    88,    52,   100,   101,   213,
     225,   226,    53,    54
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,    37,    50,   154,   170,    41,    34,    47,    36,   124,
      89,   114,   197,   198,    99,    84,    96,    36,    94,   223,
      38,   103,    75,   106,    84,   126,    59,    39,   224,    61,
      62,    63,    28,    40,    64,    65,    55,   191,   209,   210,
     173,   211,    56,    35,    42,    43,    44,    45,    46,    42,
      43,    44,    45,    46,    79,   113,    89,   185,    90,    91,
      92,    93,    95,    58,   125,   145,    97,   217,    98,   122,
     123,    29,    57,   102,   106,   214,   215,   107,   108,    67,
     167,   186,   188,     1,     2,    60,     3,    47,     4,     5,
       6,    66,    47,     7,    68,     8,   219,    73,    48,   146,
     147,   148,    69,     2,    30,     3,    70,     4,     5,     6,
      71,   149,     7,    31,     8,   150,   151,     9,    10,    10,
     130,   102,   131,   159,    72,  -121,    32,   202,    76,    11,
      12,    13,    14,    15,    16,   168,     9,   169,    10,    78,
      77,    33,   174,    80,    81,    17,   138,   139,   140,   141,
      13,    14,    15,    16,    82,    83,   179,   180,   146,   147,
     148,    47,   138,   139,   140,   141,   190,   172,    84,    86,
     149,   127,   128,   129,   150,   151,   132,   133,   134,   135,
     138,   139,   140,   141,   183,   204,   184,   169,    47,   109,
     115,   116,   117,   118,   119,    10,   216,   120,   144,   157,
     160,   121,   137,   161,   155,   162,   165,   171,   176,   177,
     182,   195,   181,   199,   200,   207,   190,   203,   205,   212,
     220,   206,   221,   227,    27,   164,   187,   218,   228,   208,
     156,     0,     0,     0,     0,     0,   153
};

static const yytype_int16 yycheck[] =
{
      10,     5,    10,   115,   144,     9,     7,    66,    66,    99,
      67,    87,    59,    60,    72,    35,    73,    66,    77,     9,
      11,    78,    50,    80,    35,   101,    30,    14,    18,    33,
      34,    35,     5,    16,    38,    39,     0,   177,    31,    32,
     152,    34,    71,    44,    23,    24,    25,    26,    27,    23,
      24,    25,    26,    27,    58,    75,   113,   169,    68,    69,
      70,    71,    72,    17,    75,    28,    76,   207,    76,    97,
      98,    44,    71,    77,   131,    33,    34,    81,    82,    38,
     137,   171,   172,     3,     4,    66,     6,    66,     8,     9,
      10,    66,    66,    13,    72,    15,   208,    19,    77,    62,
      63,    64,    72,     4,     7,     6,    72,     8,     9,    10,
      72,    74,    13,    16,    15,    78,    79,    37,    39,    39,
      73,   125,    75,   127,    72,    76,    29,   184,    75,    49,
      50,    51,    52,    53,    54,    73,    37,    75,    39,    76,
      14,    44,   152,    72,    17,    65,    67,    68,    69,    70,
      51,    52,    53,    54,    17,    12,   160,   161,    62,    63,
      64,    66,    67,    68,    69,    70,   176,    72,    35,    66,
      74,    46,    47,    48,    78,    79,    40,    41,    42,    43,
      67,    68,    69,    70,    73,    73,    75,    75,    66,    72,
      74,    73,    73,    73,    73,    39,   206,    73,    45,    21,
      46,    73,    72,    46,    73,    58,    72,    72,    22,    36,
      68,    30,    74,    73,    30,    45,   226,    73,    73,    20,
      22,    75,    61,    68,     1,   131,   171,   207,   226,   194,
     125,    -1,    -1,    -1,    -1,    -1,   113
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     6,     8,     9,    10,    13,    15,    37,
      39,    49,    50,    51,    52,    53,    54,    65,    81,    82,
      83,    84,    85,    86,    87,    89,    90,    82,     5,    44,
       7,    16,    29,    44,     7,    44,    66,   122,    11,    14,
      16,   122,    23,    24,    25,    26,    27,    66,    77,   108,
     109,   110,   116,   122,   123,     0,    71,    71,    17,   122,
      66,   122,   122,   122,   122,   122,    66,    38,    72,    72,
      72,    72,    72,    19,   111,   111,    75,    14,    76,   122,
      72,    17,    17,    12,    35,   101,    66,   114,   115,   123,
     108,   108,   108,   108,    77,   108,   123,   108,   109,    72,
     117,   118,   122,   123,    92,    94,   123,   122,   122,    72,
     100,   107,   108,    75,   101,    74,    73,    73,    73,    73,
      73,    73,   111,   111,    90,    75,   101,    46,    47,    48,
      73,    75,    40,    41,    42,    43,    95,    72,    67,    68,
      69,    70,    96,    97,    45,    28,    62,    63,    64,    74,
      78,    79,   112,   115,    97,    73,   117,    21,    99,   122,
      46,    46,    58,    88,    94,    72,    93,   123,    73,    75,
     100,    72,    72,    97,   108,   113,    22,    36,   105,   122,
     122,    74,    68,    73,    75,    97,    90,    96,    90,    98,
     108,   100,   104,   106,   109,    30,   103,    59,    60,    73,
      30,   102,   123,    73,    73,    73,    75,    45,   112,    31,
      32,    34,    20,   119,    33,    34,   108,   100,   104,    97,
      22,    61,    91,     9,    18,   120,   121,    68,    98
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    80,    81,    81,    81,    81,    81,    82,    82,    82,
      82,    82,    82,    82,    83,    83,    83,    83,    84,    85,
      85,    85,    86,    86,    87,    87,    87,    87,    87,    88,
      88,    88,    89,    89,    89,    89,    90,    91,    91,    92,
      92,    93,    93,    94,    95,    95,    95,    95,    96,    96,
      97,    97,    97,    97,    97,    98,    98,    99,    99,   100,
     100,   100,   100,   101,   101,   102,   102,   102,   103,   103,
     103,   103,   104,   105,   105,   106,   106,   106,   106,   107,
     107,   108,   108,   109,   109,   109,   109,   109,   109,   110,
     110,   110,   110,   111,   111,   112,   112,   112,   112,   112,
     112,   113,   113,   114,   114,   115,   116,   116,   117,   117,
     117,   117,   117,   118,   118,   119,   119,   120,   121,   121,
     121,   122,   123
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     1,     1,     1,     1,     2,     2,
       3,     3,     4,     2,     7,     3,     2,     9,     5,     0,
       3,     3,     7,     4,     5,     1,    10,     2,     0,     1,
       3,     1,     3,     2,     1,     1,     4,     1,     1,     3,
       1,     1,     1,     1,     0,     1,     3,     0,     3,     3,
       5,     5,     5,     0,     2,     0,     2,     2,     0,     2,
       2,     2,     3,     0,     2,     1,     1,     3,     3,     1,
       3,     3,     1,     4,     4,     4,     4,     4,     4,     2,
       2,     4,     4,     2,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     1,     1,     1,     3,
       3,     4,     4,     1,     3,     3,     0,     2,     1,     1,
       0,     1,     1
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
        yyerror (&yylloc, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = yylex (&yylval, &yylloc);
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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* start: stmt ';'  */
#line 76 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        njudb_ast_ = (yyvsp[-1].sv_node);
        YYACCEPT;
    }
#line 1773 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 3: /* start: EXPLAIN stmt ';'  */
#line 82 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        njudb_ast_ = std::make_shared<Explain>((yyvsp[-1].sv_node));
        YYACCEPT;
    }
#line 1782 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 4: /* start: HELP  */
#line 87 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        njudb_ast_ = std::make_shared<Help>();
        YYACCEPT;
    }
#line 1791 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 5: /* start: EXIT  */
#line 92 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        njudb_ast_ = nullptr;
        YYACCEPT;
    }
#line 1800 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 6: /* start: T_EOF  */
#line 97 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        njudb_ast_ = nullptr;
        YYACCEPT;
    }
#line 1809 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 13: /* stmt: %empty  */
#line 110 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
                  { (yyval.sv_node) = nullptr; }
#line 1815 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 14: /* txnStmt: TXN_BEGIN  */
#line 115 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnBegin>();
    }
#line 1823 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 15: /* txnStmt: TXN_COMMIT  */
#line 119 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnCommit>();
    }
#line 1831 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 16: /* txnStmt: TXN_ABORT  */
#line 123 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnAbort>();
    }
#line 1839 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 17: /* txnStmt: TXN_ROLLBACK  */
#line 127 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnRollback>();
    }
#line 1847 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 18: /* logStmt: CREATE STATIC_CHECKPOINT  */
#line 134 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<LogStaticCheckpoint>();
    }
#line 1855 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 19: /* dbStmt: SHOW TABLES  */
#line 140 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<ShowTables>();
    }
#line 1863 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 20: /* dbStmt: CREATE DATABASE IDENTIFIER  */
#line 144 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateDatabase>((yyvsp[0].sv_str));
    }
#line 1871 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 21: /* dbStmt: OPEN DATABASE IDENTIFIER  */
#line 148 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<OpenDatabase>((yyvsp[0].sv_str));
    }
#line 1879 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 22: /* indexStmt: SHOW INDEX ON tbName  */
#line 155 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<ShowIndexes>((yyvsp[0].sv_str));
    }
#line 1887 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 23: /* indexStmt: SHOW INDEX  */
#line 159 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<ShowIndexes>("");
    }
#line 1895 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 24: /* ddl: CREATE TABLE tbName '(' fieldList ')' optStorageModel  */
#line 165 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateTable>((yyvsp[-4].sv_str), (yyvsp[-2].sv_fields), (yyvsp[0].sv_storage_model));
    }
#line 1903 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 25: /* ddl: DROP TABLE tbName  */
#line 169 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropTable>((yyvsp[0].sv_str));
    }
#line 1911 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 26: /* ddl: DESC tbName  */
#line 173 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DescTable>((yyvsp[0].sv_str));
    }
#line 1919 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 27: /* ddl: CREATE INDEX tbName ON tbName '(' colNameList ')' optUsingIndexClause  */
#line 177 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateIndex>((yyvsp[-6].sv_str), (yyvsp[-4].sv_str), (yyvsp[-2].sv_strs), (yyvsp[0].sv_index_type));
    }
#line 1927 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 28: /* ddl: DROP INDEX tbName ON tbName  */
#line 181 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropIndex>((yyvsp[0].sv_str), (yyvsp[-2].sv_str));
    }
#line 1935 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 29: /* optStorageModel: %empty  */
#line 187 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
                  { (yyval.sv_storage_model) = NARY_MODEL; }
#line 1941 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 30: /* optStorageModel: STORAGE '=' NARY  */
#line 189 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    { (yyval.sv_storage_model) = NARY_MODEL; }
#line 1947 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 31: /* optStorageModel: STORAGE '=' PAX  */
#line 191 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    { (yyval.sv_storage_model) = PAX_MODEL; }
#line 1953 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 32: /* dml: INSERT INTO tbName VALUES '(' valueList ')'  */
#line 196 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<InsertStmt>((yyvsp[-4].sv_str), (yyvsp[-1].sv_vals));
    }
#line 1961 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 33: /* dml: DELETE FROM tbName optWhereClause  */
#line 200 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DeleteStmt>((yyvsp[-1].sv_str), (yyvsp[0].sv_conds));
    }
#line 1969 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 34: /* dml: UPDATE tbName SET setClauses optWhereClause  */
#line 204 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<UpdateStmt>((yyvsp[-3].sv_str), (yyvsp[-1].sv_set_clauses), (yyvsp[0].sv_conds));
    }
#line 1977 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 35: /* dml: selectStmt  */
#line 208 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = (yyvsp[0].sv_sel);
    }
#line 1985 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 36: /* selectStmt: SELECT selector FROM tableList optWhereClause optGroupByClause optHavingClause optUsingJoinClause opt_order_clause optLimit  */
#line 215 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_sel) = std::make_shared<SelectStmt>((yyvsp[-8].sv_cols), (yyvsp[-6].sv_node_arr), (yyvsp[-5].sv_conds), (yyvsp[-4].sv_groupby), (yyvsp[-3].sv_conds), (yyvsp[-2].sv_join_strategy), (yyvsp[-1].sv_orderby), (yyvsp[0].sv_int));
    }
#line 1993 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 37: /* optLimit: LIMIT VALUE_INT  */
#line 222 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_int) = (yyvsp[0].sv_int);
    }
#line 2001 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 38: /* optLimit: %empty  */
#line 225 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
                    { (yyval.sv_int) = -1; }
#line 2007 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 39: /* fieldList: field  */
#line 230 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_fields) = std::vector<std::shared_ptr<Field>>{(yyvsp[0].sv_field)};
    }
#line 2015 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 40: /* fieldList: fieldList ',' field  */
#line 234 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_fields).push_back((yyvsp[0].sv_field));
    }
#line 2023 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 41: /* colNameList: colName  */
#line 241 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
#line 2031 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 42: /* colNameList: colNameList ',' colName  */
#line 245 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 2039 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 43: /* field: colName type  */
#line 252 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-1].sv_str), (yyvsp[0].sv_type_len));
    }
#line 2047 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 44: /* type: INT  */
#line 259 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(TYPE_INT, sizeof(int));
    }
#line 2055 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 45: /* type: BOOL  */
#line 263 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(TYPE_BOOL, sizeof(bool));
    }
#line 2063 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 46: /* type: CHAR '(' VALUE_INT ')'  */
#line 267 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(TYPE_STRING, (yyvsp[-1].sv_int));
    }
#line 2071 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 47: /* type: FLOAT  */
#line 271 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(TYPE_FLOAT, sizeof(float));
    }
#line 2079 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 48: /* valueList: value  */
#line 278 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_vals) = std::vector<std::shared_ptr<Value>>{(yyvsp[0].sv_val)};
    }
#line 2087 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 49: /* valueList: valueList ',' value  */
#line 282 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_vals).push_back((yyvsp[0].sv_val));
    }
#line 2095 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 50: /* value: VALUE_INT  */
#line 289 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<IntLit>((yyvsp[0].sv_int));
    }
#line 2103 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 51: /* value: VALUE_FLOAT  */
#line 293 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<FloatLit>((yyvsp[0].sv_float));
    }
#line 2111 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 52: /* value: VALUE_STRING  */
#line 297 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<StringLit>((yyvsp[0].sv_str));
    }
#line 2119 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 53: /* value: VALUE_BOOL  */
#line 301 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<BoolLit>((yyvsp[0].sv_bool));
    }
#line 2127 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 54: /* value: %empty  */
#line 305 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_val) = std::make_shared<NullLit>();
    }
#line 2135 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 55: /* colListWithoutAlias: col  */
#line 312 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_cols) = std::vector<std::shared_ptr<Col>>{(yyvsp[0].sv_col)};
    }
#line 2143 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 56: /* colListWithoutAlias: colListWithoutAlias ',' col  */
#line 316 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_cols).push_back((yyvsp[0].sv_col));
    }
#line 2151 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 57: /* optGroupByClause: %empty  */
#line 322 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
                      { /* ignore*/ }
#line 2157 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 58: /* optGroupByClause: GROUP BY colListWithoutAlias  */
#line 324 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_groupby) = std::make_shared<GroupBy>((yyvsp[0].sv_cols));
    }
#line 2165 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 59: /* condition: col op expr  */
#line 331 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<BinaryExpr>((yyvsp[-2].sv_col), (yyvsp[-1].sv_comp_op), (yyvsp[0].sv_expr));
    }
#line 2173 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 60: /* condition: col op '(' selectStmt ')'  */
#line 335 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<BinaryExpr>((yyvsp[-4].sv_col), (yyvsp[-3].sv_comp_op), (yyvsp[-1].sv_sel));
    }
#line 2181 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 61: /* condition: col IN '(' selectStmt ')'  */
#line 339 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<BinaryExpr>((yyvsp[-4].sv_col), OP_IN, (yyvsp[-1].sv_sel));
    }
#line 2189 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 62: /* condition: col IN '(' valueList ')'  */
#line 343 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        auto arr = std::make_shared<ArrLit>((yyvsp[-1].sv_vals));
        (yyval.sv_cond) = std::make_shared<BinaryExpr>((yyvsp[-4].sv_col), OP_IN, arr);
    }
#line 2198 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 63: /* optWhereClause: %empty  */
#line 350 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
                      { /* ignore*/ }
#line 2204 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 64: /* optWhereClause: WHERE whereClause  */
#line 352 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_conds) = (yyvsp[0].sv_conds);
    }
#line 2212 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 65: /* optUsingIndexClause: %empty  */
#line 358 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
                  { (yyval.sv_index_type) = BPTREE; }
#line 2218 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 66: /* optUsingIndexClause: USING INDEX_BPTREE  */
#line 359 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
                         { (yyval.sv_index_type) = BPTREE; }
#line 2224 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 67: /* optUsingIndexClause: USING HASH_KWD  */
#line 360 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
                     { (yyval.sv_index_type) = HASH; }
#line 2230 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 68: /* optUsingJoinClause: %empty  */
#line 363 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
                  {(yyval.sv_join_strategy) = NESTED_LOOP;}
#line 2236 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 69: /* optUsingJoinClause: USING LOOP  */
#line 365 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {   (yyval.sv_join_strategy) = NESTED_LOOP;  }
#line 2242 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 70: /* optUsingJoinClause: USING MERGE  */
#line 367 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {   (yyval.sv_join_strategy) = SORT_MERGE;  }
#line 2248 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 71: /* optUsingJoinClause: USING HASH_KWD  */
#line 369 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {   (yyval.sv_join_strategy) = HASH_JOIN;  }
#line 2254 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 72: /* conditionAgg: aggCol op value  */
#line 373 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<BinaryExpr>((yyvsp[-2].sv_col), (yyvsp[-1].sv_comp_op), (yyvsp[0].sv_val));
    }
#line 2262 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 73: /* optHavingClause: %empty  */
#line 380 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
                      { /* ignore*/ }
#line 2268 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 74: /* optHavingClause: HAVING havingClause  */
#line 382 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_conds) = (yyvsp[0].sv_conds);
    }
#line 2276 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 75: /* havingClause: condition  */
#line 388 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_conds) = std::vector<std::shared_ptr<BinaryExpr>>{(yyvsp[0].sv_cond)};
    }
#line 2284 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 76: /* havingClause: conditionAgg  */
#line 392 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_conds) = std::vector<std::shared_ptr<BinaryExpr>>{(yyvsp[0].sv_cond)};
    }
#line 2292 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 77: /* havingClause: havingClause AND condition  */
#line 396 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_conds).push_back((yyvsp[0].sv_cond));
    }
#line 2300 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 78: /* havingClause: havingClause AND conditionAgg  */
#line 400 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_conds).push_back((yyvsp[0].sv_cond));
    }
#line 2308 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 79: /* whereClause: condition  */
#line 408 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_conds) = std::vector<std::shared_ptr<BinaryExpr>>{(yyvsp[0].sv_cond)};
    }
#line 2316 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 80: /* whereClause: whereClause AND condition  */
#line 412 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_conds).push_back((yyvsp[0].sv_cond));
    }
#line 2324 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 81: /* col: tbName '.' colName  */
#line 419 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::make_shared<Col>((yyvsp[-2].sv_str), (yyvsp[0].sv_str));
    }
#line 2332 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 82: /* col: colName  */
#line 423 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::make_shared<Col>("", (yyvsp[0].sv_str));
    }
#line 2340 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 83: /* aggCol: COUNT '(' col ')'  */
#line 430 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::make_shared<AggCol>((yyvsp[-1].sv_col), AGG_COUNT);
    }
#line 2348 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 84: /* aggCol: SUM '(' col ')'  */
#line 434 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::make_shared<AggCol>((yyvsp[-1].sv_col), AGG_SUM);
    }
#line 2356 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 85: /* aggCol: AVG '(' col ')'  */
#line 438 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::make_shared<AggCol>((yyvsp[-1].sv_col), AGG_AVG);
    }
#line 2364 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 86: /* aggCol: MAX '(' col ')'  */
#line 442 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::make_shared<AggCol>((yyvsp[-1].sv_col), AGG_MAX);
    }
#line 2372 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 87: /* aggCol: MIN '(' col ')'  */
#line 446 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_col) = std::make_shared<AggCol>((yyvsp[-1].sv_col), AGG_MIN);
    }
#line 2380 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 88: /* aggCol: COUNT '(' '*' ')'  */
#line 450 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        auto col = std::make_shared<Col>("", "*");
        (yyval.sv_col) = std::make_shared<AggCol>(col, AGG_COUNT_STAR);
    }
#line 2389 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 89: /* colList: col optAlias  */
#line 458 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_cols) = std::vector<std::shared_ptr<Col>>{(yyvsp[-1].sv_col)};
        (yyval.sv_cols)[0]->setAlias((yyvsp[0].sv_str));
    }
#line 2398 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 90: /* colList: aggCol optAlias  */
#line 463 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_cols) = std::vector<std::shared_ptr<Col>>{(yyvsp[-1].sv_col)};
        (yyval.sv_cols)[0]->setAlias((yyvsp[0].sv_str));
    }
#line 2407 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 91: /* colList: colList ',' col optAlias  */
#line 468 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_cols).push_back((yyvsp[-1].sv_col));
        (yyval.sv_cols).back()->setAlias((yyvsp[0].sv_str));
    }
#line 2416 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 92: /* colList: colList ',' aggCol optAlias  */
#line 473 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_cols).push_back((yyvsp[-1].sv_col));
        (yyval.sv_cols).back()->setAlias((yyvsp[0].sv_str));
    }
#line 2425 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 93: /* optAlias: AS colName  */
#line 481 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_str) = (yyvsp[0].sv_str);
    }
#line 2433 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 94: /* optAlias: %empty  */
#line 484 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
                      { (yyval.sv_str) = ""; }
#line 2439 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 95: /* op: '='  */
#line 489 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = OP_EQ;
    }
#line 2447 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 96: /* op: '<'  */
#line 493 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = OP_LT;
    }
#line 2455 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 97: /* op: '>'  */
#line 497 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = OP_GT;
    }
#line 2463 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 98: /* op: NEQ  */
#line 501 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = OP_NE;
    }
#line 2471 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 99: /* op: LEQ  */
#line 505 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = OP_LE;
    }
#line 2479 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 100: /* op: GEQ  */
#line 509 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_comp_op) = OP_GE;
    }
#line 2487 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 101: /* expr: value  */
#line 516 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_val));
    }
#line 2495 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 102: /* expr: col  */
#line 520 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_col));
    }
#line 2503 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 103: /* setClauses: setClause  */
#line 527 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_set_clauses) = std::vector<std::shared_ptr<SetClause>>{(yyvsp[0].sv_set_clause)};
    }
#line 2511 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 104: /* setClauses: setClauses ',' setClause  */
#line 531 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_set_clauses).push_back((yyvsp[0].sv_set_clause));
    }
#line 2519 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 105: /* setClause: colName '=' value  */
#line 538 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-2].sv_str), (yyvsp[0].sv_val));
    }
#line 2527 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 106: /* selector: '*'  */
#line 545 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_cols) = {};
    }
#line 2535 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 108: /* table: tbName  */
#line 553 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<ExplicitTable>((yyvsp[0].sv_str));
    }
#line 2543 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 109: /* table: '(' selectStmt ')'  */
#line 557 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = (yyvsp[-1].sv_sel);
    }
#line 2551 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 110: /* table: tbName JOIN tbName  */
#line 561 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<JoinExpr>((yyvsp[-2].sv_str), (yyvsp[0].sv_str), INNER_JOIN);
    }
#line 2559 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 111: /* table: tbName INNER JOIN tbName  */
#line 565 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<JoinExpr>((yyvsp[-3].sv_str), (yyvsp[0].sv_str), INNER_JOIN);
    }
#line 2567 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 112: /* table: tbName OUTER JOIN tbName  */
#line 569 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node) = std::make_shared<JoinExpr>((yyvsp[-3].sv_str), (yyvsp[0].sv_str), OUTER_JOIN);
    }
#line 2575 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 113: /* tableList: table  */
#line 576 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node_arr) = std::vector<std::shared_ptr<TreeNode>>{(yyvsp[0].sv_node)};
    }
#line 2583 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 114: /* tableList: tableList ',' table  */
#line 580 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_node_arr).push_back((yyvsp[0].sv_node));
    }
#line 2591 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 115: /* opt_order_clause: ORDER BY order_clause  */
#line 587 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_orderby) = (yyvsp[0].sv_orderby);
    }
#line 2599 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 116: /* opt_order_clause: %empty  */
#line 590 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
                      { /* ignore*/ }
#line 2605 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 117: /* order_clause: opt_asc_desc colListWithoutAlias  */
#line 595 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
    {
        (yyval.sv_orderby) = std::make_shared<OrderBy>((yyvsp[-1].sv_orderby_dir), (yyvsp[0].sv_cols));
    }
#line 2613 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 118: /* opt_asc_desc: ASC  */
#line 601 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
                    { (yyval.sv_orderby_dir) = OrderBy_ASC;     }
#line 2619 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 119: /* opt_asc_desc: DESC  */
#line 602 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
                    { (yyval.sv_orderby_dir) = OrderBy_DESC;    }
#line 2625 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;

  case 120: /* opt_asc_desc: %empty  */
#line 603 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"
                    { (yyval.sv_orderby_dir) = OrderBy_ASC; }
#line 2631 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"
    break;


#line 2635 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.tab.cpp"

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
  *++yylsp = yyloc;

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
  yyerror (&yylloc, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 609 "/home/lwy/DatabaseNJU/NJU_DBPractice/src/parser/yacc.y"

