#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([crisp], [0.1], [nick@ausimian.net])
AC_CONFIG_SRCDIR([src/bin/main.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror])

# Checks for programs.
AC_PROG_CC_C99
AC_PROG_CPP
AC_PROG_RANLIB
AM_PROG_AR
AM_SILENT_RULES([yes])


# Us the C language and compiler for the following checks
AC_LANG([C])

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdio.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
