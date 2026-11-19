#ifndef PIASL_NONATIVE_H
#define PIASL_NONATIVE_H 1

/*
 * nonative.h
 *
 * Categories
 * --------------------------------------------------------------------
 *  - Macros marked /_* No Op *​/ cannot be undefined (standard‑mandated
 *    predefined macros, special identifiers like __func__, or macros
 *    where #undef has no effect). They are commented out.
 *
 *  - Macros marked /_* Used *​/ are referenced by platform.h (either in
 *    #if or in macro bodies). They are commented out so platform.h
 *    keeps working.
 *
 *  - All other #undef lines are active and remove the macro.
 */

/* ================================================================== */
/* 1. Standard C / C++ macros                                         */
/* ================================================================== */
// #undef __STDC__                      /* No Op */
// #undef __STDC_VERSION__              /* Used   (platform.h: STD_cHas, STD_cHasYear) */
// #undef __STDC_HOSTED__               /* No Op */
// #undef __STDC_UTF_16__               /* No Op */
// #undef __STDC_UTF_32__               /* No Op */
// #undef __STDC_NO_ATOMICS__           /* No Op */
// #undef __STDC_NO_COMPLEX__           /* No Op */
// #undef __STDC_NO_THREADS__           /* No Op */
// #undef __STDC_NO_VLA__               /* No Op */
// #undef __STDC_IEC_559__              /* No Op */
// #undef __STDC_IEC_559_COMPLEX__      /* No Op */
// #undef __STDC_ISO_10646__            /* No Op */
// #undef __STDC_MB_MIGHT_NEQ_WC__      /* No Op */
// #undef __cplusplus                   /* No Op */
// #undef __STDCPP_THREADS__            /* No Op */
// #undef __STDCPP_STRICT_POINTER_SAFETY__ /* No Op */
// #undef __STDC_WANT_LIB_EXT1__        /* No Op */
// #undef __STDC_LIB_EXT1__             /* No Op */
// #undef __STDC_FORMAT_MACROS__        /* No Op */
// #undef __STDC_CONSTANT_MACROS__      /* No Op */
// #undef __STDC_LIMIT_MACROS__         /* No Op */
// #undef __STDC_ANALYZABLE__           /* No Op */
// #undef __STDC_IEC_60559_BFP__        /* No Op */
// #undef __STDC_IEC_60559_DFP__        /* No Op */
// #undef __STDC_IEC_60559_COMPLEX__    /* No Op */
// #undef __STDC_IEC_60559_TYPES__      /* No Op */

/* Special standard macros / identifiers */
// #undef __FILE__                      /* No Op */
// #undef __LINE__                      /* No Op */
// #undef __DATE__                      /* No Op */
// #undef __TIME__                      /* No Op */
// #undef __TIMESTAMP__                 /* No Op */
// #undef __func__                      /* No Op  (predefined identifier, not a macro) */
// #undef __FUNCTION__                  /* No Op  (predefined identifier, not a macro) */
// #undef __PRETTY_FUNCTION__           /* No Op  (predefined identifier, not a macro) */
// #undef __BASE_FILE__                 /* No Op  (predefined identifier, not a macro) */
// #undef __INCLUDE_LEVEL__             /* No Op */
// #undef __COUNTER__                   /* No Op */
// #undef __VA_ARGS__                   /* No Op  (special variadic identifier) */
// #undef __VA_OPT__                    /* No Op  (special variadic identifier) */

