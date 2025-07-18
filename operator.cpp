#include "operator.h"
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
