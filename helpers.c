/*
** EPITECH PROJECT, 2020
** PSU_strace_2019
** File description:
** automated desc ftw
*/

#include "strace.h"
#include "syscalls.h"

char *syscall_name(struct user_regs_struct c)
{
    static char ret[100] = {0};

    if (c.orig_rax < MAX_SCS)
        return ALLSCS[c.orig_rax].name;
    snprintf(ret, sizeof(ret), "sys_%llu", c.orig_rax);
    return ret;
}

bool not_off(int i, unsigned char arg)
{
    return !(i < MAX_SCS && ALLSCS[i].as[arg] == OFF);
}

const char *get_printf_struct(unsigned long long *as,
        unsigned long long scall, unsigned char idx)
{
    static char buf[2048] = {0};

    (void)scall;
    snprintf(buf, sizeof(buf), "%#llx", as[idx]);
    return buf;
}

void print_signal(int s)
{
    if (s < MAX_SIGS)
        fprintf(stderr, "+++ killed by %s +++\n", ALLSIGS[WSTOPSIG(s)]);
    else
        fprintf(stderr, "+++ killed by %d +++\n", s, WSTOPSIG(s));
}
