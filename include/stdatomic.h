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

#ifndef __FREESTANDING_C_HDRS_STDATOMIC_H
#define __FREESTANDING_C_HDRS_STDATOMIC_H 1

#if (defined(__cplusplus) && __cplusplus <= 202002L) \
 || (!defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L))
#  error "<stdatomic.h> requires C11 or C++23 or later"
#elif !defined(__cplusplus)

/* Workaround: GCC 13 to 14, and Clang 16 to 17, all targets: their C23 mode
 * reports 202000L, the value they give the drafts of C23.
 */
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L) \
 || (defined(__STDC_VERSION__) && __STDC_VERSION__ > 201710L \
     && ((defined(__clang__) && __clang_major__ >= 16) \
         || (!defined(__clang__) && __GNUC__ >= 13)))
#  define __STDC_VERSION_STDATOMIC_H__ 202311L
/* Workaround: Clang 16 to 18, all targets: its C23 mode does not tell whether
 * atomic char8_t is lock-free. In C23, char8_t is unsigned char, so the
 * answer for char applies.
 */
#  undef ATOMIC_CHAR8_T_LOCK_FREE
#  ifdef __GCC_ATOMIC_CHAR8_T_LOCK_FREE
#    define ATOMIC_CHAR8_T_LOCK_FREE __GCC_ATOMIC_CHAR8_T_LOCK_FREE
#  else
#    define ATOMIC_CHAR8_T_LOCK_FREE __GCC_ATOMIC_CHAR_LOCK_FREE
#  endif
#else
#  undef ATOMIC_VAR_INIT
#  define ATOMIC_VAR_INIT(value) (value)
#endif

#undef ATOMIC_BOOL_LOCK_FREE
#define ATOMIC_BOOL_LOCK_FREE __GCC_ATOMIC_BOOL_LOCK_FREE
#undef ATOMIC_CHAR_LOCK_FREE
#define ATOMIC_CHAR_LOCK_FREE __GCC_ATOMIC_CHAR_LOCK_FREE
#undef ATOMIC_CHAR16_T_LOCK_FREE
#define ATOMIC_CHAR16_T_LOCK_FREE __GCC_ATOMIC_CHAR16_T_LOCK_FREE
#undef ATOMIC_CHAR32_T_LOCK_FREE
#define ATOMIC_CHAR32_T_LOCK_FREE __GCC_ATOMIC_CHAR32_T_LOCK_FREE
#undef ATOMIC_WCHAR_T_LOCK_FREE
#define ATOMIC_WCHAR_T_LOCK_FREE __GCC_ATOMIC_WCHAR_T_LOCK_FREE
#undef ATOMIC_SHORT_LOCK_FREE
#define ATOMIC_SHORT_LOCK_FREE __GCC_ATOMIC_SHORT_LOCK_FREE
#undef ATOMIC_INT_LOCK_FREE
#define ATOMIC_INT_LOCK_FREE __GCC_ATOMIC_INT_LOCK_FREE
#undef ATOMIC_LONG_LOCK_FREE
#define ATOMIC_LONG_LOCK_FREE __GCC_ATOMIC_LONG_LOCK_FREE
#undef ATOMIC_LLONG_LOCK_FREE
#define ATOMIC_LLONG_LOCK_FREE __GCC_ATOMIC_LLONG_LOCK_FREE
#undef ATOMIC_POINTER_LOCK_FREE
#define ATOMIC_POINTER_LOCK_FREE __GCC_ATOMIC_POINTER_LOCK_FREE

#undef ATOMIC_FLAG_INIT
#define ATOMIC_FLAG_INIT { 0 }

/* The comma drops the qualifiers and the lvalue of y, as a call would. */
#undef kill_dependency
#define kill_dependency(y) ((void)0, (y))

