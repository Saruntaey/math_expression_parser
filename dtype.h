#ifndef _DTYPE_
#define _DTYPE_
#include "math_expr_tree.h"
#include "math_exp_enum.h"

class DType: public MathExprNode {
protected:
	DType();
public:
	virtual ~DType();
	math_exp_type id;
	virtual void setValue(void *v) = 0;
	virtual void setValue(DType *v) = 0;
	static DType *factory(math_exp_type id);
};

class DTypeInt: public DType {
public:
	int val;
	DTypeInt(int v=0);
	virtual void setValue(void *v) override;
	virtual void setValue(DType *v) override;
};

class DTypeDouble: public DType {
public:
	double val;
	DTypeDouble(double v=0.0);
	virtual void setValue(void *v) override;
	virtual void setValue(DType *v) override;
};

#endif
