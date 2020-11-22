#ifndef __BRAINFUCK_H__
#define __BRAINFUCK_H__

typedef struct {

	unsigned int array_size;

	unsigned char* array;

	unsigned char* ptr;

} brainfuck_st;

int bf_init(brainfuck_st* bf, unsigned int array_size);

int bf_exec(brainfuck_st* bf, char* code);

void bf_clear(brainfuck_st* bf);

#endif