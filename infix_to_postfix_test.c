#include <stdio.h>
#include "parser_export.h"

extern lex_data **infix_to_postfix(lex_data *infix, int size_in, int *size_out);

#define DO_TEST(infix_array) { \
	int n; \
	int len; \
	lex_data **postfix; \
	n = sizeof(infix_array)/sizeof(infix_array[0]); \
	for (int i = 0; i < n; i++) { \
		printf("%s", infix_array[i].text); \
	} \
	printf("\n"); \
 	postfix = infix_to_postfix(infix_array, n, &len);  \
	for (int i = 0; i < len; i++) { \
		printf("%s ", postfix[i]->text); \
	} \
	printf("\n"); \
}

int main(void) {
	// a + b * c
    lex_data infix_array1[] = {
        {MATH_IDENTIFIER, 1, "a" },
        {MATH_SPACE, 1, " " },
        {MATH_PLUS, 1, "+" },
        {MATH_SPACE, 1, " " },
        {MATH_IDENTIFIER, 1, "b" },
        {MATH_SPACE, 1, " " },
        {MATH_MUL, 1, "*" },
        {MATH_SPACE, 1, " " },
        {MATH_IDENTIFIER, 1, "c" },
    };


	// max(a, b)
    lex_data infix_array2[] = {
        {MATH_MAX, 3, "max" },
        {MATH_BRACKET_START, 1, "(" },
        {MATH_IDENTIFIER, 1, "a" },
        {MATH_COMMA, 1, "," },
        {MATH_SPACE, 1, " " },
        {MATH_IDENTIFIER, 1, "b" },
        {MATH_BRACKET_END, 1, ")" },
    };

    // a + sqr(b) * sqrt(c) + pow(d,e) 
    lex_data infix_array3[] = {
        {MATH_IDENTIFIER, 1, "a" },
        {MATH_PLUS, 1, "+" },
        {MATH_SQR, 3, "sqr" },
        {MATH_BRACKET_START, 1, "(" },
        {MATH_IDENTIFIER, 1, "b" },
        {MATH_BRACKET_END, 1, ")" },
        {MATH_MUL, 1, "*" },
        {MATH_SQRT, 4, "sqrt" },
        {MATH_BRACKET_START, 1, "(" },
        {MATH_IDENTIFIER, 1, "c" },
        {MATH_BRACKET_END, 1, ")" },
        {MATH_PLUS, 1, "+" },
        {MATH_POW, 3, "pow" },
        {MATH_BRACKET_START, 1, "(" },
        {MATH_IDENTIFIER, 1, "d" },
        {MATH_COMMA, 1, "," },
        {MATH_IDENTIFIER, 1, "e" },
        {MATH_BRACKET_END, 1, ")" },
    };    

	// a + sqr(max(b,c,d)) - e
    lex_data infix_array4[] = {
        {MATH_IDENTIFIER, 1, "a" },
        {MATH_PLUS, 1, "+" },
        {MATH_SQR, 3, "sqr" },
        {MATH_BRACKET_START, 1, "(" },
		{MATH_MAX, 3, "max"},
        {MATH_BRACKET_START, 1, "(" },
        {MATH_IDENTIFIER, 1, "b" },
        {MATH_COMMA, 1, "," },
        {MATH_IDENTIFIER, 1, "c" },
        {MATH_COMMA, 1, "," },
        {MATH_IDENTIFIER, 1, "d" },
        {MATH_BRACKET_END, 1, ")" },
        {MATH_BRACKET_END, 1, ")" },
		{MATH_MINUS, 1, "-"},
        {MATH_IDENTIFIER, 1, "e" },
    };    

	DO_TEST(infix_array1);
	DO_TEST(infix_array2);
	DO_TEST(infix_array3);
	DO_TEST(infix_array4);
}