typedef enum {
    memory_order_relaxed = __ATOMIC_RELAXED,
    memory_order_consume = __ATOMIC_CONSUME,
    memory_order_acquire = __ATOMIC_ACQUIRE,
    memory_order_release = __ATOMIC_RELEASE,
    memory_order_acq_rel = __ATOMIC_ACQ_REL,
    memory_order_seq_cst = __ATOMIC_SEQ_CST
} memory_order;

/* A plain byte, which __atomic_test_and_set and __atomic_clear take. */
typedef struct {
    unsigned char __freestanding_c_hdrs_state;
} atomic_flag;

typedef _Atomic(_Bool) atomic_bool;
typedef _Atomic(char) atomic_char;
typedef _Atomic(signed char) atomic_schar;
typedef _Atomic(unsigned char) atomic_uchar;
typedef _Atomic(short) atomic_short;
typedef _Atomic(unsigned short) atomic_ushort;
typedef _Atomic(int) atomic_int;
typedef _Atomic(unsigned int) atomic_uint;
typedef _Atomic(long) atomic_long;
typedef _Atomic(unsigned long) atomic_ulong;
typedef _Atomic(long long) atomic_llong;
typedef _Atomic(unsigned long long) atomic_ullong;
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L) \
 || (defined(__STDC_VERSION__) && __STDC_VERSION__ > 201710L \
     && ((defined(__clang__) && __clang_major__ >= 16) \
         || (!defined(__clang__) && __GNUC__ >= 13)))
typedef _Atomic(unsigned char) atomic_char8_t;
#endif
typedef _Atomic(__CHAR16_TYPE__) atomic_char16_t;
typedef _Atomic(__CHAR32_TYPE__) atomic_char32_t;
typedef _Atomic(__WCHAR_TYPE__) atomic_wchar_t;

typedef _Atomic(__INT_LEAST8_TYPE__) atomic_int_least8_t;
typedef _Atomic(__UINT_LEAST8_TYPE__) atomic_uint_least8_t;
typedef _Atomic(__INT_LEAST16_TYPE__) atomic_int_least16_t;
typedef _Atomic(__UINT_LEAST16_TYPE__) atomic_uint_least16_t;
typedef _Atomic(__INT_LEAST32_TYPE__) atomic_int_least32_t;
typedef _Atomic(__UINT_LEAST32_TYPE__) atomic_uint_least32_t;
typedef _Atomic(__INT_LEAST64_TYPE__) atomic_int_least64_t;
typedef _Atomic(__UINT_LEAST64_TYPE__) atomic_uint_least64_t;

typedef _Atomic(__INT_FAST8_TYPE__) atomic_int_fast8_t;
typedef _Atomic(__UINT_FAST8_TYPE__) atomic_uint_fast8_t;
typedef _Atomic(__INT_FAST16_TYPE__) atomic_int_fast16_t;
typedef _Atomic(__UINT_FAST16_TYPE__) atomic_uint_fast16_t;
typedef _Atomic(__INT_FAST32_TYPE__) atomic_int_fast32_t;
typedef _Atomic(__UINT_FAST32_TYPE__) atomic_uint_fast32_t;
typedef _Atomic(__INT_FAST64_TYPE__) atomic_int_fast64_t;
typedef _Atomic(__UINT_FAST64_TYPE__) atomic_uint_fast64_t;

#ifdef __INTPTR_TYPE__
typedef _Atomic(__INTPTR_TYPE__) atomic_intptr_t;
#endif
#ifdef __UINTPTR_TYPE__
typedef _Atomic(__UINTPTR_TYPE__) atomic_uintptr_t;
#endif
typedef _Atomic(__SIZE_TYPE__) atomic_size_t;
typedef _Atomic(__PTRDIFF_TYPE__) atomic_ptrdiff_t;
typedef _Atomic(__INTMAX_TYPE__) atomic_intmax_t;
typedef _Atomic(__UINTMAX_TYPE__) atomic_uintmax_t;

