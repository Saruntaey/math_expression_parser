#include "operator.h"
#include <math.h>
#include <assert.h>
#include "dtype.h"


Operator::Operator(){
	this->id = MATH_INVALID;
	this->symbol = "";
	this->is_unary = false;
};
Operator::~Operator(){};

Operator *Operator::factory(math_exp_type id) {
	switch (id) {
	case MATH_PLUS: return new OperatorPlus();
	case MATH_MINUS: return new OperatorMinus();
	case MATH_MUL: return new OperatorMul();
	case MATH_DIV: return new OperatorDiv();
	case MATH_SQRT: return new OperatorSqrt();
	case MATH_SQR: return new OperatorSqr();
	case MATH_MAX: return new OperatorMax();
	case MATH_MIN: return new OperatorMin();
	case MATH_POW: return new OperatorPow();
	case MATH_LESS_THAN_EQ: return new OperatorLessThanEq();
	case MATH_LESS_THAN: return new OperatorLessThan();
	case MATH_GREATER_THAN: return new OperatorGreaterThan();
    case MATH_GREATER_THAN_EQ: return new OperatorGreaterThanEq();
	case MATH_EQ: return new OperatorEqual();
	case MATH_NOT_EQ: return new OperatorNotEqual();
	default: assert(0);
	}
}

OperatorPlus::OperatorPlus() {
	this->id = MATH_PLUS;
	this->symbol = "+";
	this->is_unary = false;
};
OperatorPlus::~OperatorPlus() {};

math_exp_type OperatorPlus::resultType(math_exp_type a, math_exp_type b) {
	switch (comb(a, b)) {
	case comb(MATH_INTEGER_VALUE, MATH_INTEGER_VALUE): return MATH_INTEGER_VALUE;
	case comb(MATH_DOUBLE_VALUE, MATH_DOUBLE_VALUE): return MATH_DOUBLE_VALUE;
	case comb(MATH_WILDCARD_VALUE, MATH_WILDCARD_VALUE): return MATH_WILDCARD_VALUE;
	case comb(MATH_INTEGER_VALUE, MATH_DOUBLE_VALUE): return MATH_DOUBLE_VALUE;
	case comb(MATH_WILDCARD_VALUE, MATH_DOUBLE_VALUE): return MATH_DOUBLE_VALUE;
	case comb(MATH_INTEGER_VALUE, MATH_WILDCARD_VALUE): return MATH_INTEGER_VALUE;
	default: return MATH_INVALID;
	}
}

math_exp_type OperatorPlus::resultType() {
	if (!this->left || !this->right) return MATH_INVALID;
	return resultType(this->left->resultType(), this->right->resultType());
}

DType *OperatorPlus::eval() {
	if (!this->left || !this->right) {
		return nullptr;
	}
	DType *res;
	DType *left = this->left->eval();
	DType *right = this->right->eval();

	res = nullptr;
	do {
		if (!left || !right) break;
		switch (left->id) {
		case MATH_INTEGER_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					res = new DTypeInt();
					((DTypeInt *) res)->val = ((DTypeInt *) left)->val + ((DTypeInt *) right)->val;
					break;
			case MATH_DOUBLE_VALUE:
					res = new DTypeDouble();
					((DTypeDouble *) res)->val = (double) ((DTypeInt *) left)->val + ((DTypeDouble *) right)->val;
					break;
			}
			break;
		case MATH_DOUBLE_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					res = new DTypeDouble();
					((DTypeDouble *) res)->val = ((DTypeDouble *) left)->val + (double) ((DTypeInt *) right)->val ;
					break;
			case MATH_DOUBLE_VALUE:
					res = new DTypeDouble();
					((DTypeDouble *) res)->val = ((DTypeDouble *) left)->val + ((DTypeDouble *) right)->val ;
					break;
			}
			break;
		}
	} while(0);

	delete left;
	delete right;
	return res;
}

OperatorMinus::OperatorMinus() {
	this->id = MATH_MINUS;
	this->symbol = "-";
	this->is_unary = false;
};
OperatorMinus::~OperatorMinus() {};

math_exp_type OperatorMinus::resultType(math_exp_type a, math_exp_type b) {
	switch (comb(a, b)) {
	case comb(MATH_INTEGER_VALUE, MATH_INTEGER_VALUE): return MATH_INTEGER_VALUE;
	case comb(MATH_DOUBLE_VALUE, MATH_DOUBLE_VALUE): return MATH_DOUBLE_VALUE;
	case comb(MATH_WILDCARD_VALUE, MATH_WILDCARD_VALUE): return MATH_WILDCARD_VALUE;
	case comb(MATH_INTEGER_VALUE, MATH_DOUBLE_VALUE): return MATH_DOUBLE_VALUE;
	case comb(MATH_WILDCARD_VALUE, MATH_DOUBLE_VALUE): return MATH_DOUBLE_VALUE;
	case comb(MATH_INTEGER_VALUE, MATH_WILDCARD_VALUE): return MATH_INTEGER_VALUE;
	default: return MATH_INVALID;
	}
}

