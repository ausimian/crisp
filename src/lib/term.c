#include "term.h"

term_t term_from_int(intptr_t i) {
	(void)i;
	return TT_NIL;
}

term_t term_from_symbol(const char* sym) {
	(void)sym;
	return TT_NIL;
}

term_t cons(term_t car, term_t cdr) {
	(void)car;
	(void)cdr;
	return TT_NIL;
}

