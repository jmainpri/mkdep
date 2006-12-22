dnl autoconf script for mkdep
dnl 
dnl $LAAS$
dnl
AC_REVISION($LAAS$)dnl
AC_INIT([mkdep],[2.6],[http://softs.laas.fr/openrobots/], mkdep)
AC_PREREQ(2.59)
AM_INIT_AUTOMAKE([dist-bzip2])
AM_MAINTAINER_MODE

AC_PROG_CC
AC_PROG_INSTALL
AC_CHECK_HEADERS(unistd.h, [], AC_MSG_ERROR("Not a POSIX system"))
AC_REPLACE_FUNCS(strlcat strlcpy)
AC_C_CONST

dnl
dnl Get cannonical host
dnl
AC_CANONICAL_HOST
AC_DEFINE_UNQUOTED(OS_TYPE, "$host_os")

AC_SUBST(exeext)
case ${host_os} in
   cygwin*)
   exeext=.exe
   ;;
esac

dnl --- GNU tar (for make dist only) ------------------------------------
AC_ARG_VAR(TAR, [GNU tar command])
AC_CHECK_PROGS(TAR, [gtar gnutar gnu-tar tar], [no])
if test "x$TAR" = "xno"; then
	AC_MSG_ERROR([Cannot find a tar program])
fi

AC_OUTPUT(Makefile mkdep.pc)