math_exp_type OperatorMinus::resultType() {
	if (!this->left || !this->right) return MATH_INVALID;
	return resultType(this->left->resultType(), this->right->resultType());
}

DType *OperatorMinus::eval() {
	if (!this->left || !this->right) {
		return nullptr;
	}
	DType *res;
	DType *left = this->left->eval();
	DType *right = this->right->eval();

	res = nullptr;
	do {
		if (!left || !right) break;
		switch (left->id) {
		case MATH_INTEGER_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					res = new DTypeInt();
					((DTypeInt *) res)->val = ((DTypeInt *) left)->val - ((DTypeInt *) right)->val;
					break;
			case MATH_DOUBLE_VALUE:
					res = new DTypeDouble();
					((DTypeDouble *) res)->val = (double) ((DTypeInt *) left)->val - ((DTypeDouble *) right)->val;
					break;
			}
			break;
		case MATH_DOUBLE_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					res = new DTypeDouble();
					((DTypeDouble *) res)->val = ((DTypeDouble *) left)->val - (double) ((DTypeInt *) right)->val ;
					break;
			case MATH_DOUBLE_VALUE:
					res = new DTypeDouble();
					((DTypeDouble *) res)->val = ((DTypeDouble *) left)->val - ((DTypeDouble *) right)->val ;
					break;
			}
			break;
		}
	} while(0);

	delete left;
	delete right;
	return res;
}

OperatorMul::OperatorMul() {
	this->id = MATH_MUL;
	this->symbol = "*";
	this->is_unary = false;
};
OperatorMul::~OperatorMul() {};

math_exp_type OperatorMul::resultType(math_exp_type a, math_exp_type b) {
	switch (comb(a, b)) {
	case comb(MATH_INTEGER_VALUE, MATH_INTEGER_VALUE): return MATH_INTEGER_VALUE;
	case comb(MATH_DOUBLE_VALUE, MATH_DOUBLE_VALUE): return MATH_DOUBLE_VALUE;
	case comb(MATH_WILDCARD_VALUE, MATH_WILDCARD_VALUE): return MATH_WILDCARD_VALUE;
	case comb(MATH_INTEGER_VALUE, MATH_DOUBLE_VALUE): return MATH_DOUBLE_VALUE;
	case comb(MATH_WILDCARD_VALUE, MATH_DOUBLE_VALUE): return MATH_DOUBLE_VALUE;
	case comb(MATH_INTEGER_VALUE, MATH_WILDCARD_VALUE): return MATH_INTEGER_VALUE;
	default: return MATH_INVALID;
	}
}

math_exp_type OperatorMul::resultType() {
	if (!this->left || !this->right) return MATH_INVALID;
	return resultType(this->left->resultType(), this->right->resultType());
}

DType *OperatorMul::eval() {
	if (!this->left || !this->right) {
		return nullptr;
	}
	DType *res;
	DType *left = this->left->eval();
	DType *right = this->right->eval();

	res = nullptr;
	do {
		if (!left || !right) break;
		switch (left->id) {
		case MATH_INTEGER_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					res = new DTypeInt();
					((DTypeInt *) res)->val = ((DTypeInt *) left)->val * ((DTypeInt *) right)->val;
					break;
			case MATH_DOUBLE_VALUE:
					res = new DTypeDouble();
					((DTypeDouble *) res)->val = (double) ((DTypeInt *) left)->val * ((DTypeDouble *) right)->val;
					break;
			}
			break;
		case MATH_DOUBLE_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					res = new DTypeDouble();
					((DTypeDouble *) res)->val = ((DTypeDouble *) left)->val * (double) ((DTypeInt *) right)->val ;
					break;
			case MATH_DOUBLE_VALUE:
					res = new DTypeDouble();
					((DTypeDouble *) res)->val = ((DTypeDouble *) left)->val * ((DTypeDouble *) right)->val ;
					break;
			}
			break;
		}
	} while(0);

	delete left;
	delete right;
	return res;
}

OperatorDiv::OperatorDiv() {
	this->id = MATH_DIV;
	this->symbol = "/";
	this->is_unary = false;
};
OperatorDiv::~OperatorDiv() {};

