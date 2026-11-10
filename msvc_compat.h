#pragma once

/*
 * Small shims for the MSVC build only. Mingw and POSIX provide these.
 */

#ifdef _MSC_VER

#include <string.h>

#define strcasecmp _stricmp

extern char *optarg;
extern int optind;

int getopt(int argc, char *const argv[], const char *optstring);

#endif
