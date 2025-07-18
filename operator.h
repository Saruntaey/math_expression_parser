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
	virtual math_exp_type resultType() = 0;
};

class OperatorPlus: public Operator {
private:
	math_exp_type resultType(math_exp_type a, math_exp_type b); 
public:
	OperatorPlus();
	~OperatorPlus();
	math_exp_type resultType() override;
};

class OperatorMinus: public Operator {
private:
	math_exp_type resultType(math_exp_type a, math_exp_type b); 
public:
	OperatorMinus();
	~OperatorMinus();
	math_exp_type resultType() override;
};

class OperatorMul: public Operator {
private:
	math_exp_type resultType(math_exp_type a, math_exp_type b); 
public:
	OperatorMul();
	~OperatorMul();
	math_exp_type resultType() override;
};

class OperatorDiv: public Operator {
private:
	math_exp_type resultType(math_exp_type a, math_exp_type b); 
public:
	OperatorDiv();
	~OperatorDiv();
	math_exp_type resultType() override;
};

#endif
