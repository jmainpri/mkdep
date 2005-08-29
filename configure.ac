dnl autoconf script for mkdep
dnl 
dnl $LAAS$
dnl
AC_REVISION($LAAS$)dnl
AC_INIT([mkdep],[2.4],[openrobots@laas.fr])
AC_PREREQ(2.59)

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

AC_OUTPUT(Makefile)
