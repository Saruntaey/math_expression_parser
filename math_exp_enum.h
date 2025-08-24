#ifndef _MATH_EXP_H
#define _MATH_EXP_H

typedef enum math_exp_type {
	MATH_BRACKET_START,
	MATH_BRACKET_END,

	MATH_OPERATOR_START,
	MATH_LESS_THAN_EQ,
	MATH_LESS_THAN,
	MATH_GREATER_THAN,
    MATH_GREATER_THAN_EQ,
	MATH_EQ,
	MATH_NOT_EQ,
	MATH_AND,
	MATH_OR,
	MATH_MUL,
	MATH_PLUS,
	MATH_MINUS,
	MATH_DIV,
	MATH_SQRT,
	MATH_SQR,
	MATH_MAX,
	MATH_MIN,
	MATH_SIN,
	MATH_COS,
	MATH_POW,
	MATH_OPERATOR_END,

	MATH_COMMA,

	MATH_OPERAND_START,
	MATH_INTEGER_VALUE,
	MATH_DOUBLE_VALUE,
	MATH_IDENTIFIER,
	MATH_IDENTIFIER_IDENTIFIER,
	MATH_BOOL,
	MATH_STRING_VALUE,
	MATH_OPERAND_END,

	MATH_WILDCARD_VALUE,

	MATH_INVALID,

	MATH_EXP_TYPE_MAX,
} math_exp_type;

static inline constexpr int comb(int a, int b) {
	if (a > b) return comb(b, a);
	return (int) a * (int) MATH_EXP_TYPE_MAX + (int) b;
}

static inline bool is_operator(int token_code) {
	return MATH_OPERATOR_START < token_code && token_code < MATH_OPERATOR_END;
}

static inline bool is_operand(int token_code) {
	return MATH_OPERAND_START < token_code && token_code < MATH_OPERAND_END;
}

static inline bool is_unary_op(int token_code) {
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

static inline int precedent(int token_code) {
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
