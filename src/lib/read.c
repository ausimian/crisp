#include <ctype.h>
#include <stdio.h>
#include "read.h"

static
term_t reverse(term_t t) {
	term_t r = TT_NIL;
	while (!nil_p(t)) {
		r = cons(car(t), r);
		t = cdr(t);
	}
	return r;
}

static
term_t parse_list(FILE *fp) {
	term_t t = TT_NIL;
	int c;

	while ((c = getc(fp)) && c != ')') {
		ungetc(c, fp);
		t = cons(read(fp), t);
	}

	return reverse(t);
}

static
term_t parse_num(FILE *fp) {
	intptr_t v = 0;
	int c;

	while ((c = getc(fp)) && isdigit(c)) {
		v *= 10;
		v += c - '0';
	}
	ungetc(c, fp);

	return term_from_int(v);
}

static
term_t parse_symbol(FILE* fp) {
	size_t len = 0;
	int    c;
	char   sym[256];

	while ((c = getc(fp)) != EOF && c != ')' && !isspace(c)) {
		sym[len++] = toupper(c);
	}
	sym[len] = 0;
	ungetc(c, fp);

	return term_from_symbol(sym);
}

term_t read(FILE* fp) {
	int c;
	while ((c = getc(fp)) != EOF) {
		if (isspace(c)) {
			continue;
		} else if (c == '(') {
			return parse_list(fp);
		} else if (isdigit(c)) {
			ungetc(c, fp);
			return parse_num(fp);
		} else {
			ungetc(c, fp);
			return parse_symbol(fp);
		}
	}
	return TT_NIL;
}