/* Clang's __atomic builtins reject _Atomic objects, but its __c11_atomic
 * builtins take them. GCC has none of those, but its generic __atomic builtins
 * take _Atomic objects of any type, through pointers.
 */
#undef atomic_init
#undef atomic_is_lock_free
#undef atomic_store_explicit
#undef atomic_load_explicit
#undef atomic_exchange_explicit
#undef atomic_compare_exchange_strong_explicit
#undef atomic_compare_exchange_weak_explicit
#undef atomic_fetch_add_explicit
#undef atomic_fetch_sub_explicit
#undef atomic_fetch_or_explicit
#undef atomic_fetch_xor_explicit
#undef atomic_fetch_and_explicit
#ifdef __clang__
#  define atomic_init(obj, value) __c11_atomic_init((obj), (value))
/* Workaround: Clang 3.5 to 10, all targets: its __c11_atomic_is_lock_free
 * yields an int, not a _Bool.
 */
#  define atomic_is_lock_free(obj) \
       ((void)(obj), (_Bool)__c11_atomic_is_lock_free(sizeof(*(obj))))
#  define atomic_store_explicit(obj, desired, order) \
       __c11_atomic_store((obj), (desired), (order))
#  define atomic_load_explicit(obj, order) __c11_atomic_load((obj), (order))
#  define atomic_exchange_explicit(obj, desired, order) \
       __c11_atomic_exchange((obj), (desired), (order))
#  define atomic_compare_exchange_strong_explicit(obj, expected, desired, \
                                                  success, failure) \
       __c11_atomic_compare_exchange_strong((obj), (expected), (desired), \
                                            (success), (failure))
#  define atomic_compare_exchange_weak_explicit(obj, expected, desired, \
                                                success, failure) \
       __c11_atomic_compare_exchange_weak((obj), (expected), (desired), \
                                          (success), (failure))
#  define atomic_fetch_add_explicit(obj, operand, order) \
       __c11_atomic_fetch_add((obj), (operand), (order))
#  define atomic_fetch_sub_explicit(obj, operand, order) \
       __c11_atomic_fetch_sub((obj), (operand), (order))
#  define atomic_fetch_or_explicit(obj, operand, order) \
       __c11_atomic_fetch_or((obj), (operand), (order))
#  define atomic_fetch_xor_explicit(obj, operand, order) \
       __c11_atomic_fetch_xor((obj), (operand), (order))
#  define atomic_fetch_and_explicit(obj, operand, order) \
       __c11_atomic_fetch_and((obj), (operand), (order))
#else
/* GCC has no builtin that initialises an atomic object, so a relaxed store
 * does it.
 */
#  define atomic_init(obj, value) \
       atomic_store_explicit((obj), (value), memory_order_relaxed)
/* A null pointer asks about the usual alignment of the type, which its atomic
 * objects have.
 */
#  define atomic_is_lock_free(obj) \
       ((void)(obj), __atomic_is_lock_free(sizeof(*(obj)), 0))
#  define atomic_store_explicit(obj, desired, order) \
       __extension__ ({ \
           __auto_type __freestanding_c_hdrs_obj = (obj); \
           __typeof__((void)0, *__freestanding_c_hdrs_obj) \
               __freestanding_c_hdrs_desired = (desired); \
           __atomic_store(__freestanding_c_hdrs_obj, \
                          &__freestanding_c_hdrs_desired, (order)); \
       })
#  define atomic_load_explicit(obj, order) \
       __extension__ ({ \
           __auto_type __freestanding_c_hdrs_obj = (obj); \
           __typeof__((void)0, *__freestanding_c_hdrs_obj) \
               __freestanding_c_hdrs_value; \
           __atomic_load(__freestanding_c_hdrs_obj, \
                         &__freestanding_c_hdrs_value, (order)); \
           __freestanding_c_hdrs_value; \
       })
