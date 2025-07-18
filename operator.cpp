#include "operator.h"
#include <assert.h>

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
