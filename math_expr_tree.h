#ifndef _MATH_EXPR_TREE_
#define _MATH_EXPR_TREE_

#include <list>
#include "parser_export.h"
#include "dtype.h"

class MathExprTree {
private:
	void clear(MathExprNode *node);
	std::list<DTypeVar *> vars;
public:
	MathExprNode *root;
	MathExprTree(lex_data **postfix, int size, DType *(get_val)(const char *name)=nullptr);
	virtual ~MathExprTree();
	void inorderPrint();
	bool valid();
	DType *eval();
	void setGetVal(DType *(*get_val)(const char *name));
};

#endif
