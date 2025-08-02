#include <stdio.h>
#include "parser_export.h"
#include "math_exp_enum.h"
#include "adapter.h"


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

parse_status E(); // math expression
static parse_status F();
static parse_status T();
static parse_status G();
static parse_status P();

parse_status Q(); // inequality expression
static parse_status INEQ();

parse_status S(); // logical expression
static parse_status S_dash();
static parse_status J();
static parse_status J_dash();
static parse_status K();
static parse_status K_dash();
static parse_status D();
static parse_status LOP();

// E -> F + E | F - E | F
// F -> T * F | T / F | T
// T -> (E) | <var> | <int> | <double> | G(E) | P(E, E)
// G -> sqr | sqrt | sin | cos
// P -> min | max | pow
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
		if (_tokcnv(d.token_code) != MATH_PLUS) break;
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
		if (_tokcnv(d.token_code) != MATH_MINUS) break;
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
		if (_tokcnv(d.token_code) != MATH_MUL) break;
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
		if (_tokcnv(d.token_code) != MATH_DIV) break;
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


// T -> (E) | <var> | <int> | <double> | G(E) | P(E, E)
parse_status T() {
	PARSE_INIT;
	parse_status s;

	// T -> (E)
	do {
		d = cyylex();
		if (_tokcnv(d.token_code) != MATH_BRACKET_START) break;
		s = E();
		if (s == PARSE_ERROR) break;
		d = cyylex();
		if (_tokcnv(d.token_code) != MATH_BRACKET_END) break;
		return PARSE_SUCCESS;
	} while(0);
	RESTORE_CHECK_POINT;

	// T -> <var>
	do {
		d = cyylex();
		if (_tokcnv(d.token_code) != MATH_IDENTIFIER) break;
		return PARSE_SUCCESS;
	} while(0);
	RESTORE_CHECK_POINT;

	// T -> <int>
	do {
		d = cyylex();
		if (_tokcnv(d.token_code) != MATH_INTEGER_VALUE) break;
		return PARSE_SUCCESS;
	} while(0);
	RESTORE_CHECK_POINT;

	// T -> <double>
	do {
		d = cyylex();
		if (_tokcnv(d.token_code) != MATH_DOUBLE_VALUE) break;
		return PARSE_SUCCESS;
	} while(0);
	RESTORE_CHECK_POINT;

	// T -> G(E)
	do {
		s = G();
		if (s == PARSE_ERROR) break;
		d = cyylex();
		if (_tokcnv(d.token_code) != MATH_BRACKET_START) break;
		s = E();
		if (s == PARSE_ERROR) break;
		d = cyylex();
		if (_tokcnv(d.token_code) != MATH_BRACKET_END) break;
		return PARSE_SUCCESS;
	} while(0);
	RESTORE_CHECK_POINT;

	// T -> P(E, E) 
	do {
		s = P();
		if (s == PARSE_ERROR) break;
		d = cyylex();
		if (_tokcnv(d.token_code) != MATH_BRACKET_START) break;
		s = E();
		if (s == PARSE_ERROR) break;
		d = cyylex();
		if (_tokcnv(d.token_code) != MATH_COMMA) break;
		s = E();
		if (s == PARSE_ERROR) break;
		d = cyylex();
		if (_tokcnv(d.token_code) != MATH_BRACKET_END) break;
		return PARSE_SUCCESS;
	} while(0);

	RETURN_PARSE_ERROR;
}
// G -> sqr | sqrt | sin | cos
parse_status G() {
	PARSE_INIT;

	d = cyylex();
	switch (_tokcnv(d.token_code)) {
	case MATH_SQRT:
	case MATH_SQR:
	case MATH_SIN:
	case MATH_COS:
		return PARSE_SUCCESS;
	default:
		RETURN_PARSE_ERROR;
	}
}

