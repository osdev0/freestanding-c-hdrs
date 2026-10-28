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

#ifndef __FREESTANDING_C_HDRS_FLOAT_H
#define __FREESTANDING_C_HDRS_FLOAT_H 1

#pragma GCC system_header

#include <__freestanding_c_hdrs/revision.h>

/* FLT_ROUNDS is left out. It is the rounding mode of floating-point addition
 * at run time, which only the state of the floating-point unit tells, and
 * which the compilers cannot read on every target.
 */

#undef FLT_RADIX
#define FLT_RADIX __FLT_RADIX__

#undef FLT_MANT_DIG
#define FLT_MANT_DIG __FLT_MANT_DIG__
#undef DBL_MANT_DIG
#define DBL_MANT_DIG __DBL_MANT_DIG__
#undef LDBL_MANT_DIG
#define LDBL_MANT_DIG __LDBL_MANT_DIG__

#if __FREESTANDING_C_HDRS_FLOAT_REVISION >= 199901L

#undef DECIMAL_DIG
#define DECIMAL_DIG __DECIMAL_DIG__

#undef FLT_EVAL_METHOD
#define FLT_EVAL_METHOD __FLT_EVAL_METHOD__

#endif

#undef FLT_DIG
#define FLT_DIG __FLT_DIG__
#undef DBL_DIG
#define DBL_DIG __DBL_DIG__
#undef LDBL_DIG
#define LDBL_DIG __LDBL_DIG__

#undef FLT_MIN_EXP
#define FLT_MIN_EXP __FLT_MIN_EXP__
#undef DBL_MIN_EXP
#define DBL_MIN_EXP __DBL_MIN_EXP__
#undef LDBL_MIN_EXP
#define LDBL_MIN_EXP __LDBL_MIN_EXP__

#undef FLT_MIN_10_EXP
#define FLT_MIN_10_EXP __FLT_MIN_10_EXP__
#undef DBL_MIN_10_EXP
#define DBL_MIN_10_EXP __DBL_MIN_10_EXP__
#undef LDBL_MIN_10_EXP
#define LDBL_MIN_10_EXP __LDBL_MIN_10_EXP__

#undef FLT_MAX_EXP
#define FLT_MAX_EXP __FLT_MAX_EXP__
#undef DBL_MAX_EXP
#define DBL_MAX_EXP __DBL_MAX_EXP__
#undef LDBL_MAX_EXP
#define LDBL_MAX_EXP __LDBL_MAX_EXP__

#undef FLT_MAX_10_EXP
#define FLT_MAX_10_EXP __FLT_MAX_10_EXP__
#undef DBL_MAX_10_EXP
#define DBL_MAX_10_EXP __DBL_MAX_10_EXP__
#undef LDBL_MAX_10_EXP
#define LDBL_MAX_10_EXP __LDBL_MAX_10_EXP__

#undef FLT_MAX
#define FLT_MAX __FLT_MAX__
#undef DBL_MAX
#define DBL_MAX __DBL_MAX__
#undef LDBL_MAX
#define LDBL_MAX __LDBL_MAX__

#undef FLT_EPSILON
#define FLT_EPSILON __FLT_EPSILON__
#undef DBL_EPSILON
#define DBL_EPSILON __DBL_EPSILON__
#undef LDBL_EPSILON
#define LDBL_EPSILON __LDBL_EPSILON__

#undef FLT_MIN
#define FLT_MIN __FLT_MIN__
#undef DBL_MIN
#define DBL_MIN __DBL_MIN__
#undef LDBL_MIN
#define LDBL_MIN __LDBL_MIN__

#if __FREESTANDING_C_HDRS_FLOAT_REVISION >= 201112L

#undef FLT_DECIMAL_DIG
#define FLT_DECIMAL_DIG __FLT_DECIMAL_DIG__
#undef DBL_DECIMAL_DIG
#define DBL_DECIMAL_DIG __DBL_DECIMAL_DIG__
/* GCC before 7 lacks __LDBL_DECIMAL_DIG__, but __DECIMAL_DIG__ is the same. */
#undef LDBL_DECIMAL_DIG
#define LDBL_DECIMAL_DIG __DECIMAL_DIG__

#undef FLT_TRUE_MIN
#define FLT_TRUE_MIN __FLT_DENORM_MIN__
#undef DBL_TRUE_MIN
#define DBL_TRUE_MIN __DBL_DENORM_MIN__
#undef LDBL_TRUE_MIN
#define LDBL_TRUE_MIN __LDBL_DENORM_MIN__

