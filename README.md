# cbrainfuck
Interpret Brainfuck in C

```c
#include "brainfuck.h"

int main(int argc, char* argv[]) {

	const char* code = ">+[++[++>]<<+]>+.+++.---.";

	brainfuck_st bf;

	bf_init(&bf, 1000);

	bf_exec(&bf, code);

	bf_clear(&bf);

	return 0;
}
```

