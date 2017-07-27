#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <lib/init.h>
#include <lib/read.h> 
#include <lib/eval.h> 
#include <lib/print.h> 


int main() {
	static char expr[] = "(+ 1 2)";
	FILE* f;

	f = fmemopen(expr, strlen(expr), "r");
	print(eval(read(f), init()));
	term();
	fclose(f);
}
