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
    print_args(p, full, num);
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

void print_args(pid_t p, bool full, struct user_regs_struct num)
{
    for (char i = 0; i < 6 && not_off(num.orig_rax, i); i++)
        print_arg(p, full, num.orig_rax, i);
}

void print_arg(pid_t p,
        bool full, unsigned long long scidx, unsigned char idx)
{
    struct user_regs_struct d = REGS(p);
    unsigned long long as[6] = {d.rdi, d.rsi, d.rdx, d.r10, d.r8, d.r9};

    if (idx && not_off(scidx, idx))
        fprintf(stderr, ", ");
    if (!full)
        fprintf(stderr, "%#llx", as[idx]);
    fprintf(stderr, get_printf_fmt(scidx, idx),
                    get_printf_arg(p, scidx, as, idx));
}

char *get_string(pid_t p, unsigned long addr)
{
	char *buf = malloc(4096);

	for (unsigned long tmp = 0, read = 0; ; read += sizeof(unsigned long)) {
		if (read + sizeof(unsigned long) > 4096)
			buf = realloc(buf, sizeof(buf) * 2);
        errno = 0;
		tmp = ptrace(PTRACE_PEEKDATA, p, addr + read);
		if (errno != 0) {
            free(buf);
            perror("strace");
            exit(84);
		}
		memcpy(buf + read, &tmp, sizeof(unsigned long));
		if (memchr(&tmp, 0, sizeof(unsigned long)) != NULL)
			break;
	}
	return buf;
}