/* ================================================================== */
/* 2. GCC / Clang compiler identification and versioning              */
/* ================================================================== */
#undef __GNUC__
#undef __GNUC_MINOR__
#undef __GNUC_PATCHLEVEL__
#undef __GNUG__
#undef __GNUC_STDC_INLINE__
#undef __GNUC_GNU_INLINE__
#undef __STRICT_ANSI__
#undef __VERSION__
#undef __OPTIMIZE__
#undef __OPTIMIZE_SIZE__
#undef __NO_INLINE__
#undef __PIC__
#undef __pic__
#undef __PIE__
#undef __pie__
#undef __DEPRECATED
#undef __EXCEPTIONS
#undef __GXX_RTTI
#undef __GXX_ABI_VERSION
#undef __GXX_WEAK__
#undef __GXX_MERGED_TYPEINFO_NAMES
#undef __GXX_TYPEINFO_EQUALITY_INLINE
#undef __GXX_EXPERIMENTAL_CXX0X__
#undef __GXX_CONSTEXPR_ASM__
#undef __GNUC_EXECUTION_CHARSET_NAME
#undef __GNUC_WIDE_EXECUTION_CHARSET_NAME

#undef __clang__
#undef __clang_major__
#undef __clang_minor__
#undef __clang_patchlevel__
#undef __clang_version__
#undef __llvm__
#undef __clang_literal_encoding__
#undef __clang_wide_literal_encoding__
#undef __clang_analyzer__

/* Intel compiler */
#undef __INTEL_COMPILER
#undef __ICC
#undef __ICL
#undef __ECC
#undef __INTEL_LLVM_COMPILER

/* MSVC compiler identification and versioning */
// #undef _MSC_VER                      /* Used   (platform.h: COMPILER_versionMajor) */
// #undef _MSC_FULL_VER                 /* Used   (platform.h: COMPILER_versionMajor) */
#undef _MSC_BUILD
#undef _MSC_EXTENSIONS
#undef _MSVC_LANG
#undef _MSVC_RUNTIME_CHECKS
#undef _MT
#undef _DLL
#undef _DEBUG
#undef _MANAGED
#undef _M_CEE
#undef _M_CEE_PURE
#undef _M_CEE_SAFE
#undef _MFC_VER
#undef _ATL_VER
#undef _CONTROL_FLOW_GUARD
#undef _CPPRTTI
#undef _CPPUNWIND
#undef _PREFAST_
#undef _WCHAR_T_DEFINED
#undef _NATIVE_WCHAR_T_DEFINED
#undef _ISO_VOLATILE
#undef _CHAR_UNSIGNED
#undef _INTEGRAL_MAX_BITS
#undef _VC_NODEFAULTLIB
#undef _NO_SIZED_DEALLOCATION
#undef _KERNEL_MODE
#undef _WINRT_DLL
#undef _RESUMABLE_FUNCTIONS_SUPPORTED
#undef _RTC_CONVERSION_CHECKS_ENABLED
#undef _OPENMP

/* Other compiler families */
#undef __BORLANDC__
#undef __CODEGEARC__
#undef __WATCOMC__
#undef __TINYC__
#undef __SUNPRO_C
#undef __SUNPRO_CC
#undef __SUNPRO_CC_COMPAT
#undef __IBMC__
#undef __IBMCPP__
#undef __xlC__
#undef __XLC__
#undef __HP_cc
#undef __HP_aCC
#undef __DECC
#undef __DECCXX
#undef __USLC__
#undef __PGI
#undef __PATHCC__
#undef __PATHSCALE__
#undef __CAF
#undef __NEC__
#undef __HIGHC__
#undef __LCC__
#undef __ACK__
#undef __CC_ARM
#undef __ARMCC_VERSION
#undef __TI_COMPILER_VERSION__
#undef __TI_GNU_CC
#undef __IAR_SYSTEMS_ICC__
#undef __IAR_SYSTEMS_ASM__
#undef __IAR_SYSTEMS_ICCL__
#undef __IAR_SYSTEMS_ICCM__
#undef __IAR_SYSTEMS_ICCR__
#undef __IAR_SYSTEMS_ICCAVR__
#undef __IAR_SYSTEMS_ICCARM__
#undef __IAR_SYSTEMS_ICCRL78__
#undef __IAR_SYSTEMS_ICC430__
#undef __IAR_SYSTEMS_ICCMSP430__
#undef __IAR_SYSTEMS_ICCRX__
#undef __IAR_SYSTEMS_ICCV850__
#undef __IAR_SYSTEMS_ICC78K__
#undef __IAR_SYSTEMS_ICCSH__
#undef __IAR_SYSTEMS_ICCAVR32__
#undef __IAR_SYSTEMS_ICCM16C__
#undef __IAR_SYSTEMS_ICCM32C__
#undef __IAR_SYSTEMS_ICCR32C__
#undef __IAR_SYSTEMS_ICCCR16C__
#undef __IAR_SYSTEMS_ICCCR16X__

