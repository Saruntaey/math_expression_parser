#include <stdio.h>
#include "parser_export.h"
#include "math_expr_tree.h"
#include "dtype.h"
#include <assert.h>

extern lex_data **infix_to_postfix(lex_data *infix, int size_in, int *size_out);

int app_to_mexpr_enum_converter(int token_code) {
	return token_code;
}

#define DO_TEST(infix_array, test_tree) { \
	int n; \
	int len; \
	lex_data **postfix; \
	n = sizeof(infix_array)/sizeof(infix_array[0]); \
	printf("---\n"); \
	for (int i = 0; i < n; i++) { \
		printf("%s", infix_array[i].text); \
	} \
	printf("\n"); \
 	postfix = infix_to_postfix(infix_array, n, &len);  \
	for (int i = 0; i < len; i++) { \
		printf("%s ", postfix[i]->text); \
	} \
	printf("\n"); \
	if (test_tree) { \
		MathExprTree *tree = new MathExprTree(postfix, len); \
		tree->inorderPrint(); \
		printf("\n"); \
		bool ok = tree->valid(); \
		printf("tree %s\n", ok ? "valid" : "in-valid"); \
		if (ok) { \
			printf("res: "); \
			DType *res = tree->eval(); \
			switch (res->id) { \
			case MATH_INTEGER_VALUE: printf("%d", ((DTypeInt *) res)->val); break; \
			case MATH_DOUBLE_VALUE: printf("%f", ((DTypeDouble *) res)->val); break; \
			case MATH_BOOL: printf("%s", ((DTypeBool *) res)->val ? "True" : "False"); break; \
			default: assert(0); \
			} \
			printf("\n"); \
			delete res; \
		} \
		delete tree; \
	} \
}

int main(void) {
	// a + b * c
    lex_data infix_array1[] = {
        {MATH_IDENTIFIER, 1, "a" },
        {PARSER_WHITE_SPACE, 1, " " },
        {MATH_PLUS, 1, "+" },
        {PARSER_WHITE_SPACE, 1, " " },
        {MATH_IDENTIFIER, 1, "b" },
        {PARSER_WHITE_SPACE, 1, " " },
        {MATH_MUL, 1, "*" },
        {PARSER_WHITE_SPACE, 1, " " },
        {MATH_IDENTIFIER, 1, "c" },
    };


	// max(a, b)
    lex_data infix_array2[] = {
        {MATH_MAX, 3, "max" },
        {MATH_BRACKET_START, 1, "(" },
        {MATH_IDENTIFIER, 1, "a" },
        {MATH_COMMA, 1, "," },
        {PARSER_WHITE_SPACE, 1, " " },
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

	// 10 + 12 * 42.3 / (2 - 0.5)
    lex_data infix_array5[] = {
        {MATH_INTEGER_VALUE, 2, "10" },
        {PARSER_WHITE_SPACE, 1, " " },
        {MATH_PLUS, 1, "+" },
        {PARSER_WHITE_SPACE, 1, " " },
        {MATH_INTEGER_VALUE, 2, "12" },
        {PARSER_WHITE_SPACE, 1, " " },
        {MATH_MUL, 1, "*" },
        {PARSER_WHITE_SPACE, 1, " " },
        {MATH_DOUBLE_VALUE, 4, "42.3" },
        {MATH_DIV, 1, "/" },
        {MATH_BRACKET_START, 1, "(" },
        {MATH_INTEGER_VALUE, 1, "2" },
        {MATH_MINUS, 1, "-" },
        {MATH_DOUBLE_VALUE, 3, "0.5" },
        {MATH_BRACKET_END, 1, ")" },
    };

	// 1 + 2 * 3 
    lex_data infix_array6[] = {
        {MATH_INTEGER_VALUE, 1, "1" },
        {MATH_PLUS, 1, "+" },
        {MATH_INTEGER_VALUE, 1, "2" },
        {MATH_MUL, 1, "*" },
        {MATH_INTEGER_VALUE, 1, "3" },
    };

	// 1 + 2 * 3.0 
    lex_data infix_array7[] = {
        {MATH_INTEGER_VALUE, 1, "1" },
        {MATH_PLUS, 1, "+" },
        {MATH_INTEGER_VALUE, 1, "2" },
        {MATH_MUL, 1, "*" },
        {MATH_DOUBLE_VALUE, 3, "3.0" },
    };

	// max(1, 2)
    lex_data infix_array8[] = {
        {MATH_MAX, 3, "max" },
        {MATH_BRACKET_START, 1, "(" },
        {MATH_INTEGER_VALUE, 1, "1" },
        {MATH_COMMA, 1, "," },
        {PARSER_WHITE_SPACE, 1, " " },
        {MATH_INTEGER_VALUE, 1, "2" },
        {MATH_BRACKET_END, 1, ")" },
    };

    // 1 + sqr(2) * sqrt(9) + pow(2,3) 
    lex_data infix_array9[] = {
        {MATH_INTEGER_VALUE, 1, "1" },
        {MATH_PLUS, 1, "+" },
        {MATH_SQR, 3, "sqr" },
        {MATH_BRACKET_START, 1, "(" },
        {MATH_INTEGER_VALUE, 1, "2" },
        {MATH_BRACKET_END, 1, ")" },
        {MATH_MUL, 1, "*" },
        {MATH_SQRT, 4, "sqrt" },
        {MATH_BRACKET_START, 1, "(" },
        {MATH_INTEGER_VALUE, 1, "9" },
        {MATH_BRACKET_END, 1, ")" },
        {MATH_PLUS, 1, "+" },
        {MATH_POW, 3, "pow" },
        {MATH_BRACKET_START, 1, "(" },
        {MATH_INTEGER_VALUE, 1, "2" },
        {MATH_COMMA, 1, "," },
        {MATH_INTEGER_VALUE, 1, "3" },
        {MATH_BRACKET_END, 1, ")" },
    };    

	// 1 + 3 = pow(2,2)
    lex_data infix_array10[] = {
        {MATH_INTEGER_VALUE, 1, "1" },
        {MATH_PLUS, 1, "+" },
        {MATH_INTEGER_VALUE, 1, "3" },
		{MATH_EQ, 1, "="},
        {MATH_POW, 3, "pow" },
        {MATH_BRACKET_START, 1, "(" },
        {MATH_INTEGER_VALUE, 1, "2" },
        {MATH_COMMA, 1, "," },
        {MATH_INTEGER_VALUE, 1, "2" },
        {MATH_BRACKET_END, 1, ")" },
    };

	DO_TEST(infix_array1, 0);
	DO_TEST(infix_array2, 0);
	DO_TEST(infix_array3, 0);
	DO_TEST(infix_array4, 0);
	DO_TEST(infix_array5, 1);
	DO_TEST(infix_array6, 1);
	DO_TEST(infix_array7, 1);
	DO_TEST(infix_array8, 1);
	DO_TEST(infix_array9, 1);
	DO_TEST(infix_array10, 1);
}