#  define atomic_exchange_explicit(obj, desired, order) \
       __extension__ ({ \
           __auto_type __freestanding_c_hdrs_obj = (obj); \
           __typeof__((void)0, *__freestanding_c_hdrs_obj) \
               __freestanding_c_hdrs_desired = (desired); \
           __typeof__((void)0, *__freestanding_c_hdrs_obj) \
               __freestanding_c_hdrs_value; \
           __atomic_exchange(__freestanding_c_hdrs_obj, \
                             &__freestanding_c_hdrs_desired, \
                             &__freestanding_c_hdrs_value, (order)); \
           __freestanding_c_hdrs_value; \
       })
/* Workaround: GCC 4.9 to 6, all targets: its __atomic_compare_exchange on an
 * object of one byte yields a type that is neither _Bool nor int.
 */
#  define atomic_compare_exchange_strong_explicit(obj, expected, desired, \
                                                  success, failure) \
       __extension__ ({ \
           __auto_type __freestanding_c_hdrs_obj = (obj); \
           __typeof__((void)0, *__freestanding_c_hdrs_obj) \
               __freestanding_c_hdrs_desired = (desired); \
           (_Bool)__atomic_compare_exchange(__freestanding_c_hdrs_obj, \
                                            (expected), \
                                            &__freestanding_c_hdrs_desired, \
                                            0, (success), (failure)); \
       })
#  define atomic_compare_exchange_weak_explicit(obj, expected, desired, \
                                                success, failure) \
       __extension__ ({ \
           __auto_type __freestanding_c_hdrs_obj = (obj); \
           __typeof__((void)0, *__freestanding_c_hdrs_obj) \
               __freestanding_c_hdrs_desired = (desired); \
           (_Bool)__atomic_compare_exchange(__freestanding_c_hdrs_obj, \
                                            (expected), \
                                            &__freestanding_c_hdrs_desired, \
                                            1, (success), (failure)); \
       })
/* GCC's __atomic_fetch_add and __atomic_fetch_sub, whose arithmetic wraps
 * around, take the operand of a pointer in bytes, so the macros below scale it
 * by the size of the type pointed to. GCC checks both branches of
 * __builtin_choose_expr, so for integers the size taken is that of a char.
 */
#  define __FREESTANDING_C_HDRS_IS_POINTER(obj) \
       (__builtin_classify_type((__typeof__((void)0, *(obj)))0) == 5)
#  define __FREESTANDING_C_HDRS_OPERAND(obj, operand) \
       __builtin_choose_expr(__FREESTANDING_C_HDRS_IS_POINTER(obj), \
           (__PTRDIFF_TYPE__)(operand) \
               * sizeof(*__builtin_choose_expr( \
                   __FREESTANDING_C_HDRS_IS_POINTER(obj), \
                   (__typeof__((void)0, *(obj)))0, (char *)0)), \
           (operand))
#  define atomic_fetch_add_explicit(obj, operand, order) \
       __extension__ ({ \
           __auto_type __freestanding_c_hdrs_obj = (obj); \
           __atomic_fetch_add(__freestanding_c_hdrs_obj, \
                              __FREESTANDING_C_HDRS_OPERAND( \
                                  __freestanding_c_hdrs_obj, operand), \
                              (order)); \
       })
#  define atomic_fetch_sub_explicit(obj, operand, order) \
       __extension__ ({ \
           __auto_type __freestanding_c_hdrs_obj = (obj); \
           __atomic_fetch_sub(__freestanding_c_hdrs_obj, \
                              __FREESTANDING_C_HDRS_OPERAND( \
                                  __freestanding_c_hdrs_obj, operand), \
                              (order)); \
       })
#  define atomic_fetch_or_explicit(obj, operand, order) \
       __atomic_fetch_or((obj), (operand), (order))
#  define atomic_fetch_xor_explicit(obj, operand, order) \
       __atomic_fetch_xor((obj), (operand), (order))
