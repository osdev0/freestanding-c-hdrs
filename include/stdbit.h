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

#ifndef __FREESTANDING_C_HDRS_STDBIT_H
#define __FREESTANDING_C_HDRS_STDBIT_H 1

#pragma GCC system_header

#include <__freestanding_c_hdrs/revision.h>

#if __FREESTANDING_C_HDRS_STDBIT_REVISION < 202311L
#  error "<stdbit.h> requires C23 or C++26 or later"
#else

#define __STDC_VERSION_STDBIT_H__ 202311L

/* The byte orders, in the values the compilers give them. */
#define __STDC_ENDIAN_LITTLE__ __ORDER_LITTLE_ENDIAN__
#define __STDC_ENDIAN_BIG__ __ORDER_BIG_ENDIAN__
#define __STDC_ENDIAN_NATIVE__ __BYTE_ORDER__

/* The type names the header makes available, which <stddef.h> and
 * <stdint.h> declare too.
 */
typedef __SIZE_TYPE__ size_t;

#ifdef __UINT8_TYPE__
typedef __UINT8_TYPE__ uint8_t;
#endif
#ifdef __UINT16_TYPE__
typedef __UINT16_TYPE__ uint16_t;
#endif
#ifdef __UINT32_TYPE__
typedef __UINT32_TYPE__ uint32_t;
#endif
#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ uint64_t;
#endif

typedef __UINT_LEAST8_TYPE__ uint_least8_t;
typedef __UINT_LEAST16_TYPE__ uint_least16_t;
typedef __UINT_LEAST32_TYPE__ uint_least32_t;
typedef __UINT_LEAST64_TYPE__ uint_least64_t;

#ifdef __INT8_TYPE__
typedef __INT8_TYPE__ int8_t;
#endif
#ifdef __INT16_TYPE__
typedef __INT16_TYPE__ int16_t;
#endif
#ifdef __INT32_TYPE__
typedef __INT32_TYPE__ int32_t;
#endif
#ifdef __INT64_TYPE__
typedef __INT64_TYPE__ int64_t;
#endif

typedef __INT_LEAST8_TYPE__ int_least8_t;
typedef __INT_LEAST16_TYPE__ int_least16_t;
typedef __INT_LEAST32_TYPE__ int_least32_t;
typedef __INT_LEAST64_TYPE__ int_least64_t;

#ifndef __cplusplus

/* What the operations are made of, for x, an object of an unsigned integer
 * type, which they read more than once: its width, and the numbers of its
 * leading and of its trailing zero bits, which are z where x is 0, and of its
 * one bits.
 */
#if __has_builtin(__builtin_clzg) && __has_builtin(__builtin_ctzg) \
 && __has_builtin(__builtin_popcountg)
#  define __FREESTANDING_C_HDRS_STDBIT_WIDTH(x) \
       __builtin_popcountg((__typeof__(x))~(__typeof__(x))0)
#  define __FREESTANDING_C_HDRS_STDBIT_CLZ(x, z) __builtin_clzg((x), (z))
#  define __FREESTANDING_C_HDRS_STDBIT_CTZ(x, z) __builtin_ctzg((x), (z))
#  define __FREESTANDING_C_HDRS_STDBIT_POPCOUNT(x) __builtin_popcountg((x))
#else
/* GCC before 14 and Clang before 19 have these builtins for unsigned int,
 * long and long long alone: those of unsigned long long, of which the types
 * twice as wide, unsigned __int128 and unsigned _BitInt(128), are made of two.
 */
#  define __FREESTANDING_C_HDRS_STDBIT_LLONG \
       ((int)(sizeof(unsigned long long) * __CHAR_BIT__))
#  define __FREESTANDING_C_HDRS_STDBIT_WIDTH(x) \
       ((int)(sizeof(x) * __CHAR_BIT__))
#  define __FREESTANDING_C_HDRS_STDBIT_WIDE(x) \
       (sizeof(x) > sizeof(unsigned long long))
#  define __FREESTANDING_C_HDRS_STDBIT_LOW(x) ((unsigned long long)(x))
#  define __FREESTANDING_C_HDRS_STDBIT_HIGH(x) \
       ((unsigned long long)((x) >> (__FREESTANDING_C_HDRS_STDBIT_WIDE(x) \
                                     ? __FREESTANDING_C_HDRS_STDBIT_LLONG : 0)))
