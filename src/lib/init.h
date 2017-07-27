#pragma once

#include "term.h"

extern term_t g_define;
extern term_t g_lambda;
extern term_t g_quote;
extern term_t g_eval;
extern term_t g_iff;

term_t init();
void   term();
