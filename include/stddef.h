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

typedef __SIZE_TYPE__ size_t;
typedef __PTRDIFF_TYPE__ ptrdiff_t;

#ifndef __cplusplus
typedef __WCHAR_TYPE__ wchar_t;

/* Workaround: GCC 13 to 14, and Clang 16 to 17, all targets: their C23 mode
 * reports 202000L, the value they give the drafts of C23.
 */
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L) \
 || (defined(__STDC_VERSION__) && __STDC_VERSION__ > 201710L \
     && ((defined(__clang__) && __clang_major__ >= 16) \
         || (!defined(__clang__) && __GNUC__ >= 13)))
typedef typeof(nullptr) nullptr_t;
#endif

#endif

#if defined(__cplusplus) && __cplusplus >= 201103L
typedef decltype(nullptr) nullptr_t;
#endif

/* As in the stddef.h of GCC and Clang, max_align_t is as aligned as the most
 * aligned scalar type, including __float128 on i386 for GCC 7 and later,
 * except that Clang makes it long double for Apple targets.
 */
#if (defined(__cplusplus) && __cplusplus >= 201103L) \
 || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L)
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
#ifndef __cplusplus
#  define NULL ((void *)0)
#else
#  define NULL __null
#endif

#undef offsetof
#define offsetof(s, m) __builtin_offsetof(s, m)

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L) \
 || (defined(__STDC_VERSION__) && __STDC_VERSION__ > 201710L \
     && ((defined(__clang__) && __clang_major__ >= 16) \
         || (!defined(__clang__) && __GNUC__ >= 13)))
#  undef unreachable
#  define unreachable() __builtin_unreachable()
#endif

#if (defined(__cplusplus) && __cplusplus > 202302L) \
 || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L) \
 || (defined(__STDC_VERSION__) && __STDC_VERSION__ > 201710L \
     && ((defined(__clang__) && __clang_major__ >= 16) \
         || (!defined(__clang__) && __GNUC__ >= 13)))
#  define __STDC_VERSION_STDDEF_H__ 202311L
#endif

#endif
