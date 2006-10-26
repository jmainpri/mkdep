#
# Copyright (c) 2006 LAAS/CNRS                        --  Thu Oct 16 2006
# All rights reserved.
#
# Redistribution  and  use in source   and binary forms,  with or without
# modification, are permitted provided that  the following conditions are
# met:
#
#   1. Redistributions  of  source code must  retain  the above copyright
#      notice, this list of conditions and the following disclaimer.
#   2. Redistributions in binary form must  reproduce the above copyright
#      notice,  this list of  conditions and  the following disclaimer in
#      the  documentation   and/or  other  materials   provided with  the
#      distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE  AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY  EXPRESS OR IMPLIED WARRANTIES, INCLUDING,  BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES   OF MERCHANTABILITY AND  FITNESS  FOR  A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO  EVENT SHALL THE AUTHOR OR  CONTRIBUTORS
# BE LIABLE FOR ANY DIRECT, INDIRECT,  INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING,  BUT  NOT LIMITED TO, PROCUREMENT  OF
# SUBSTITUTE  GOODS OR SERVICES;  LOSS   OF  USE,  DATA, OR PROFITS;   OR
# BUSINESS  INTERRUPTION) HOWEVER CAUSED AND  ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE  USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

dnl --- Look for the openrobots mkdep executable ---------------------

AC_DEFUN([ROBOT_PROG_MKDEP],
[
   m4_define([MKDEP_PKG_TEXT], [
Package requirements (openrobots mkdep) were not met.
Consider adjusting the PKG_CONFIG_PATH environment variable if you
installed software in a non-standard prefix.])

   AC_MSG_CHECKING([for mkdep])
   PKG_CHECK_EXISTS(mkdep, [
     _PKG_CONFIG(MKDEP, [variable=program], [mkdep])
     AC_MSG_RESULT($pkg_cv_MKDEP)
     AC_CACHE_CHECK(
     [whether mkdep accepts -I/-D options], ac_cv_robot_mkdep,
      [
         if $pkg_cv_MKDEP -I foo -D bar 1>/dev/null 2>&1; then
	    ac_cv_robot_mkdep=yes;
	 else
	    ac_cv_robot_mkdep=no;
         fi
      ])
     if test x"${ac_cv_robot_mkdep}" = xno; then
        AC_MSG_ERROR(MKDEP_PKG_TEXT)
     fi 
     AC_SUBST(MKDEP, $pkg_cv_MKDEP)
   ], [
        AC_MSG_ERROR(MKDEP_PKG_TEXT)
   ])
])
