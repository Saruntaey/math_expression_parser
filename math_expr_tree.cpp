#include <stdlib.h>
#include <assert.h>
#include <stack>
#include "parser_export.h"
#include "math_expr_tree.h"
#include "operator.h"
#include "dtype.h"

static void _inorderPrint(MathExprNode *node); 

MathExprNode::MathExprNode() {
	this->parent = NULL;
	this->left = NULL;
	this->right = NULL;
}

MathExprNode::~MathExprNode() {}

MathExprTree::MathExprTree(lex_data **postfix, int size) {
	lex_data *l;
	std::stack<MathExprNode *> s;

	for (int i = 0; i < size; i++) {
		l = postfix[i];
		if (l->token_code == MATH_SPACE) continue;
		assert(is_operator(l->token_code) || is_operand(l->token_code));
		if (is_operand(l->token_code)) {
			DType *o = DType::factory(l->token_code);
			o->setValue(l->text);
			s.push(o);
		} else if (is_unary_op(l->token_code)) {
	  		MathExprNode *node = Operator::factory(l->token_code);
			MathExprNode *left = s.top(); s.pop();
			left->parent = node;
			node->left = left;
			s.push(node);
		} else {
			MathExprNode *node = Operator::factory(l->token_code);
			MathExprNode *right = s.top(); s.pop();
			MathExprNode *left = s.top(); s.pop();
			node->left = left;
			node->right = right;
			left->parent = node;
			right->parent = node;
			s.push(node);
		}
	}
	this->root = s.top(); s.pop();
	assert(s.empty());
	assert(!this->root->parent);
}

MathExprTree::~MathExprTree() {}

void MathExprTree::inorderPrint() {
	_inorderPrint(this->root);
}

static void _inorderPrint(MathExprNode *node) {
	if (!node) return;
	_inorderPrint(node->left);
	Operator *o = dynamic_cast<Operator *>(node);
	if (o) {
		printf("%s ", o->symbol.c_str());
	} else {
		DType *t = dynamic_cast<DType *>(node);
		assert(t);
		switch (t->id) {
		case MATH_INTEGER_VALUE: printf("%d ", ((DTypeInt *) t)->val); break;
		case MATH_DOUBLE_VALUE: printf("%f ", ((DTypeDouble *) t)->val); break;
		default: assert(0);
		}
	}
	_inorderPrint(node->right);
}
