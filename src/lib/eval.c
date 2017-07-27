#include "init.h"
#include "env.h"
#include "gc.h"
#include "eval.h"

static inline 
int eql(term_t t1, term_t t2) {
	return t1 == t2;
}

static 
term_t lookup(term_t sym, term_t env) {
	while (!nil_p(env)) {
		term_t binding = car(env);
		if (eql(car(binding), sym))
			return cdr(binding);
		env = cdr(env);
	}
	return sym;
}

static 
term_t evlis(term_t exp, term_t env) {
	if (nil_p(exp))
		return TT_NIL;

	return cons(eval(car(exp), env), evlis(cdr(exp), env));
}

static
term_t invoke_lambda(lambda_t *l, term_t args) {
    return eval(l->body, extendl(l->env, l->bindings, args));
}

static
term_t invoke(term_t func, term_t args) {
    lambda_t* l = lambda_from_term(func);
	return l->invoke(l, args);
}

term_t lambda(term_t env, term_t bindings, term_t body) {

	lambda_t* l = (lambda_t*)alloc(sizeof(lambda_t) / sizeof(term_t));	
	l->invoke   = invoke_lambda;
	l->env      = env;
	l->bindings = bindings;
	l->body     = body;

	return term_from_lambda(l);
}


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
    if (eql(first, g_define)) {
      g_env = extend(g_env, car(rest), eval(cdar(rest), env));
      return car(rest);
    } else if (eql(first, g_lambda)) {
      return lambda(env, car(rest), cdar(rest));
    } else if (eql(first, g_quote)) {
      return car(rest);
    } else if (eql(first, g_eval)) {
      return eval(car(evlis(rest, env)), env);
    } else if (eql(first, g_iff)) {
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


