#ifndef __CBRAINFUCK_EXEC_H__
#define __CBRAINFUCK_EXEC_H__

/** Brainfuck struct
 */
typedef struct {

	/** Brainfuck array
	 */
	unsigned char* array;

	unsigned char* array_end;

	unsigned char* array_ptr;

	/** Stack of the starting position of the loops
	 */
	char** jmp_stack;

	char** jmp_stack_end;

	char** jmp_stack_top;

} bf_exec_st;

/** Brainfuck interpreter return values
 */
enum bf_exec_status_e {

	/** No error occurred
	 */
	BF_EXEC_OK = 0,

	/** There is a missing or an extra bracket
	 */
	BF_EXEC_BRACKET,

	/** The pointer goes out of the array
	 * The pointer is reset to the beginning of the array
	 */
	BF_EXEC_POINTER,

	/** There was an allocation failure
	 */
	BF_EXEC_ALLOC
};

/** Initialize a brainfuck struct
 * @param bf the struct
 * @param array_size the brainfuck array length
 * @return 0 if it fails, a different value otherwise
 */
int bf_exec_init(bf_exec_st* bf, unsigned int array_size);

/** Interpret a brainfuck string
 * @param bf a brainfuck struct
 * @param code the brainfuck string
 * @return a value in brainfuck_status_e enum
 */
int bf_exec(bf_exec_st* bf, const char* code);

/** Same as bf_exec() but uses user-defined input/output functions
 * @param input a function to read a character
 * @param output a function to send a character
 */
int bf_exec_io(bf_exec_st* bf, const char* code, char (*input)(), void (*output)(char c));

/** Free the memory of a brainfuck struct
 * @param bf the struct
 */
void bf_exec_clear(bf_exec_st* bf);

#endif