#ifndef _OPERATOR_
#define _OPERATOR_
#include <string>
#include <stdbool.h>
#include "math_exp_enum.h"
#include "math_expr_tree.h"

class Operator: public MathExprNode {
protected:
	Operator();
public:
	virtual ~Operator();
	math_exp_type id;
	std::string symbol;
	bool is_unary;
	static Operator *factory(math_exp_type id);
};

class OperatorPlus: public Operator {
public:
	OperatorPlus();
	~OperatorPlus();
};

class OperatorMinus: public Operator {
public:
	OperatorMinus();
	~OperatorMinus();
};

class OperatorMul: public Operator {
public:
	OperatorMul();
	~OperatorMul();
};

class OperatorDiv: public Operator {
public:
	OperatorDiv();
	~OperatorDiv();
};

#endif
