#ifndef _PARSER_EXPORT_
#define _PARSER_EXPORT_

extern "C" int yylex();
#include "assert.h"
#include "math_exp_enum.h"
#define MAX_STR_SIZE 512
#define STACK_CAP 512

typedef enum parse_status {
	PARSE_ERROR,
	PARSE_SUCCESS,
} parse_status;

typedef struct lex_data {
	math_exp_type token_code;
	int len;
	char *text;
} lex_data;

typedef struct stack {
	int top;
	lex_data data[STACK_CAP];
} stack;

extern char lex_buffer[MAX_STR_SIZE];
extern char *curr_ptr;
extern stack lex_stack;

lex_data cyylex(); 
void yyrewind(int n); 
void stack_reset(); 
void restore(int _chkp); 

#define PARSE_INIT \
	lex_data d; \
	int _chkp = lex_stack.top;

#define RETURN_PARSE_ERROR { \
	restore(_chkp); \
	return PARSE_ERROR; \
}

#define RESTORE_CHECK_POINT { \
	restore(_chkp); \
}

static inline bool is_operator(math_exp_type token_code) {
	return MATH_OPERATOR_START < token_code && token_code < MATH_OPERATOR_END;
}

static inline bool is_operand(math_exp_type token_code) {
	return MATH_OPERAND_START < token_code && token_code < MATH_OPERAND_END;
}

static inline bool is_unary_op(math_exp_type token_code) {
	switch (token_code) {
	case MATH_SQRT:
	case MATH_SQR:
	case MATH_SIN:
	case MATH_COS:
		return true;
	default:
		return false;
	}
}

static inline int precedent(math_exp_type token_code) {
	switch (token_code) {
	case MATH_MAX:
	case MATH_MIN:
	case MATH_POW:
		return 6;
	case MATH_SQRT:
	case MATH_SQR:
	case MATH_SIN:
	case MATH_COS:
		return 5;
	case MATH_DIV:
	case MATH_MUL:
		return 4;
	case MATH_PLUS:
	case MATH_MINUS:
		return 3;
	case MATH_EQ:
	case MATH_NOT_EQ:
	case MATH_LESS_THAN_EQ:
	case MATH_LESS_THAN:
	case MATH_GREATER_THAN:
    case MATH_GREATER_THAN_EQ:
		return 2;
	case MATH_AND:
		return 1;
	case MATH_OR:
		return 0;
	default: 
		return -1; 

	}
}

#endif
