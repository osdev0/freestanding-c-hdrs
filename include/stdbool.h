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

#ifndef __FREESTANDING_C_HDRS_STDBOOL_H
#define __FREESTANDING_C_HDRS_STDBOOL_H 1

#if (defined(__cplusplus) && __cplusplus < 201103L) \
 || (!defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L))
#  error "<stdbool.h> requires C99 or C++11 or later"
#endif

#ifndef __cplusplus

/* Workaround: GCC 13 to 14, and Clang 15 to 17, all targets: their C23 mode
 * reports 202000L, the value they give the drafts of C23. That of Clang 15
 * lacks much of C23, but has the keywords bool, true, and false.
 */
#if __STDC_VERSION__ >= 202311L \
 || (__STDC_VERSION__ > 201710L \
     && ((defined(__clang__) && __clang_major__ >= 15) \
         || (!defined(__clang__) && __GNUC__ >= 13)))
    /* These do not need to be defined for C23+. */
#else
#  undef bool
#  define bool _Bool

#  undef true
#  define true 1
#  undef false
#  define false 0
#endif

#endif

#undef __bool_true_false_are_defined
#define __bool_true_false_are_defined 1

#endif
