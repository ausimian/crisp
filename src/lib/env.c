#include "crisp.h"

/*
 * An enviroment is a list of lists of cons-cells, initially empty.
 */
term_t g_env = TT_NIL;

/*
 * Extend the given environment with a new binding
 */
term_t extend(term_t env, term_t name, term_t value) {
	return cons(cons(name, value), env);
}

/* 
 * Extend the given environment with a set of new bindings.
 */
term_t extendl(term_t env, term_t names, term_t values) {
	while (!nil_p(names)) {
		term_t name  = car(names);
		term_t value = car(values);
		env = extend(env, name, value);

		names = cdr(names);
		values = cdr(values);
	}
	return env;
}

/*
 * Extend the global environment with the given binding.
 */
void define(term_t name, term_t value) {
	g_env = extend(g_env, name, value);
}

/*
 * Lookup the given symbol in the environment, returning its value if found
 * or the symbol if not (this is what I think some of the original Lisps did,
 * might change it).
 */
term_t lookup(term_t sym, term_t env) {
	while (!nil_p(env)) {
		term_t binding = car(env);
		if (eq(car(binding), sym))
			return cdr(binding);
		env = cdr(env);
	}
	return sym;
}

