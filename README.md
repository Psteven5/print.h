# print.h
Convenient print macros with user extensibility

# Usage
print.h exposes four macros to the user (WRITE, WRITELN, PRINT, PRINTLN), to write to a stream with or without newline, or to default to stdout.

The macros are overloaded with _Generic (C11) to print default types, but they are extendable through providing your own functions. If C11 is not used, this extendability is preserved, but the macros will not be overloaded for default types, only strings.

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
	PRINTLN((Vector2), " + ", s, " = ", (Vector2), (v, w));
}
```
```
(1, 2) + 0.5 = (1.5, 2.5)
```
