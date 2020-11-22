#ifndef __BRAINFUCK_H__
#define __BRAINFUCK_H__

typedef struct {

	unsigned char* array;

	unsigned char* array_end;

	unsigned char* array_ptr;

	char** jmp_stack;

	char** jmp_stack_end;

	char** jmp_stack_top;

} brainfuck_st;

int bf_init(brainfuck_st* bf, unsigned int array_size);

int bf_exec(brainfuck_st* bf, const char* code);

void bf_clear(brainfuck_st* bf);

#endif