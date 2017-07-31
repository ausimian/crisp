#include <string.h>
#include <lib/crisp.h>

void repl() {
        for (;;) {
                print(eval(read(stdin), g_env));
                putc('\n', stdout);
        }
}

int main() {
	init();
        repl();
        term();
}
