#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <lib/symtab.h>
#include <lib/read.h> 


int main() {
	static char expr[] = "(+ 1 2)";
	FILE* f;

	mksym("+");
	f = fmemopen(expr, strlen(expr), "r");
	read(f);
	fclose(f);
}
