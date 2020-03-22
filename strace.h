/*
** EPITECH PROJECT, 2020
** PSU_strace_2019
** File description:
** automated desc ftw
*/

#ifndef STRACE_H_
#define STRACE_H_

#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct {
    bool s;
    bool p;
    pid_t grab;
} opts_t;

void parse_args(opts_t *, int *, int, const char **);
void child(int, const char **);

int trace(bool, pid_t);
void loop(bool, pid_t);
bool wait_syscall(pid_t);
struct user_regs_struct _get_registers(pid_t);

char *syscall_name(struct user_regs_struct);
bool not_off(int, unsigned char);
const char *get_printf_struct(unsigned long long *,
        unsigned long long, unsigned char);
void print_signal(int);

void print_syscall(bool, pid_t);
void print_ret(bool, pid_t);
void print_arg(pid_t, bool, unsigned long long, unsigned char);
void print_args(pid_t, bool, struct user_regs_struct);
char *get_string(pid_t, unsigned long);

const char *get_printf_fmt(unsigned long long, unsigned char);
const void *get_printf_arg(pid_t, unsigned long long,
        unsigned long long *, unsigned char);

#define REGS(a) _get_registers((a))
#define RETS rax

#endif