#  define __FREESTANDING_C_HDRS_STDBIT_CLZ(x, z) \
       ((x) == 0 ? (z) \
        : !__FREESTANDING_C_HDRS_STDBIT_WIDE(x) \
        ? __builtin_clzll(__FREESTANDING_C_HDRS_STDBIT_LOW(x)) \
          - (__FREESTANDING_C_HDRS_STDBIT_LLONG \
             - __FREESTANDING_C_HDRS_STDBIT_WIDTH(x)) \
        : __FREESTANDING_C_HDRS_STDBIT_HIGH(x) != 0 \
        ? __builtin_clzll(__FREESTANDING_C_HDRS_STDBIT_HIGH(x)) \
        : __FREESTANDING_C_HDRS_STDBIT_LLONG \
          + __builtin_clzll(__FREESTANDING_C_HDRS_STDBIT_LOW(x)))
#  define __FREESTANDING_C_HDRS_STDBIT_CTZ(x, z) \
       ((x) == 0 ? (z) \
        : __FREESTANDING_C_HDRS_STDBIT_LOW(x) != 0 \
        ? __builtin_ctzll(__FREESTANDING_C_HDRS_STDBIT_LOW(x)) \
        : __FREESTANDING_C_HDRS_STDBIT_LLONG \
          + __builtin_ctzll(__FREESTANDING_C_HDRS_STDBIT_HIGH(x)))
#  define __FREESTANDING_C_HDRS_STDBIT_POPCOUNT(x) \
       (__builtin_popcountll(__FREESTANDING_C_HDRS_STDBIT_LOW(x)) \
        + (__FREESTANDING_C_HDRS_STDBIT_WIDE(x) \
           ? __builtin_popcountll(__FREESTANDING_C_HDRS_STDBIT_HIGH(x)) : 0))
#endif

/* The operations, on such an x, with results of the types of those of the
 * functions: the first bits are at their index plus 1, or at 0 where there is
 * none, and the ceiling is 0 where it cannot be represented, which a shift of
 * 2 rather than of 1 gives. The floor and the ceiling are converted to the
 * type of x as a whole, as C promotes the operands of the conditional
 * operator.
 */
#define __FREESTANDING_C_HDRS_STDBIT_NOT(x) ((__typeof__(x))~(x))
#define __FREESTANDING_C_HDRS_STDBIT_OP_leading_zeros(x) \
    ((unsigned int)__FREESTANDING_C_HDRS_STDBIT_CLZ( \
        x, __FREESTANDING_C_HDRS_STDBIT_WIDTH(x)))
#define __FREESTANDING_C_HDRS_STDBIT_OP_leading_ones(x) \
    __FREESTANDING_C_HDRS_STDBIT_OP_leading_zeros( \
        __FREESTANDING_C_HDRS_STDBIT_NOT(x))
#define __FREESTANDING_C_HDRS_STDBIT_OP_trailing_zeros(x) \
    ((unsigned int)__FREESTANDING_C_HDRS_STDBIT_CTZ( \
        x, __FREESTANDING_C_HDRS_STDBIT_WIDTH(x)))
#define __FREESTANDING_C_HDRS_STDBIT_OP_trailing_ones(x) \
    __FREESTANDING_C_HDRS_STDBIT_OP_trailing_zeros( \
        __FREESTANDING_C_HDRS_STDBIT_NOT(x))
#define __FREESTANDING_C_HDRS_STDBIT_OP_first_leading_zero(x) \
    __FREESTANDING_C_HDRS_STDBIT_OP_first_leading_one( \
        __FREESTANDING_C_HDRS_STDBIT_NOT(x))
#define __FREESTANDING_C_HDRS_STDBIT_OP_first_leading_one(x) \
    ((unsigned int)(__FREESTANDING_C_HDRS_STDBIT_CLZ(x, -1) + 1))
#define __FREESTANDING_C_HDRS_STDBIT_OP_first_trailing_zero(x) \
    __FREESTANDING_C_HDRS_STDBIT_OP_first_trailing_one( \
        __FREESTANDING_C_HDRS_STDBIT_NOT(x))
