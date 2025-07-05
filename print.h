#ifndef PRINT_H_
#define PRINT_H_

#include <float.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#define WRITE(Stream, ...) do { \
	_Pragma("GCC diagnostic push"); \
	_Pragma("GCC diagnostic ignored \"-Wformat\""); \
	FILE *const PRINT_WRITE_STREAM_ = (Stream); \
	PRINT_IF_(PRINT_IS_PACK_     (PRINT_LAST_(__VA_ARGS__))) ( \
		PRINT_EVAL_(PRINT_WRITE0_(PRINT_LAST_(__VA_ARGS__), __VA_ARGS__)) \
	) ( \
		PRINT_EVAL_(PRINT_WRITE3_(__VA_ARGS__)) \
	) \
	_Pragma("GCC diagnostic pop"); \
} while (0)
#define WRITELN(Stream, ...) do { \
	FILE *const PRINT_WRITELN_STREAM_ = (Stream); \
	__VA_OPT__(WRITE(PRINT_WRITELN_STREAM_, __VA_ARGS__);) \
	fputc('\n', PRINT_WRITELN_STREAM_); \
} while (0)
#define PRINT(...)   WRITE  (stdout, __VA_ARGS__)
#define PRINTLN(...) WRITELN(stdout, __VA_ARGS__)

#define PRINT_WRITE0_(Args, X, Peek, ...) PRINT_IF_(PRINT_IS_PACK_(X)) ( \
	PRINT_CONCAT_(write, PRINT_HEAD_ X) \
		(PRINT_WRITE_STREAM_, PRINT_HEAD_ Args); \
) ( \
	PRINT_WRITE1_(PRINT_WRITE_STREAM_, X) \
) __VA_OPT__(PRINT_DEFER_(PRINT_WRITE2_)()(PRINT_IF_(PRINT_IS_PACK_(X)) ( \
	(PRINT_TAIL_ Args) \
) ( \
	Args \
), Peek, __VA_ARGS__))
#define PRINT_WRITE1_(S, X) _Generic((X), \
	int8_t      : fprintf(S, "%"  PRIi8,                     (X)), \
	uint8_t     : fprintf(S, "%"  PRIu8,                     (X)), \
	int16_t     : fprintf(S, "%"  PRIi16,                    (X)), \
	uint16_t    : fprintf(S, "%"  PRIu16,                    (X)), \
	int32_t     : fprintf(S, "%"  PRIi32,                    (X)), \
	uint32_t    : fprintf(S, "%"  PRIu32,                    (X)), \
	int64_t     : fprintf(S, "%"  PRIi64,                    (X)), \
	uint64_t    : fprintf(S, "%"  PRIu64,                    (X)), \
	float       : fprintf(S, "%." PRINT_STR_(FLT_DIG)  "g",  (X)), \
	double      : fprintf(S, "%." PRINT_STR_(DBL_DIG)  "lg", (X)), \
	long double : fprintf(S, "%." PRINT_STR_(LDBL_DIG) "Lg", (X)), \
	_Bool       : fprintf(S,              (X) ? "true" : "false"), \
	char        : fprintf(S, "%c",                           (X)), \
	char       *: fprintf(S, "%s",                           (X)), \
	char const *: fprintf(S, "%s",                           (X)), \
	default     : fprintf(S, "%p",                           (X)));
#define PRINT_WRITE2_() PRINT_WRITE0_
#define PRINT_WRITE3_(X, ...) \
	PRINT_WRITE1_(PRINT_WRITE_STREAM_, X) \
__VA_OPT__ ( \
	PRINT_DEFER_(PRINT_WRITE4_)()(__VA_ARGS__) \
)
#define PRINT_WRITE4_() PRINT_WRITE3_

#define PRINT_CONCAT_(X, ...)  PRINT_CONCAT__(X, __VA_ARGS__)
#define PRINT_CONCAT__(X, ...) X ## __VA_ARGS__
#define PRINT_DEFER_(Macro)    Macro PRINT_EMPTY_()
#define PRINT_ELSE0_(...)
#define PRINT_ELSE1_(...)      __VA_ARGS__
#define PRINT_EMPTY_() 
#define PRINT_EVAL_(...)       PRINT_EVAL0_(__VA_ARGS__)
#define PRINT_EVAL0_(...)      PRINT_EVAL1_(PRINT_EVAL1_(PRINT_EVAL1_(__VA_ARGS__)))
#define PRINT_EVAL1_(...)      PRINT_EVAL2_(PRINT_EVAL2_(PRINT_EVAL2_(__VA_ARGS__)))
#define PRINT_EVAL2_(...)      PRINT_EVAL3_(PRINT_EVAL3_(PRINT_EVAL3_(__VA_ARGS__)))
#define PRINT_EVAL3_(...)      PRINT_EVAL4_(PRINT_EVAL4_(PRINT_EVAL4_(__VA_ARGS__)))
#define PRINT_EVAL4_(...)      PRINT_EVAL5_(PRINT_EVAL5_(PRINT_EVAL5_(__VA_ARGS__)))
#define PRINT_EVAL5_(...)      __VA_ARGS__
#define PRINT_HEAD_(X, ...)    X
#define PRINT_IF_(...)         PRINT_CONCAT_ ( \
	PRINT_CONCAT_(PRINT_IF, __VA_ARGS__), _)
#define PRINT_IF0_(...)        PRINT_ELSE1_
#define PRINT_IF1_(...)        __VA_ARGS__ PRINT_ELSE0_
#define PRINT_IS_PACK_(X)      PRINT_IS_PACK0_(PRINT_IS_PACK1_ X)
#define PRINT_IS_PACK0_(...)   PRINT_SND_(__VA_ARGS__, 0,)
#define PRINT_IS_PACK1_(...)   ~, 1
#define PRINT_LAST_(...)       PRINT_EVAL_(PRINT_LAST0_(__VA_ARGS__))
#define PRINT_LAST0_(X, ...)   PRINT_VA_OPT_(__VA_OPT__(1), \
	X \
) __VA_OPT__ ( \
	PRINT_DEFER_(PRINT_LAST1_)()(__VA_ARGS__) \
)
#define PRINT_LAST1_()         PRINT_LAST0_
#define PRINT_SND_(X, Y, ...)  Y
#define PRINT_STR_(...)        PRINT_STR__(__VA_ARGS__)
#define PRINT_STR__(...)       #__VA_ARGS__
#define PRINT_TAIL_(_, ...)    __VA_ARGS__ 
#define PRINT_VA_OPT_(Cond, ...) PRINT_CONCAT_ ( \
	PRINT_CONCAT_(PRINT_VA_OPT, Cond), __)(__VA_ARGS__)
#define PRINT_VA_OPT__(...)    __VA_ARGS__
#define PRINT_VA_OPT0__(...)   __VA_ARGS__
#define PRINT_VA_OPT1__(...)

#endif
