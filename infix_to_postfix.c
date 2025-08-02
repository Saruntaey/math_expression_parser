#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include "parser_export.h"
#include "math_exp_enum.h"
#include "adapter.h"

typedef struct _stack {
	int top;
	int cap;
	void **data;
} _stack;

static _stack make_stack(int cap);
static void free_stack(_stack *s);
static void stack_push(_stack *s, void *v);
static void *stack_pop(_stack *s);
static void *stack_peek(_stack *s);
static bool stack_is_empty(_stack *s);


lex_data **infix_to_postfix(lex_data *infix, int size_in, int *size_out) {
	lex_data **postfix;
	_stack s = make_stack(size_in);
	int len = 0;
	lex_data *l;
	lex_data *o;

	postfix = (lex_data**) malloc(size_in * sizeof(lex_data**));

	for (int i = 0; i < size_in; i++) {
		l = &infix[i];
		if (l->token_code == PARSER_WHITE_SPACE) continue;
		if (is_operand(_tokcnv(l->token_code))) {
			postfix[len++] = l;
		} else if (_tokcnv(l->token_code) == MATH_BRACKET_START) {
			stack_push(&s, (void *) l);
		} else if (_tokcnv(l->token_code) == MATH_BRACKET_END) {
			while (1) {
				o = (lex_data*) stack_pop(&s);
				if (_tokcnv(o->token_code) == MATH_BRACKET_START) {
					break;
				}
				postfix[len++] = o;
			}
		} else if (_tokcnv(l->token_code) == MATH_COMMA) {
			while (!stack_is_empty(&s) && _tokcnv(((lex_data*) stack_peek(&s))->token_code) != MATH_BRACKET_START) {
				postfix[len++] = (lex_data*) stack_pop(&s);
			}
		}else {
			if (!is_unary_op(_tokcnv(l->token_code))) {
				while (!stack_is_empty(&s) && precedent(_tokcnv(l->token_code)) <= precedent(_tokcnv(((lex_data*) stack_peek(&s))->token_code))) {
					postfix[len++] = (lex_data*) stack_pop(&s);
				}
			}
			stack_push(&s, l);
		}
	}

	while (!stack_is_empty(&s)) {
		postfix[len++] = (lex_data*) stack_pop(&s);
	}

	free_stack(&s);
	*size_out = len;
	return postfix;
}


_stack make_stack(int cap) {
	_stack s = {.top = -1, .cap = cap}; 
	s.data = (void**) malloc(cap * sizeof(void*));
	return s;
}

void free_stack(_stack *s) {
	assert(s);
	free(s->data);
	s->data = NULL;
}

void stack_push(_stack *s, void *v) {
	assert(s && s->top + 1 < s->cap);
	s->data[++s->top] = v;
}

void *stack_pop(_stack *s) {
	assert(s && s->top > -1);
	return s->data[s->top--];
}

void *stack_peek(_stack *s) {
	assert(s && s->top > -1);
	return s->data[s->top];
}

bool stack_is_empty(_stack *s) {
	assert(s);
	return s->top == -1;
}
