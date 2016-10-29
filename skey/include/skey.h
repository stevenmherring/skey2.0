/*
 * S/KEY v1.1b (skey.h)
 *
 * Authors:
 *          Neil M. Haller <nmh@thumper.bellcore.com>
 *          Philip R. Karn <karn@chicago.qualcomm.com>
 *          John S. Walden <jsw@thumper.bellcore.com>
 *
 * Modifications:
 *          Scott Chasin <chasin@crimelab.com>
 *
 * Main client header
 */
/*
#if	defined(__TURBOC__) || defined(__STDC__) || defined(LATTICE)
#define	ANSIPROTO	1
#endif

#ifndef	__ARGS
#ifdef	ANSIPROTO
#define	__ARGS(x)	x
#else
#define	__ARGS(x)	()
#endif
#endif

*/
#ifndef __SKEY_H__
#define __SKEY_H__

#include "config.h"
#include "debug.h"
#include "md4.h"

#ifdef HAVE_STDARG_H
#include <stdarg.h>
#endif

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_GRP_H
#include <grp.h>
#endif

#ifdef HAVE_SYS_GRP_H
#include <sys/grp.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_CTYPE_H
#include <ctype.h>
#endif

#ifdef HAVE_ASSERT_H
#include <assert.h>
#endif

#ifdef HAVE_IOCTL_H
#include <ioctl.h>
#endif

#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif

#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_PWD_H
#include <pwd.h>
#endif

#ifdef HAVE_SIGNAL_H
#include <signal.h>
#endif

#ifdef HAVE_ERRNO_H
#include <errno.h>
#endif
//timeb removed, deprecated.
#ifdef HAVE_SYS_QUOTA_H
#include <sys/quota.h>
#endif

#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif

#ifdef HAVE_SYS_RESOURCE_H
#include <sys/resource.h>
#endif

#ifdef HAVE_TIME_H
#include <time.h>
#endif

#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#ifdef HAVE_SYS_SYSTEMINFO_H
#include <sys/systeminfo.h>
#endif

#ifdef HAVE_SHADOW_H
#include <shadow.h>
#endif

#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

/* Server-side data structure for reading keys file during login */
struct skey {
  FILE *keyfile;
  char buf[256];
  char *logname;
  int n;
  char *seed;
  char *val;
  long recstart;		/* needed so reread of buffer is efficient */
};

//debug stuff

#define _d_enter_func(file, count, func, ...)\
  if(dLevel > 0) debug_1_enter(file, func);\
  if(dLevel > 2) debug_3_enter(file, count, func, __VA_ARGS__);
#define _d_exit_func(file, func, val)\
  if(dLevel > 0) debug_1_exit(file, func);\
  if(dLevel > 1) debug_2_exit(file, val);
#define logfile (logging == 1) ? logFile : NULL
/* Client-side structure for scanning data stream for challenge */
struct mc
{
  char buf[256];
  int skip;
  int cnt;
};

void f (char *x);
int keycrunch (char *result, char *seed, char *passwd);
char *btoe (char *engout, char *c);
char *put8 (char *out, char *s);
int etob (char *out, char *e);
void rip (char *buf);
int skeychallenge (struct skey * mp, char *name, char *ss);
int skeylookup (struct skey * mp, char *name);
int skeyverify (struct skey * mp, char *response);
char* readpass(char* buf, int n, int eflag);
void sevenbit(char* s);
int htoi(register char c);
void backspace(char *buf);
int atob8(register char *out, register char *in);
int btoa8(register char *out, register char *in);
int skey_haskey (char *username);
int skey_authenticate (char *username);

#endif
