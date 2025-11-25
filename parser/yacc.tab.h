/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_HOME_LWY_DATABASENJU_NJU_DBPRACTICE_SRC_PARSER_YACC_TAB_H_INCLUDED
# define YY_YY_HOME_LWY_DATABASENJU_NJU_DBPRACTICE_SRC_PARSER_YACC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    EXPLAIN = 258,                 /* EXPLAIN  */
    SHOW = 259,                    /* SHOW  */
    TABLES = 260,                  /* TABLES  */
    CREATE = 261,                  /* CREATE  */
    TABLE = 262,                   /* TABLE  */
    DROP = 263,                    /* DROP  */
    DESC = 264,                    /* DESC  */
    INSERT = 265,                  /* INSERT  */
    INTO = 266,                    /* INTO  */
    VALUES = 267,                  /* VALUES  */
    DELETE = 268,                  /* DELETE  */
    FROM = 269,                    /* FROM  */
    OPEN = 270,                    /* OPEN  */
    DATABASE = 271,                /* DATABASE  */
    ON = 272,                      /* ON  */
    ASC = 273,                     /* ASC  */
    AS = 274,                      /* AS  */
    ORDER = 275,                   /* ORDER  */
    GROUP = 276,                   /* GROUP  */
    BY = 277,                      /* BY  */
    SUM = 278,                     /* SUM  */
    AVG = 279,                     /* AVG  */
    MAX = 280,                     /* MAX  */
    MIN = 281,                     /* MIN  */
    COUNT = 282,                   /* COUNT  */
    IN = 283,                      /* IN  */
    STATIC_CHECKPOINT = 284,       /* STATIC_CHECKPOINT  */
    USING = 285,                   /* USING  */
    LOOP = 286,                    /* LOOP  */
    MERGE = 287,                   /* MERGE  */
    INDEX_BPTREE = 288,            /* INDEX_BPTREE  */
    HASH_KWD = 289,                /* HASH_KWD  */
    WHERE = 290,                   /* WHERE  */
    HAVING = 291,                  /* HAVING  */
    UPDATE = 292,                  /* UPDATE  */
    SET = 293,                     /* SET  */
    SELECT = 294,                  /* SELECT  */
    INT = 295,                     /* INT  */
    CHAR = 296,                    /* CHAR  */
    FLOAT = 297,                   /* FLOAT  */
    BOOL = 298,                    /* BOOL  */
    INDEX = 299,                   /* INDEX  */
    AND = 300,                     /* AND  */
    JOIN = 301,                    /* JOIN  */
    INNER = 302,                   /* INNER  */
    OUTER = 303,                   /* OUTER  */
    EXIT = 304,                    /* EXIT  */
    HELP = 305,                    /* HELP  */
    TXN_BEGIN = 306,               /* TXN_BEGIN  */
    TXN_COMMIT = 307,              /* TXN_COMMIT  */
    TXN_ABORT = 308,               /* TXN_ABORT  */
    TXN_ROLLBACK = 309,            /* TXN_ROLLBACK  */
    ORDER_BY = 310,                /* ORDER_BY  */
    ENABLE_NESTLOOP = 311,         /* ENABLE_NESTLOOP  */
    ENABLE_SORTMERGE = 312,        /* ENABLE_SORTMERGE  */
    STORAGE = 313,                 /* STORAGE  */
    PAX = 314,                     /* PAX  */
    NARY = 315,                    /* NARY  */
    LIMIT = 316,                   /* LIMIT  */
    LEQ = 317,                     /* LEQ  */
    NEQ = 318,                     /* NEQ  */
    GEQ = 319,                     /* GEQ  */
    T_EOF = 320,                   /* T_EOF  */
    IDENTIFIER = 321,              /* IDENTIFIER  */
    VALUE_STRING = 322,            /* VALUE_STRING  */
    VALUE_INT = 323,               /* VALUE_INT  */
    VALUE_FLOAT = 324,             /* VALUE_FLOAT  */
    VALUE_BOOL = 325               /* VALUE_BOOL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (void);


#endif /* !YY_YY_HOME_LWY_DATABASENJU_NJU_DBPRACTICE_SRC_PARSER_YACC_TAB_H_INCLUDED  */