math_exp_type OperatorDiv::resultType(math_exp_type a, math_exp_type b) {
	switch (comb(a, b)) {
	case comb(MATH_INTEGER_VALUE, MATH_INTEGER_VALUE): return MATH_INTEGER_VALUE;
	case comb(MATH_DOUBLE_VALUE, MATH_DOUBLE_VALUE): return MATH_DOUBLE_VALUE;
	case comb(MATH_WILDCARD_VALUE, MATH_WILDCARD_VALUE): return MATH_WILDCARD_VALUE;
	case comb(MATH_INTEGER_VALUE, MATH_DOUBLE_VALUE): return MATH_DOUBLE_VALUE;
	case comb(MATH_WILDCARD_VALUE, MATH_DOUBLE_VALUE): return MATH_DOUBLE_VALUE;
	case comb(MATH_INTEGER_VALUE, MATH_WILDCARD_VALUE): return MATH_INTEGER_VALUE;
	default: return MATH_INVALID;
	}
}

math_exp_type OperatorDiv::resultType() {
	if (!this->left || !this->right) return MATH_INVALID;
	return resultType(this->left->resultType(), this->right->resultType());
}

DType *OperatorDiv::eval() {
	if (!this->left || !this->right) {
		return nullptr;
	}
	DType *res;
	DType *left = this->left->eval();
	DType *right = this->right->eval();

	res = nullptr;
	do {
		if (!left || !right) break;
		switch (left->id) {
		case MATH_INTEGER_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					res = new DTypeInt();
					((DTypeInt *) res)->val = ((DTypeInt *) left)->val / ((DTypeInt *) right)->val;
					break;
			case MATH_DOUBLE_VALUE:
					res = new DTypeDouble();
					((DTypeDouble *) res)->val = (double) ((DTypeInt *) left)->val / ((DTypeDouble *) right)->val;
					break;
			}
			break;
		case MATH_DOUBLE_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					res = new DTypeDouble();
					((DTypeDouble *) res)->val = ((DTypeDouble *) left)->val / (double) ((DTypeInt *) right)->val ;
					break;
			case MATH_DOUBLE_VALUE:
					res = new DTypeDouble();
					((DTypeDouble *) res)->val = ((DTypeDouble *) left)->val / ((DTypeDouble *) right)->val ;
					break;
			}
			break;
		}
	} while(0);

	delete left;
	delete right;
	return res;
}

OperatorSqr::OperatorSqr() {
	this->id = MATH_SQR;
	this->symbol = "sqr";
	this->is_unary = true;
};
OperatorSqr::~OperatorSqr() {};

math_exp_type OperatorSqr::resultType(math_exp_type a, math_exp_type b) {
	switch (a) {
	case MATH_INTEGER_VALUE: return MATH_INTEGER_VALUE;
	case MATH_DOUBLE_VALUE: return MATH_DOUBLE_VALUE;
	case MATH_WILDCARD_VALUE: return MATH_WILDCARD_VALUE;
	default: return MATH_INVALID;
	}
}

math_exp_type OperatorSqr::resultType() {
	assert(!this->right);
	if (!this->left) return MATH_INVALID;
	return resultType(this->left->resultType(), MATH_INVALID);
}

DType *OperatorSqr::eval() {
	assert(!this->right);
	if (!this->left) {
		return nullptr;
	}
	DType *res;
	DType *left = this->left->eval();

	res = nullptr;
	do {
		if (!left) break;
		switch (left->id) {
		case MATH_INTEGER_VALUE:
			{
				int v = ((DTypeInt *) left)->val;
				res = new DTypeInt(v*v);
				break;
			}
		case MATH_DOUBLE_VALUE:
			{
				double v = ((DTypeDouble *) left)->val;
				res = new DTypeDouble(v*v);
				break;
			}
		}
	} while(0);

	delete left;
	return res;
}

OperatorSqrt::OperatorSqrt() {
	this->id = MATH_SQRT;
	this->symbol = "sqrt";
	this->is_unary = true;
};
OperatorSqrt::~OperatorSqrt() {};

math_exp_type OperatorSqrt::resultType(math_exp_type a, math_exp_type b) {
	switch (a) {
	case MATH_INTEGER_VALUE:
	case MATH_DOUBLE_VALUE:
	case MATH_WILDCARD_VALUE: 
			return MATH_DOUBLE_VALUE;
	default: 
			return MATH_INVALID;
	}
}

math_exp_type OperatorSqrt::resultType() {
	assert(!this->right);
	if (!this->left) return MATH_INVALID;
	return resultType(this->left->resultType(), MATH_INVALID);
}