/* ================================================================== */
/* 3. Operating system identification                                 */
/* ================================================================== */
/* Windows */
#undef _WIN32
#undef _WIN64
#undef _WIN16
#undef WIN32
#undef WIN64
#undef WINNT
#undef __MINGW32__
#undef __MINGW64__
#undef __MINGW32_MAJOR_VERSION
#undef __MINGW32_MINOR_VERSION
#undef __MINGW64_VERSION_MAJOR
#undef __MINGW64_VERSION_MINOR
#undef __CYGWIN__
#undef __CYGWIN32__
#undef _WIN32_WCE
#undef UNDER_CE
#undef _XBOX_VER

/* Unix-like systems */
#undef __unix__
#undef __unix
#undef unix
#undef __linux__
#undef __linux
#undef linux
#undef __gnu_linux__
#undef __ANDROID__
#undef __ANDROID_API__
#undef __APPLE__
#undef __MACH__
#undef __OSX__
#undef __DARWIN__
#undef __FreeBSD__
#undef __FreeBSD_version
#undef __NetBSD__
#undef __NetBSD_Version__
#undef __OpenBSD__
#undef __DragonFly__
#undef __DragonFly_cc_version
#undef __sun__
#undef __sun
#undef __SVR4
#undef __svr4__
#undef __SVR4__
#undef __hpux__
#undef __hpux
#undef hpux
#undef __AIX__
#undef _AIX
#undef _AIX3
#undef _AIX32
#undef _AIX41
#undef _AIX43
#undef __TOS_AIX__
#undef __HURD__
#undef __GNU__
#undef __GLIBC__
#undef __GLIBC_MINOR__
#undef __UCLIBC__
#undef __BIONIC__
#undef __Fuchsia__
#undef __ros__
#undef __native_client__
#undef __EMSCRIPTEN__
#undef __asmjs__
#undef __wasm__
#undef __wasi__
#undef __CloudABI__
#undef __MVS__
#undef __OS400__
#undef __VOS__
#undef __AMIGA__
#undef AMIGA
#undef __amigaos__
#undef __AROS__
#undef __BEOS__
#undef __HAIKU__
#undef __bg__
#undef __bgq__
#undef __THW_BLUEGENE__
#undef __TOS_BGQ__
#undef __UTS__
#undef UTS
#undef aegis
#undef apollo
#undef __QNX__
#undef __QNXNTO__
#undef __rtems__
#undef __VXWORKS__
#undef __vxworks
#undef __ZEPHYR__
#undef __NETWARE__
#undef __nw__
#undef _NETWARE
#undef __SCO__
#undef _SCO_DS
#undef __UNIXWARE__
#undef __USLC__
#undef __SINIX__
#undef __MUNIX__
#undef __DGUX__
#undef __hiuxmpp
#undef __hiux__
#undef __Lynx__
#undef __FreeBSD_kernel__
#undef __MidnightBSD__
#undef __MidnightBSD_version

