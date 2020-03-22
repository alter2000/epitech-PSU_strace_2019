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

const char *get_printf_struct(unsigned long long scall, unsigned char idx)
{
    (void)scall;
    (void)idx;
    return "%#llx";
}