DType *OperatorSqrt::eval() {
	assert(!this->right);
	if (!this->left) {
		return nullptr;
	}
	DType *res;
	DType *left = this->left->eval();

	res = nullptr;
	do {
		if (!left) break;
		switch (left->id) {
		case MATH_INTEGER_VALUE:
			res = new DTypeDouble(sqrt(((DTypeInt *) left)->val));
			break;
		case MATH_DOUBLE_VALUE:
			res = new DTypeDouble(sqrt(((DTypeDouble *) left)->val));
			break;
		}
	} while(0);

	delete left;
	return res;
}

OperatorPow::OperatorPow() {
	this->id = MATH_POW;
	this->symbol = "pow";
	this->is_unary = false;
};
OperatorPow::~OperatorPow() {};

bool OperatorPow::checkType(math_exp_type t) {
	switch (t) {
	case MATH_INTEGER_VALUE:
	case MATH_DOUBLE_VALUE:
	case MATH_WILDCARD_VALUE:
			return true;
	default:
			return false;
	}
}

math_exp_type OperatorPow::resultType(math_exp_type a, math_exp_type b) {
	return checkType(a) && checkType(b) ? MATH_DOUBLE_VALUE : MATH_INVALID;
}

math_exp_type OperatorPow::resultType() {
	if (!this->left || !this->right) return MATH_INVALID;
	return resultType(this->left->resultType(), this->right->resultType());
}

DType *OperatorPow::eval() {
	if (!this->left || !this->right) {
		return nullptr;
	}
	DType *res;
	DType *left = this->left->eval();
	DType *right = this->right->eval();

	res = nullptr;
	do {
		if (!left || !right) break;
		switch (left->id) {
		case MATH_INTEGER_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					{
						int l = ((DTypeInt *) left)->val;
						int r = ((DTypeInt *) right)->val;
						res = new DTypeDouble(pow(l, r));
						break;
					}
			case MATH_DOUBLE_VALUE:
					{
						int l = ((DTypeInt *) left)->val;
						double r = ((DTypeDouble *) right)->val;
						res = new DTypeDouble(pow(l, r));
						break;
					}
			}
			break;
		case MATH_DOUBLE_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					{
						double l = ((DTypeDouble *) left)->val;
						int r = ((DTypeInt *) right)->val;
						res = new DTypeDouble(pow(l, r));
						break;
					}
			case MATH_DOUBLE_VALUE:
					{
						double l = ((DTypeDouble *) left)->val;
						double r = ((DTypeDouble *) right)->val;
						res = new DTypeDouble(pow(l, r));
						break;
					}
			}
			break;
		}
	} while(0);

	delete left;
	delete right;
	return res;
}

OperatorMin::OperatorMin() {
	this->id = MATH_MIN;
	this->symbol = "min";
	this->is_unary = false;
};
OperatorMin::~OperatorMin() {};

math_exp_type OperatorMin::resultType(math_exp_type a, math_exp_type b) {
	switch (comb(a, b)) {
	case comb(MATH_INTEGER_VALUE, MATH_INTEGER_VALUE): return MATH_INTEGER_VALUE;
	case comb(MATH_DOUBLE_VALUE, MATH_DOUBLE_VALUE): return MATH_DOUBLE_VALUE;
	case comb(MATH_WILDCARD_VALUE, MATH_WILDCARD_VALUE): return MATH_WILDCARD_VALUE;
	case comb(MATH_INTEGER_VALUE, MATH_DOUBLE_VALUE): return MATH_DOUBLE_VALUE;
	case comb(MATH_WILDCARD_VALUE, MATH_DOUBLE_VALUE): return MATH_DOUBLE_VALUE;
	case comb(MATH_INTEGER_VALUE, MATH_WILDCARD_VALUE): return MATH_INTEGER_VALUE;
	default: return MATH_INVALID;
	}

}

math_exp_type OperatorMin::resultType() {
	if (!this->left || !this->right) return MATH_INVALID;
	return resultType(this->left->resultType(), this->right->resultType());
}