/* ================================================================== */
/* 4. Architecture / CPU identification                               */
/* ================================================================== */
#undef __i386__
#undef __i386
#undef i386
#undef __i486__
#undef __i586__
#undef __i686__
#undef _M_IX86
#undef _M_IX86_FP
#undef __x86_64__
#undef __x86_64
#undef __amd64__
#undef __amd64
#undef _M_X64
#undef _M_AMD64
#undef __arm__
#undef __arm
#undef __thumb__
#undef __aarch64__
#undef _M_ARM
#undef _M_ARM64
#undef _M_ARMT
#undef __ARM_ARCH
#undef __ARM_ARCH_2__
#undef __ARM_ARCH_3__
#undef __ARM_ARCH_3M__
#undef __ARM_ARCH_4T__
#undef __ARM_ARCH_5__
#undef __ARM_ARCH_5E__
#undef __ARM_ARCH_5T__
#undef __ARM_ARCH_5TE__
#undef __ARM_ARCH_5TEJ__
#undef __ARM_ARCH_6__
#undef __ARM_ARCH_6J__
#undef __ARM_ARCH_6K__
#undef __ARM_ARCH_6Z__
#undef __ARM_ARCH_6ZK__
#undef __ARM_ARCH_6T2__
#undef __ARM_ARCH_7__
#undef __ARM_ARCH_7A__
#undef __ARM_ARCH_7R__
#undef __ARM_ARCH_7M__
#undef __ARM_ARCH_7S__
#undef __ARM_ARCH_8A__
#undef __ARM_ARCH_8M__
#undef __ARM_ARCH_8R__
#undef __ARM_FEATURE_CRC32
#undef __ARM_FEATURE_CRYPTO
#undef __ARM_FEATURE_DIRECTED_ROUNDING
#undef __ARM_FEATURE_DSP
#undef __ARM_FEATURE_FMA
#undef __ARM_FEATURE_IDIV
#undef __ARM_FEATURE_LDREX
#undef __ARM_FEATURE_NUMERIC_MAXMIN
#undef __ARM_FEATURE_QBIT
#undef __ARM_FEATURE_SAT
#undef __ARM_FEATURE_SIMD32
#undef __ARM_FEATURE_UNALIGNED
#undef __ARM_FP
#undef __ARM_FP16_FORMAT_IEEE
#undef __ARM_FP16_FORMAT_ALTERNATIVE
#undef __ARM_FP_FAST
#undef __ARM_NEON
#undef __ARM_NEON__
#undef __ARM_NEON_FP
#undef __ARM_PCS
#undef __ARM_PCS_VFP
#undef __ARM_SIZEOF_MINIMAL_ENUM
#undef __ARM_SIZEOF_WCHAR_T
#undef __ARM_32BIT_STATE
#undef __ARM_64BIT_STATE
#undef __ARM_ACLE
#undef __ARM_ALIGN_MAX_STACK_PWR
#undef __ARM_ARCH_ISA_ARM
#undef __ARM_ARCH_ISA_THUMB
#undef __ARM_ARCH_PROFILE
#undef __ARM_BIG_ENDIAN
#undef __ARM_FEATURE_CLZ
#undef __ARM_FEATURE_COPROC
#undef __ARM_FEATURE_EBF
#undef __ARM_FEATURE_ETM
#undef __ARM_FEATURE_MVE
#undef __ARM_FEATURE_PAUTH
#undef __ARM_FEATURE_QRDMX
#undef __ARM_FEATURE_SHA2
#undef __ARM_FEATURE_SHA3
#undef __ARM_FEATURE_SHA512
#undef __ARM_FEATURE_SM4
#undef __ARM_FEATURE_SVE
#undef __ARM_FEATURE_SVE2
#undef __ARM_FEATURE_SVE2_AES
#undef __ARM_FEATURE_SVE2_BITPERM
#undef __ARM_FEATURE_SVE2_SHA3
#undef __ARM_FEATURE_SVE2_SM4
#undef __ARM_FEATURE_SVE_MATMUL_FP32
#undef __ARM_FEATURE_SVE_MATMUL_FP64
#undef __ARM_FEATURE_SVE_MATMUL_INT8
#undef __ARM_FEATURE_SVE_VECTOR_OPERATORS
#undef __ARM_FEATURE_TME

#undef __mips__
#undef __mips
#undef _MIPS_ARCH
#undef _MIPS_TUNE
#undef __mips_isa_rev
#undef __mips_hard_float
#undef __mips_soft_float
#undef __mips16
#undef __mips64
#undef __mips_dsp
#undef __mips_dspr2
#undef __mips_msa
#undef __mips_micromips
#undef __mips_virtual
#undef __mips_fpxx

