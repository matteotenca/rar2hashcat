/* Minimal portable getopt for MSVC.
 * Handles single-char short options, the ':' (required arg) and '!'
 * (optional arg) modifiers, attached args (-iv / -i=v) and separate args (-i v),
 * plus the '--' end-of-options. No long options (none are used here). */

#include <stddef.h> /* NULL, size_t */

int optind = 1;
char *optarg = NULL;

int getopt(int argc, char *argv[], const char *optstring) {
    char *arg;
    const char *o;
    int c;

    if (optind >= argc)
        return -1;

    arg = argv[optind];

    /* A non-option (or a lone '-') ends option processing.
     * optind must point AT the first positional arg (POSIX semantics);
     * main adjusts with argc -= optind. */
    if (arg[0] != '-' || arg[1] == 0) {
        return -1;
    }

    /* A double dash ends option processing. */
    if (arg[1] == '-' && arg[2] == 0) {
        optind++;
        return -1;
    }

    optind++;
    c = arg[1];
    o = optstring;
    while (*o && *o != c)
        o++;
    if (!*o)
        return '?';

    switch (o[1]) {
    case ':': /* required argument */
        if (arg[2] == 0) {
            /* arg follows as a separate token */
            if (optind >= argc)
                return -1;
            optarg = argv[optind];
            optind++;
        } else {
            optarg = (arg[2] == '=') ? arg + 3 : arg + 2;
        }
        break;
    case '!': /* optional argument */
        optarg = (arg[2] == '=') ? arg + 3 : NULL;
        break;
    default: /* boolean flag */
        optarg = NULL;
        break;
    }

    return c;
}
