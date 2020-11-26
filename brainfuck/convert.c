#include "convert.h"


static int inc_ptr(const bf_convert_st* bf, int* inc) {
	
	if (inc != 0) {

		if (!bf->inc_ptr(inc)) {
			return 0;
		}

		inc = 0;
	}

	return 1;
}


static int inc_val(const bf_convert_st* bf, int* inc) {
	
	if (inc != 0) {
		
		if (!bf->inc_val(inc)) {
			return 0;
		}

		inc = 0;
	}

	return 1;
}


int bf_convert(const bf_convert_st* bf, const char* code) {
	
	int ptr_inc = 0, val_inc = 0;

	char c;

	while ((c = *code++) != '\0') {

		if (c == '+') {

			if (!inc_ptr(bf, &ptr_inc)) {
				return 0;
			}

			val_inc++;
		}

		else if (c == '-') {

			if (!inc_ptr(bf, &ptr_inc)) {
				return 0;
			}

			val_inc--;
		}

		else if (c == '>') {

			if (!inc_val(bf, &val_inc)) {
				return 0;
			}

			ptr_inc++;
		}

		else if (c == '<') {

			if (!inc_val(bf, &val_inc)) {
				return 0;
			}

			ptr_inc--;
		}

		else if (c == '.') {

			if (!inc_val(bf, &val_inc) || !inc_ptr(bf, &ptr_inc)) {
				return 0;
			}

			bf->put_char();
		}

		else if (c == ',') {

			if (!inc_val(bf, &val_inc) || !inc_ptr(bf, &ptr_inc)) {
				return 0;
			}

			bf->get_char();
		}

		else if (c == '[') {

			if (!inc_val(bf, &val_inc) || !inc_ptr(bf, &ptr_inc)) {
				return 0;
			}

			bf->loop_start();
		}

		else if (c == ']') {

			if (!inc_val(bf, &val_inc) || !inc_ptr(bf, &ptr_inc)) {
				return 0;
			}

			bf->loop_end();
		}
	}

	return 1;
}



