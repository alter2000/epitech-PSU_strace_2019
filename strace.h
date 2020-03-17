/*
** EPITECH PROJECT, 2020
** PSU_strace_2019
** File description:
** automated desc ftw
*/

#ifndef STRACE_H
#define STRACE_H__

#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/user.h>

typedef struct {
    bool s;
    bool p;
    pid_t grab;
} opts_t;

void parse_args(opts_t *as, int *off, int c, const char **v);
void child(int c, const char **v);

void print_ret(bool full, pid_t p);
void print_syscall(bool full, pid_t p);

void trace(bool full, pid_t pid);
void loop(bool full, pid_t p);
bool wait_syscall(pid_t p);
long _get_registers(pid_t p, int off);

#define REGS(a, b) _get_registers((a), offsetof(struct user, regs.b))
#define RETS rax

#endif
