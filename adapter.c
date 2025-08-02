#include "adapter.h"

int _tokcmp(int token_code, int math_expr_enum) {
	return app_to_mexpr_enum_converter(token_code) - math_expr_enum;
}

int _tokcnv(int token_code) {
	return app_to_mexpr_enum_converter(token_code);
}
