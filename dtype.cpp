#include "dtype.h"
#include <stdlib.h>
#include <assert.h>

DType::DType() {
	this->id = MATH_INVALID;
}
DType::~DType() {}

DType *DType::factory(math_exp_type id, const char *v, DType *(*get_val)(const char *name)) {
	switch (id) {
	case MATH_INTEGER_VALUE: return new DTypeInt(v);
	case MATH_DOUBLE_VALUE: return new DTypeDouble(v);
	case MATH_IDENTIFIER: return new DTypeVar(v, get_val);
	default: assert(0);
	}
}

DTypeInt::DTypeInt(int v) {
	this->id = MATH_INTEGER_VALUE;
	this->val = v;
}

DTypeInt::DTypeInt(const char *v): DTypeInt() {
	setValue((void *) v);
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
	return new DTypeInt(this->val);
}

DTypeDouble::DTypeDouble(double v) {
	this->id = MATH_DOUBLE_VALUE;
	this->val = v;
}

DTypeDouble::DTypeDouble(const char* v): DTypeDouble() {
	setValue((void *) v);
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
	return new DTypeDouble(this->val);
}

DTypeBool::DTypeBool(bool v) {
	this->id = MATH_BOOL;
	this->val = v;
}

void DTypeBool::setValue(void *v) {
	// empty
}

void DTypeBool::setValue(DType *v) {
	this->val = dynamic_cast<DTypeBool *>(v)->val;
}

math_exp_type DTypeBool::resultType() {
	return MATH_BOOL;
}

DType *DTypeBool::eval() {
	return clone();
}

DType *DTypeBool::clone() {
	return new DTypeBool(this->val);
}

DTypeVar::DTypeVar(const char *name, DType *(*get_val)(const char *name)) {
	this->id = MATH_IDENTIFIER;
	this->name.assign(name);
	this->get_val = get_val;
}



void DTypeVar::set_get_val(DType *(*get_val)(const char *name)) {
	this->get_val = get_val;
}

void DTypeVar::setValue(void *v) {
	// empty
}

void DTypeVar::setValue(DType *v) {
	// empty
}

math_exp_type DTypeVar::resultType() {
	if (!this->get_val) return MATH_WILDCARD_VALUE;
	DType *t = this->get_val(this->name.c_str());
	if (!t) return MATH_WILDCARD_VALUE;
	return t->id;
}

DType *DTypeVar::eval() {
	if (!this->get_val) return nullptr;
	return this->get_val(this->name.c_str());
}

DType *DTypeVar::clone() {
	DTypeVar *c = new DTypeVar(this->name.c_str());
	*c = *this;
	c->left = nullptr;
	c->right = nullptr;
	c->parent = nullptr;
	return c;
}
