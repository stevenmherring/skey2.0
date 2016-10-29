/* S/KEY v1.1b (skeyinit.c)
 *
 * Authors:
 *          Neil M. Haller <nmh@thumper.bellcore.com>
 *          Philip R. Karn <karn@chicago.qualcomm.com>
 *          John S. Walden <jsw@thumper.bellcore.com>
 *          Scott Chasin <chasin@crimelab.com>
 *
 * S/KEY initialization and seed update
 */
/*
#include <stdio.h>
#include <string.h>
#include <pwd.h>
#incoude <sys/resource.h>
#include <time.h>

#ifdef __svr4__
#include <sys/systeminfo.h>
#include <unistd.h>
#include <shadow.h>
*/
#include "skey.h"

//#include "sysv_shadow.h"

int optind;
char *optarg;

// char *readpass (), *malloc (), *getpass (), *crypt ();
char *readpass();
char *getpass();
char *crypt();
int skeylookup (struct skey * mp, char *name);

#define NAMELEN 2

int main (int argc, char *argv[]) {
  int rval, n, nn, i, defaultsetup, l;
  time_t now;
  char seed[18], tmp[80], key[8], defaultseed[17], passwd[256], passwd2[256],
       tbuf[27], buf[60], lastc, me[80], *salt, *p, *pw;
  struct skey skey;
  struct passwd *pp;
  struct tm *tm;
  int echo_flag2 = 0;
  char *lolerror;


  time (&now);
  tm = localtime (&now);
  strftime (tbuf, sizeof (tbuf), "%M%j", tm);

  if ((gethostname (defaultseed, sizeof (defaultseed))) < 0)
      exit (-1);

  strcpy (&defaultseed[NAMELEN], tbuf);

  pp = getpwuid (getuid ());
  strcpy (me, pp->pw_name);

  if ((pp = getpwnam (me)) == NULL) {
     fprintf(stderr, "Who are you?\n");
     exit(1);
  }

  defaultsetup = 1;

  if (argc > 1)
  {
    if (strcmp ("-s", argv[1]) == 0)
      defaultsetup = 0;
    else
      pp = getpwnam (argv[1]);

    if (argc > 2)
      pp = getpwnam (argv[2]);

  }

  if (pp == NULL)
  {
    printf ("User unknown\n");
    exit (1);
  }

  if (strcmp (pp->pw_name, me) != 0)
  {
    if (getuid () != 0)
    {
      /* Only root can change other's passwds */
      printf ("Permission denied.\n");
      exit (1);
    }
  }

  salt = pp->pw_passwd;

  setpriority (PRIO_PROCESS, 0, -4);

  if (getuid () != 0) {
     setpriority (PRIO_PROCESS, 0, -4);

     pw = getpass ("Password:");
     p = crypt (pw, salt);

     setpriority(PRIO_PROCESS, 0, 0);

     if (pp && strcmp(p, pp->pw_passwd)) {
        printf ("Password incorrect.\n");
        exit (-1);
     }
  }

  rval = skeylookup (&skey, pp->pw_name);
  switch (rval)
  {
  case -1:
    perror ("Error opening database: ");
    exit (1);
  case 0:
    printf ("[Updating %s]\n", pp->pw_name);
    printf ("Old key: %s\n", skey.seed);

    /* lets be nice if they have a skey.seed that ends in 0-8 just add one */
    l = strlen (skey.seed);
    if (l > 0)
    {
      lastc = skey.seed[l - 1];
      if (isdigit ((int) lastc) && lastc != '9') //WHICH ONE
      {
	strcpy (defaultseed, skey.seed);
	defaultseed[l - 1] = lastc + 1;
      }
      if (isdigit ((int) lastc) && lastc == '9' && l < 16) //WHICH ONE
      {
	strcpy (defaultseed, skey.seed);
	defaultseed[l - 1] = '0';
	defaultseed[l] = '0';
	defaultseed[l + 1] = '\0';
      }
    }
    break;
  case 1:
    printf ("[Adding %s]\n", pp->pw_name);
    break;
  }
  n = 99;

  if (!defaultsetup)
  {
    printf ("You need the 6 english words generated from the \"key\" command.\n");
    for (i = 0 ;; i++)
    {
      if (i >= 2)
	exit (1);
      printf ("Enter sequence count from 1 to 10000: ");
      lolerror = fgets (tmp, sizeof (tmp), stdin);
      if(lolerror == NULL){
        exit(1);
      }
      n = atoi (tmp);
      if (n > 0 && n < 10000)
	break;		/* Valid range */
      printf ("\n Error: Count must be > 0 and < 10000\n");
    }
  }

  if (!defaultsetup)
  {
    printf ("Enter new key [default %s]: ", defaultseed);
    fflush (stdout);
    lolerror = fgets (seed, sizeof (seed), stdin);
    if(lolerror == NULL) {
      exit(1);
    }
    rip (seed);
    if (strlen (seed) > 16)
    {
      printf ("Notice: Seed truncated to 16 characters.\n");
      seed[16] = '\0';
    }

    if (seed[0] == '\0')
      strcpy (seed, defaultseed);

    for (i = 0 ;; i++)
    {
      if (i >= 2)
	exit (1);

      printf ("s/key %d %s\ns/key access password: ", n, seed);
      lolerror = fgets (tmp, sizeof (tmp), stdin);
      if(lolerror == NULL) {
        exit(1);
      }
      rip (tmp);
      backspace (tmp);

      if (tmp[0] == '?')
      {
	printf ("Enter 6 English words from secure S/Key calculation.\n");
	continue;
      }

      if (tmp[0] == '\0')
      {
	exit (1);
      }
      if (etob (key, tmp) == 1 || atob8 (key, tmp) == 0)
	break;			/* Valid format */
      printf ("Invalid format - try again with 6 English words.\n");
    }
  }
  else
  {
    /* Get user's secret password */
    for (i = 0 ;; i++)
    {

      if (i >= 2)
	exit (1);

      printf ("Enter secret password: ");
      readpass (passwd, sizeof (passwd), echo_flag2);

      if (passwd[0] == '\0')
	exit (1);

      printf ("Again secret password: ");
      readpass (passwd2, sizeof (passwd), echo_flag2);

      if (passwd2[0] == '\0')
	exit (1);

      if (strlen (passwd) < 4 && strlen (passwd2) < 4)
      {
	fprintf (stderr, "Error: Your password must be longer.\n\r");
	exit (1);
      }

      if (strcmp (passwd, passwd2) == 0)
	break;

      printf ("Error: Passwords dont match.\n");
    }
    strcpy (seed, defaultseed);

    /* Crunch seed and password into starting key */
    if (keycrunch (key, seed, passwd) != 0)
    {
      fprintf (stderr, "%s: key crunch failed.\n", argv[0]);
      exit (2);
    }
    nn = n;
    while (nn-- != 0)
      f (key);
  }
  time (&now);
  tm = localtime (&now);
  strftime (tbuf, sizeof (tbuf), " %b %d,%Y %T", tm);

  skey.val = malloc (16 + 1);

  btoa8 (skey.val, key);

  fprintf (skey.keyfile, "%s %04d %-16s %s %-21s\n", pp->pw_name, n,
	   seed, skey.val, tbuf);
  fclose (skey.keyfile);
  printf ("\nID %s s/key is %d %s\n", pp->pw_name, n, seed);
  printf ("Next login password: %s\n", btoe (buf, key));

  exit (1);
}
