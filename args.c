/*
** EPITECH PROJECT, 2020
** PSU_strace_2019
** File description:
** automated desc ftw
*/

#include "strace.h"

void parse_args(opts_t *as, int *off, int c, const char **v)
{
    if (c == 1) {
        fputs("no arguments; try `--help`?\n", stderr);
        exit(84);
    }
    if (!strcmp(v[1], "--help")) {
        fputs("USAGE: ./strace [-s] [-p <pid>|<command>]\n", stdout);
        exit(0);
    }
    if (!strcmp(v[*off], "-s")) {
        as->s = true;
        (*off)++;
    }
    if (!strcmp(v[*off], "-p")) {
        as->p = true;
        as->grab = atoi(v[*off + 1]);
        if (!as->grab)
            exit(84);
        *off += 2;
    }
}

void child(int c, const char **v)
{
    char *args[c + 1];

    if (c <= 0) {
        fputs("any commands?\n", stderr);
        exit(84);
    }
    memcpy(args, v, c * sizeof(*v));
    args[c] = NULL;
    ptrace(PTRACE_TRACEME, 0, 0, 0);
    kill(getpid(), SIGSTOP);
    execvp(args[0], args);
}