DType *OperatorMin::eval() {
	if (!this->left || !this->right) {
		return nullptr;
	}
	DType *res;
	DType *left = this->left->eval();
	DType *right = this->right->eval();

	res = nullptr;
	do {
		if (!left || !right) break;
		switch (left->id) {
		case MATH_INTEGER_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					{
						int l = ((DTypeInt *) left)->val;
						int r = ((DTypeInt *) right)->val;
						res = new DTypeInt(l < r ? l : r);
						break;
					}
			case MATH_DOUBLE_VALUE:
					{
						int l = ((DTypeInt *) left)->val;
						double r = ((DTypeDouble *) right)->val;
						res = l < r ? (DType *) new DTypeInt(l) : (DType *) new DTypeDouble(r); 
						break;
					}
			}
			break;
		case MATH_DOUBLE_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					{
						double l = ((DTypeDouble *) left)->val;
						int r = ((DTypeInt *) right)->val;
						res = l < r ? (DType *) new DTypeDouble(l) : (DType *) new DTypeInt(r); 
						break;
					}
			case MATH_DOUBLE_VALUE:
					{
						double l = ((DTypeDouble *) left)->val;
						double r = ((DTypeDouble *) right)->val;
						res = new DTypeDouble(l < r ? l : r);
						break;
					}
			}
			break;
		}
	} while(0);

	delete left;
	delete right;
	return res;
}

OperatorMax::OperatorMax() {
	this->id = MATH_MAX;
	this->symbol = "max";
	this->is_unary = false;
};
OperatorMax::~OperatorMax() {};

math_exp_type OperatorMax::resultType(math_exp_type a, math_exp_type b) {
	switch (comb(a, b)) {
	case comb(MATH_INTEGER_VALUE, MATH_INTEGER_VALUE): return MATH_INTEGER_VALUE;
	case comb(MATH_DOUBLE_VALUE, MATH_DOUBLE_VALUE): return MATH_DOUBLE_VALUE;
	case comb(MATH_WILDCARD_VALUE, MATH_WILDCARD_VALUE): return MATH_WILDCARD_VALUE;
	case comb(MATH_INTEGER_VALUE, MATH_DOUBLE_VALUE): return MATH_DOUBLE_VALUE;
	case comb(MATH_WILDCARD_VALUE, MATH_DOUBLE_VALUE): return MATH_DOUBLE_VALUE;
	case comb(MATH_INTEGER_VALUE, MATH_WILDCARD_VALUE): return MATH_INTEGER_VALUE;
	default: return MATH_INVALID;
	}

}

math_exp_type OperatorMax::resultType() {
	if (!this->left || !this->right) return MATH_INVALID;
	return resultType(this->left->resultType(), this->right->resultType());
}

DType *OperatorMax::eval() {
	if (!this->left || !this->right) {
		return nullptr;
	}
	DType *res;
	DType *left = this->left->eval();
	DType *right = this->right->eval();

	res = nullptr;
	do {
		if (!left || !right) break;
		switch (left->id) {
		case MATH_INTEGER_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					{
						int l = ((DTypeInt *) left)->val;
						int r = ((DTypeInt *) right)->val;
						res = new DTypeInt(l > r ? l : r);
						break;
					}
			case MATH_DOUBLE_VALUE:
					{
						int l = ((DTypeInt *) left)->val;
						double r = ((DTypeDouble *) right)->val;
						res = l > r ? (DType *) new DTypeInt(l) : (DType *) new DTypeDouble(r);
						break;
					}
			}
			break;
		case MATH_DOUBLE_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					{
						double l = ((DTypeDouble *) left)->val;
						int r = ((DTypeInt *) right)->val;
						res = l > r ? (DType *) new DTypeDouble(l) : (DType *) new DTypeInt(r); 
						break;
					}
			case MATH_DOUBLE_VALUE:
					{
						double l = ((DTypeDouble *) left)->val;
						double r = ((DTypeDouble *) right)->val;
						res = new DTypeDouble(l > r ? l : r);
						break;
					}
			}
			break;
		}
	} while(0);

	delete left;
	delete right;
	return res;
}

OperatorLessThanEq::OperatorLessThanEq() {
	this->id = MATH_LESS_THAN_EQ;
	this->symbol = "<=";
	this->is_unary = false;
};
OperatorLessThanEq::~OperatorLessThanEq() {};

math_exp_type OperatorLessThanEq::resultType(math_exp_type a, math_exp_type b) {
	switch (comb(a, b)) {
	case comb(MATH_INTEGER_VALUE, MATH_INTEGER_VALUE):
	case comb(MATH_DOUBLE_VALUE, MATH_DOUBLE_VALUE):
	case comb(MATH_WILDCARD_VALUE, MATH_WILDCARD_VALUE):
	case comb(MATH_INTEGER_VALUE, MATH_DOUBLE_VALUE):
	case comb(MATH_WILDCARD_VALUE, MATH_DOUBLE_VALUE):
	case comb(MATH_INTEGER_VALUE, MATH_WILDCARD_VALUE):
		return MATH_BOOL;
	default: 
		return MATH_INVALID;
	}

}

