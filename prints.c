/*
** EPITECH PROJECT, 2020
** PSU_strace_2019
** File description:
** automated desc ftw
*/

#include "strace.h"
#include "syscalls.h"

extern char **environ;

void print_syscall(bool full, pid_t p)
{
    struct user_regs_struct num = REGS(p);

    if (num.rip == 0x050f)
        return;
    fprintf(stderr, "%s(", syscall_name(num));
    print_args(full, p, num);
    fprintf(stderr, ") = ");
}

void print_ret(bool full, pid_t p)
{
    struct user_regs_struct ret = REGS(p);

    if (ret.orig_rax < MAX_SCS && ALLSCS[ret.orig_rax].ret == OFF)
        fprintf(stderr, "?\n");
    else
        fprintf(stderr, full && (ret.orig_rax < MAX_SCS &&
                                ALLSCS[ret.orig_rax].ret != PTR)
                ? "%lld\n" : "%#llx\n", ret.rax);
}

void print_args(bool full, pid_t p, struct user_regs_struct num)
{
    unsigned long long tmp = REGS(p).orig_rax;

    for (char i = 0; i < 6 && not_off(tmp, i); i++)
        print_arg(full, tmp, num, i);
}

void print_arg(bool full,
        unsigned long long scidx, struct user_regs_struct d, unsigned char idx)
{
    unsigned long long as[6] = {d.rdi, d.rsi, d.rdx, d.r10, d.r8, d.r9};

    if (idx && not_off(scidx, idx))
        fprintf(stderr, ", ");
    fprintf(stderr, full
                        ? get_printf_correct(scidx, idx)
                        : "%#llx", as[idx]);
}

const char *get_printf_correct(unsigned long long scall, unsigned char idx)
{
    if (scall >= MAX_SCS)
        return "%#llx";
    switch (ALLSCS[scall].as[idx]) {
        case OFF: return "";
        case INT: case CHAR: case U: case U_L: case LONG: return "%llu";
        case PTR: case CHAR_PTRPTR: return "%#llx";
        case CHAR_PTR: return "\"%s\"";
        case STRUCT: return get_printf_struct(scall, idx);
    }
    return "";
}