#undef __powerpc__
#undef __powerpc
#undef __ppc__
#undef __ppc
#undef _M_PPC
#undef _ARCH_PPC
#undef _ARCH_PPC64
#undef __ppc64__
#undef __powerpc64__
#undef __PPC__
#undef __PPC64__
#undef __POWERPC__
#undef __POWERPC64__
#undef __ALTIVEC__
#undef __VSX__
#undef __SPE__
#undef __PAIR__

#undef __sparc__
#undef __sparc
#undef __sparcv8
#undef __sparcv9
#undef __sparc_v8__
#undef __sparc_v9__
#undef __sparcv9__
#undef __sparc64__
#undef _M_SPARC

#undef __s390__
#undef __s390x__
#undef __zarch__
#undef __370__
#undef __THW_INTEL__
#undef __THW_BIG_ENDIAN__
#undef __THW_LITTLE_ENDIAN__
#undef __THW_370__
#undef __THW_S390__
#undef __THW_S390X__

#undef __ia64__
#undef __ia64
#undef _M_IA64
#undef __ia64_reg
#undef __IA64__
#undef __IA64_REG

#undef __alpha__
#undef __alpha
#undef _M_ALPHA
#undef __alpha_ev4__
#undef __alpha_ev5__
#undef __alpha_ev6__
#undef __ALPHA__
#undef __ALPHA_EV4__
#undef __ALPHA_EV5__
#undef __ALPHA_EV6__

#undef __hppa__
#undef __hppa
#undef __HPPA__
#undef _M_HPUX
#undef __hp9000s800
#undef __hp9000s700
#undef __hp9000s300
#undef __hp9000s200
#undef __hp9000s500
#undef __hp9000s400
#undef __hp9000s100
#undef __hp9000s
#undef __hp9000

#undef __m68k__
#undef __m68k
#undef __mc68000__
#undef __mc68000
#undef __MC68000__
#undef __MC68000

#undef __sh__
#undef __sh
#undef __SH__
#undef __sh1__
#undef __sh2__
#undef __sh3__
#undef __sh4__
#undef __SH1__
#undef __SH2__
#undef __SH3__
#undef __SH4__
#undef __SH5__

#undef __vax__
#undef __vax
#undef __VAX__
#undef vax
#undef __vax11__
#undef __vax11

#undef __convex__
#undef __convex
#undef __CONVEX__
#undef convex
#undef __convex_c1__
#undef __convex_c2__
#undef __convex_c38__
#undef __convex_c1
#undef __convex_c2
#undef __convex_c38

#undef __cray__
#undef __cray
#undef _CRAY
#undef _CRAYMPP
#undef _CRAYT3E
#undef _CRAYT3D
#undef _CRAY1
#undef _CRAY2
#undef _CRAYX1
#undef _CRAYX1E
#undef _CRAYX2
#undef _CRAYXK
#undef _CRAYXC
#undef _CRAYFTN
#undef _CRAYCCE
#undef _CRAYCCC
#undef _CRAYGNU
#undef _CRAYPGI
#undef _CRAYNVHPC

/* ================================================================== */
/* 5. Endianness / data model                                         */
/* ================================================================== */
#undef __BYTE_ORDER__
#undef __ORDER_LITTLE_ENDIAN__
#undef __ORDER_BIG_ENDIAN__
#undef __ORDER_PDP_ENDIAN__
#undef __FLOAT_WORD_ORDER__
#undef __LITTLE_ENDIAN__
#undef __BIG_ENDIAN__
#undef __PDP_ENDIAN__
#undef __LITTLE_ENDIAN
#undef __BIG_ENDIAN
#undef __PDP_ENDIAN
#undef BYTE_ORDER
#undef LITTLE_ENDIAN
#undef BIG_ENDIAN
#undef PDP_ENDIAN