math_exp_type OperatorLessThanEq::resultType() {
	if (!this->left || !this->right) return MATH_INVALID;
	return resultType(this->left->resultType(), this->right->resultType());
}

DType *OperatorLessThanEq::eval() {
	if (!this->left || !this->right) {
		return nullptr;
	}
	DType *res;
	DType *left = this->left->eval();
	DType *right = this->right->eval();

	res = nullptr;
	do {
		if (!left || !right) break;
		switch (left->id) {
		case MATH_INTEGER_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					{
						int l = ((DTypeInt *) left)->val;
						int r = ((DTypeInt *) right)->val;
						res = new DTypeBool(l <= r);
						break;
					}
			case MATH_DOUBLE_VALUE:
					{
						int l = ((DTypeInt *) left)->val;
						double r = ((DTypeDouble *) right)->val;
						res = new DTypeBool(l <= r);
						break;
					}
			}
			break;
		case MATH_DOUBLE_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					{
						double l = ((DTypeDouble *) left)->val;
						int r = ((DTypeInt *) right)->val;
						res = new DTypeBool(l <= r); 
						break;
					}
			case MATH_DOUBLE_VALUE:
					{
						double l = ((DTypeDouble *) left)->val;
						double r = ((DTypeDouble *) right)->val;
						res = new DTypeBool(l <= r);
						break;
					}
			}
			break;
		}
	} while(0);

	delete left;
	delete right;
	return res;
}


OperatorLessThan::OperatorLessThan() {
	this->id = MATH_LESS_THAN;
	this->symbol = "<";
	this->is_unary = false;
};
OperatorLessThan::~OperatorLessThan() {};

math_exp_type OperatorLessThan::resultType(math_exp_type a, math_exp_type b) {
	switch (comb(a, b)) {
	case comb(MATH_INTEGER_VALUE, MATH_INTEGER_VALUE):
	case comb(MATH_DOUBLE_VALUE, MATH_DOUBLE_VALUE):
	case comb(MATH_WILDCARD_VALUE, MATH_WILDCARD_VALUE):
	case comb(MATH_INTEGER_VALUE, MATH_DOUBLE_VALUE):
	case comb(MATH_WILDCARD_VALUE, MATH_DOUBLE_VALUE):
	case comb(MATH_INTEGER_VALUE, MATH_WILDCARD_VALUE):
		return MATH_BOOL;
	default: 
		return MATH_INVALID;
	}

}

math_exp_type OperatorLessThan::resultType() {
	if (!this->left || !this->right) return MATH_INVALID;
	return resultType(this->left->resultType(), this->right->resultType());
}

DType *OperatorLessThan::eval() {
	if (!this->left || !this->right) {
		return nullptr;
	}
	DType *res;
	DType *left = this->left->eval();
	DType *right = this->right->eval();

	res = nullptr;
	do {
		if (!left || !right) break;
		switch (left->id) {
		case MATH_INTEGER_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					{
						int l = ((DTypeInt *) left)->val;
						int r = ((DTypeInt *) right)->val;
						res = new DTypeBool(l < r);
						break;
					}
			case MATH_DOUBLE_VALUE:
					{
						int l = ((DTypeInt *) left)->val;
						double r = ((DTypeDouble *) right)->val;
						res = new DTypeBool(l < r);
						break;
					}
			}
			break;
		case MATH_DOUBLE_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					{
						double l = ((DTypeDouble *) left)->val;
						int r = ((DTypeInt *) right)->val;
						res = new DTypeBool(l < r); 
						break;
					}
			case MATH_DOUBLE_VALUE:
					{
						double l = ((DTypeDouble *) left)->val;
						double r = ((DTypeDouble *) right)->val;
						res = new DTypeBool(l < r);
						break;
					}
			}
			break;
		}
	} while(0);

	delete left;
	delete right;
	return res;
}

OperatorGreaterThanEq::OperatorGreaterThanEq() {
	this->id = MATH_GREATER_THAN_EQ;
	this->symbol = ">=";
	this->is_unary = false;
};
OperatorGreaterThanEq::~OperatorGreaterThanEq() {};

