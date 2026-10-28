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

#pragma GCC system_header

#include <__freestanding_c_hdrs/revision.h>

#if __FREESTANDING_C_HDRS_STDALIGN_REVISION < 201112L
#  error "<stdalign.h> requires C11 or C++11 or later"
#else

#if __FREESTANDING_C_HDRS_STDALIGN_REVISION >= 202311L
    /* These do not need to be defined for C23+. */
#else
#  undef alignas
#  define alignas _Alignas
#  undef alignof
#  define alignof _Alignof

#  undef __alignas_is_defined
#  define __alignas_is_defined 1
#  undef __alignof_is_defined
#  define __alignof_is_defined 1
#endif

#ifdef __cplusplus
#  include <__fcxx/c_stdalign.h>
#endif

#endif

#endif
