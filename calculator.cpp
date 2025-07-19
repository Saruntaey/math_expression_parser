#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser_export.h"
#include "math_expr_tree.h"
#include "dtype.h"

extern parse_status E();
extern parse_status Q();
extern lex_data **infix_to_postfix(lex_data *infix, int size_in, int *size_out);

DType *get_val(const char *name) {
	if (strcmp(name, "a") == 0) {
		return new DTypeInt(2);
	}
	if (strcmp(name, "b") == 0) {
		return new DTypeDouble(1.5);
	}
	return nullptr;
}

int main(void) {
	parse_status s;
	lex_data **postfix;
	int postfix_len;
	MathExprTree *tree;
	DType *res;
	lex_data d;

	while (1) {
		printf("input -> ");
		fgets(lex_buffer, sizeof(lex_buffer), stdin);
		stack_reset();
		s = Q();
		if (s == PARSE_ERROR) {
			s = E();
		}
		d = cyylex(); yyrewind(1);
		if (s == PARSE_ERROR || d.token_code != PARSER_EOL) {
			printf("invalid math expression\n");
			continue;
		}
		postfix = infix_to_postfix(lex_stack.data, lex_stack.top + 1, &postfix_len);
		tree = new MathExprTree(postfix, postfix_len, get_val);
		// tree = new MathExprTree(postfix, postfix_len);
		// tree->setGetVal(get_val);
		do {
			if (!tree->valid()) {
				printf("invalid math operation\n");
				break;
			}
			res = tree->eval();
			if (!res) {
				printf("cannot slove equation\n");
				break;
			}
			switch (res->id) {
			case MATH_INTEGER_VALUE: printf("%d", ((DTypeInt *) res)->val); break; 
			case MATH_DOUBLE_VALUE: printf("%f", ((DTypeDouble *) res)->val); break; 
			case MATH_BOOL: printf("%s", ((DTypeBool *) res)->val ? "True" : "False"); break;
			default: assert(0);
			}
			printf("\n");
		} while (0);
		delete tree;
		free(postfix);
		tree = nullptr;
		postfix = nullptr;
	}
	return 0;
}
