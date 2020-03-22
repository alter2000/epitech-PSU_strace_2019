/*
** EPITECH PROJECT, 2020
** PSU_strace_2019
** File description:
** automated desc ftw
*/

#include "strace.h"
#include "syscalls.h"

const char *get_printf_fmt(unsigned long long scall, unsigned char idx)
{
    if (scall >= MAX_SCS)
        return "%#llx";
    switch (ALLSCS[scall].as[idx]) {
        case OFF: return "";
        case INT:    case CHAR:     return "%lld";
        case U:      case U_L:      return "%llu";
        case CHAR_PTRPTR:
        case STRUCT:
        case LONG:   case PTR:      return "%#llx";
        case CHAR_PTR: return "\"%s\"";
    }
    return "";
}

const void *get_printf_arg(pid_t p, unsigned long long scidx,
        unsigned long long *as, unsigned char idx)
{
    switch (ALLSCS[scidx].as[idx]) {
        case OFF: return "";
        case INT: case CHAR: case U: case U_L:
        case CHAR_PTRPTR:
        case LONG: case PTR: return (const void*)as[idx];
        case CHAR_PTR: return get_string(p, as[idx]);
        case STRUCT:   return get_printf_struct(as, scidx, idx);
    }
    return 0;
}
