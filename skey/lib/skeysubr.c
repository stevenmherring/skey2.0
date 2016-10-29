/* S/KEY v1.1b (skeysubr.c)
 *
 * Authors:
 *          Neil M. Haller <nmh@thumper.bellcore.com>
 *          Philip R. Karn <karn@chicago.qualcomm.com>
 *          John S. Walden <jsw@thumper.bellcore.com>
 *
 * Modifications:
 *          Scott Chasin <chasin@crimelab.com>
 *
 * S/KEY misc routines.
 */

#include "skey.h"

#ifdef HAVE_TERMIOS_H
#include <termios.h>
#define TTYSTRUCT termios
struct termios newtty;
struct termios oldtty;
#define stty(fd,buf) tcsetattr((fd), TCSAFLUSH, buf)
#define gtty(fd,buf) tcgetattr((fd), buf)
#endif

#ifdef HAVE_TERMIO_H
#ifndef HAVE_TERMIOS_H
#include <termio.h>
#define TTYSTRUCT termio
#define stty(fd,buf) ioctl((fd),TCSETA,(buf)) //tcsetattr
#define gtty(fd,buf) ioctl((fd),TCGETA,(buf)) //tcgetatt
struct termio newtty;
struct termio oldtty;
#endif
#endif

#ifdef HAVE_SGTTY_H
#ifndef HAVE_TERMIO_H
#ifndef HAVE_TERMIOS_H
#include <sgtty.h>
#define TTYSTRUCT sgttyb
#define stty(fd,buf) ioctl((fd),TIOCSETN,(buf))
#define gtty(fd,buf) ioctl((fd),TIOCGETP,(buf))
struct sgttyb newtty;
struct sgttyb oldtty;
struct tchars chars;
#endif
#endif
#endif

#ifdef SIGVOID
#define SIGTYPE void
#else
#define SIGTYPE void
#endif

SIGTYPE trapped();
int keycrunch(char *result, char *seed, char *passwd);
void f (char *x);
char *readpass (char *buf, int n, int eflag);
void rip (char *buf);
void set_term ();
void echo_off ();
void backspace(char *buf);
void seventbit(char *s);
void trapped();
void unset_term();


/* Crunch a key:
 * concatenate the seed and the password, run through MD4 and
 * collapse to 64 bits. This is defined as the user's starting key.
 */
int keycrunch(char *result, char *seed, char *passwd)
{
	char *buf;
	MDstruct md;
	unsigned int buflen;
#ifdef WORDS_BIGENDIAN
	int i;
	register long tmp;
#endif

	buflen = strlen(seed) + strlen(passwd);
	if ((buf = (char *)malloc(buflen+1)) == NULL)
		return -1;
	strcpy(buf,seed);
	strcat(buf,passwd);

	/* Crunch the key through MD4 */
	sevenbit(buf);
	MDbegin(&md);
	MDupdate(&md,(unsigned char *)buf,8*buflen);

	free(buf);

	/* Fold result from 128 to 64 bits */
	md.buffer[0] ^= md.buffer[2];
	md.buffer[1] ^= md.buffer[3];

#ifndef	WORDS_BIGENDIAN
	/* Only works on byte-addressed little-endian machines!! */
	memcpy(result,(char *)md.buffer,8);
#else
	/* Default (but slow) code that will convert to
	 * little-endian byte ordering on any machine
	 */
	for (i=0; i<2; i++) {
		tmp = md.buffer[i];
		*result++ = tmp;
		tmp >>= 8;
		*result++ = tmp;
		tmp >>= 8;
		*result++ = tmp;
		tmp >>= 8;
		*result++ = tmp;
	}
#endif

	return 0;
}

