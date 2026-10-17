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

#ifndef __FREESTANDING_C_HDRS_STDALIGN_H
#define __FREESTANDING_C_HDRS_STDALIGN_H 1

#if (defined(__cplusplus) && __cplusplus < 201103L) \
 || (!defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L))
#  error "<stdalign.h> requires C11 or C++11 or later"
#endif

#ifndef __cplusplus

/* Workaround: GCC 13 to 14, and Clang 16 to 17, all targets: their C23 mode
 * reports 202000L, the value they give the drafts of C23.
 */
#if __STDC_VERSION__ >= 202311L \
 || (__STDC_VERSION__ > 201710L \
     && ((defined(__clang__) && __clang_major__ >= 16) \
         || (!defined(__clang__) && __GNUC__ >= 13)))
    /* These do not need to be defined for C23+. */
#else
#  undef alignas
#  define alignas _Alignas
#  undef alignof
#  define alignof _Alignof
#endif

#endif

/* C11 to C17, where alignas is the macro above, and C++11 to C++23 have
 * __alignas_is_defined, and C23 and C++26 none.
 */
#if defined(alignas) || (defined(__cplusplus) && __cplusplus <= 202302L)
#  undef __alignas_is_defined
#  define __alignas_is_defined 1
#endif
/* C11 to C17, where alignof is the macro above, and C++17 to C++23 (LWG 4036)
 * also have __alignof_is_defined.
 */
#if defined(alignof) \
 || (defined(__cplusplus) && __cplusplus > 201402L && __cplusplus <= 202302L)
#  undef __alignof_is_defined
#  define __alignof_is_defined 1
#endif

#endif
