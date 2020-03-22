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

void trace(bool, pid_t);
void loop(bool, pid_t);
bool wait_syscall(pid_t);
struct user_regs_struct _get_registers(pid_t);
bool not_off(int, unsigned char);

void print_syscall(bool, pid_t);
void print_ret(bool, pid_t);
void print_arg(bool,
        unsigned long long, struct user_regs_struct, unsigned char);
void print_args(bool, pid_t, struct user_regs_struct);
const char *get_printf_correct(unsigned long long, unsigned char);

char *syscall_name(struct user_regs_struct);
const char *get_printf_struct(unsigned long long, unsigned char);

#define REGS(a) _get_registers((a))
#define RETS rax

#endif
