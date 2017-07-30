#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

static symbol_t *syms  = NULL;
static size_t    csyms = 0;
static size_t    nsyms = 256;

static int symcmp(const void *s1, const void *s2) {
	return strcmp(*(char* const*)s1, *(char* const*)s2);
}

symbol_t mksym(const char* name) {
	symbol_t *sym = NULL;
	if (!syms) {
		syms = (symbol_t*)calloc(nsyms, sizeof(symbol_t));
	}

	while (!(sym = bsearch(&name, syms, csyms, sizeof(symbol_t), symcmp))) {
		if (csyms == nsyms) {
			nsyms *= 2;
			syms = (symbol_t*)realloc(syms, nsyms);
		}

		syms[csyms++] = strdup(name);
		qsort(syms, csyms, sizeof(symbol_t), symcmp);
	}

	return *sym;
}

void syminit() {}

void symterm() {
	for (size_t i = 0; i < csyms; ++i)
		free(syms[i]);
	free(syms);
}

