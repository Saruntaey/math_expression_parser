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

OperatorMinus::OperatorMinus() {
	this->id = MATH_MINUS;
	this->symbol = "-";
	this->is_unary = false;
};
OperatorMinus::~OperatorMinus() {};

OperatorMul::OperatorMul() {
	this->id = MATH_MUL;
	this->symbol = "*";
	this->is_unary = false;
};
OperatorMul::~OperatorMul() {};

OperatorDiv::OperatorDiv() {
	this->id = MATH_DIV;
	this->symbol = "/";
	this->is_unary = false;
};
OperatorDiv::~OperatorDiv() {};
