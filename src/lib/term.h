#pragma once

#include <stdint.h>
#include <stdbool.h>

/*--
	term.h

	The definition of the unitype term_t. Holds (or points to) all supported
	types.

	The runtime encoding uses low bits to distinguish between value types and
	heap types. The bottom 2 bits of the value are used to tag the type. These
	tag bits must be removed before the value can be used.

	00 - a pointer to a heap type, or NIL
	01 - a native integer, using the remaining bits in the word.
	10 - a symbol (pointer to the symbol table)
	11 - a cons pair pointer. Technically also a heap type, but encoded directly for performance.

  --*/	

typedef uintptr_t term_t;

#define TT_HEAP  ((term_t)0)
#define TT_INT   ((term_t)1)
#define TT_SYM   ((term_t)2)
#define TT_CONS  ((term_t)3)

#define TT_MASK       ((term_t)3)
#define TT_MASK_WIDTH 2

static inline 
uintptr_t ttype(term_t t) { return t & TT_MASK; }

// NIL
#define TT_NIL  ((term_t)0)
static inline 
bool nil_p(term_t t) { return t == TT_NIL; }


// Native integers
static inline 
bool int_p(term_t t) { return ttype(t) == TT_INT; }

static inline
intptr_t int_from_term(term_t t) { return ((intptr_t)(t >> TT_MASK_WIDTH)); }

term_t term_from_int(intptr_t i);


// Symbols
static inline 
bool sym_p(term_t t) { return ttype(t) == TT_SYM; }

static inline
const char* symbol_from_term(term_t t) { return ((const char*)(t & ~TT_MASK)); }

term_t term_from_symbol(const char* sym);


// Cons cells
static inline 
bool cons_p(term_t t) { return ttype(t) == TT_CONS; }

typedef struct cons_t {
	term_t car;
	term_t cdr;
} cons_t;

static inline
cons_t* cons_from_term(term_t t) { return (cons_t*)(t & ~TT_MASK); }

static inline 
term_t car(term_t t) { return cons_from_term(t)->car; }

static inline 
term_t cdr(term_t t) { return cons_from_term(t)->cdr; }

static inline
term_t term_from_cons(cons_t *p) { return ((term_t)p) | TT_CONS; }

term_t cons(term_t car, term_t cdr);