#undef __LP64__
#undef _LP64
#undef __ILP32__
#undef _ILP32
#undef __SIZEOF_POINTER__
#undef __SIZEOF_LONG__
#undef __SIZEOF_INT__
#undef __SIZEOF_SHORT__
#undef __SIZEOF_LONG_LONG__
#undef __SIZEOF_FLOAT__
#undef __SIZEOF_DOUBLE__
#undef __SIZEOF_LONG_DOUBLE__
#undef __SIZEOF_SIZE_T__
#undef __SIZEOF_PTRDIFF_T__
#undef __SIZEOF_WCHAR_T__
#undef __SIZEOF_WINT_T__
#undef __SIZEOF_INT128__
#undef __SIZEOF_FLOAT128__
#undef __SIZEOF_FLOAT80__
#undef __SIZEOF_INT64__
#undef __SIZEOF_INT32__
#undef __SIZEOF_INT16__
#undef __SIZEOF_INT8__
#undef __SIZEOF_UINT64__
#undef __SIZEOF_UINT32__
#undef __SIZEOF_UINT16__
#undef __SIZEOF_UINT8__

#undef __CHAR_BIT__
#undef __SCHAR_MAX__
#undef __SHRT_MAX__
#undef __INT_MAX__
#undef __LONG_MAX__
#undef __LONG_LONG_MAX__
#undef __WCHAR_MAX__
#undef __WCHAR_MIN__
#undef __WINT_MAX__
#undef __WINT_MIN__
#undef __SIZE_MAX__
#undef __PTRDIFF_MAX__
#undef __INTMAX_MAX__
#undef __UINTMAX_MAX__
#undef __INT8_MAX__
#undef __INT16_MAX__
#undef __INT32_MAX__
#undef __INT64_MAX__
#undef __UINT8_MAX__
#undef __UINT16_MAX__
#undef __UINT32_MAX__
#undef __UINT64_MAX__
#undef __INT8_C
#undef __INT16_C
#undef __INT32_C
#undef __INT64_C
#undef __UINT8_C
#undef __UINT16_C
#undef __UINT32_C
#undef __UINT64_C
#undef __INTMAX_C
#undef __UINTMAX_C

#undef __FLT_MAX__
#undef __FLT_MIN__
#undef __FLT_EPSILON__
#undef __FLT_DENORM_MIN__
#undef __FLT_DIG__
#undef __FLT_MANT_DIG__
#undef __FLT_MIN_EXP__
#undef __FLT_MAX_EXP__
#undef __FLT_MIN_10_EXP__
#undef __FLT_MAX_10_EXP__
#undef __FLT_RADIX__
#undef __FLT_HAS_INFINITY__
#undef __FLT_HAS_QUIET_NAN__
#undef __DBL_MAX__
#undef __DBL_MIN__
#undef __DBL_EPSILON__
#undef __DBL_DENORM_MIN__
#undef __DBL_DIG__
#undef __DBL_MANT_DIG__
#undef __DBL_MIN_EXP__
#undef __DBL_MAX_EXP__
#undef __DBL_MIN_10_EXP__
#undef __DBL_MAX_10_EXP__
#undef __DBL_HAS_INFINITY__
#undef __DBL_HAS_QUIET_NAN__
#undef __LDBL_MAX__
#undef __LDBL_MIN__
#undef __LDBL_EPSILON__
#undef __LDBL_DENORM_MIN__
#undef __LDBL_DIG__
#undef __LDBL_MANT_DIG__
#undef __LDBL_MIN_EXP__
#undef __LDBL_MAX_EXP__
#undef __LDBL_MIN_10_EXP__
#undef __LDBL_MAX_10_EXP__
#undef __LDBL_HAS_INFINITY__
#undef __LDBL_HAS_QUIET_NAN__
#undef __DECIMAL_DIG__
// #undef __FLT_EVAL_METHOD__           /* No Op */

