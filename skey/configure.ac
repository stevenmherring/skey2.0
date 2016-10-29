#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.59])
AC_INIT(SKEY, 2.0, stevenmherring@gmail.com)
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([src/config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AM_PROG_LIBTOOL

#endian check
AC_C_BIGENDIAN

# Init automake
AM_INIT_AUTOMAKE([1.9.6 no-define])
#CFLAGS="$CFLAGS -Wall -Werror -lcrypt"
AC_CONFIG_FILES([Makefile man/Makefile scripts/Makefile lib/Makefile include/Makefile src/Makefile])

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h sgtty.h shadow.h stdlib.h string.h strings.h sys/file.h sys/ioctl.h sys/param.h sys/systeminfo.h sys/time.h sys/quota.h syslog.h termio.h termios.h unistd.h signal.h pwd.h stdarg.h time.h crypt.h ctype.h errno.h ioctl.h pwd.h grp.h sys/ioctl.h assert.h sys/resource.h sys/grp.h stdio.h])

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([gethostname getpass isascii memset setenv getenv strchr strdup sysinfo])

AC_CHECK_FUNC(crypt, , AC_CHECK_LIB(crypt, crypt, ,
                     [echo "cannot find crypt anywhere"; exit 1]))
AC_CONFIG_COMMANDS_PRE
AC_OUTPUT
