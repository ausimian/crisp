#pragma once

typedef char* symbol_t;

void syminit();
void symterm();

symbol_t mksym(const char* name);

