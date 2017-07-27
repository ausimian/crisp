#pragma once

#include "term.h"

extern term_t g_env;

/*
 * Extend the environment with a single name/value pair.
 */
term_t extend(term_t env, term_t name, term_t value);

/*
 * Extend the environment with multiple name/value pairs.
 */
term_t extendl(term_t env, term_t names, term_t values);

/*
 * Define a name-value pair in the current global environment
 */
void define(term_t name, term_t value);
