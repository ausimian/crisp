#include <inttypes.h>
#include <stdio.h>
#include <lib/term.h> 

int main() {
	term_t t = term_from_int(23);
	printf("Hello, world %" PRIiPTR ".\n", int_from_term(t));
}