#define __FREESTANDING_C_HDRS_STDBIT_OP_first_trailing_one(x) \
    ((unsigned int)(__FREESTANDING_C_HDRS_STDBIT_CTZ(x, -1) + 1))
#define __FREESTANDING_C_HDRS_STDBIT_OP_count_zeros(x) \
    ((unsigned int)(__FREESTANDING_C_HDRS_STDBIT_WIDTH(x) \
                    - __FREESTANDING_C_HDRS_STDBIT_POPCOUNT(x)))
#define __FREESTANDING_C_HDRS_STDBIT_OP_count_ones(x) \
    ((unsigned int)__FREESTANDING_C_HDRS_STDBIT_POPCOUNT(x))
#define __FREESTANDING_C_HDRS_STDBIT_OP_has_single_bit(x) \
    ((_Bool)((x) != 0 && ((x) & ((x) - 1)) == 0))
#define __FREESTANDING_C_HDRS_STDBIT_OP_bit_width(x) \
    ((unsigned int)(__FREESTANDING_C_HDRS_STDBIT_WIDTH(x) \
                    - __FREESTANDING_C_HDRS_STDBIT_CLZ( \
                        x, __FREESTANDING_C_HDRS_STDBIT_WIDTH(x))))
#define __FREESTANDING_C_HDRS_STDBIT_OP_bit_floor(x) \
    ((__typeof__(x))((x) == 0 ? 0 \
                     : (__typeof__(x))1 \
                       << (__FREESTANDING_C_HDRS_STDBIT_WIDTH(x) - 1 \
                           - __FREESTANDING_C_HDRS_STDBIT_CLZ(x, 0))))
#define __FREESTANDING_C_HDRS_STDBIT_OP_bit_ceil(x) \
    ((__typeof__(x))((x) <= 1 ? 1 \
                     : (__typeof__(x))2 \
                       << (__FREESTANDING_C_HDRS_STDBIT_WIDTH(x) - 1 \
                           - __FREESTANDING_C_HDRS_STDBIT_CLZ( \
                               (__typeof__(x))((x) - 1), 0))))

/* Each operation, F(name, its results for unsigned char, short, int, long
 * and long long).
 */
#define __FREESTANDING_C_HDRS_STDBIT_OPERATIONS(F) \
    F(leading_zeros, unsigned int, unsigned int, unsigned int, \
      unsigned int, unsigned int) \
    F(leading_ones, unsigned int, unsigned int, unsigned int, \
      unsigned int, unsigned int) \
    F(trailing_zeros, unsigned int, unsigned int, unsigned int, \
      unsigned int, unsigned int) \
    F(trailing_ones, unsigned int, unsigned int, unsigned int, \
      unsigned int, unsigned int) \
    F(first_leading_zero, unsigned int, unsigned int, unsigned int, \
      unsigned int, unsigned int) \
    F(first_leading_one, unsigned int, unsigned int, unsigned int, \
      unsigned int, unsigned int) \
    F(first_trailing_zero, unsigned int, unsigned int, unsigned int, \
      unsigned int, unsigned int) \
    F(first_trailing_one, unsigned int, unsigned int, unsigned int, \
      unsigned int, unsigned int) \
    F(count_zeros, unsigned int, unsigned int, unsigned int, \
      unsigned int, unsigned int) \
    F(count_ones, unsigned int, unsigned int, unsigned int, \
      unsigned int, unsigned int) \
    F(has_single_bit, _Bool, _Bool, _Bool, _Bool, _Bool) \
    F(bit_width, unsigned int, unsigned int, unsigned int, \
      unsigned int, unsigned int) \
    F(bit_floor, unsigned char, unsigned short, unsigned int, unsigned long, \
      unsigned long long) \
    F(bit_ceil, unsigned char, unsigned short, unsigned int, unsigned long, \
      unsigned long long)

#if defined(__has_c_attribute)
#  if __has_c_attribute(__unsequenced__)
#    define __FREESTANDING_C_HDRS_STDBIT_UNSEQUENCED [[__unsequenced__]]
#  endif
#endif
#ifndef __FREESTANDING_C_HDRS_STDBIT_UNSEQUENCED
#  define __FREESTANDING_C_HDRS_STDBIT_UNSEQUENCED
#endif

