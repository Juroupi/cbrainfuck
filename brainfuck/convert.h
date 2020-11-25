#ifndef __CBRAINFUCK_CONVERT_H__
#define __CBRAINFUCK_CONVERT_H__

typedef struct {

	int (*inc_ptr)(int x);

	int (*inc_val)(int x);

	int (*put_char)(char c);

	char (*get_char)();

	int (*loop_start)();

	int (*loop_end)();

} bf_convert_st;

int bf_convert(const bf_convert_st* bf, const char* code);

#endif