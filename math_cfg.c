#include "parser_export.h"
#include <stdio.h>


/*
 * E -> E + F | E - F | F
 * F -> F * T | F / T | T
 * T -> (E) | <var> | <int> | <double>
 * ---
 * E -> F + E | F - E | F
 * F -> T * F | T / F | T
 * T -> (E) | <var> | <int> | <double> 
 * ---
 * E -> FE'
 * E' -> +FE' | -FE' | $ // $ mean empty
 *
 * F -> TF'
 * F' -> *TF' | /TF' | $
 *
 * T -> (E) | <var> | <int> | <double>
*/

static parse_status E();
static parse_status F();
static parse_status T();
static parse_status Q();
static parse_status INEQ();

void parse_math() {
	if (E() == PARSE_SUCCESS) {
		printf("vaild\n");
	} else {
		printf("invaild\n");
	}
}

void parse_inequlity() {
	if (Q() == PARSE_SUCCESS) {
		printf("vaild\n");
	} else {
		printf("invaild\n");
	}
}

// E -> F + E | F - E | F
parse_status E() {
	PARSE_INIT;
	parse_status s;

	// E -> F + E
	do {
		s = F();
		if (s == PARSE_ERROR) break;
		d = cyylex();
		if (d.token_code != MATH_PLUS) break;
		s = E();
		if (s == PARSE_ERROR) break;
		return PARSE_SUCCESS;
	} while(0);
	RESTORE_CHECK_POINT;

	// E -> F - E
	do {
		s = F();
		if (s == PARSE_ERROR) break;
		d = cyylex();
		if (d.token_code != MATH_MINUS) break;
		s = E();
		if (s == PARSE_ERROR) break;
		return PARSE_SUCCESS;
	} while(0);
	RESTORE_CHECK_POINT;

	// E -> F
	do {
		s = F();
		if (s == PARSE_ERROR) break;
		return PARSE_SUCCESS;
	} while(0);

	RETURN_PARSE_ERROR;
}

// F -> T * F | T / F | T
parse_status F() {
	PARSE_INIT;
	parse_status s;

	// F -> T * F
	do {
		s = T();
		if (s == PARSE_ERROR) break;
		d = cyylex();
		if (d.token_code != MATH_MUL) break;
		s = F();
		if (s == PARSE_ERROR) break;
		return PARSE_SUCCESS;
	} while(0);
	RESTORE_CHECK_POINT;

	// F -> T / F
	do {
		s = T();
		if (s == PARSE_ERROR) break;
		d = cyylex();
		if (d.token_code != MATH_DIV) break;
		s = F();
		if (s == PARSE_ERROR) break;
		return PARSE_SUCCESS;
	} while(0);
	RESTORE_CHECK_POINT;

	// F -> T
	do {
		s = T();
		if (s == PARSE_ERROR) break;
		return PARSE_SUCCESS;
	} while(0);

	RETURN_PARSE_ERROR;
}


// T -> (E) | <var> | <int> | <double>
parse_status T() {
	PARSE_INIT;
	parse_status s;

	// T -> (E)
	do {
		d = cyylex();
		if (d.token_code != MATH_BRACKET_START) break;
		s = E();
		if (s == PARSE_ERROR) break;
		d = cyylex();
		if (d.token_code != MATH_BRACKET_END) break;
		return PARSE_SUCCESS;
	} while(0);
	RESTORE_CHECK_POINT;

	// T -> <var>
	do {
		d = cyylex();
		if (d.token_code != MATH_IDENTIFIER) break;
		return PARSE_SUCCESS;
	} while(0);
	RESTORE_CHECK_POINT;

	// T -> <int>
	do {
		d = cyylex();
		if (d.token_code != MATH_INTEGER_VALUE) break;
		return PARSE_SUCCESS;
	} while(0);
	RESTORE_CHECK_POINT;

	// T -> <double>
	do {
		d = cyylex();
		if (d.token_code != MATH_DOUBLE_VALUE) break;
		return PARSE_SUCCESS;
	} while(0);

	RETURN_PARSE_ERROR;
}


// Q -> E INEQ E
parse_status Q() {
	PARSE_INIT;
	parse_status s;

	s = E();
	if (s == PARSE_ERROR) RETURN_PARSE_ERROR;
	s = INEQ();
	if (s == PARSE_ERROR) RETURN_PARSE_ERROR;
	s = E();
	if (s == PARSE_ERROR) RETURN_PARSE_ERROR;
	return PARSE_SUCCESS;
}

// INEQ -> == | != | < | <= | > | >=
parse_status INEQ() {
	PARSE_INIT;

	d = cyylex();
	switch (d.token_code) {
	case MATH_EQ:
	case MATH_NOT_EQ:
	case MATH_LESS_THAN:
	case MATH_LESS_THAN_EQ:
	case MATH_GREATER_THAN:
	case MATH_GREATER_THAN_EQ:
		return PARSE_SUCCESS;
	default:
		RETURN_PARSE_ERROR;
	}
}
