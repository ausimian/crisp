#include <stdio.h>
#include "init.h"
#include "env.h"
#include "gc.h"
#include "symtab.h"

term_t g_define;
term_t g_lambda;
term_t g_quote;
term_t g_eval;
term_t g_iff;

static inline term_t mkbuiltin(const char* sym) {
	return term_from_symbol(mksym(sym));
}

static term_t add(lambda_t* ignored, term_t args) {
	(void)ignored;
	int sum = 0;
	while (!nil_p(args)) {
		sum += int_from_term(car(args));
		args = cdr(args);
	}
	return term_from_int(sum);
}

static term_t lambda(term_t (*native)(lambda_t*, term_t)) {

	lambda_t* l = (lambda_t*)alloc(sizeof(lambda_t) / sizeof(term_t));	
	l->invoke   = native;
	l->env      = TT_NIL;
	l->bindings = TT_NIL;
	l->body     = TT_NIL;

	return term_from_lambda(l);
}

term_t init() {
	syminit();

	// Install keywords
	g_define = mkbuiltin("define");
	g_lambda = mkbuiltin("lambda");
	g_quote  = mkbuiltin("quote");
	g_eval   = mkbuiltin("eval");
	g_iff    = mkbuiltin("if");

	// Install native 
	define(mkbuiltin("+"), lambda(add));

	return g_env;
}

void term() {
	symterm();
	printf("\n\n");
}
