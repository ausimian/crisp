#include "env.h"

term_t g_env = TT_NIL;

term_t extend(term_t env, term_t name, term_t value) {
	return cons(cons(name, value), env);
}

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

void define(term_t name, term_t value) {
	g_env = extend(g_env, name, value);
}