/* ================================================================== */
/* 6. Other common system / library macros                            */
/* ================================================================== */
#undef __ELF__
#undef __COFF__
#undef __PE__
#undef __wasm_simd128__
#undef __wasm_atomics__
#undef __wasm_bulk_memory__
#undef __wasm_exception_handling__
#undef __wasm_multivalue__
#undef __wasm_mutable_globals__
#undef __wasm_nontrapping_fptoint__
#undef __wasm_reference_types__
#undef __wasm_sign_ext__
#undef __wasm_tail_call__
#undef __wasm_threads__
#undef __wasm_relaxed_simd__
#undef __wasm_extended_const__

#undef __SSE__
#undef __SSE2__
#undef __SSE3__
#undef __SSSE3__
#undef __SSE4_1__
#undef __SSE4_2__
#undef __AVX__
#undef __AVX2__
#undef __AVX512F__
#undef __AVX512BW__
#undef __AVX512CD__
#undef __AVX512DQ__
#undef __AVX512VL__
#undef __AVX512VBMI__
#undef __AVX512VBMI2__
#undef __AVX512VNNI__
#undef __AVX512BITALG__
#undef __AVX512VPOPCNTDQ__
#undef __AVX512ER__
#undef __AVX512PF__
#undef __AVX512IFMA__
#undef __AVX5124FMAPS__
#undef __AVX5124VNNIW__
#undef __AVX512BF16__
#undef __AVX512FP16__
#undef __AVX512VP2INTERSECT__

#undef __FMA__
#undef __FMA4__
#undef __XOP__
#undef __BMI__
#undef __BMI2__
#undef __LZCNT__
#undef __POPCNT__
#undef __AES__
#undef __PCLMUL__
#undef __RDRND__
#undef __RDSEED__
#undef __SHA__
#undef __ADX__
#undef __CLFLUSHOPT__
#undef __CLWB__
#undef __FSGSBASE__
#undef __FXSR__
#undef __HLE__
#undef __MMX__
#undef __RTM__
#undef __SGX__
#undef __3dNOW__
#undef __3dNOW_A__
#undef __PRFCHW__
#undef __PREFETCHWT1__
#undef __ABM__
#undef __TBM__
#undef __MOVBE__
#undef __MWAITX__
#undef __PKU__
#undef __GFNI__
#undef __VAES__
#undef __VPCLMULQDQ__
#undef __CET__
#undef __SHSTK__
#undef __IBT__
#undef __SERIALIZE__
#undef __TSXLDTRK__
#undef __UINTR__
#undef __HRESET__
#undef __KL__
#undef __WIDEKL__
#undef __AMX_TILE__
#undef __AMX_INT8__
#undef __AMX_BF16__
#undef __AMX_FP16__
#undef __AMX_COMPLEX__
#undef __AMX_AVX512__
#undef __AMX_MOVRS__
#undef __AMX_FP8__
#undef __AMX_TRANSPOSE__
#undef __AMX_TF32__

