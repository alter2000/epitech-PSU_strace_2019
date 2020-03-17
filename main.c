/*
** EPITECH PROJECT, 2020
** PSU_strace_2019
** File description:
** automated desc ftw
*/

#include "strace.h"

static void sigs(int p, siginfo_t *act, void *old)
{
    (void)act;
    (void)old;
    ptrace(PTRACE_DETACH, p, 0, 0);
}

static void attach_to(opts_t as)
{
    struct sigaction act;

    act.sa_sigaction = &sigs;
    act.sa_flags = SA_SIGINFO;
    if (ptrace(PTRACE_DETACH, as.grab, 0, 0) &&
            sigaction(SIGINT, &act, 0) < 0 &&
            ptrace(PTRACE_ATTACH, as.grab, 0, 0)) {
        perror("strace");
        exit(84);
    }
    trace(as.s, as.grab);
    if (ptrace(PTRACE_DETACH, as.grab, 0, 0)) {
        perror("strace");
        exit(84);
    }
}

int main(int c, const char **v)
{
    int off = 1;
    opts_t as = {0};
    pid_t pid = 0;

    parse_args(&as, &off, c, v);
    if (as.p) {
        attach_to(as);
        return 0;
    }
    pid = fork();
    switch (pid) {
        case -1:
            perror("strace");
            return 84;
        case 0: child(c - off, v + off);
            return 0;
        default: trace(as.s, pid);
            return 0;
    }
}