/* C makes these functions: a program that takes their addresses or suppresses
 * their macros links with a library that defines them. The macros below
 * compute their results themselves, and need no library.
 */
#define __FREESTANDING_C_HDRS_STDBIT_DECLARE(name, ruc, rus, rui, rul, rull) \
    ruc stdc_##name##_uc(unsigned char) \
        __FREESTANDING_C_HDRS_STDBIT_UNSEQUENCED; \
    rus stdc_##name##_us(unsigned short) \
        __FREESTANDING_C_HDRS_STDBIT_UNSEQUENCED; \
    rui stdc_##name##_ui(unsigned int) \
        __FREESTANDING_C_HDRS_STDBIT_UNSEQUENCED; \
    rul stdc_##name##_ul(unsigned long) \
        __FREESTANDING_C_HDRS_STDBIT_UNSEQUENCED; \
    rull stdc_##name##_ull(unsigned long long) \
        __FREESTANDING_C_HDRS_STDBIT_UNSEQUENCED;
__FREESTANDING_C_HDRS_STDBIT_OPERATIONS(__FREESTANDING_C_HDRS_STDBIT_DECLARE)
#undef __FREESTANDING_C_HDRS_STDBIT_DECLARE
#undef __FREESTANDING_C_HDRS_STDBIT_UNSEQUENCED

/* The macros of the functions, which convert their argument as a call does,
 * and of the type-generic functions, which are the builtins of the compilers
 * that have them, GCC 14 and later and Clang 23 and later. A call of a
 * function that is declared alone, in sizeof, makes the conversion check its
 * argument as a call does, without evaluating it.
 */
#if __has_builtin(__builtin_stdc_leading_zeros) \
 && __has_builtin(__builtin_stdc_leading_ones) \
 && __has_builtin(__builtin_stdc_trailing_zeros) \
 && __has_builtin(__builtin_stdc_trailing_ones) \
 && __has_builtin(__builtin_stdc_first_leading_zero) \
 && __has_builtin(__builtin_stdc_first_leading_one) \
 && __has_builtin(__builtin_stdc_first_trailing_zero) \
 && __has_builtin(__builtin_stdc_first_trailing_one) \
 && __has_builtin(__builtin_stdc_count_zeros) \
 && __has_builtin(__builtin_stdc_count_ones) \
 && __has_builtin(__builtin_stdc_has_single_bit) \
 && __has_builtin(__builtin_stdc_bit_width) \
 && __has_builtin(__builtin_stdc_bit_floor) \
 && __has_builtin(__builtin_stdc_bit_ceil)
