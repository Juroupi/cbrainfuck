#include "brainfuck.h"

#include <stdlib.h>

int bf_init(brainfuck_st* bf, unsigned int array_size) {
	
	bf->array_size = array_size;

	bf->array = malloc((size_t)bf->array_size);
	if (bf->array == NULL) {
		return 0;
	}

	bf->ptr = bf->array;

	return 1;
}

void bf_clear(brainfuck_st* bf) {
	free(bf->array);
}