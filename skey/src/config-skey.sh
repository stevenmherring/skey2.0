
#############create makefile via template###############
# cleaner version, easier to add additional sed commands
# 1. prepare temp makefile
#cp Makefile.tmpl tmpmk
# 2. series of sed+mv pairs (use tmp names in case any sed cmd fails)
#sed "s/@MYCC@/$MYCC/g" < tmpmk > Makefile2
#v Makefile2 tmpmk # faster than 'cp'
#sed "s/@MYLDFLAGS@/$MYLDFLAGS/g" < tmpmk > Makefile2
#mv Makefile2 tmpmk # faster than 'cp'
#sed "s/@FOO@/$MYFOO/g" < tmpmk > Makefile2
#mv Makefile2 tmpmk # faster than 'cp'
#sed "s/@BAR@/$MYBAR/g" < tmpmk > Makefile2
#mv Makefile2 tmpmk
# 3. finally, rename to final Makefile
#mv tmpmk Makefile
_CONFIG_H="config.h"

identifyEndianess() {
  ENDIAN=$(echo -n I | hexdump -o | awk '{ print substr($2,6,1); exit}')
  ENDIAN_L="#define __LITTLE__ENDIAN__ 1\n"
  ENDIAN_B="#undef __LITTLE__ENDIAN__\n"
  if grep -Fxq "$ENDIAN_L" $_CONFIG_H ; then
    echo "Double include"
  elif grep -Fxq "$ENDIAN_B" $_CONFIG_H ; then
    echo "Double include"
  else
    if [ "$ENDIAN" -eq 1 ] ; then
      echo -e "$ENDIAN_L" >> $_CONFIG_H
    else
      echo -e "$ENDIAN_B" >> $_CONFIG_H
    fi
  fi
}
#-----------------------------------------------------------------------#

