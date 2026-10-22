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

typedef __builtin_va_list va_list;

#undef va_start
/* Workaround: GCC 13 to 14, and Clang 16 to 17, all targets: their C23 mode
 * reports 202000L, the value they give the drafts of C23.
 */
#if (defined(__cplusplus) && __cplusplus > 202302L) \
 || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L) \
 || (defined(__STDC_VERSION__) && __STDC_VERSION__ > 201710L \
     && ((defined(__clang__) && __clang_major__ >= 16) \
         || (!defined(__clang__) && __GNUC__ >= 13)))
/* The builtin of C23 diagnoses unexpected arguments, as C23 recommends. */
#  if __has_builtin(__builtin_c23_va_start)
#    define va_start(...) __builtin_c23_va_start(__VA_ARGS__)
#  elif defined(__clang__) && defined(__cplusplus)
/* Workaround: Clang 17 up to at least 23, all targets: it has no builtin of
 * C23 for C++, and its -Wvarargs warns, in the code of the program, that the
 * 0 passed in its stead is not the last named parameter.
 */
#    define va_start(v, ...) \
         _Pragma("clang diagnostic push") \
         _Pragma("clang diagnostic ignored \"-Wvarargs\"") \
         __builtin_va_start(v, 0) \
         _Pragma("clang diagnostic pop")
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
#if (defined(__cplusplus) && (__cplusplus >= 201103L)) || (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L))
#  undef va_copy
#  define va_copy(d, s) __builtin_va_copy(d, s)
#endif

#if (defined(__cplusplus) && __cplusplus > 202302L) \
 || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L) \
 || (defined(__STDC_VERSION__) && __STDC_VERSION__ > 201710L \
     && ((defined(__clang__) && __clang_major__ >= 16) \
         || (!defined(__clang__) && __GNUC__ >= 13)))
#  define __STDC_VERSION_STDARG_H__ 202311L
#endif

#endif