math_exp_type OperatorGreaterThanEq::resultType(math_exp_type a, math_exp_type b) {
	switch (comb(a, b)) {
	case comb(MATH_INTEGER_VALUE, MATH_INTEGER_VALUE):
	case comb(MATH_DOUBLE_VALUE, MATH_DOUBLE_VALUE):
	case comb(MATH_WILDCARD_VALUE, MATH_WILDCARD_VALUE):
	case comb(MATH_INTEGER_VALUE, MATH_DOUBLE_VALUE):
	case comb(MATH_WILDCARD_VALUE, MATH_DOUBLE_VALUE):
	case comb(MATH_INTEGER_VALUE, MATH_WILDCARD_VALUE):
		return MATH_BOOL;
	default: 
		return MATH_INVALID;
	}

}

math_exp_type OperatorGreaterThanEq::resultType() {
	if (!this->left || !this->right) return MATH_INVALID;
	return resultType(this->left->resultType(), this->right->resultType());
}

DType *OperatorGreaterThanEq::eval() {
	if (!this->left || !this->right) {
		return nullptr;
	}
	DType *res;
	DType *left = this->left->eval();
	DType *right = this->right->eval();

	res = nullptr;
	do {
		if (!left || !right) break;
		switch (left->id) {
		case MATH_INTEGER_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					{
						int l = ((DTypeInt *) left)->val;
						int r = ((DTypeInt *) right)->val;
						res = new DTypeBool(l >= r);
						break;
					}
			case MATH_DOUBLE_VALUE:
					{
						int l = ((DTypeInt *) left)->val;
						double r = ((DTypeDouble *) right)->val;
						res = new DTypeBool(l >= r);
						break;
					}
			}
			break;
		case MATH_DOUBLE_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					{
						double l = ((DTypeDouble *) left)->val;
						int r = ((DTypeInt *) right)->val;
						res = new DTypeBool(l >= r); 
						break;
					}
			case MATH_DOUBLE_VALUE:
					{
						double l = ((DTypeDouble *) left)->val;
						double r = ((DTypeDouble *) right)->val;
						res = new DTypeBool(l >= r);
						break;
					}
			}
			break;
		}
	} while(0);

	delete left;
	delete right;
	return res;
}

OperatorGreaterThan::OperatorGreaterThan() {
	this->id = MATH_GREATER_THAN;
	this->symbol = ">";
	this->is_unary = false;
};
OperatorGreaterThan::~OperatorGreaterThan() {};

math_exp_type OperatorGreaterThan::resultType(math_exp_type a, math_exp_type b) {
	switch (comb(a, b)) {
	case comb(MATH_INTEGER_VALUE, MATH_INTEGER_VALUE):
	case comb(MATH_DOUBLE_VALUE, MATH_DOUBLE_VALUE):
	case comb(MATH_WILDCARD_VALUE, MATH_WILDCARD_VALUE):
	case comb(MATH_INTEGER_VALUE, MATH_DOUBLE_VALUE):
	case comb(MATH_WILDCARD_VALUE, MATH_DOUBLE_VALUE):
	case comb(MATH_INTEGER_VALUE, MATH_WILDCARD_VALUE):
		return MATH_BOOL;
	default: 
		return MATH_INVALID;
	}

}

math_exp_type OperatorGreaterThan::resultType() {
	if (!this->left || !this->right) return MATH_INVALID;
	return resultType(this->left->resultType(), this->right->resultType());
}

DType *OperatorGreaterThan::eval() {
	if (!this->left || !this->right) {
		return nullptr;
	}
	DType *res;
	DType *left = this->left->eval();
	DType *right = this->right->eval();

	res = nullptr;
	do {
		if (!left || !right) break;
		switch (left->id) {
		case MATH_INTEGER_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					{
						int l = ((DTypeInt *) left)->val;
						int r = ((DTypeInt *) right)->val;
						res = new DTypeBool(l > r);
						break;
					}
			case MATH_DOUBLE_VALUE:
					{
						int l = ((DTypeInt *) left)->val;
						double r = ((DTypeDouble *) right)->val;
						res = new DTypeBool(l > r);
						break;
					}
			}
			break;
		case MATH_DOUBLE_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					{
						double l = ((DTypeDouble *) left)->val;
						int r = ((DTypeInt *) right)->val;
						res = new DTypeBool(l > r); 
						break;
					}
			case MATH_DOUBLE_VALUE:
					{
						double l = ((DTypeDouble *) left)->val;
						double r = ((DTypeDouble *) right)->val;
						res = new DTypeBool(l > r);
						break;
					}
			}
			break;
		}
	} while(0);

	delete left;
	delete right;
	return res;
}

OperatorEqual::OperatorEqual() {
	this->id = MATH_EQ;
	this->symbol = "=";
	this->is_unary = false;
};
OperatorEqual::~OperatorEqual() {};

