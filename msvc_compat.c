#ifdef _MSC_VER

#include <stdio.h>
#include <string.h>

#include "msvc_compat.h"

char *optarg = NULL;
int optind = 1;

/* Enough of getopt(3) for "-v" and the base64conv option string. No argument
 * permutation, same as the mingw implementation. */
int getopt(int argc, char *const argv[], const char *optstring)
{
	static int optpos = 1;
	const char *arg;
	const char *p;
	int c;

	optarg = NULL;

	if (optind >= argc)
		return -1;

	arg = argv[optind];
	if (arg[0] != '-' || arg[1] == '\0')
		return -1;
	if (arg[1] == '-' && arg[2] == '\0') {
		optind++;
		return -1;
	}

	c = (unsigned char)arg[optpos];
	if (c == '\0') {
		optind++;
		optpos = 1;
		return getopt(argc, argv, optstring);
	}
	optpos++;

	p = strchr(optstring, c);
	if (!p || c == ':') {
		fprintf(stderr, "%s: invalid option -- '%c'\n", argv[0], c);
		if (argv[optind][optpos] == '\0') {
			optind++;
			optpos = 1;
		}
		return '?';
	}

	if (p[1] != ':')
		return c;

	if (argv[optind][optpos] != '\0') {
		optarg = &argv[optind][optpos];
		optind++;
	} else if (optind + 1 < argc) {
		optarg = argv[optind + 1];
		optind += 2;
	} else {
		fprintf(stderr, "%s: option requires an argument -- '%c'\n", argv[0], c);
		optind++;
		optpos = 1;
		return '?';
	}
	optpos = 1;
	return c;
}

#endif
