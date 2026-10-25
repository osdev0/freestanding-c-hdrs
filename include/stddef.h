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

#ifndef __FREESTANDING_C_HDRS_STDDEF_H
#define __FREESTANDING_C_HDRS_STDDEF_H 1

#pragma GCC system_header

#include <__freestanding_c_hdrs/revision.h>

/* On LLP64 targets these are long long, which C90 and C++98 do not have. */
__extension__ typedef __SIZE_TYPE__ size_t;
__extension__ typedef __PTRDIFF_TYPE__ ptrdiff_t;

#ifndef __cplusplus
typedef __WCHAR_TYPE__ wchar_t;

#if __FREESTANDING_C_HDRS_STDDEF_REVISION >= 202311L
/* Workaround: GCC 13 to 14, all targets: it declares nullptr_t itself, and
 * its -Wshadow warns that this declaration shadows that one.
 */
#  if !defined(__clang__) && __GNUC__ < 15
_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wshadow\"")
#  endif
typedef typeof(nullptr) nullptr_t;
#  if !defined(__clang__) && __GNUC__ < 15
_Pragma("GCC diagnostic pop")
#  endif
#endif

#endif

/* As in the stddef.h of GCC and Clang, max_align_t is as aligned as the most
 * aligned scalar type, including __float128 on i386 for GCC 7 and later,
 * except that Clang makes it long double for Apple targets.
 */
#if __FREESTANDING_C_HDRS_STDDEF_REVISION >= 201112L
#if defined(__clang__) && defined(__APPLE__)
typedef long double max_align_t;
#else
typedef struct {
    long long __freestanding_c_hdrs_ll __attribute__((__aligned__(__alignof__(long long))));
    long double __freestanding_c_hdrs_ld __attribute__((__aligned__(__alignof__(long double))));
#if defined(__i386__) && !defined(__clang__) && __GNUC__ >= 7
    __float128 __freestanding_c_hdrs_f128 __attribute__((__aligned__(__alignof__(__float128))));
#endif
} max_align_t;
#endif
#endif

#undef NULL
#define NULL ((void *)0)

#undef offsetof
#define offsetof(s, m) __builtin_offsetof(s, m)

/* C++26 does not take this one from C23. */
#if !defined(__cplusplus) && __FREESTANDING_C_HDRS_STDDEF_REVISION >= 202311L
#  undef unreachable
#  define unreachable() __builtin_unreachable()
#endif

#if __FREESTANDING_C_HDRS_STDDEF_REVISION >= 202311L
#  define __STDC_VERSION_STDDEF_H__ 202311L
#endif

#ifdef __cplusplus
#  include <__fcxx/c_stddef.h>
#endif

#endif