/* POSIX / feature‑test macros */
#undef _POSIX_SOURCE
#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE
#undef _XOPEN_SOURCE_EXTENDED
#undef _BSD_SOURCE
#undef _DEFAULT_SOURCE
#undef _GNU_SOURCE
#undef _LARGEFILE_SOURCE
#undef _LARGEFILE64_SOURCE
#undef _FILE_OFFSET_BITS
#undef _TIME_BITS
#undef _ISOC99_SOURCE
#undef _ISOC11_SOURCE
#undef _ISOC17_SOURCE
#undef _ISOC23_SOURCE
#undef _POSIX_ASYNCHRONOUS_IO
#undef _POSIX_BARRIERS
#undef _POSIX_CHOWN_RESTRICTED
#undef _POSIX_CLOCK_SELECTION
#undef _POSIX_CPUTIME
#undef _POSIX_FSYNC
#undef _POSIX_JOB_CONTROL
#undef _POSIX_MAPPED_FILES
#undef _POSIX_MEMLOCK
#undef _POSIX_MEMLOCK_RANGE
#undef _POSIX_MEMORY_PROTECTION
#undef _POSIX_MESSAGE_PASSING
#undef _POSIX_MONOTONIC_CLOCK
#undef _POSIX_NO_TRUNC
#undef _POSIX_PRIORITIZED_IO
#undef _POSIX_PRIORITY_SCHEDULING
#undef _POSIX_RAW_SOCKETS
#undef _POSIX_READER_WRITER_LOCKS
#undef _POSIX_REALTIME_SIGNALS
#undef _POSIX_REGEXP
#undef _POSIX_SAVED_IDS
#undef _POSIX_SEMAPHORES
#undef _POSIX_SHARED_MEMORY_OBJECTS
#undef _POSIX_SHELL
#undef _POSIX_SPAWN
#undef _POSIX_SPIN_LOCKS
#undef _POSIX_SPORADIC_SERVER
#undef _POSIX_SYNCHRONIZED_IO
#undef _POSIX_THREAD_ATTR_STACKADDR
#undef _POSIX_THREAD_ATTR_STACKSIZE
#undef _POSIX_THREAD_CPUTIME
#undef _POSIX_THREAD_PRIO_INHERIT
#undef _POSIX_THREAD_PRIO_PROTECT
#undef _POSIX_THREAD_PRIORITY_SCHEDULING
#undef _POSIX_THREAD_PROCESS_SHARED
#undef _POSIX_THREAD_SAFE_FUNCTIONS
#undef _POSIX_THREAD_SPORADIC_SERVER
#undef _POSIX_THREADS
#undef _POSIX_TIMEOUTS
#undef _POSIX_TIMERS
#undef _POSIX_TRACE
#undef _POSIX_TRACE_EVENT_FILTER
#undef _POSIX_TRACE_INHERIT
#undef _POSIX_TRACE_LOG
#undef _POSIX_TYPED_MEMORY_OBJECTS
#undef _POSIX_V6_ILP32_OFF32
#undef _POSIX_V6_ILP32_OFFBIG
#undef _POSIX_V6_LP64_OFF64
#undef _POSIX_V6_LPBIG_OFFBIG
#undef _POSIX_V7_ILP32_OFF32
#undef _POSIX_V7_ILP32_OFFBIG
#undef _POSIX_V7_LP64_OFF64
#undef _POSIX_V7_LPBIG_OFFBIG
#undef _XOPEN_CRYPT
#undef _XOPEN_ENH_I18N
#undef _XOPEN_LEGACY
#undef _XOPEN_REALTIME
#undef _XOPEN_REALTIME_THREADS
#undef _XOPEN_SHM
#undef _XOPEN_STREAMS
#undef _XOPEN_UNIX
#undef _XOPEN_UUCP
#undef _XOPEN_VERSION

/* Kernel / assembler contexts */
#undef __KERNEL__
#undef __KERNEL_STRICT_NAMES
#undef __KERNEL_DS
#undef __USER_DS
#undef MODULE
#undef KBUILD_MODNAME
#undef KBUILD_BASENAME
#undef __VMLINUX_H__
#undef __ASSEMBLY__
#undef __ASSEMBLER__
#undef __LINKER__
#undef __CPP__
#undef __C__
#undef __C89__
#undef __C99__
#undef __C11__
#undef __C17__
#undef __C18__
#undef __C2X__
#undef __C23__
#undef __OBJC__

/* ================================================================== */
/* 7. Feature‑detection macros used by platform.h                     */
/* ================================================================== */
// #undef __has_attribute               /* Used   (platform.h: ATTR_* bodies) */
// #undef __has_builtin                 /* Used   (platform.h: B_* bodies) */
// #undef __has_cpp_attribute           /* Used   (platform.h: COMPILER_hasCppAttribute) */
// #undef __has_feature                 /* Used   (platform.h: COMPILER_hasFeature) */
// #undef __has_extension               /* Used   (platform.h: COMPILER_hasExtension) */

#endif /* PIASL_NONATIVE_H */