unsigned char __freestanding_c_hdrs_stdbit_uc(unsigned char);
unsigned short __freestanding_c_hdrs_stdbit_us(unsigned short);
unsigned int __freestanding_c_hdrs_stdbit_ui(unsigned int);
unsigned long __freestanding_c_hdrs_stdbit_ul(unsigned long);
unsigned long long __freestanding_c_hdrs_stdbit_ull(unsigned long long);
#  define __FREESTANDING_C_HDRS_STDBIT(type, conversion, name, value) \
       ((void)sizeof(conversion(value)), __builtin_stdc_##name((type)(value)))
#  define __FREESTANDING_C_HDRS_STDBIT_GENERIC(name, value) \
       __builtin_stdc_##name(value)
#else
/* Workaround: GCC 13, and Clang 16 to 22, all targets: they have no such
 * builtins, so the macros compute the results in statement expressions, which
 * cannot be used outside of a function, not even in sizeof or typeof.
 */
#  define __FREESTANDING_C_HDRS_STDBIT_CALL(type, name, value) \
       (__extension__({ \
           type __freestanding_c_hdrs_x = (value); \
           __FREESTANDING_C_HDRS_STDBIT_OP_##name(__freestanding_c_hdrs_x); \
       }))
#  define __FREESTANDING_C_HDRS_STDBIT(type, conversion, name, value) \
       __FREESTANDING_C_HDRS_STDBIT_CALL(type, name, value)
#  define __FREESTANDING_C_HDRS_STDBIT_GENERIC(name, value) \
       __FREESTANDING_C_HDRS_STDBIT_CALL( \
           __typeof__((void)0, (value)), name, value)
#endif
#define __FREESTANDING_C_HDRS_STDBIT_UC(name, value) \
    __FREESTANDING_C_HDRS_STDBIT(unsigned char, \
                                 __freestanding_c_hdrs_stdbit_uc, name, value)
#define __FREESTANDING_C_HDRS_STDBIT_US(name, value) \
    __FREESTANDING_C_HDRS_STDBIT(unsigned short, \
                                 __freestanding_c_hdrs_stdbit_us, name, value)
#define __FREESTANDING_C_HDRS_STDBIT_UI(name, value) \
    __FREESTANDING_C_HDRS_STDBIT(unsigned int, \
                                 __freestanding_c_hdrs_stdbit_ui, name, value)
#define __FREESTANDING_C_HDRS_STDBIT_UL(name, value) \
    __FREESTANDING_C_HDRS_STDBIT(unsigned long, \
                                 __freestanding_c_hdrs_stdbit_ul, name, value)
#define __FREESTANDING_C_HDRS_STDBIT_ULL(name, value) \
    __FREESTANDING_C_HDRS_STDBIT(unsigned long long, \
                                 __freestanding_c_hdrs_stdbit_ull, name, value)

#undef stdc_leading_zeros_uc
#define stdc_leading_zeros_uc(value) \
    __FREESTANDING_C_HDRS_STDBIT_UC(leading_zeros, value)
#undef stdc_leading_zeros_us
#define stdc_leading_zeros_us(value) \
    __FREESTANDING_C_HDRS_STDBIT_US(leading_zeros, value)
#undef stdc_leading_zeros_ui
#define stdc_leading_zeros_ui(value) \
    __FREESTANDING_C_HDRS_STDBIT_UI(leading_zeros, value)
#undef stdc_leading_zeros_ul
#define stdc_leading_zeros_ul(value) \
    __FREESTANDING_C_HDRS_STDBIT_UL(leading_zeros, value)
#undef stdc_leading_zeros_ull
#define stdc_leading_zeros_ull(value) \
    __FREESTANDING_C_HDRS_STDBIT_ULL(leading_zeros, value)
#undef stdc_leading_zeros
#define stdc_leading_zeros(value) \
    __FREESTANDING_C_HDRS_STDBIT_GENERIC(leading_zeros, value)

#undef stdc_leading_ones_uc
#define stdc_leading_ones_uc(value) \
    __FREESTANDING_C_HDRS_STDBIT_UC(leading_ones, value)
#undef stdc_leading_ones_us
#define stdc_leading_ones_us(value) \
    __FREESTANDING_C_HDRS_STDBIT_US(leading_ones, value)
#undef stdc_leading_ones_ui
#define stdc_leading_ones_ui(value) \
    __FREESTANDING_C_HDRS_STDBIT_UI(leading_ones, value)
#undef stdc_leading_ones_ul
#define stdc_leading_ones_ul(value) \
    __FREESTANDING_C_HDRS_STDBIT_UL(leading_ones, value)
#undef stdc_leading_ones_ull
#define stdc_leading_ones_ull(value) \
    __FREESTANDING_C_HDRS_STDBIT_ULL(leading_ones, value)
#undef stdc_leading_ones
#define stdc_leading_ones(value) \
    __FREESTANDING_C_HDRS_STDBIT_GENERIC(leading_ones, value)

#undef stdc_trailing_zeros_uc
#define stdc_trailing_zeros_uc(value) \
    __FREESTANDING_C_HDRS_STDBIT_UC(trailing_zeros, value)
#undef stdc_trailing_zeros_us
#define stdc_trailing_zeros_us(value) \
    __FREESTANDING_C_HDRS_STDBIT_US(trailing_zeros, value)
#undef stdc_trailing_zeros_ui
#define stdc_trailing_zeros_ui(value) \
    __FREESTANDING_C_HDRS_STDBIT_UI(trailing_zeros, value)
#undef stdc_trailing_zeros_ul
#define stdc_trailing_zeros_ul(value) \
    __FREESTANDING_C_HDRS_STDBIT_UL(trailing_zeros, value)
#undef stdc_trailing_zeros_ull
#define stdc_trailing_zeros_ull(value) \
    __FREESTANDING_C_HDRS_STDBIT_ULL(trailing_zeros, value)
#undef stdc_trailing_zeros
#define stdc_trailing_zeros(value) \
    __FREESTANDING_C_HDRS_STDBIT_GENERIC(trailing_zeros, value)

#undef stdc_trailing_ones_uc
#define stdc_trailing_ones_uc(value) \
    __FREESTANDING_C_HDRS_STDBIT_UC(trailing_ones, value)
#undef stdc_trailing_ones_us
#define stdc_trailing_ones_us(value) \
    __FREESTANDING_C_HDRS_STDBIT_US(trailing_ones, value)
#undef stdc_trailing_ones_ui
#define stdc_trailing_ones_ui(value) \
    __FREESTANDING_C_HDRS_STDBIT_UI(trailing_ones, value)
#undef stdc_trailing_ones_ul
#define stdc_trailing_ones_ul(value) \
    __FREESTANDING_C_HDRS_STDBIT_UL(trailing_ones, value)
#undef stdc_trailing_ones_ull
#define stdc_trailing_ones_ull(value) \
    __FREESTANDING_C_HDRS_STDBIT_ULL(trailing_ones, value)
#undef stdc_trailing_ones
#define stdc_trailing_ones(value) \
    __FREESTANDING_C_HDRS_STDBIT_GENERIC(trailing_ones, value)

#undef stdc_first_leading_zero_uc
#define stdc_first_leading_zero_uc(value) \
    __FREESTANDING_C_HDRS_STDBIT_UC(first_leading_zero, value)
#undef stdc_first_leading_zero_us
#define stdc_first_leading_zero_us(value) \
    __FREESTANDING_C_HDRS_STDBIT_US(first_leading_zero, value)
#undef stdc_first_leading_zero_ui
#define stdc_first_leading_zero_ui(value) \
    __FREESTANDING_C_HDRS_STDBIT_UI(first_leading_zero, value)
#undef stdc_first_leading_zero_ul
#define stdc_first_leading_zero_ul(value) \
    __FREESTANDING_C_HDRS_STDBIT_UL(first_leading_zero, value)
#undef stdc_first_leading_zero_ull
#define stdc_first_leading_zero_ull(value) \
    __FREESTANDING_C_HDRS_STDBIT_ULL(first_leading_zero, value)
#undef stdc_first_leading_zero
#define stdc_first_leading_zero(value) \
    __FREESTANDING_C_HDRS_STDBIT_GENERIC(first_leading_zero, value)

#undef stdc_first_leading_one_uc
#define stdc_first_leading_one_uc(value) \
    __FREESTANDING_C_HDRS_STDBIT_UC(first_leading_one, value)
#undef stdc_first_leading_one_us
#define stdc_first_leading_one_us(value) \
    __FREESTANDING_C_HDRS_STDBIT_US(first_leading_one, value)
#undef stdc_first_leading_one_ui
#define stdc_first_leading_one_ui(value) \
    __FREESTANDING_C_HDRS_STDBIT_UI(first_leading_one, value)
#undef stdc_first_leading_one_ul
#define stdc_first_leading_one_ul(value) \
    __FREESTANDING_C_HDRS_STDBIT_UL(first_leading_one, value)
#undef stdc_first_leading_one_ull
#define stdc_first_leading_one_ull(value) \
    __FREESTANDING_C_HDRS_STDBIT_ULL(first_leading_one, value)
#undef stdc_first_leading_one
#define stdc_first_leading_one(value) \
    __FREESTANDING_C_HDRS_STDBIT_GENERIC(first_leading_one, value)

#undef stdc_first_trailing_zero_uc
#define stdc_first_trailing_zero_uc(value) \
    __FREESTANDING_C_HDRS_STDBIT_UC(first_trailing_zero, value)
#undef stdc_first_trailing_zero_us
#define stdc_first_trailing_zero_us(value) \
    __FREESTANDING_C_HDRS_STDBIT_US(first_trailing_zero, value)
#undef stdc_first_trailing_zero_ui
#define stdc_first_trailing_zero_ui(value) \
    __FREESTANDING_C_HDRS_STDBIT_UI(first_trailing_zero, value)
#undef stdc_first_trailing_zero_ul
#define stdc_first_trailing_zero_ul(value) \
    __FREESTANDING_C_HDRS_STDBIT_UL(first_trailing_zero, value)
#undef stdc_first_trailing_zero_ull
#define stdc_first_trailing_zero_ull(value) \
    __FREESTANDING_C_HDRS_STDBIT_ULL(first_trailing_zero, value)
#undef stdc_first_trailing_zero
#define stdc_first_trailing_zero(value) \
    __FREESTANDING_C_HDRS_STDBIT_GENERIC(first_trailing_zero, value)

#undef stdc_first_trailing_one_uc
#define stdc_first_trailing_one_uc(value) \
    __FREESTANDING_C_HDRS_STDBIT_UC(first_trailing_one, value)
#undef stdc_first_trailing_one_us
#define stdc_first_trailing_one_us(value) \
    __FREESTANDING_C_HDRS_STDBIT_US(first_trailing_one, value)
#undef stdc_first_trailing_one_ui
#define stdc_first_trailing_one_ui(value) \
    __FREESTANDING_C_HDRS_STDBIT_UI(first_trailing_one, value)
#undef stdc_first_trailing_one_ul
#define stdc_first_trailing_one_ul(value) \
    __FREESTANDING_C_HDRS_STDBIT_UL(first_trailing_one, value)
#undef stdc_first_trailing_one_ull
#define stdc_first_trailing_one_ull(value) \
    __FREESTANDING_C_HDRS_STDBIT_ULL(first_trailing_one, value)
#undef stdc_first_trailing_one
#define stdc_first_trailing_one(value) \
    __FREESTANDING_C_HDRS_STDBIT_GENERIC(first_trailing_one, value)

#undef stdc_count_zeros_uc
#define stdc_count_zeros_uc(value) \
    __FREESTANDING_C_HDRS_STDBIT_UC(count_zeros, value)
#undef stdc_count_zeros_us
#define stdc_count_zeros_us(value) \
    __FREESTANDING_C_HDRS_STDBIT_US(count_zeros, value)
#undef stdc_count_zeros_ui
#define stdc_count_zeros_ui(value) \
    __FREESTANDING_C_HDRS_STDBIT_UI(count_zeros, value)
#undef stdc_count_zeros_ul
#define stdc_count_zeros_ul(value) \
    __FREESTANDING_C_HDRS_STDBIT_UL(count_zeros, value)
#undef stdc_count_zeros_ull
#define stdc_count_zeros_ull(value) \
    __FREESTANDING_C_HDRS_STDBIT_ULL(count_zeros, value)
#undef stdc_count_zeros
#define stdc_count_zeros(value) \
    __FREESTANDING_C_HDRS_STDBIT_GENERIC(count_zeros, value)

#undef stdc_count_ones_uc
#define stdc_count_ones_uc(value) \
    __FREESTANDING_C_HDRS_STDBIT_UC(count_ones, value)
#undef stdc_count_ones_us
#define stdc_count_ones_us(value) \
    __FREESTANDING_C_HDRS_STDBIT_US(count_ones, value)
#undef stdc_count_ones_ui
#define stdc_count_ones_ui(value) \
    __FREESTANDING_C_HDRS_STDBIT_UI(count_ones, value)
#undef stdc_count_ones_ul
#define stdc_count_ones_ul(value) \
    __FREESTANDING_C_HDRS_STDBIT_UL(count_ones, value)
#undef stdc_count_ones_ull
#define stdc_count_ones_ull(value) \
    __FREESTANDING_C_HDRS_STDBIT_ULL(count_ones, value)
#undef stdc_count_ones
#define stdc_count_ones(value) \
    __FREESTANDING_C_HDRS_STDBIT_GENERIC(count_ones, value)

#undef stdc_has_single_bit_uc
#define stdc_has_single_bit_uc(value) \
    __FREESTANDING_C_HDRS_STDBIT_UC(has_single_bit, value)
#undef stdc_has_single_bit_us
#define stdc_has_single_bit_us(value) \
    __FREESTANDING_C_HDRS_STDBIT_US(has_single_bit, value)
#undef stdc_has_single_bit_ui
#define stdc_has_single_bit_ui(value) \
    __FREESTANDING_C_HDRS_STDBIT_UI(has_single_bit, value)
#undef stdc_has_single_bit_ul
#define stdc_has_single_bit_ul(value) \
    __FREESTANDING_C_HDRS_STDBIT_UL(has_single_bit, value)
#undef stdc_has_single_bit_ull
#define stdc_has_single_bit_ull(value) \
    __FREESTANDING_C_HDRS_STDBIT_ULL(has_single_bit, value)
#undef stdc_has_single_bit
#define stdc_has_single_bit(value) \
    __FREESTANDING_C_HDRS_STDBIT_GENERIC(has_single_bit, value)

#undef stdc_bit_width_uc
#define stdc_bit_width_uc(value) \
    __FREESTANDING_C_HDRS_STDBIT_UC(bit_width, value)
#undef stdc_bit_width_us
#define stdc_bit_width_us(value) \
    __FREESTANDING_C_HDRS_STDBIT_US(bit_width, value)
#undef stdc_bit_width_ui
#define stdc_bit_width_ui(value) \
    __FREESTANDING_C_HDRS_STDBIT_UI(bit_width, value)
#undef stdc_bit_width_ul
#define stdc_bit_width_ul(value) \
    __FREESTANDING_C_HDRS_STDBIT_UL(bit_width, value)
#undef stdc_bit_width_ull
#define stdc_bit_width_ull(value) \
    __FREESTANDING_C_HDRS_STDBIT_ULL(bit_width, value)
#undef stdc_bit_width
#define stdc_bit_width(value) \
    __FREESTANDING_C_HDRS_STDBIT_GENERIC(bit_width, value)

#undef stdc_bit_floor_uc
#define stdc_bit_floor_uc(value) \
    __FREESTANDING_C_HDRS_STDBIT_UC(bit_floor, value)
#undef stdc_bit_floor_us
#define stdc_bit_floor_us(value) \
    __FREESTANDING_C_HDRS_STDBIT_US(bit_floor, value)
#undef stdc_bit_floor_ui
#define stdc_bit_floor_ui(value) \
    __FREESTANDING_C_HDRS_STDBIT_UI(bit_floor, value)
#undef stdc_bit_floor_ul
#define stdc_bit_floor_ul(value) \
    __FREESTANDING_C_HDRS_STDBIT_UL(bit_floor, value)
#undef stdc_bit_floor_ull
#define stdc_bit_floor_ull(value) \
    __FREESTANDING_C_HDRS_STDBIT_ULL(bit_floor, value)
#undef stdc_bit_floor
#define stdc_bit_floor(value) \
    __FREESTANDING_C_HDRS_STDBIT_GENERIC(bit_floor, value)

#undef stdc_bit_ceil_uc
#define stdc_bit_ceil_uc(value) \
    __FREESTANDING_C_HDRS_STDBIT_UC(bit_ceil, value)
#undef stdc_bit_ceil_us
#define stdc_bit_ceil_us(value) \
    __FREESTANDING_C_HDRS_STDBIT_US(bit_ceil, value)
#undef stdc_bit_ceil_ui
#define stdc_bit_ceil_ui(value) \
    __FREESTANDING_C_HDRS_STDBIT_UI(bit_ceil, value)
#undef stdc_bit_ceil_ul
#define stdc_bit_ceil_ul(value) \
    __FREESTANDING_C_HDRS_STDBIT_UL(bit_ceil, value)
#undef stdc_bit_ceil_ull
#define stdc_bit_ceil_ull(value) \
    __FREESTANDING_C_HDRS_STDBIT_ULL(bit_ceil, value)
#undef stdc_bit_ceil
#define stdc_bit_ceil(value) \
    __FREESTANDING_C_HDRS_STDBIT_GENERIC(bit_ceil, value)

#undef __FREESTANDING_C_HDRS_STDBIT_OPERATIONS

#else

#include <__fcxx/c_stdbit.h>

#endif

#endif

#endif
