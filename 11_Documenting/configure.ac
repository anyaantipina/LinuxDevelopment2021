#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([guess_the_number], [1.0], [anya.antipina@gmail.com])
AM_INIT_AUTOMAKE([foreign])
DX_INIT_DOXYGEN([guess_the_number])
AC_CONFIG_SRCDIR([src/guess_the_number.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([string.h stdio.h libintl.h locale.h argp.h])

# Checks for library functions.
AC_CHECK_FUNCS([setlocale])

# Checks for library functions.
# Checks --enable options

AC_CONFIG_FILES([Makefile src/Makefile po/Makefile Doxyfile])

AC_OUTPUT