#  define atomic_fetch_and_explicit(obj, operand, order) \
       __atomic_fetch_and((obj), (operand), (order))
#endif

#undef atomic_store
#define atomic_store(obj, desired) \
     atomic_store_explicit((obj), (desired), memory_order_seq_cst)
#undef atomic_load
#define atomic_load(obj) atomic_load_explicit((obj), memory_order_seq_cst)
#undef atomic_exchange
#define atomic_exchange(obj, desired) \
     atomic_exchange_explicit((obj), (desired), memory_order_seq_cst)
#undef atomic_compare_exchange_strong
#define atomic_compare_exchange_strong(obj, expected, desired) \
     atomic_compare_exchange_strong_explicit((obj), (expected), (desired), \
                                             memory_order_seq_cst, \
                                             memory_order_seq_cst)
#undef atomic_compare_exchange_weak
#define atomic_compare_exchange_weak(obj, expected, desired) \
     atomic_compare_exchange_weak_explicit((obj), (expected), (desired), \
                                           memory_order_seq_cst, \
                                           memory_order_seq_cst)
#undef atomic_fetch_add
#define atomic_fetch_add(obj, operand) \
     atomic_fetch_add_explicit((obj), (operand), memory_order_seq_cst)
#undef atomic_fetch_sub
#define atomic_fetch_sub(obj, operand) \
     atomic_fetch_sub_explicit((obj), (operand), memory_order_seq_cst)
#undef atomic_fetch_or
#define atomic_fetch_or(obj, operand) \
     atomic_fetch_or_explicit((obj), (operand), memory_order_seq_cst)
#undef atomic_fetch_xor
#define atomic_fetch_xor(obj, operand) \
     atomic_fetch_xor_explicit((obj), (operand), memory_order_seq_cst)
#undef atomic_fetch_and
#define atomic_fetch_and(obj, operand) \
     atomic_fetch_and_explicit((obj), (operand), memory_order_seq_cst)

/* C makes these functions: a program that takes their addresses or suppresses
 * their macros links with a library that defines them. The macros below use
 * builtins, and need no library.
 */
void atomic_thread_fence(memory_order);
void atomic_signal_fence(memory_order);
_Bool atomic_flag_test_and_set(volatile atomic_flag *);
_Bool atomic_flag_test_and_set_explicit(volatile atomic_flag *, memory_order);
void atomic_flag_clear(volatile atomic_flag *);
void atomic_flag_clear_explicit(volatile atomic_flag *, memory_order);

#undef atomic_thread_fence
#undef atomic_signal_fence
#ifdef __clang__
#  define atomic_thread_fence(order) __c11_atomic_thread_fence((order))
#  define atomic_signal_fence(order) __c11_atomic_signal_fence((order))
#else
#  define atomic_thread_fence(order) __atomic_thread_fence((order))
#  define atomic_signal_fence(order) __atomic_signal_fence((order))
#endif
#undef atomic_flag_test_and_set_explicit
#define atomic_flag_test_and_set_explicit(obj, order) \
     __atomic_test_and_set(&(obj)->__freestanding_c_hdrs_state, (order))
#undef atomic_flag_test_and_set
#define atomic_flag_test_and_set(obj) \
     atomic_flag_test_and_set_explicit((obj), memory_order_seq_cst)
#undef atomic_flag_clear_explicit
#define atomic_flag_clear_explicit(obj, order) \
     __atomic_clear(&(obj)->__freestanding_c_hdrs_state, (order))
#undef atomic_flag_clear
#define atomic_flag_clear(obj) \
     atomic_flag_clear_explicit((obj), memory_order_seq_cst)

#else

#if !__has_include(<atomic>)
#  error "<stdatomic.h> requires <atomic> in C++"
#else

#include <atomic>

template <class __freestanding_c_hdrs_t>
using __freestanding_c_hdrs_atomic = std::atomic<__freestanding_c_hdrs_t>;

