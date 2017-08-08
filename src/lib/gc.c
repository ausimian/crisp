#include <stddef.h>
#include "crisp.h"
#include "gc.h"

/*
 * A semi-space copying collector. Highly inefficient and as dumb as a rock.
 */

#define ARENA_SZ 16384

static term_t arena1[ARENA_SZ];
static term_t arena2[ARENA_SZ];

static term_t *curr = arena1;
static size_t  cidx = 0;

static term_t *next = arena2;
static size_t  nidx = 0;

static inline bool in_arena(const term_t* arena, const void *p) {
	return p >= (const void*)curr && p < (const void*)&arena[ARENA_SZ];
}

/*
 * Deep copy reachable terms from the current arena to the next,
 * skipping already copied terms.
 */
static term_t copy(term_t t) {
	size_t idx = nidx;

	switch (ttype(t)) {
		case TT_CONS:	
			{
				cons_t *src = cons_from_term(t);
				if (in_arena(curr, src))
				{
					cons_t *dst = (cons_t*)&next[idx];
					nidx += sizeof(cons_t) / sizeof(term_t);

					src->car = dst->car = copy(car(t));
					src->cdr = dst->cdr = copy(cdr(t));

					return term_from_cons(dst);
				}
			}
			break;
		case TT_HEAP:
			if (t == TT_NIL)
				break;
				
			lambda_t *src = lambda_from_term(t);
			if (in_arena(curr, src))
			{
				lambda_t *dst = (lambda_t*)&next[idx];
				nidx += sizeof(lambda_t) / sizeof(term_t);

				dst->htype    = HT_LAMBDA;
				dst->invoke   = src->invoke;
				src->env      = dst->env      = copy(src->env);
				src->bindings = dst->bindings = copy(src->bindings);
				src->body     = dst->body     = copy(src->body);

				return term_from_lambda(dst);
			}
			break;
		default:
			break;
	}
	return t;
}

static void swap() {
	// swap the arenas round
	term_t *tmp = next;
	next = curr;
	curr = tmp;

	// and their indices
	cidx = nidx;
	nidx = 0;
}

void gc() {
	// copy the reachable objects from the current arena to the next arena
	g_env = copy(g_env);
	// swap the arenas
	swap();
}

term_t* alloc(size_t n_terms) {
	term_t *p;

	if (cidx + n_terms >= ARENA_SZ)
		gc();

	if (cidx + n_terms == ARENA_SZ) 
		return NULL;

	p = &curr[cidx];
	cidx += n_terms;

	return p;
};
