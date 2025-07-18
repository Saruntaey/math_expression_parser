#include "dtype.h"
#include <stdlib.h>
#include <assert.h>

DType::DType() {
	this->id = MATH_INVALID;
}
DType::~DType() {}

DType *DType::factory(math_exp_type id) {
	switch (id) {
	case MATH_INTEGER_VALUE: return new DTypeInt();
	case MATH_DOUBLE_VALUE: return new DTypeDouble();
	default: assert(0);
	}
}

DTypeInt::DTypeInt(int v) {
	this->id = MATH_INTEGER_VALUE;
	this->val = v;
}

void DTypeInt::setValue(void *v) {
	this->val = atoi((char*) v);
}

void DTypeInt::setValue(DType *v) {
	this->val = dynamic_cast<DTypeInt *>(v)->val;
}

math_exp_type DTypeInt::resultType() {
	return MATH_INTEGER_VALUE;
}

DType *DTypeInt::eval() {
	return clone();
}

DType *DTypeInt::clone() {
	DTypeInt *c = new DTypeInt();
	c->val = this->val;
	return c;
}

DTypeDouble::DTypeDouble(double v) {
	this->id = MATH_DOUBLE_VALUE;
	this->val = v;
}

void DTypeDouble::setValue(void *v) {
	this->val = atof((char*) v);
}

void DTypeDouble::setValue(DType *v) {
	this->val = dynamic_cast<DTypeDouble *>(v)->val;
}

math_exp_type DTypeDouble::resultType() {
	return MATH_DOUBLE_VALUE;
}

DType *DTypeDouble::eval() {
	return clone();
}

DType *DTypeDouble::clone() {
	DTypeDouble *c = new DTypeDouble();
	c->val = this->val;
	return c;
}