#undef _Atomic
#define _Atomic(T) ::__freestanding_c_hdrs_atomic<T>

/* C++ has <stdatomic.h> itself define this, not <atomic>. */
#undef __cpp_lib_stdatomic_h
#define __cpp_lib_stdatomic_h 202011L

using std::memory_order;
using std::memory_order_relaxed;
using std::memory_order_consume;
using std::memory_order_acquire;
using std::memory_order_release;
using std::memory_order_acq_rel;
using std::memory_order_seq_cst;

using std::atomic_flag;

using std::atomic_bool;
using std::atomic_char;
using std::atomic_schar;
using std::atomic_uchar;
using std::atomic_short;
using std::atomic_ushort;
using std::atomic_int;
using std::atomic_uint;
using std::atomic_long;
using std::atomic_ulong;
using std::atomic_llong;
using std::atomic_ullong;
#ifdef __cpp_char8_t
using std::atomic_char8_t;
#endif
using std::atomic_char16_t;
using std::atomic_char32_t;
using std::atomic_wchar_t;

#ifdef __INT8_TYPE__
using std::atomic_int8_t;
#endif
#ifdef __UINT8_TYPE__
using std::atomic_uint8_t;
#endif
#ifdef __INT16_TYPE__
using std::atomic_int16_t;
#endif
#ifdef __UINT16_TYPE__
using std::atomic_uint16_t;
#endif
#ifdef __INT32_TYPE__
using std::atomic_int32_t;
#endif
#ifdef __UINT32_TYPE__
using std::atomic_uint32_t;
#endif
#ifdef __INT64_TYPE__
using std::atomic_int64_t;
#endif
#ifdef __UINT64_TYPE__
using std::atomic_uint64_t;
#endif

using std::atomic_int_least8_t;
using std::atomic_uint_least8_t;
using std::atomic_int_least16_t;
using std::atomic_uint_least16_t;
using std::atomic_int_least32_t;
using std::atomic_uint_least32_t;
using std::atomic_int_least64_t;
using std::atomic_uint_least64_t;

using std::atomic_int_fast8_t;
using std::atomic_uint_fast8_t;
using std::atomic_int_fast16_t;
using std::atomic_uint_fast16_t;
using std::atomic_int_fast32_t;
using std::atomic_uint_fast32_t;
using std::atomic_int_fast64_t;
using std::atomic_uint_fast64_t;

#ifdef __INTPTR_TYPE__
using std::atomic_intptr_t;
#endif
#ifdef __UINTPTR_TYPE__
using std::atomic_uintptr_t;
#endif
using std::atomic_size_t;
using std::atomic_ptrdiff_t;
using std::atomic_intmax_t;
using std::atomic_uintmax_t;

using std::atomic_is_lock_free;
using std::atomic_load;
using std::atomic_load_explicit;
using std::atomic_store;
using std::atomic_store_explicit;
using std::atomic_exchange;
using std::atomic_exchange_explicit;
using std::atomic_compare_exchange_strong;
using std::atomic_compare_exchange_strong_explicit;
using std::atomic_compare_exchange_weak;
using std::atomic_compare_exchange_weak_explicit;
using std::atomic_fetch_add;
using std::atomic_fetch_add_explicit;
using std::atomic_fetch_sub;
using std::atomic_fetch_sub_explicit;
using std::atomic_fetch_and;
using std::atomic_fetch_and_explicit;
using std::atomic_fetch_or;
using std::atomic_fetch_or_explicit;
using std::atomic_fetch_xor;
using std::atomic_fetch_xor_explicit;
using std::atomic_flag_test_and_set;
using std::atomic_flag_test_and_set_explicit;
using std::atomic_flag_clear;
using std::atomic_flag_clear_explicit;
using std::atomic_thread_fence;
using std::atomic_signal_fence;

#endif

#endif

#endif
