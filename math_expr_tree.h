#ifndef _MATH_EXPR_TREE_
#define _MATH_EXPR_TREE_
#include "parser_export.h"

class MathExprNode {
protected:
	MathExprNode();
public:
	virtual ~MathExprNode();
	MathExprNode *parent;
	MathExprNode *left;
	MathExprNode *right;
};

class MathExprTree {
public:
	MathExprNode *root;
	MathExprTree(lex_data **postfix, int size);
	virtual ~MathExprTree();
	void inorderPrint();
};

#endif
