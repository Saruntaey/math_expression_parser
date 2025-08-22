#ifndef _DTYPE_
#define _DTYPE_
#include "math_exp_enum.h"
#include <string>

class DType;

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

class DType: public MathExprNode {
protected:
	DType();
public:
	virtual ~DType();
	math_exp_type id;
	virtual void setValue(void *v) = 0;
	virtual void setValue(DType *v) = 0;
	virtual math_exp_type resultType() = 0;
	virtual DType *eval() = 0;
	virtual DType *clone() = 0;
	static DType *factory(math_exp_type id, const char *v, DType *(*get_val)(const char *name)=nullptr);
};

class DTypeInt: public DType {
public:
	int val;
	DTypeInt(int v=0);
	DTypeInt(const char *v);
	virtual void setValue(void *v) override;
	virtual void setValue(DType *v) override;
	virtual math_exp_type resultType() override;
	virtual DType *eval() override;
	virtual DType *clone() override;
};

class DTypeDouble: public DType {
public:
	double val;
	DTypeDouble(double v=0.0);
	DTypeDouble(const char *v);
	virtual void setValue(void *v) override;
	virtual void setValue(DType *v) override;
	virtual math_exp_type resultType() override;
	virtual DType *eval() override;
	virtual DType *clone() override;
};

class DTypeBool: public DType {
public:
	bool val;
	DTypeBool(bool v=false);
	virtual void setValue(void *v) override;
	virtual void setValue(DType *v) override;
	virtual math_exp_type resultType() override;
	virtual DType *eval() override;
	virtual DType *clone() override;
};

class DTypeVar: public DType {
private:
	std::string name;
public:
	DTypeVar(const char *name, DType *(*get_val)(const char *name)=nullptr);
	DType* (*get_val)(const char *name);
	virtual void set_get_val(DType *(*get_val)(const char *name));
	virtual void setValue(void *v) override;
	virtual void setValue(DType *v) override;
	virtual math_exp_type resultType() override;
	virtual DType *eval() override;
	virtual DType *clone() override;
};

#endif