/* The one-way function f(). Takes 8 bytes and returns 8 bytes in place */
void f (char *x) {
	MDstruct md;
#ifdef WORDS_BIGENDIAN
	register long tmp;
#endif

	MDbegin(&md);
	MDupdate(&md,(unsigned char *)x,64);

	/* Fold 128 to 64 bits */
	md.buffer[0] ^= md.buffer[2];
	md.buffer[1] ^= md.buffer[3];

#ifndef	WORDS_BIGENDIAN
	/* Only works on byte-addressed little-endian machines!! */
	memcpy(x,(char *)md.buffer,8);

#else
	/* Default (but slow) code that will convert to
	 * little-endian byte ordering on any machine
	 */
	tmp = md.buffer[0];
	*x++ = tmp;
	tmp >>= 8;
	*x++ = tmp;
	tmp >>= 8;
	*x++ = tmp;
	tmp >>= 8;
	*x++ = tmp;

	tmp = md.buffer[1];
	*x++ = tmp;
	tmp >>= 8;
	*x++ = tmp;
	tmp >>= 8;
	*x++ = tmp;
	tmp >>= 8;
	*x = tmp;
#endif
}

/* Strip trailing cr/lf from a line of text */
void rip (char *buf) {
	char *cp;

	if((cp = strchr(buf,'\r')) != NULL)
		*cp = '\0';

	if((cp = strchr(buf,'\n')) != NULL)
		*cp = '\0';
}

#ifdef	__MSDOS__
char *readpass(char *buf, int n)
{
  int i;
  char *cp;

  for (cp=buf,i = 0; i < n ; i++)
       if ((*cp++ = bdos(7,0,0)) == '\r')
          break;
   *cp = '\0';
   putchar('\n');
   rip(buf);
   return buf;
}
#else

char *readpass (char *buf, int n, int eflag)
{
    //TODO: echo flag
		if(!eflag){
    	set_term ();
    	echo_off ();
		}

    char *lolerror = fgets (buf, n, stdin);
		if(lolerror == NULL) {
			exit(1);
		}

    rip (buf);

    printf ("\n\n");
    sevenbit (buf);

		if(!eflag) {
    	unset_term ();
		}
    return buf;
}

void set_term ()
{
    gtty (fileno(stdin), &newtty);
    gtty (fileno(stdin), &oldtty);

    signal (SIGINT, trapped);
}

void echo_off ()
{
 #ifdef HAVE_TERMIOS_H
    newtty.c_lflag &= ~(ICANON | ECHO | ECHONL);
 #else
    newtty.sg_flags |= CBREAK;
    newtty.sg_flags &= ~ECHO;
 #endif

 #ifdef HAVE_TERMIOS_H
    newtty.c_cc[VMIN] = 1;
    newtty.c_cc[VTIME] = 0;
    newtty.c_cc[VINTR] = 3;
 #else
    ioctl(fileno(stdin), TIOCGETA, &chars);
    chars.t_intrc = 3;
    ioctl(fileno(stdin), TIOCSETA, &chars);
 #endif
    tcsetattr(fileno (stdin), TCSAFLUSH, &newtty);
    //stty (fileno (stdin), &newtty);
  //  stty (fileno (stdin), &newtty); // @TODO: stty gtty
}

void unset_term ()
{
  tcsetattr(fileno (stdin), TCSAFLUSH, &oldtty);
  #ifndef HAVE_TERMIOS_H
    ioctl(fileno(stdin), TIOCSETC, &chars);
  #endif
}

void trapped()
 {
  signal (SIGINT, trapped);
  printf ("^C\n");
  unset_term ();
  exit (-1);
 }

#endif

/* removebackspaced over charaters from the string */
void backspace(char *buf) {
	char bs = 0x8;
	char *cp = buf;
	char *out = buf;

	while(*cp){
		if( *cp == bs ) {
			if(out == buf){
				cp++;
				continue;
			}
			else {
			  cp++;
			  out--;
			}
		}
		else {
			*out++ = *cp++;
		}

	}
	*out = '\0';
}

/* sevenbit ()
 *
 * Make sure line is all seven bits.
 */

void sevenbit (char *s) {
   while (*s) {
     *s = 0x7f & ( *s);
     s++;
   }
}
