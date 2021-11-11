#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash], [rhash_library_init, rhash_file, rhash_msg, rhash_print_bytes], [], [AC_MSG_ERROR([Rhash is needed])])
AC_ARG_WITH([readline],
    [AS_HELP_STRING([--without-readline],
    [disable support for readline])],
    [],
    [with_readline=yes])
HAVE_READLINE=
AS_IF([test "x$with_readline" != xno],
[AC_CHECK_LIB([readline], [readline], 
    [AC_SUBST([HAVE_READLINE], ["-lreadline -lrhash"])
    AC_DEFINE([HAVE_LIBREADLINE], [1], [Define if you have libreadline])], 
    [AC_MSG_FAILURE(
        [readline test failed (--without-readline to disable)])],
    ["-lrhash"]
    )])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
# Checks --enable options
AC_ARG_ENABLE([readline],
    AS_HELP_STRING([--enable-readline], [Enable readline library]),
    AC_DEFINE(ENABLE_READLINE, [], [Readline library])
    )

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
