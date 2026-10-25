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

#include <__freestanding_c_hdrs/revision.h>

#if __FREESTANDING_C_HDRS_STDCKDINT_REVISION < 202311L
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

#include <__fcxx/c_stdckdint.h>

#endif

#endif

#endif
