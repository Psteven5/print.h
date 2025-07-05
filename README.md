# print.h
Convenient print macros with user extensibility (C23, GNU-C)

# Usage
print.h exposes four macros to the user (WRITE, WRITELN, PRINT, PRINTLN), to write to a stream with or without newline, or to default to stdout.

The macros are overloaded with _Generic (C11) to print default types, but they are extendable through providing your own functions.

Here is a simple example:

```c
#include "print.h"

typedef struct {
	float x, y;
} Vector2;

static inline void writeVector2(FILE *restrict stream, Vector2 v)
{
	// writing is overloaded on basic types
	WRITE(stream, "(", v.x, ", ", v.y, ")");
}

int main(void)
{
	Vector2 v = {1.f, 2.f};
	float   s = 0.5f;
	Vector2 w = {s + v.x, s + v.y};
	// but custom types need callbacks (enclosed) and a tuple as the last argument
	PRINTLN(s, " + ", (Vector2) , " = ", (Vector2), (v, w));
}
```

Compilation is limited to C23, because the macros use \__VA_OPT__ for detecting the end of variadic arguments and for allowing zero arguments to WRITELN and PRINTLN (to easily print a newline).

Additionally, only GNU-C compliant compilers are supported for now as the macros use GCC pragmas to silence formatting warnings. This is not a security risk; it is only necessary because _Generic evaluates every branch during compilation.
