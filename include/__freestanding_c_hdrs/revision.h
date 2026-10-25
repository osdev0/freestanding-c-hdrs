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


/* The revision of C whose contents each header has, as
 * __FREESTANDING_C_HDRS_<NAME>_REVISION, which the headers include this
 * for: in C, the revision in use, and in C++, what freestanding-cxx-hdrs,
 * which has all that C++ makes of the headers, tells. Where it is missing,
 * the error below comes before that of its include, which ends the
 * compilation.
 */

#ifndef __FREESTANDING_C_HDRS_REVISION_H
#define __FREESTANDING_C_HDRS_REVISION_H 1

#pragma GCC system_header

#ifdef __cplusplus

#if defined(__has_include)
#  if !__has_include(<__fcxx/c_revision.h>)
#    error "the C headers require freestanding-cxx-hdrs in C++"
#  endif
#endif
#include <__fcxx/c_revision.h>

#else

/* Workaround: GCC 13 to 14, and Clang 16 to 17, all targets: their C23 mode
 * reports 202000L, the value they give the drafts of C23.
 */
#if defined(__STDC_VERSION__) \
 && (__STDC_VERSION__ >= 202311L \
     || (__STDC_VERSION__ > 201710L \
         && ((defined(__clang__) && __clang_major__ >= 16) \
             || (!defined(__clang__) && __GNUC__ >= 13))))
#  define __FREESTANDING_C_HDRS_C 202311L
#elif defined(__STDC_VERSION__)
#  define __FREESTANDING_C_HDRS_C __STDC_VERSION__
#else
#  define __FREESTANDING_C_HDRS_C 198900L
#endif

#define __FREESTANDING_C_HDRS_FLOAT_REVISION __FREESTANDING_C_HDRS_C
#define __FREESTANDING_C_HDRS_ISO646_REVISION __FREESTANDING_C_HDRS_C
#define __FREESTANDING_C_HDRS_LIMITS_REVISION __FREESTANDING_C_HDRS_C
#define __FREESTANDING_C_HDRS_STDALIGN_REVISION __FREESTANDING_C_HDRS_C
#define __FREESTANDING_C_HDRS_STDARG_REVISION __FREESTANDING_C_HDRS_C
#define __FREESTANDING_C_HDRS_STDATOMIC_REVISION __FREESTANDING_C_HDRS_C
#define __FREESTANDING_C_HDRS_STDBIT_REVISION __FREESTANDING_C_HDRS_C
#define __FREESTANDING_C_HDRS_STDCKDINT_REVISION __FREESTANDING_C_HDRS_C
#define __FREESTANDING_C_HDRS_STDDEF_REVISION __FREESTANDING_C_HDRS_C
#define __FREESTANDING_C_HDRS_STDINT_REVISION __FREESTANDING_C_HDRS_C
#define __FREESTANDING_C_HDRS_STDNORETURN_REVISION __FREESTANDING_C_HDRS_C

/* Workaround: Clang 15, all targets: its C23 mode, which lacks much of C23,
 * has the keywords bool, true, and false.
 */
#if defined(__clang__) && __clang_major__ == 15 && defined(__STDC_VERSION__) \
 && __STDC_VERSION__ > 201710L
#  define __FREESTANDING_C_HDRS_STDBOOL_REVISION 202311L
#else
#  define __FREESTANDING_C_HDRS_STDBOOL_REVISION __FREESTANDING_C_HDRS_C
#endif

#endif

#endif
