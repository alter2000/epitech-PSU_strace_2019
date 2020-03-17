/*
** EPITECH PROJECT, 2020
** PSU_strace_2019
** File description:
** automated desc ftw
*/

#include "strace.h"

void print_ret(bool full, pid_t p)
{
    int ret = REGS(p, RETS);

    (void)ret;
    (void)full;
}

char *syscall_name(int c)
{
    switch (c) {
        default: return NULL;
    }
}

void print_syscall_args(bool full, pid_t p, int num)
{
    (void)full;
    (void)p;
    (void)num;
}

void print_syscall(bool full, pid_t p)
{
    int num = REGS(p, orig_rax);

    fprintf(stderr, "%s(", syscall_name(num));
    print_syscall_args(full, p, num);
    fprintf(stderr, ") = ");
}
