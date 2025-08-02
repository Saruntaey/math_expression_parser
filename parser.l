%{
#include "parser_export.h"
#include "math_exp_enum.h"

char lex_buffer[MAX_STR_SIZE];
char *curr_ptr = lex_buffer;
stack lex_stack = {.top = -1};


static void stack_push(lex_data v) {
	assert(lex_stack.top+1 < STACK_CAP);
	lex_stack.data[++lex_stack.top] = v;
}

static lex_data stack_pop() {
	assert(lex_stack.top > -1);
	return lex_stack.data[lex_stack.top--];
}

static int stack_size() {
	return lex_stack.top + 1;
}

static lex_data stack_peek() {
	assert(lex_stack.top > -1);
	return lex_stack.data[lex_stack.top];
}

void stack_reset() {
	lex_data d;

	while (stack_size() > 0) {
		d = stack_pop();
		free(d.text);
	}
	yy_scan_string(lex_buffer);
	curr_ptr = lex_buffer;
}

lex_data cyylex() {
	int token_code = yylex();
	lex_data d = {.token_code = (math_exp_type) token_code, .len = yyleng};
	d.text = (char*) malloc(yyleng+1);
	strncpy(d.text, yytext, yyleng+1);
	stack_push(d);
	curr_ptr += yyleng;
	return d;
}

void yyrewind(int n) {
	int i;

	while (n > 0 && lex_stack.top != -1) {
		i = lex_stack.top;
		free(lex_stack.data[i].text);
		lex_stack.data[i].text = NULL;
		if (lex_stack.data[i].token_code != PARSER_WHITE_SPACE) {
			n--;
		}
		curr_ptr -= lex_stack.data[lex_stack.top--].len;
	}
	yy_scan_string(curr_ptr);
}

void restore(int _chkp) {
	assert(_chkp <= lex_stack.top);
	lex_data *p;
	while (lex_stack.top > _chkp) {
		p = &lex_stack.data[lex_stack.top--];
		free(p->text);
		p->text = NULL;
		curr_ptr -= p->len;
	}
	yy_scan_string(curr_ptr);
}

static void process_white_space(int n) {
	lex_data d = {.token_code = PARSER_WHITE_SPACE, .len = n};
	stack_push(d);
	curr_ptr += n;
}

%}

%%

"(" {
    return MATH_BRACKET_START;
}

")" {
    return MATH_BRACKET_END;
}

"<=" {
    return MATH_LESS_THAN_EQ;
}

"<" {
    return MATH_LESS_THAN;
}

">" {
    return MATH_GREATER_THAN;
}

">=" {
    return MATH_GREATER_THAN_EQ;
}

"=" {
    return MATH_EQ;
}

"!=" {
    return MATH_NOT_EQ;
}

"and" {
    return MATH_AND;
}

"or" {
    return MATH_OR;
}

"*" {
    return MATH_MUL;
}

"+" {
    return MATH_PLUS;
}

"-" {
    return  MATH_MINUS;
}

"/" {
    return MATH_DIV;
}

"," {
    return MATH_COMMA;
}

"sqrt" {
    return MATH_SQRT;
}

"sqr" {
    return MATH_SQR;
}

"max" {
    return MATH_MAX;
}

"min" {
    return MATH_MIN;
}

"sin" {
    return MATH_SIN;
}

"cos" {
    return MATH_COS;
}

"pow" {
    return MATH_POW;
}

\n {
    return PARSER_EOL;
}

"\\\n" {

}

[ ] {
    /* Ignore */
    process_white_space(1);
}

[\t] {
    /*ignore*/
    process_white_space(4);
}

"\\q" {
    return PARSER_QUIT;
}

0|-?[1-9][0-9]* {
    return MATH_INTEGER_VALUE;
}

-?[0-9]*\.[0-9]+ {
    return MATH_DOUBLE_VALUE;
}

[a-zA-Z0-9_]+ {
    return MATH_IDENTIFIER;
}

[a-zA-Z0-9_]+\.[a-zA-Z0-9_]+ {
    return MATH_IDENTIFIER_IDENTIFIER;
}

'[^']*' {
    // string enclosed within single quotes
    return MATH_STRING_VALUE;
}

\"[^"]*\" {
    // string enclosed within double quotes
    return MATH_STRING_VALUE;
}


. {
    // ignore any other character
}

%%

// extern void parse_equation();
// extern void parse_alternate_a_b();
// extern void parse_sql_select();
// extern void parse_math();
// extern void parse_inequlity();
// 
// int main(int argc, char** argv) {
// 	int token_code;
// 
// 	while (1) {
// 		printf("input -> ");
// 		fgets(lex_buffer, sizeof(lex_buffer), stdin);
// 		stack_reset();
// 		// parse_equation();
// 		// parse_alternate_a_b();
// 		// parse_sql_select();
// 		// parse_math();
// 		parse_inequlity();
// 	}
// 	return 0;
// }
