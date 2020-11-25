# cbrainfuck
Brainfuck in C

### Interpret Brainfuck

```c
#include "brainfuck/exec.h"

int main(int argc, char* argv[]) {

	const char* code = ">+[++[++>]<<+]>+.+++.---.";

	bf_exec_st bf;

	bf_exec_init(&bf, 1000);

	bf_exec(&bf, code);

	bf_exec_clear(&bf);

	return 0;
}
```

