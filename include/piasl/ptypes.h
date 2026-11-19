#ifndef PIASL_PTYPES_H
#define PIASL_PTYPES_H 1

typedef unsigned char p_u8;
typedef unsigned short p_u16;
typedef unsigned int p_u32;
typedef unsigned long long p_u64;
typedef unsigned long p_uL;

typedef signed char p_i8;
typedef signed short p_i16;
typedef signed int p_i32;
typedef signed long long p_i64;
typedef signed long p_iL;

typedef char p_c8;
typedef unsigned short p_c16;
typedef unsigned int p_c32;

typedef signed char p_b8;
typedef signed short p_b16;
typedef signed int p_b32;

typedef float p_f32;
typedef double p_f64;
typedef long double p_f128;

typedef void p_vd;
typedef void* p_ptr;
typedef const void* const p_ref;
typedef p_c8* p_buf;
typedef const p_c8* const p_viw;
typedef p_ptr p_handle;

#define reinterpret(from, to, val) ((union{from a;to b;}){.a=(from)(val)}.b)

#if ARCH_is64Bit
    typedef p_u64 p_uS;
    typedef p_i64 p_iS;
    typedef p_u64 p_uP;
    typedef p_i64 p_iP;
#   define P_US_MIN 0
#   define P_US_MAX P_U64_MAX
#   define P_IS_MIN P_I64_MIN
#   define P_IS_MAX P_I64_MAX
#   define P_PTR_SIZE 8
#elif ARCH_is32Bit
    typedef p_u32 p_uS;
    typedef p_i32 p_iS;
    typedef p_u32 p_uP;
    typedef p_i32 p_iP;
#   define P_US_MIN 0
#   define P_US_MAX P_U32_MAX
#   define P_IS_MIN P_I32_MIN
#   define P_IS_MAX P_I32_MAX
#   define P_PTR_SIZE 4
#endif

#if OS_isWindows
#   define P_UL_MIN 0
#   define P_UL_MAX P_U32_MAX
#   define P_IL_MIN P_I32_MIN
#   define P_IL_MAX P_I32_MAX
#   define P_LONG_SIZE 4
#else
#   define P_UL_MIN 0
#   define P_UL_MAX P_U64_MAX
#   define P_IL_MIN P_I64_MIN
#   define P_IL_MAX P_I64_MAX
#   define P_LONG_SIZE 8
#endif

#define P_I8_MIN    (-127)
#define P_I16_MIN   (-32767)
#define P_I32_MIN   (-2147483647)
#define P_I64_MIN   (-9223372036854775807LL)

#define P_I8_MAX    127
#define P_I16_MAX   32767
#define P_I32_MAX   2147483647
#define P_I64_MAX   9223372036854775807LL

#define P_U8_MIN    0
#define P_U16_MIN   0
#define P_U32_MIN   0
#define P_U64_MIN   0

#define P_U8_MAX    255
#define P_U16_MAX   65535
#define P_U32_MAX   0xffffffffU
#define P_U64_MAX   0xffffffffffffffffULL
#define P_F64_NAN   reinterpret(p_u64, p_f64, 0x7ff8000000000000ULL) /* (0.0/0.0) */
#define P_F64_INF   reinterpret(p_u64, p_f64, 0x7ff0000000000000ULL) /* (1.0/0.0) */
#define P_F64_NINF  reinterpret(p_u64, p_f64, 0xfff0000000000000ULL) /* (-1.0/0.0) */

#if STD_hasC23
#elif STD_hasC17 || STD_hasC11 || STD_hasC99
    typedef _Bool bool;
    #undef true
    #undef false
    #define true ((bool)1)
    #define false ((bool)0)
#elif !LANG_isCPP
    typedef p_u8 bool;
    #undef true
    #undef false
    #define true ((bool)1)
    #define false ((bool)0)
#endif

#endif /* PIASL_PTYPES_H */
