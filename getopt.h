/* Portable getopt declarations for MSVC, which lacks the POSIX getopt API.
 * Only included/used on MSVC; the POSIX <unistd.h> is used elsewhere. */
#ifndef GETOPT_H
#define GETOPT_H

int  getopt(int argc, char *argv[], const char *optstring);
extern int optind;
extern char *optarg;

#endif /* GETOPT_H */