#undef FLT_HAS_SUBNORM
#define FLT_HAS_SUBNORM __FLT_HAS_DENORM__
#undef DBL_HAS_SUBNORM
#define DBL_HAS_SUBNORM __DBL_HAS_DENORM__
#undef LDBL_HAS_SUBNORM
#define LDBL_HAS_SUBNORM __LDBL_HAS_DENORM__

#endif

#if __FREESTANDING_C_HDRS_FLOAT_REVISION >= 202311L

#undef __STDC_VERSION_FLOAT_H__
#define __STDC_VERSION_FLOAT_H__ 202311L

/* GCC defines the __*_HAS_* macros as 0 where the format lacks the values. */
#if __FLT_HAS_INFINITY__
#  undef INFINITY
#  define INFINITY (__builtin_inff())
#endif

/* The types with quiet NaNs have signalling ones too. */
#if __FLT_HAS_QUIET_NAN__
#  undef NAN
#  define NAN (__builtin_nanf(""))
#  undef FLT_SNAN
#  define FLT_SNAN (__builtin_nansf(""))
#endif
#if __DBL_HAS_QUIET_NAN__
#  undef DBL_SNAN
#  define DBL_SNAN (__builtin_nans(""))
#endif
#if __LDBL_HAS_QUIET_NAN__
#  undef LDBL_SNAN
#  define LDBL_SNAN (__builtin_nansl(""))
#endif

/* Workaround: Clang up to at least 23, all targets: it does not tell whether
 * the types have the radix, precision, and exponent range of an ISO/IEC 60559
 * format. Of its formats, binary16, binary32, binary64, binary128, and the
 * binary64-extended format of x87 do, with the parameters of C23 Annex H.
 */
#undef FLT_IS_IEC_60559
#undef DBL_IS_IEC_60559
#undef LDBL_IS_IEC_60559
#ifdef __FLT_IS_IEC_60559__
#  define FLT_IS_IEC_60559 __FLT_IS_IEC_60559__
#  define DBL_IS_IEC_60559 __DBL_IS_IEC_60559__
#  define LDBL_IS_IEC_60559 __LDBL_IS_IEC_60559__
#else
#  define __FREESTANDING_C_HDRS_IS_IEC_60559(p, emin, emax) \
       (__FLT_RADIX__ == 2 && (emin) == 3 - (emax) \
           && (((p) == 11 && (emax) == 16) || ((p) == 24 && (emax) == 128) \
               || ((p) == 53 && (emax) == 1024) || ((p) == 64 && (emax) == 16384) \
               || ((p) == 113 && (emax) == 16384)))
#  define FLT_IS_IEC_60559 __FREESTANDING_C_HDRS_IS_IEC_60559(__FLT_MANT_DIG__, __FLT_MIN_EXP__, __FLT_MAX_EXP__)
#  define DBL_IS_IEC_60559 __FREESTANDING_C_HDRS_IS_IEC_60559(__DBL_MANT_DIG__, __DBL_MIN_EXP__, __DBL_MAX_EXP__)
#  define LDBL_IS_IEC_60559 __FREESTANDING_C_HDRS_IS_IEC_60559(__LDBL_MANT_DIG__, __LDBL_MIN_EXP__, __LDBL_MAX_EXP__)
#endif

/* Workaround: Clang 16 to 18, all targets: it does not tell the largest
 * normalised numbers. Those are the largest finite numbers, except for the
 * double-double long double of PowerPC, where it is (1 - 2^-106) * 2^1023.
 */
#undef FLT_NORM_MAX
#undef DBL_NORM_MAX
#undef LDBL_NORM_MAX
#ifdef __FLT_NORM_MAX__
#  define FLT_NORM_MAX __FLT_NORM_MAX__
#  define DBL_NORM_MAX __DBL_NORM_MAX__
#  define LDBL_NORM_MAX __LDBL_NORM_MAX__
#else
#  define FLT_NORM_MAX __FLT_MAX__
#  define DBL_NORM_MAX __DBL_MAX__
#  if __LDBL_MANT_DIG__ == 106
#    define LDBL_NORM_MAX 0x1.ffffffffffffffffffffffffff8p+1022L
#  else
#    define LDBL_NORM_MAX __LDBL_MAX__
#  endif
#endif

#endif

#endif
