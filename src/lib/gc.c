#include <stddef.h>
#include "term.h"
#include "env.h"

#define ARENA_SZ 16384

static cons_t arena1[ARENA_SZ];
static cons_t arena2[ARENA_SZ];

static cons_t *curr = arena1;
static size_t  cidx = 0;

static cons_t *next = arena2;
static size_t  nidx = 0;

static inline bool in_curr_arena(cons_t *p) {
	return p >= curr && p < &curr[ARENA_SZ];
}

static term_t copy(term_t root) {
	if (ttype(root) == TT_CONS) {
		// cons cells are recursively copied (if they haven't already been)
		cons_t *src = cons_from_term(root);
		if (in_curr_arena(src)) {
			size_t idx = nidx++;
			src->car = next[idx].car = copy(car(root));
			src->cdr = next[idx].cdr = copy(cdr(root));
			return term_from_cons(&next[idx]);
		}
	}
	return root;
}

static void swap() {
	// swap the arenas round
	cons_t *tmp = next;
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

cons_t* mkcons() {
	if (cidx == ARENA_SZ)
		gc();

	if (cidx == ARENA_SZ) 
		return NULL;

	return &curr[cidx++];
};
