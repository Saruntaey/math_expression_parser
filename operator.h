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
	virtual DType *eval() = 0;
};

class OperatorPlus: public Operator {
private:
	math_exp_type resultType(math_exp_type a, math_exp_type b); 
public:
	OperatorPlus();
	~OperatorPlus();
	virtual math_exp_type resultType() override;
	virtual DType *eval() override;
};

class OperatorMinus: public Operator {
private:
	math_exp_type resultType(math_exp_type a, math_exp_type b); 
public:
	OperatorMinus();
	~OperatorMinus();
	virtual math_exp_type resultType() override;
	virtual DType *eval() override;
};

class OperatorMul: public Operator {
private:
	math_exp_type resultType(math_exp_type a, math_exp_type b); 
public:
	OperatorMul();
	~OperatorMul();
	virtual math_exp_type resultType() override;
	virtual DType *eval() override;
};

class OperatorDiv: public Operator {
private:
	math_exp_type resultType(math_exp_type a, math_exp_type b); 
public:
	OperatorDiv();
	~OperatorDiv();
	virtual math_exp_type resultType() override;
	virtual DType *eval() override;
};

class OperatorSqr: public Operator {
private:
	math_exp_type resultType(math_exp_type a, math_exp_type b); 
public:
	OperatorSqr();
	~OperatorSqr();
	virtual math_exp_type resultType() override;
	virtual DType *eval() override;
};

class OperatorSqrt: public Operator {
private:
	math_exp_type resultType(math_exp_type a, math_exp_type b); 
public:
	OperatorSqrt();
	~OperatorSqrt();
	virtual math_exp_type resultType() override;
	virtual DType *eval() override;
};

class OperatorPow: public Operator {
private:
	math_exp_type resultType(math_exp_type a, math_exp_type b); 
	bool checkType(math_exp_type t);
public:
	OperatorPow();
	~OperatorPow();
	virtual math_exp_type resultType() override;
	virtual DType *eval() override;
};

class OperatorMin: public Operator {
private:
	math_exp_type resultType(math_exp_type a, math_exp_type b); 
public:
	OperatorMin();
	~OperatorMin();
	virtual math_exp_type resultType() override;
	virtual DType *eval() override;
};

class OperatorMax: public Operator {
private:
	math_exp_type resultType(math_exp_type a, math_exp_type b); 
public:
	OperatorMax();
	~OperatorMax();
	virtual math_exp_type resultType() override;
	virtual DType *eval() override;
};

#endif
