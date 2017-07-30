#include <string.h>
#include <lib/crisp.h>


int main() {
	static char expr[] = "(+ 1 2)";
	FILE* f;

	f = fmemopen(expr, strlen(expr), "r");
	print(eval(read(f), init()));
	term();
	fclose(f);
}
