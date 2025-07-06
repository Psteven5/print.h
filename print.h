#ifndef PRINT_H_
#define PRINT_H_

#include <float.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#define WRITE(Stream, ...) do { \
	FILE *const PRINT_WRITE_STREAM_ = (Stream); \
	PRINT_IF_(PRINT_IS_PACK_     (PRINT_LAST_(__VA_ARGS__))) ( \
		PRINT_EVAL_(PRINT_WRITE0_(PRINT_LAST_(__VA_ARGS__), __VA_ARGS__)) \
	) ( \
		PRINT_EVAL_(PRINT_WRITE3_(__VA_ARGS__)) \
	) \
} while (0)
#define WRITELN(Stream, ...) do { \
	FILE *const PRINT_WRITELN_STREAM_ = (Stream); \
	PRINT_IF_(PRINT_NO_ARGS_(__VA_ARGS__))()(WRITE(PRINT_WRITELN_STREAM_, __VA_ARGS__);) \
	fputc('\n', PRINT_WRITELN_STREAM_); \
} while (0)
#define PRINT(...)   WRITE  (stdout, __VA_ARGS__)
#define PRINTLN(...) WRITELN(stdout, __VA_ARGS__)

#define PRINT_WRITE0_(Args, X, Peek, ...) PRINT_IF_(PRINT_IS_PACK_(X)) ( \
	PRINT_CONCAT_(write, PRINT_HEAD_ X) \
		(PRINT_WRITE_STREAM_, PRINT_HEAD_ Args); \
) ( \
	PRINT_WRITE1_(PRINT_WRITE_STREAM_, X) \
) PRINT_IF_(PRINT_NO_ARGS_(__VA_ARGS__))() ( \
	PRINT_DEFER_ PRINT_EMPTY_()(PRINT_WRITE2_)() ( \
		PRINT_IF_(PRINT_IS_PACK_(X)) ( \
			(PRINT_TAIL_ Args) \
		) ( \
			Args \
		), Peek, __VA_ARGS__))
#if defined(__STDC__) && defined(__STDC_VERSION__)
#if 201112L <= __STDC_VERSION__
	#define PRINT_WRITE1_(S, X) _Generic((X), \
	int8_t      : fprintf(S, "%"  PRIi8,                     _Generic((X), int8_t      : X, default : (int8_t)      0)), \
	uint8_t     : fprintf(S, "%"  PRIu8,                     _Generic((X), uint8_t     : X, default : (uint8_t)     0)), \
	int16_t     : fprintf(S, "%"  PRIi16,                    _Generic((X), int16_t     : X, default : (int16_t)     0)), \
	uint16_t    : fprintf(S, "%"  PRIu16,                    _Generic((X), uint16_t    : X, default : (uint16_t)    0)), \
	int32_t     : fprintf(S, "%"  PRIi32,                    _Generic((X), int32_t     : X, default : (int32_t)     0)), \
	uint32_t    : fprintf(S, "%"  PRIu32,                    _Generic((X), uint32_t    : X, default : (uint32_t)    0)), \
	int64_t     : fprintf(S, "%"  PRIi64,                    _Generic((X), int64_t     : X, default : (int64_t)     0)), \
	uint64_t    : fprintf(S, "%"  PRIu64,                    _Generic((X), uint64_t    : X, default : (uint64_t)    0)), \
	float       : fprintf(S, "%." PRINT_STR_(FLT_DIG)  "g",  _Generic((X), float       : X, default : (float)       0)), \
	double      : fprintf(S, "%." PRINT_STR_(DBL_DIG)  "lg", _Generic((X), double      : X, default : (double)      0)), \
	long double : fprintf(S, "%." PRINT_STR_(LDBL_DIG) "Lg", _Generic((X), long double : X, default : (long double) 0)), \
	_Bool       : fputs  (                                                                      (X) ? "true" : "false", S), \
	char        : fputc  (                                   _Generic((X), char        : X, default : (char)        0), S), \
	char       *: fputs  (                                   _Generic((X), char       *: X, default : (char       *)0), S), \
	char const *: fputs  (                                   _Generic((X), char const *: X, default : (char const *)0), S), \
	default     : fprintf(S, "%p",                                                      (void const *)(uintptr_t) (X)));
#endif
#endif
#ifndef PRINT_WRITE1_
		#define PRINT_WRITE1_(S, X) fputs(X, S);
#endif
#define PRINT_WRITE2_() PRINT_WRITE0_
#define PRINT_WRITE3_(X, ...) \
	PRINT_WRITE1_(PRINT_WRITE_STREAM_, X) \
PRINT_IF_(PRINT_NO_ARGS_(__VA_ARGS__))() ( \
	PRINT_DEFER_ PRINT_EMPTY_()(PRINT_WRITE4_)()(__VA_ARGS__) \
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
#ifdef _MSC_VER_
	#define PRINT_EVAL5_(...)  PRINT_EVAL6_(PRINT_EVAL6_(__VA_ARGS__))
	#define PRINT_EVAL6_(...)  __VA_ARGS__
#else
	#define PRINT_EVAL5_(...)  __VA_ARGS__
#endif
#define PRINT_HEAD_(X, ...)    X
#define PRINT_IF_(...)         PRINT_CONCAT_ ( \
	PRINT_CONCAT_(PRINT_IF, __VA_ARGS__), _)
#define PRINT_IF0_(...)        PRINT_ELSE1_
#define PRINT_IF1_(...)        __VA_ARGS__ PRINT_ELSE0_
#define PRINT_IS_PACK_(X)      PRINT_IS_PACK0_(PRINT_IS_PACK1_ X)
#define PRINT_IS_PACK0_(...)   PRINT_SND_(__VA_ARGS__, 0,)
#define PRINT_IS_PACK1_(...)   ~, 1
#define PRINT_LAST_(...)       PRINT_EVAL_(PRINT_LAST0_(__VA_ARGS__))
#define PRINT_LAST0_(X, ...)   PRINT_IF_(PRINT_NO_ARGS_(__VA_ARGS__)) ( \
	X \
) ( \
	PRINT_DEFER_ PRINT_EMPTY_()(PRINT_LAST1_)()(__VA_ARGS__) \
)
#define PRINT_LAST1_()         PRINT_LAST0_
#define PRINT_NO_ARGS_(...) PRINT_IS_PACK_ ( \
	PRINT_IF_(PRINT_IS_PACK_(PRINT_HEAD_(__VA_ARGS__)))(~)( \
		PRINT_HEAD_(__VA_ARGS__) \
	)())
#define PRINT_SND_(X, Y, ...)  Y
#define PRINT_STR_(...)        PRINT_STR__(__VA_ARGS__)
#define PRINT_STR__(...)       #__VA_ARGS__
#define PRINT_TAIL_(_, ...)    __VA_ARGS__ 

#endif
