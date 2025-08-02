#include <stdio.h>
#include <string.h>
#include "parser_export.h"
#include "math_exp_enum.h"

static parse_status A();
static parse_status B();

void parse_alternate_a_b() {
	if (A() == PARSE_ERROR) {
		printf("invalid ab\n");
	} else {
		lex_data d = cyylex();
		yyrewind(1);
		if ((int) d.token_code == (int) PARSER_EOL)
			printf("valid ab\n");
		else 
			printf("valid ab partial\n");
	}
	for (int i = 0; i <= lex_stack.top; i++) {
		lex_data *p = &lex_stack.data[i];
		printf("%s ", p->text);
	}
	printf("\n");
}

// A -> aB
// B -> bA | b | ba
parse_status A() {
	PARSE_INIT
	d = cyylex();
	if (d.token_code != MATH_IDENTIFIER || strcmp(d.text, "a") != 0) RETURN_PARSE_ERROR;
	parse_status s = B();
	if (s == PARSE_ERROR) RETURN_PARSE_ERROR;
	return PARSE_SUCCESS;
}

parse_status B() {
	PARSE_INIT
	parse_status s;

	do {
		d = cyylex();
		if (d.token_code != MATH_IDENTIFIER || strcmp(d.text, "b") != 0)
			break;
		s = A();
		if (s == PARSE_ERROR) 
			break;
		return PARSE_SUCCESS;
	} while(0);

	RESTORE_CHECK_POINT;

	do {
		d = cyylex();
		if (d.token_code != MATH_IDENTIFIER || strcmp(d.text, "b") != 0) 
			break;
		d = cyylex();
		if (d.token_code != MATH_IDENTIFIER || strcmp(d.text, "a") != 0)
			break;
		return PARSE_SUCCESS;
	} while(0);

	RESTORE_CHECK_POINT;

	do {
		d = cyylex();
		if (d.token_code != MATH_IDENTIFIER || strcmp(d.text, "b") != 0)
			break;
		return PARSE_SUCCESS;
	} while(0);
	
	RETURN_PARSE_ERROR;
}

// // A -> a | aB
// // B -> b | bA
// parse_status A() {
// 	PARSE_INIT
// 	d = cyylex();
// 	if (d.token_code != MATH_IDENTIFIER || strcmp(d.text, "a") != 0) RETURN_PARSE_ERROR
// 	B();
// 	return PARSE_SUCCESS;
// }
//
// parse_status B() {
// 	PARSE_INIT
// 	d = cyylex();
// 	if (d.token_code != MATH_IDENTIFIER || strcmp(d.text, "b") != 0) RETURN_PARSE_ERROR
// 	A();
// 	return PARSE_SUCCESS;
// }
