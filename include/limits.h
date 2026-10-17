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

#ifndef __FREESTANDING_C_HDRS_LIMITS_H
#define __FREESTANDING_C_HDRS_LIMITS_H 1

#undef CHAR_BIT
#define CHAR_BIT __CHAR_BIT__

#ifndef MB_LEN_MAX
#   define MB_LEN_MAX 1
#endif

#undef SCHAR_MAX
#define SCHAR_MAX __SCHAR_MAX__
#undef SCHAR_MIN
#define SCHAR_MIN (-SCHAR_MAX - 1)

#undef UCHAR_MAX
#if __SCHAR_MAX__ == __INT_MAX__
#   define UCHAR_MAX (SCHAR_MAX * 2U + 1U)
#else
#   define UCHAR_MAX (SCHAR_MAX * 2 + 1)
#endif

#ifdef __CHAR_UNSIGNED__
#   undef CHAR_MAX
#   define CHAR_MAX UCHAR_MAX
#   undef CHAR_MIN
#   if __SCHAR_MAX__ == __INT_MAX__
#       define CHAR_MIN 0U
#   else
#       define CHAR_MIN 0
#   endif
#else
#   undef CHAR_MAX
#   define CHAR_MAX SCHAR_MAX
#   undef CHAR_MIN
#   define CHAR_MIN SCHAR_MIN
#endif

#undef SHRT_MAX
#define SHRT_MAX __SHRT_MAX__
#undef SHRT_MIN
#define SHRT_MIN (-SHRT_MAX - 1)

#undef USHRT_MAX
#if __SHRT_MAX__ == __INT_MAX__
#   define USHRT_MAX (SHRT_MAX * 2U + 1U)
#else
#   define USHRT_MAX (SHRT_MAX * 2 + 1)
#endif

#undef INT_MAX
#define INT_MAX __INT_MAX__
#undef INT_MIN
#define INT_MIN (-INT_MAX - 1)

#undef UINT_MAX
#define UINT_MAX (INT_MAX * 2U + 1U)

#undef LONG_MAX
#define LONG_MAX __LONG_MAX__
#undef LONG_MIN
#define LONG_MIN (-LONG_MAX - 1L)

#undef ULONG_MAX
#define ULONG_MAX (LONG_MAX * 2UL + 1UL)

#if (defined(__cplusplus) && __cplusplus >= 201103L) \
 || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L)

#undef LLONG_MAX
#define LLONG_MAX __LONG_LONG_MAX__
#undef LLONG_MIN
#define LLONG_MIN (-LLONG_MAX - 1LL)

#undef ULLONG_MAX
#define ULLONG_MAX (LLONG_MAX * 2ULL + 1ULL)

#endif

/* Workaround: GCC 13 to 14, and Clang 16 to 17, all targets: their C23 mode
 * reports 202000L, the value they give the drafts of C23.
 */
#if (defined(__cplusplus) && __cplusplus > 202302L) \
 || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L) \
 || (defined(__STDC_VERSION__) && __STDC_VERSION__ > 201710L \
     && ((defined(__clang__) && __clang_major__ >= 16) \
         || (!defined(__clang__) && __GNUC__ >= 13)))

#if defined(__clang__)
#   undef CHAR_WIDTH
#   define CHAR_WIDTH CHAR_BIT
#   undef SCHAR_WIDTH
#   define SCHAR_WIDTH CHAR_BIT
#   undef UCHAR_WIDTH
#   define UCHAR_WIDTH CHAR_BIT
#else
#   undef CHAR_WIDTH
#   define CHAR_WIDTH __SCHAR_WIDTH__
#   undef SCHAR_WIDTH
#   define SCHAR_WIDTH __SCHAR_WIDTH__
#   undef UCHAR_WIDTH
#   define UCHAR_WIDTH __SCHAR_WIDTH__
#endif
#   undef SHRT_WIDTH
#   define SHRT_WIDTH __SHRT_WIDTH__
#   undef USHRT_WIDTH
#   define USHRT_WIDTH __SHRT_WIDTH__
#   undef INT_WIDTH
#   define INT_WIDTH __INT_WIDTH__
#   undef UINT_WIDTH
#   define UINT_WIDTH __INT_WIDTH__
#   undef LONG_WIDTH
#   define LONG_WIDTH __LONG_WIDTH__
#   undef ULONG_WIDTH
#   define ULONG_WIDTH __LONG_WIDTH__
#if defined(__clang__)
#   undef LLONG_WIDTH
#   define LLONG_WIDTH __LLONG_WIDTH__
#   undef ULLONG_WIDTH
#   define ULLONG_WIDTH __LLONG_WIDTH__
#else
#   undef LLONG_WIDTH
#   define LLONG_WIDTH __LONG_LONG_WIDTH__
#   undef ULLONG_WIDTH
#   define ULLONG_WIDTH __LONG_LONG_WIDTH__
#endif

#undef BOOL_MAX
#define BOOL_MAX 1
#undef BOOL_WIDTH
#define BOOL_WIDTH 1

/* C++26 does not take this one from C23. */
#if !defined(__cplusplus) && defined(__BITINT_MAXWIDTH__)
#   undef BITINT_MAXWIDTH
#   define BITINT_MAXWIDTH __BITINT_MAXWIDTH__
#endif

#define __STDC_VERSION_LIMITS_H__ 202311L
#endif

#endif
