#ifndef _MATH_EXPR_TREE_
#define _MATH_EXPR_TREE_

#include <list>
#include "parser_export.h"
#include "math_exp_enum.h"

class DType;
class DTypeVar;

class MathExprNode {
protected:
	MathExprNode();
public:
	virtual ~MathExprNode();
	MathExprNode *parent;
	MathExprNode *left;
	MathExprNode *right;
	virtual math_exp_type resultType() = 0;
	virtual DType *eval() = 0;
};

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
