#include "crisp.h"
#include "gc.h"

/*
 * Evaluate the list of terms (typically function arguments) in the given
 * environment.
 */
static 
term_t evlis(term_t exp, term_t env) {
	if (nil_p(exp))
		return TT_NIL;

	return cons(eval(car(exp), env), evlis(cdr(exp), env));
}

/*
 * Apply the arguments to the lambda (plus its enviromnent)
 */
static
term_t invoke_lambda(lambda_t *l, term_t args) {
	return eval(l->body, extendl(l->env, l->bindings, args));
}

/*
 * Apply the arguments to the provided function (which may be
 * either a lambda or a built-in function.)
 */
static
term_t invoke(term_t func, term_t args) {
	lambda_t* l = lambda_from_term(func);
	return l->invoke(l, args);
}

/*
 * Build a lambda term from an environment, a current set of bindings and
 * a body.
 */
term_t lambda(term_t env, term_t bindings, term_t body) {

	lambda_t* l = (lambda_t*)alloc(sizeof(lambda_t) / sizeof(term_t));	
	l->invoke   = invoke_lambda;
	l->env      = env;
	l->bindings = bindings;
	l->body     = body;

	return term_from_lambda(l);
}


/*
 * Evaluation
 *
 * 1. Atoms eval to themselves.
 * 2. Symbols eval to their binding.
 * 3. Lists are either special forms (such as lambda or if) or application.
 */
term_t eval(term_t exp, term_t env) {
	if (!cons_p(exp)) {
		if (sym_p(exp)) {
			return lookup(exp, env);
		} else {
			return exp;
		}
	} else {
		term_t first = car(exp);
		term_t rest  = cdr(exp);
		if (eq(first, g_define)) {
			g_env = extend(g_env, car(rest), eval(cdar(rest), env));
			return car(rest);
		} else if (eq(first, g_lambda)) {
			return lambda(env, car(rest), cdar(rest));
		} else if (eq(first, g_quote)) {
			return car(rest);
		} else if (eq(first, g_progn)) {
			term_t r = TT_NIL;
			while (!nil_p(car(rest))) {
				r    = eval(car(rest), env);
				rest = cdr(rest);
			}
			return r;
		} else if (eq(first, g_eval)) {
			return eval(car(evlis(rest, env)), env);
		} else if (eq(first, g_iff)) {
			if (!nil_p(eval(car(rest), env))) {
				return eval(cdar(rest), env);
			} else {
				return eval(cddar(rest), env);
			}
		} else {
			return invoke(eval(first, env), evlis(rest, env));
		}
	}
}


