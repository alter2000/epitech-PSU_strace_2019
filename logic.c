/*
** EPITECH PROJECT, 2020
** PSU_strace_2019
** File description:
** automated desc ftw
*/

#include "strace.h"
#include "syscalls.h"

void loop(bool full, pid_t p)
{
    for (; !wait_syscall(p); ) {
        print_syscall(full, p);
        if (wait_syscall(p))
            break;
        print_ret(full, p);
    }
}

struct user_regs_struct _get_registers(pid_t p)
{
    static struct user_regs_struct ret;

    errno = 0;
    ptrace(PTRACE_GETREGS, p, 0, &ret);
    if (errno) {
        perror("strace");
        exit(84);
    }
    return ret;
}

bool wait_syscall(pid_t p)
{
    int s = 0;

    while (true) {
        ptrace(PTRACE_SYSCALL, p, 0, 0);
        waitpid(p, &s, 0);
        if (WIFSTOPPED(s) && (WSTOPSIG(s) & 0x80))
            return 0;
        if (WIFEXITED(s)) {
            fprintf(stderr, "--- %s ---\n", ALLSIGS[WSTOPSIG(s)]);
            return 1;
        }
        fprintf(stderr, "+++ killed by %d (%x) +++\n", s, WSTOPSIG(s));
    }
}

void trace(bool full, pid_t p)
{
    int s = 0;

    waitpid(p, &s, 0);
    ptrace(PTRACE_SETOPTIONS, p, 0, PTRACE_O_TRACESYSGOOD
            | PTRACE_O_EXITKILL | PTRACE_O_TRACEEXIT);
    loop(full, p);
}

bool not_off(int i, unsigned char arg)
{
    return !(i < MAX_SCS && ALLSCS[i].as[arg] == OFF);
}