math_exp_type OperatorEqual::resultType(math_exp_type a, math_exp_type b) {
	switch (comb(a, b)) {
	case comb(MATH_INTEGER_VALUE, MATH_INTEGER_VALUE):
	case comb(MATH_DOUBLE_VALUE, MATH_DOUBLE_VALUE):
	case comb(MATH_WILDCARD_VALUE, MATH_WILDCARD_VALUE):
	case comb(MATH_INTEGER_VALUE, MATH_DOUBLE_VALUE):
	case comb(MATH_WILDCARD_VALUE, MATH_DOUBLE_VALUE):
	case comb(MATH_INTEGER_VALUE, MATH_WILDCARD_VALUE):
		return MATH_BOOL;
	default: 
		return MATH_INVALID;
	}

}

math_exp_type OperatorEqual::resultType() {
	if (!this->left || !this->right) return MATH_INVALID;
	return resultType(this->left->resultType(), this->right->resultType());
}

DType *OperatorEqual::eval() {
	if (!this->left || !this->right) {
		return nullptr;
	}
	DType *res;
	DType *left = this->left->eval();
	DType *right = this->right->eval();

	res = nullptr;
	do {
		if (!left || !right) break;
		switch (left->id) {
		case MATH_INTEGER_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					{
						int l = ((DTypeInt *) left)->val;
						int r = ((DTypeInt *) right)->val;
						res = new DTypeBool(l == r);
						break;
					}
			case MATH_DOUBLE_VALUE:
					{
						int l = ((DTypeInt *) left)->val;
						double r = ((DTypeDouble *) right)->val;
						res = new DTypeBool(l == r);
						break;
					}
			}
			break;
		case MATH_DOUBLE_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					{
						double l = ((DTypeDouble *) left)->val;
						int r = ((DTypeInt *) right)->val;
						res = new DTypeBool(l == r); 
						break;
					}
			case MATH_DOUBLE_VALUE:
					{
						double l = ((DTypeDouble *) left)->val;
						double r = ((DTypeDouble *) right)->val;
						res = new DTypeBool(l == r);
						break;
					}
			}
			break;
		}
	} while(0);

	delete left;
	delete right;
	return res;
}

OperatorNotEqual::OperatorNotEqual() {
	this->id = MATH_EQ;
	this->symbol = "=";
	this->is_unary = false;
};
OperatorNotEqual::~OperatorNotEqual() {};

math_exp_type OperatorNotEqual::resultType(math_exp_type a, math_exp_type b) {
	switch (comb(a, b)) {
	case comb(MATH_INTEGER_VALUE, MATH_INTEGER_VALUE):
	case comb(MATH_DOUBLE_VALUE, MATH_DOUBLE_VALUE):
	case comb(MATH_WILDCARD_VALUE, MATH_WILDCARD_VALUE):
	case comb(MATH_INTEGER_VALUE, MATH_DOUBLE_VALUE):
	case comb(MATH_WILDCARD_VALUE, MATH_DOUBLE_VALUE):
	case comb(MATH_INTEGER_VALUE, MATH_WILDCARD_VALUE):
		return MATH_BOOL;
	default: 
		return MATH_INVALID;
	}

}

math_exp_type OperatorNotEqual::resultType() {
	if (!this->left || !this->right) return MATH_INVALID;
	return resultType(this->left->resultType(), this->right->resultType());
}

DType *OperatorNotEqual::eval() {
	if (!this->left || !this->right) {
		return nullptr;
	}
	DType *res;
	DType *left = this->left->eval();
	DType *right = this->right->eval();

	res = nullptr;
	do {
		if (!left || !right) break;
		switch (left->id) {
		case MATH_INTEGER_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					{
						int l = ((DTypeInt *) left)->val;
						int r = ((DTypeInt *) right)->val;
						res = new DTypeBool(l != r);
						break;
					}
			case MATH_DOUBLE_VALUE:
					{
						int l = ((DTypeInt *) left)->val;
						double r = ((DTypeDouble *) right)->val;
						res = new DTypeBool(l != r);
						break;
					}
			}
			break;
		case MATH_DOUBLE_VALUE:
			switch (right->id) {
			case MATH_INTEGER_VALUE:
					{
						double l = ((DTypeDouble *) left)->val;
						int r = ((DTypeInt *) right)->val;
						res = new DTypeBool(l != r); 
						break;
					}
			case MATH_DOUBLE_VALUE:
					{
						double l = ((DTypeDouble *) left)->val;
						double r = ((DTypeDouble *) right)->val;
						res = new DTypeBool(l != r);
						break;
					}
			}
			break;
		}
	} while(0);

	delete left;
	delete right;
	return res;
}
