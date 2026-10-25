/* SPDX-License-Identifier: 0BSD */

/* Copyright (C) 2022-2026 Mintsuki and contributors.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef __FREESTANDING_C_HDRS_STDARG_H
#define __FREESTANDING_C_HDRS_STDARG_H 1

#pragma GCC system_header

#include <__freestanding_c_hdrs/revision.h>

typedef __builtin_va_list va_list;

#undef va_start
#if __FREESTANDING_C_HDRS_STDARG_REVISION >= 202311L
/* The builtin of C23 diagnoses unexpected arguments, as C23 recommends. */
#  if __has_builtin(__builtin_c23_va_start)
#    define va_start(...) __builtin_c23_va_start(__VA_ARGS__)
#  elif defined(__clang__) && __clang_major__ < 19
/* Workaround: Clang 16 to 18, all targets: -Wpedantic warns, in the code of
 * the program, that va_start(ap) leaves out the variadic arguments, so they
 * go to another macro, with one more, which expands the macros of any
 * further arguments, which C23 leaves alone.
 */
#    define va_start(...) __FREESTANDING_C_HDRS_VA_START(__VA_ARGS__, 0)
#    define __FREESTANDING_C_HDRS_VA_START(v, ...) __builtin_va_start(v, 0)
#  else
#    define va_start(v, ...) __builtin_va_start(v, 0)
#  endif
#else
#  define va_start(v, l) __builtin_va_start(v, l)
#endif
#undef va_end
#define va_end(v) __builtin_va_end(v)
#undef va_arg
#define va_arg(v, l) __builtin_va_arg(v, l)
#if __FREESTANDING_C_HDRS_STDARG_REVISION >= 199901L
#  undef va_copy
#  define va_copy(d, s) __builtin_va_copy(d, s)
#endif

#if __FREESTANDING_C_HDRS_STDARG_REVISION >= 202311L
#  define __STDC_VERSION_STDARG_H__ 202311L
#endif

#ifdef __cplusplus
#  include <__fcxx/c_stdarg.h>
#endif

#endif
