#include <stdio.h>
#include "print.h"

void print(term_t t) {
	if (nil_p(t)) {
		printf("NIL");
		return;
	}

	switch (ttype(t)) {
		case TT_CONS:
			putchar('(');
			do {
				print(car(t));
				if (!nil_p(cdr(t)))
					putchar(' ');
				t = cdr(t);
			} while(!nil_p(t));
			putchar(')');
			break;
		case TT_INT:
			printf("%d", int_from_term(t));
			break;
		case TT_SYM:
			printf("%s", symbol_from_term(t));
			break;
		case TT_HEAP:
			{
				lambda_t* l = lambda_from_term(t);
				printf("LAMBDA(%p)", nil_p(l->body) ? (void*)l->invoke : (void*)l->body);
			}
			break;
	}
}