#build config.h by searching for header files and setting definitions
buildHeaderConfig() {
  #init file config.h
    echo "//CONFIG.h" > "$_CONFIG_H"
#--------------check stdlib---------
    if grep -Fxq "#define HAVE_STDLIB_H 1" $_CONFIG_H; then
      echo "Already defined stdlib"
    elif grep -Fxq "#undef HAVE_STDLIB_H" $_CONFIG_H; then
      echo "Already undefined stdlib"
    else
      if test -f "/usr/include/stdlib.h"; then
        echo "#define HAVE_STDLIB_H 1" >> $_CONFIG_H
      else
        echo "#undef HAVE_STDLIB_H" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define HAVE_SYS_TYPES_H 1" $_CONFIG_H; then
      echo "Already defined"
    elif grep -Fxq "#undef HAVE_SYS_TYPES_H" $_CONFIG_H; then
      echo "Already undefined"
    else
      if test -f "/usr/include/sys/types.h"; then
        echo "#define HAVE_SYS_TYPES_H 1" >> $_CONFIG_H
      else
        echo "#undef HAVE_SYS_TYPES_H" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define HAVE_STRING_H 1" $_CONFIG_H; then
      echo "Already defined"
    elif grep -Fxq "#undef HAVE_STRING_H" $_CONFIG_H; then
      echo "Already undefined"
    else
      if test -f "/usr/include/string.h"; then
        echo "#define HAVE_STRING_H 1" >> $_CONFIG_H
      else
        echo "#undef HAVE_STRING_H" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define __FCNTL__ 1" $_CONFIG_H; then
      echo "Already defined"
    elif grep -Fxq "#undef __FCNTL__" $_CONFIG_H; then
      echo "Already undefined"
    else
      if test -f "/usr/include/fcntl.h"; then
        echo "#define __FCNTL__ 1" >> $_CONFIG_H
      else
        echo "#undef __FCNTL__" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define HAVE_SGTTY_H 1" $_CONFIG_H; then
      echo "Already defined"
    elif grep -Fxq "#undef HAVE_SGTTY_H" $_CONFIG_H; then
      echo "Already undefined"
    else
      if test -f "/usr/include/sgtty.h"; then
        echo "#define HAVE_SGTTY_H 1" >> $_CONFIG_H
      else
        echo "#undef HAVE_SGTTY_H" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define HAVE_PWD_H 1" $_CONFIG_H; then
      echo "Already defined"
    elif grep -Fxq "#undef HAVE_PWD_H" $_CONFIG_H; then
      echo "Already undefined"
    else
      if test -f "/usr/include/pwd.h"; then
        echo "#define HAVE_PWD_H 1" >> $_CONFIG_H
      else
        echo "#undef HAVE_PWD_H" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define __TIMEA__ 1" $_CONFIG_H; then
      echo "Already defined "
    elif grep -Fxq "#undef __TIMEA__" $_CONFIG_H; then
      echo "Already undefined "
    else
      if test -f "/usr/include/time.h"; then
        echo "#define __TIMEA__ 1" >> $_CONFIG_H
      else
        echo "#undef __TIMEA__" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define HAVE_TERMIO_H 1" $_CONFIG_H; then
      echo "Already defined "
    elif grep -Fxq "#undef HAVE_TERMIO_H" $_CONFIG_H; then
      echo "Already undefined "
    else
      if test -f "/usr/include/termio.h"; then
        echo "#define HAVE_TERMIO_H 1" >> $_CONFIG_H
      else
        echo "#undef HAVE_TERMIO_H" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define __SYSRESOURCE__ 1" $_CONFIG_H; then
      echo "Already defined"
    elif grep -Fxq "#undef __SYSRESOURCE__" $_CONFIG_H; then
      echo "Already undefined"
    else
      if test -f "/usr/include/sys/resource.h"; then
        echo "#define __SYSRESOURCE__ 1" >> $_CONFIG_H
      else
        echo "#undef __SYSRESOURCE__" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define HAVE_IOCTL_H 1" $_CONFIG_H; then
      echo "Already defined"
    elif grep -Fxq "#undef HAVE_IOCTL_H" $_CONFIG_H; then
      echo "Already undefined"
    else
      if test -f "/usr/include/ioctl.h"; then
        echo "#define HAVE_IOCTL_H 1" >> $_CONFIG_H
      else
        echo "#undef HAVE_IOCTL_H" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define HAVE_SYS_IOCTL_H 1" $_CONFIG_H; then
      echo "Already defined"
    elif grep -Fxq "#undef HAVE_SYS_IOCTL_H" $_CONFIG_H; then
      echo "Already undefined"
    else
      if test -f "/usr/include/sys/ioctl.h"; then
        echo "#define HAVE_SYS_IOCTL_H 1" >> $_CONFIG_H
      else
        echo "#undef HAVE_SYS_IOCTL_H" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define __SIGNAL__ 1" $_CONFIG_H; then
      echo "Already defined"
    elif grep -Fxq "#undef __SIGNAL__" $_CONFIG_H; then
      echo "Already undefined"
    else
      if test -f "/usr/include/signal.h"; then
        echo "#define __SIGNAL__ 1" >> $_CONFIG_H
      else
        echo "#undef __SIGNAL__" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define __ERRNO__ 1" $_CONFIG_H; then
      echo "Already defined"
    elif grep -Fxq "#undef __ERRNO__" $_CONFIG_H; then
      echo "Already undefined"
    else
      if test -f "/usr/include/errno.h"; then
        echo "#define __ERRNO__ 1" >> $_CONFIG_H
      else
        echo "#undef __ERRNO__" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define HAVE_ASSERT_H 1" $_CONFIG_H; then
      echo "Already defined"
    elif grep -Fxq "#undef HAVE_ASSERT_H" $_CONFIG_H; then
      echo "Already undefined"
    else
      if test -f "/usr/include/assert.h"; then
        echo "#define HAVE_ASSERT_H 1" >> $_CONFIG_H
      else
        echo "#undef HAVE_ASSERT_H" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define HAVE_CTYPE_H 1" $_CONFIG_H; then
      echo "Already defined"
    elif grep -Fxq "#undef HAVE_CTYPE_H" $_CONFIG_H; then
      echo "Already undefined"
    else
      if test -f "/usr/include/ctype.h"; then
        echo "#define HAVE_CTYPE_H 1" >> $_CONFIG_H
      else
        echo "#undef HAVE_CTYPE_H" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define __SYSTIME__ 1" $_CONFIG_H; then
      echo "Already defined "
    elif grep -Fxq "#undef __SYSTIME__" $_CONFIG_H; then
      echo "Already undefined "
    else
      if test -f "/usr/include/sys/time.h"; then
        echo "#define __SYSTIME__ 1" >> $_CONFIG_H
      else
        echo "#undef __SYSTIME__" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define __SYSTIMEB__ 1" $_CONFIG_H; then
      echo "Already defined "
    elif grep -Fxq "#undef __SYSTIMEB__" $_CONFIG_H; then
      echo "Already undefined "
    else
      if test -f "/usr/include/sys/timeb.h"; then
        echo "#define __SYSTIMEB__ 1" >> $_CONFIG_H
      else
        echo "#undef __SYSTIMEB__" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define HAVE_STDIO_H 1" $_CONFIG_H; then
      echo "Already defined "
    elif grep -Fxq "#undef HAVE_STDIO_H" $_CONFIG_H; then
      echo "Already undefined "
    else
      if test -f "/usr/include/stdio.h"; then
        echo "#define HAVE_STDIO_H 1" >> $_CONFIG_H
      else
        echo "#undef HAVE_STDIO_H" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define __QUOTA__ 1" $_CONFIG_H; then
      echo "Already defined "
    elif grep -Fxq "#undef __QUOTA__" $_CONFIG_H; then
      echo "Already undefined "
    else
      if test -f "/usr/include/sys/quota.h"; then
        echo "#define __QUOTA__ 1" >> $_CONFIG_H
      else
        echo "#undef __QUOTA__" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define __SYSPARAM__ 1" $_CONFIG_H; then
      echo "Already defined"
    elif grep -Fxq "#undef __SYSPARAM__" $_CONFIG_H; then
      echo "Already undefined"
    else
      if test -f "/usr/include/sys/param.h"; then
        echo "#define __SYSPARAM__ 1" >> $_CONFIG_H
      else
        echo "#undef __SYSPARAM__" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define __SHADOW__ 1" $_CONFIG_H; then
      echo "Already defined "
    elif grep -Fxq "#undef __SHADOW__" $_CONFIG_H; then
      echo "Already undefined "
    else
      if test -f "/usr/include/shadow.h"; then
        echo "#define __SHADOW__ 1" >> $_CONFIG_H
      else
        echo "#undef __SHADOW__" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define __SYSINFO__ 1" $_CONFIG_H; then
      echo "Already defined "
    elif grep -Fxq "#undef __SYSINFO__" $_CONFIG_H; then
      echo "Already undefined "
    else
      if test -f "/usr/include/sys/systeminfo.h"; then
        echo "#define __SYSINFO__ 1" >> $_CONFIG_H
      else
        echo "#undef __SYSINFO__" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define HAVE_UNISTD_H 1" $_CONFIG_H; then
      echo "Already defined"
    elif grep -Fxq "#undef HAVE_UNISTD_H" $_CONFIG_H; then
      echo "Already undefined"
    else
      if test -f "/usr/include/unistd.h"; then
        echo "#define HAVE_UNISTD_H 1" >> $_CONFIG_H
      else
        echo "#undef HAVE_UNISTD_H" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define HAVE_GRP_H 1" $_CONFIG_H; then
      echo "Already defined"
    elif grep -Fxq "#undef HAVE_GRP_H" $_CONFIG_H; then
      echo "Already undefined"
    else
      if test -f "/usr/include/grp.h"; then
        echo "#define HAVE_GRP_H 1" >> $_CONFIG_H
      else
        echo "#undef HAVE_GRP_H" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define HAVE_TERMIOS_H 1" $_CONFIG_H; then
      echo "Already defined"
    elif grep -Fxq "#undef HAVE_TERMIOS_H" $_CONFIG_H; then
      echo "Already undefined"
    else
      if test -f "/usr/include/termios.h"; then
        echo "#define HAVE_TERMIOS_H 1" >> $_CONFIG_H
      else
        echo "#undef HAVE_TERMIOS_H" >> $_CONFIG_H
      fi
    fi
#--------------check stdlib---------
    if grep -Fxq "#define HAVE_SYS_GRP_H 1" $_CONFIG_H; then
      echo "Already defined"
    elif grep -Fxq "#undef HAVE_SYS_GRP_H" $_CONFIG_H; then
      echo "Already undefined"
    else
      if test -f "/usr/include/sys/grp.h"; then
        echo "#define HAVE_SYS_GRP_H 1" >> $_CONFIG_H
      else
        echo "#undef HAVE_SYS_GRP_H" >> $_CONFIG_H
      fi
    fi
#------define debug macros
    DEBUG_START="//DEBUG START"
    if grep -Fxq "$DEBUG_START" $_CONFIG_H; then
      echo "do nothing"
    else
      echo "$DEBUG_START" >> $_CONFIG_H
      echo "#define _d_enter_func(file, count, func, ...)\\" >> $_CONFIG_H
      echo "  if(dLevel > 0) debug_1_enter(file, func);\\" >> $_CONFIG_H
      echo "  if(dLevel > 2) debug_3_enter(file, count, func, __VA_ARGS__);" >> $_CONFIG_H
      echo "#define _d_exit_func(file, func, val)\\" >> $_CONFIG_H
      echo "  if(dLevel > 0) debug_1_exit(file, func);\\" >> $_CONFIG_H
      echo "  if(dLevel > 1) debug_2_exit(file, val);" >> $_CONFIG_H
      echo "#define logfile (logging == 1) ? logFile : NULL" >> $_CONFIG_H
    fi
}
#build makefile using template provided and two arguments passed, compiler&installpath
buildMakefile() {
  #copy template to
  cp Makefile.tmpl tmpmk
  #get arguments, set to var.
  INSTALL_PATH=$1
  COMPILER=$2
  GCC_FLAGS="-Werror -Wall -lcrypt -DUSE_ECHO"
  CC_FLAGS=""

  #set up compiler
  if [ -n "$COMPILER" ] ; then
    #define compiler type, either gcc or cc only @TODO: confirm assumption
    GCC=$(command -v gcc)
    if [ -z "$GCC" ] ; then
      CC=$(command -v cc)
      if [ -z "$CC" ] ; then
        echo "no GCC, no CC exit"
        exit 1
      else
        echo "$CC"
        sed "s!@COMPILER@!$GCC!g" < tmpmk > Makefile2
        mv Makefile2 tmpmk
      fi
    else
      echo "$GCC"
      sed "s!@COMPILER@!$GCC!g" < tmpmk > Makefile2
      mv Makefile2 tmpmk
    fi
  else
    echo "no compiler exit"
    exit 1
  fi
  echo "Makefile Update: Compiler"
  #set up compiler flags
  if [ -n "$COMPILER" ] ; then
    if [ "$COMPILER" == "gcc" ] ; then
      sed "s/@CFLAGS@/$GCC_FLAGS/g" < tmpmk > Makefile2
      mv Makefile2 tmpmk
    else
      if [ "$COMPILER" == "cc" ] ; then
        sed "s/@CFLAGS@/$CC_FLAGS/g" < tmpmk > Makefile2
        mv Makefile2 tmpmk
      else
        sed "s/@CFLAGS@//g" < tmpmk > Makefile2
        mv Makefile2 tmpmk
        echo "No flags ~ Warning"
      fi
    fi
  else
    if $(command -v cc | grep -q 'cc') ; then
      sed "s/@CFLAGS@/$CC_FLAGS/g" < tmpmk > Makefile2
      mv Makefile2 tmpmk
    else
      if $(command -v gcc | grep -q 'gcc') ; then
        sed "s/@CFLAGS@/$GCC_FLAGS/g" < tmpmk > Makefile2
        mv Makefile2 tmpmk
      else
        echo "No Compiler ~ Error"
        exit 1
      fi
    fi
  fi
  echo "Makefile Update: Compiler & flags set"

  #set up install path
  if [ -d "$INSTALL_PATH" ] ; then
    sed "s!@DESTDIR@!$INSTALL_PATH!g" < tmpmk > Makefile2
    mv Makefile2 tmpmk
  else
    echo "Not a directory ~ Error"
    exit 1
  fi

  echo "Makefile Update: Install path set"

  #install
  INSTALL=$(command -v install)
  if [ -n "$INSTALL" ] ; then
    sed "s/@INSTALLPROGRAM@/cp/g" < tmpmk > Makefile2
    mv Makefile2 tmpmk
  else
    sed "s/@INSTALLPROGRAM@/install/g" < tmpmk > Makefile2
    mv Makefile2 tmpmk
  fi

  #move to make file, profit.
  echo "Makefile Update: Install added"
  echo "Makefile Update: Finished"
  cp tmpmk Makefile
}

ARGS=$#
shift $((OPTIND-1))
while getopts ":C:" opt; do
  case $opt in
    C)
      echo "Compiler requested $OPTARG" >&2
      COMP="$OPTARG"
      ;;
    *)
      echo "Bad input" >&2
      ;;
   esac
done
#if only one argument, must be compiler
#if more, it must be in one of two deterministic formsw
if [ "$ARGS" -eq 1 ] ; then
  IPATH=$1
elif [ "$ARGS" -eq 3 ] ; then
  if [ "$2" == "-C" ] ; then
    IPATH="$1"
    COMP="$3"
  else
    IPATH="$3"
  fi
fi
echo "install: $IPATH COMPILER: $COMP"
#create install path
if [ -d $IPATH ] ; then
  #if director, build header and makefile
  buildHeaderConfig
  echo "Header completed"
  buildMakefile $IPATH $COMP
  identifyEndianess
elif [ -f $IPATH ] ; then
  #is a file
  echo "is file"
else
  #doesn't exists
  echo "doesn't exist"
  mkdir $IPATH
  buildHeaderConfig
  buildMakefile $IPATH $COMP
  identifyEndianess
fi
