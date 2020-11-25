#include "brainfuck.h"

#include <stdio.h>
#include <stdlib.h>


int bf_init(brainfuck_st* bf, unsigned int array_size) {
	
	static const size_t jmp_stack_size = 16;

	if (array_size == 0) {
		return 0;
	}

	bf->array = calloc((size_t)array_size, 1);
	if (bf->array == NULL) {
		return 0;
	}
	bf->array_end = bf->array + array_size;
	bf->array_ptr = bf->array;

	bf->jmp_stack = malloc(sizeof(char*) * jmp_stack_size);
	if (bf->jmp_stack == NULL) {
		free(bf->array);
		return 0;
	}
	bf->jmp_stack_end = bf->jmp_stack + jmp_stack_size;
	bf->jmp_stack_top = bf->jmp_stack;

	return 1;
}


static int increase_stack_size(brainfuck_st* bf) {

	size_t new_jmp_stack_size = (bf->jmp_stack_end - bf->jmp_stack) * 2;

	char** new_jmp_stack = realloc(bf->jmp_stack, sizeof(char*) * new_jmp_stack_size);
	if (new_jmp_stack == NULL) {
		return 0;
	}

	size_t stack_top_offset = bf->jmp_stack_top - bf->jmp_stack;

	bf->jmp_stack = new_jmp_stack;
	bf->jmp_stack_end = bf->jmp_stack + new_jmp_stack_size;
	bf->jmp_stack_top = bf->jmp_stack + stack_top_offset;

	return 1;
}


int bf_exec(brainfuck_st* bf, const char* code) {

	int ret = BF_OK;

	char c;
	
	while ((c = *code) != '\0') {

		if (c == '+') {
			++(*bf->array_ptr);
		}

		else if (c == '-') {
			--(*bf->array_ptr);
		}

		else if (c == '>') {

			if (++bf->array_ptr == bf->array_end) {
				--bf->array_ptr, ret = BF_POINTER;
				break;
			}
		}

		else if (c == '<') {

			if (--bf->array_ptr < bf->array) {
				++bf->array_ptr, ret = BF_POINTER;
				break;
			}
		}

		else if (c == '.') {
			putchar(*bf->array_ptr);
		}

		else if (c == ',') {
			*bf->array_ptr = getchar();
		}

		else if (c == '[') {

			if (*bf->array_ptr) {

				if (bf->jmp_stack_top == bf->jmp_stack_end && !increase_stack_size(bf)) {
					ret = BF_ALLOC;
					break;
				}

				*bf->jmp_stack_top++ = (char*)code;
			}
			
			else {

				unsigned int tmp_stack_count = 1;

				do {

					c = *(++code);

					if (c == '[') {
						++tmp_stack_count;
					}

					else if (c == ']') {
						--tmp_stack_count;
					}
					
					else if (c == '\0') {
						--code, ret = BF_BRACKET;
						break;
					}

				} while (tmp_stack_count != 0);
			}
		}

		else if (c == ']') {

			if (bf->jmp_stack_top == bf->jmp_stack) {
				ret = BF_BRACKET;
				break;
			}

			--bf->jmp_stack_top;

			if (*bf->array_ptr) {
				code = *bf->jmp_stack_top++;
			}
		}

		++code;
	}

	if (bf->jmp_stack_top > bf->jmp_stack && ret == BF_OK) {
		ret = BF_BRACKET;
	}

	bf->jmp_stack_top = bf->jmp_stack;

	return ret;
}


void bf_clear(brainfuck_st* bf) {
	free(bf->array);
	free(bf->jmp_stack);
}