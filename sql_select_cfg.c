#include "parser_export.h"
#include <string.h>
#include <stdio.h>

void parse_sql_select();
static parse_status Q();
static parse_status COLS();
static parse_status COL();
static parse_status TAB();


void parse_sql_select() {
	if (Q()) {
		printf("sql select: valid\n");
	} else {
		printf("sql select: invalid\n");
	}
}

// Q -> select COLS from TAB
parse_status Q() {
	PARSE_INIT;
	parse_status s;

	d = cyylex();
	if (d.token_code != MATH_IDENTIFIER || strcmp(d.text, "select")) RETURN_PARSE_ERROR;
	s = COLS();
	if (s == PARSE_ERROR) RETURN_PARSE_ERROR;
	d = cyylex();
	if (d.token_code != MATH_IDENTIFIER || strcmp(d.text, "from")) RETURN_PARSE_ERROR;
	s = TAB();
	if (s == PARSE_ERROR) RETURN_PARSE_ERROR;
	d = cyylex();
	yyrewind(1);
	if ((int) d.token_code != (int) PARSER_EOL) RETURN_PARSE_ERROR; 
	return PARSE_SUCCESS;
}

// COLS -> COL | COL,COLS
parse_status COLS() {
	PARSE_INIT;
	parse_status s;

	do {
		s = COL();
		if (s == PARSE_ERROR) break;
		d = cyylex();
		if (d.token_code != MATH_COMMA) break;
		s = COLS();
		if (s == PARSE_ERROR) break;
		return PARSE_SUCCESS;
	} while(0);

	RESTORE_CHECK_POINT;

	do {
		s = COL();
		if (s == PARSE_ERROR) break;
		return PARSE_SUCCESS;
	} while(0);

	RETURN_PARSE_ERROR;
}

// COL -> <var>
parse_status COL() {
	PARSE_INIT;
	d = cyylex();
	if (d.token_code != MATH_IDENTIFIER) RETURN_PARSE_ERROR;
	return PARSE_SUCCESS;
}


// TAB -> <var>
parse_status TAB() {
	PARSE_INIT;
	d = cyylex();
	if (d.token_code != MATH_IDENTIFIER) RETURN_PARSE_ERROR;
	return PARSE_SUCCESS;
}
