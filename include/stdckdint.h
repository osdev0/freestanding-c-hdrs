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

#ifndef __FREESTANDING_C_HDRS_STDCKDINT_H
#define __FREESTANDING_C_HDRS_STDCKDINT_H 1

#pragma GCC system_header

/* Workaround: GCC 13 to 14, and Clang 16 to 17, all targets: their C23 mode
 * reports 202000L, the value they give the drafts of C23.
 */
#if !((defined(__cplusplus) && __cplusplus > 202302L) \
 || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L) \
 || (defined(__STDC_VERSION__) && __STDC_VERSION__ > 201710L \
     && ((defined(__clang__) && __clang_major__ >= 16) \
         || (!defined(__clang__) && __GNUC__ >= 13))))
#  error "<stdckdint.h> requires C23 or C++26 or later"
#else

#define __STDC_VERSION_STDCKDINT_H__ 202311L

#ifndef __cplusplus

#undef ckd_add
#define ckd_add(result, a, b) (__builtin_add_overflow((a), (b), (result)))
#undef ckd_sub
#define ckd_sub(result, a, b) (__builtin_sub_overflow((a), (b), (result)))
#undef ckd_mul
#define ckd_mul(result, a, b) (__builtin_mul_overflow((a), (b), (result)))

#else

#undef __cpp_lib_stdckdint_h
#define __cpp_lib_stdckdint_h 202603L

/* The templates accept only these types: __is_same tells them apart from
 * their const and volatile versions.
 */
template<class __freestanding_c_hdrs_type>
inline constexpr bool __freestanding_c_hdrs_ckd_type =
    __is_same(__freestanding_c_hdrs_type, signed char)
    || __is_same(__freestanding_c_hdrs_type, short)
    || __is_same(__freestanding_c_hdrs_type, int)
    || __is_same(__freestanding_c_hdrs_type, long)
    || __is_same(__freestanding_c_hdrs_type, long long)
    || __is_same(__freestanding_c_hdrs_type, unsigned char)
    || __is_same(__freestanding_c_hdrs_type, unsigned short)
    || __is_same(__freestanding_c_hdrs_type, unsigned int)
    || __is_same(__freestanding_c_hdrs_type, unsigned long)
    || __is_same(__freestanding_c_hdrs_type, unsigned long long)
#ifdef __SIZEOF_INT128__
    || __extension__ __is_same(__freestanding_c_hdrs_type, __int128)
    || __extension__ __is_same(__freestanding_c_hdrs_type, unsigned __int128)
#endif
    ;

template<class __freestanding_c_hdrs_type1, class __freestanding_c_hdrs_type2,
         class __freestanding_c_hdrs_type3>
bool ckd_add(__freestanding_c_hdrs_type1 *__freestanding_c_hdrs_result,
             __freestanding_c_hdrs_type2 __freestanding_c_hdrs_a,
             __freestanding_c_hdrs_type3 __freestanding_c_hdrs_b)
{
    static_assert(__freestanding_c_hdrs_ckd_type<__freestanding_c_hdrs_type1>,
                  "ckd_add requires result to be a pointer to a signed or "
                  "unsigned integer type that is neither const nor volatile");
    static_assert(__freestanding_c_hdrs_ckd_type<__freestanding_c_hdrs_type2>,
                  "ckd_add requires operand a to have a signed or unsigned "
                  "integer type");
    static_assert(__freestanding_c_hdrs_ckd_type<__freestanding_c_hdrs_type3>,
                  "ckd_add requires operand b to have a signed or unsigned "
                  "integer type");
    return __builtin_add_overflow(__freestanding_c_hdrs_a,
                                  __freestanding_c_hdrs_b,
                                  __freestanding_c_hdrs_result);
}

template<class __freestanding_c_hdrs_type1, class __freestanding_c_hdrs_type2,
         class __freestanding_c_hdrs_type3>
bool ckd_sub(__freestanding_c_hdrs_type1 *__freestanding_c_hdrs_result,
             __freestanding_c_hdrs_type2 __freestanding_c_hdrs_a,
             __freestanding_c_hdrs_type3 __freestanding_c_hdrs_b)
{
    static_assert(__freestanding_c_hdrs_ckd_type<__freestanding_c_hdrs_type1>,
                  "ckd_sub requires result to be a pointer to a signed or "
                  "unsigned integer type that is neither const nor volatile");
    static_assert(__freestanding_c_hdrs_ckd_type<__freestanding_c_hdrs_type2>,
                  "ckd_sub requires operand a to have a signed or unsigned "
                  "integer type");
    static_assert(__freestanding_c_hdrs_ckd_type<__freestanding_c_hdrs_type3>,
                  "ckd_sub requires operand b to have a signed or unsigned "
                  "integer type");
    return __builtin_sub_overflow(__freestanding_c_hdrs_a,
                                  __freestanding_c_hdrs_b,
                                  __freestanding_c_hdrs_result);
}

template<class __freestanding_c_hdrs_type1, class __freestanding_c_hdrs_type2,
         class __freestanding_c_hdrs_type3>
bool ckd_mul(__freestanding_c_hdrs_type1 *__freestanding_c_hdrs_result,
             __freestanding_c_hdrs_type2 __freestanding_c_hdrs_a,
             __freestanding_c_hdrs_type3 __freestanding_c_hdrs_b)
{
    static_assert(__freestanding_c_hdrs_ckd_type<__freestanding_c_hdrs_type1>,
                  "ckd_mul requires result to be a pointer to a signed or "
                  "unsigned integer type that is neither const nor volatile");
    static_assert(__freestanding_c_hdrs_ckd_type<__freestanding_c_hdrs_type2>,
                  "ckd_mul requires operand a to have a signed or unsigned "
                  "integer type");
    static_assert(__freestanding_c_hdrs_ckd_type<__freestanding_c_hdrs_type3>,
                  "ckd_mul requires operand b to have a signed or unsigned "
                  "integer type");
    return __builtin_mul_overflow(__freestanding_c_hdrs_a,
                                  __freestanding_c_hdrs_b,
                                  __freestanding_c_hdrs_result);
}

#endif

#endif

#endif
