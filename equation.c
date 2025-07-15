#include <stdio.h>
#include <string.h>
#include "parser_export.h"

// pow(x,2) + pow(y,2) = c
static parse_status circle_eql() {
	PARSE_INIT
	d = cyylex();
	if (d.token_code != MATH_POW)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_BRACKET_START)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_IDENTIFIER)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_COMMA)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_INTEGER_VALUE || strcmp("2", d.text) != 0)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_BRACKET_END)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_PLUS)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_POW)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_BRACKET_START)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_IDENTIFIER)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_COMMA)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_INTEGER_VALUE || strcmp("2", d.text) != 0)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_BRACKET_END)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_EQ)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_INTEGER_VALUE)
		RETURN_PARSE_ERROR
	return PARSE_SUCCESS;
}

// pow(x,2)/pow(a,2) + pow(y,2)/pow(b,2) = 1
static parse_status ellipse_eql() {
	PARSE_INIT
	d = cyylex();
	if (d.token_code != MATH_POW)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_BRACKET_START)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_IDENTIFIER)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_COMMA)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_INTEGER_VALUE || strcmp("2", d.text) != 0)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_BRACKET_END)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_DIV)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_POW)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_BRACKET_START)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_IDENTIFIER)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_COMMA)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_INTEGER_VALUE || strcmp("2", d.text) != 0)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_BRACKET_END)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_PLUS)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_POW)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_BRACKET_START)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_IDENTIFIER)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_COMMA)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_INTEGER_VALUE || strcmp("2", d.text) != 0)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_BRACKET_END)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_DIV)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_POW)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_BRACKET_START)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_IDENTIFIER)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_COMMA)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_INTEGER_VALUE || strcmp("2", d.text) != 0)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_BRACKET_END)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_EQ)
		RETURN_PARSE_ERROR
	d = cyylex();
	if (d.token_code != MATH_INTEGER_VALUE || strcmp("1", d.text) != 0)
		RETURN_PARSE_ERROR
	return PARSE_SUCCESS;
}

void parse_equation() {
	if (circle_eql() == PARSE_SUCCESS)
		printf("equation of circle\n");
	if (ellipse_eql() == PARSE_SUCCESS)
		printf("equation fo ellipse\n");
}