// P -> min | max | pow
parse_status P() {
	PARSE_INIT;

	d = cyylex();
	switch (_tokcnv(d.token_code)) {
	case MATH_MAX:
	case MATH_MIN:
	case MATH_POW:
		return PARSE_SUCCESS;
	default:
		RETURN_PARSE_ERROR;
	}
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
	switch (_tokcnv(d.token_code)) {
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

/*
 * Logical Expression
 * 1. S -> S or J | J
 * 2. J -> J and K | K 
 * 3. K -> (S) | D | K LOP Q | Q LOP K
 * 4. D -> Q LOP Q
 * 5. LOP -> and | or
 * 
 * Removing Left Recursion :
 * 1. S -> S or J | J
 *     S -> J S'
 *     S' -> or J S' | $
 * 2. J -> J and K | K
 *     J -> K J'
 *     J' -> and K J' | $
 * 3. K -> (S) | D | K LOP Q | Q LOP K
 *     K -> (S) K' |  D K' |  Q LOP K K'
 *     K' -> LOP Q K' | $
 * 
 * Overall Grammar will be :
 * =====================
 * 1. S -> J S'
 * 2. S' -> or J S' | $
 * 3. J -> K J'
 * 4. J' -> and K J' | $
 * 5. K -> (S) K' | D K' | Q LOP K K'
 * 6. K' -> LOP Q K' | $
 * 7. D -> Q LOP Q
 * 8. LOP -> and | or
*/

// S -> J S'
parse_status S() {
	PARSE_INIT;
	parse_status s;

	s = J();
	if (s == PARSE_ERROR) RETURN_PARSE_ERROR;
	s = S_dash();
	if (s == PARSE_ERROR) RETURN_PARSE_ERROR;
	return PARSE_SUCCESS;
}

// S' -> or J S' | $
parse_status S_dash() {
	PARSE_INIT;
	parse_status s;

	do {
		d = cyylex();
		if (_tokcnv(d.token_code) != MATH_OR) break;
		s = J();
		if (s == PARSE_ERROR) break;
		s = S_dash();
		if (s == PARSE_ERROR) break;
		return PARSE_SUCCESS;
	} while (0);
	RESTORE_CHECK_POINT;

	return PARSE_SUCCESS;
}


// J -> K J'
parse_status J() {
	PARSE_INIT;
	parse_status s;

	s = K();
	if (s == PARSE_ERROR) RETURN_PARSE_ERROR;
	s = J_dash();
	if (s == PARSE_ERROR) RETURN_PARSE_ERROR;
	return PARSE_SUCCESS;
}

// J' -> and K J' | $
parse_status J_dash() {
	PARSE_INIT;
	parse_status s;

	do {
		d = cyylex();
		if (_tokcnv(d.token_code) != MATH_AND) break;
		s = K();
		if (s == PARSE_ERROR) break;
		s = J_dash();
		if (s == PARSE_ERROR) break;
		return PARSE_SUCCESS;
	} while(0);
	RESTORE_CHECK_POINT;

	return PARSE_SUCCESS;
}

// K -> (S) K' | D K' | Q LOP K K'
parse_status K() {
	PARSE_INIT;
	parse_status s;

	do {
		d = cyylex();
		if (_tokcnv(d.token_code) != MATH_BRACKET_START) break;
		s = S();
		if (s == PARSE_ERROR) break;
		d = cyylex();
		if (_tokcnv(d.token_code) != MATH_BRACKET_END) break;
		s = K_dash();
		if (s == PARSE_ERROR) break;
		return PARSE_SUCCESS;
	} while(0);
	RESTORE_CHECK_POINT;

	do {
		s = D();
		if (s == PARSE_ERROR) break;
		s = K_dash();
		if (s == PARSE_ERROR) break;
		return PARSE_SUCCESS;
	} while(0);
	RESTORE_CHECK_POINT;

	do {
		s = Q();
		if (s == PARSE_ERROR) break;
		s = LOP();
		if (s == PARSE_ERROR) break;
		s = K();
		if (s == PARSE_ERROR) break;
		s = K_dash();
		if (s == PARSE_ERROR) break;
		return PARSE_SUCCESS;
	} while(0);

	RETURN_PARSE_ERROR;
}

 // K' -> LOP Q K' | $
parse_status K_dash() {
	PARSE_INIT;
	parse_status s;

	do {
		s = LOP();
		if (s == PARSE_ERROR) break;
		s = Q();
		if (s == PARSE_ERROR) break;
		s = K_dash();
		if (s == PARSE_ERROR) break;
		return PARSE_SUCCESS;
	} while(0);
	RESTORE_CHECK_POINT;

	return PARSE_SUCCESS;
}

// D -> Q LOP Q
parse_status D() {
	PARSE_INIT;
	parse_status s;

	s = Q();
	if (s == PARSE_ERROR) RETURN_PARSE_ERROR;
	s = LOP();
	if (s == PARSE_ERROR) RETURN_PARSE_ERROR;
	s = Q();
	if (s == PARSE_ERROR) RETURN_PARSE_ERROR;
	return PARSE_SUCCESS;
}

// LOP -> and | or
parse_status LOP() {
	PARSE_INIT;

	d = cyylex();
	switch (_tokcnv(d.token_code)) {
	case MATH_AND:
	case MATH_OR:
		return PARSE_SUCCESS;
	default:
		RETURN_PARSE_ERROR;
	}
}
