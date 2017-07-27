#include "term.h"
#include "symtab.h"
#include "gc.h"

term_t term_from_int(intptr_t i) {
	return (i << TT_MASK_WIDTH) | TT_INT;
}

term_t term_from_symbol(const char* name) {
	return ((term_t)(mksym(name))) | TT_SYM;
}

term_t cons(term_t car, term_t cdr) {
	cons_t *p = (cons_t*)alloc(sizeof(cons_t) / sizeof(term_t));
	p->car = car;
	p->cdr = cdr;
	return term_from_cons(p);
}

