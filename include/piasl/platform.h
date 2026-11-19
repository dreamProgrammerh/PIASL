#ifndef PIASL_PLATFORM_H
#define PIASL_PLATFORM_H 1

// platform.h - Platform, Architecture, Compiler detection

/* ================================================================== */
/* Operating System Detection                                         */
/* ================================================================== */

// === Windows (catches MSVC, MinGW, Cygwin - all define _WIN32/_WIN64) ===
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__WINDOWS__)
#   define OS_isWindows 1
#   if defined(_WIN64) || defined(__WIN64__)
#       define OS_isWindows64 1
#       define OS_isWindows32 0
#   else
#       define OS_isWindows64 0
#       define OS_isWindows32 1
#   endif
#else
#   define OS_isWindows 0
#   define OS_isWindows64 0
#   define OS_isWindows32 0
#endif

// === MinGW (GCC targeting Windows) ===
#if defined(__MINGW32__) || defined(__MINGW64__)
#   define OS_isMinGW 1
#else
#   define OS_isMinGW 0
#endif

// === Cygwin (POSIX compatibility layer on Windows) ===
#if defined(__CYGWIN__) || defined(__CYGWIN32__)
#   define OS_isCygwin 1
#else
#   define OS_isCygwin 0
#endif

// === Apple / Darwin ===
// no <TargetConditionals.h>. TARGET_OS_* are available only
// after that header; we detect Apple via __APPLE__/__MACH__ and default
// to macOS. iOS/tvOS/watchOS are distinguished via __ENVIRONMENT_* and
// __IPHONE_OS_VERSION_MIN_REQUIRED__ without any include.
#if defined(__APPLE__) || defined(__MACH__)
#   define OS_isApple 1
#   define OS_isUnix 1
#   if defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__TV_OS_VERSION_MIN_REQUIRED__) || defined(__WATCH_OS_VERSION_MIN_REQUIRED__)
        // Compiling for embedded Apple OS - heuristic: iPhone if watch/tv not set
#       if defined(__WATCH_OS_VERSION_MIN_REQUIRED__)
#           define OS_isMacOS 0
#           define OS_isIOS 0
#           define OS_isTVOS 0
#           define OS_isWatchOS 1
#       elif defined(__TV_OS_VERSION_MIN_REQUIRED__)
#           define OS_isMacOS 0
#           define OS_isIOS 0
#           define OS_isTVOS 1
#           define OS_isWatchOS 0
#       else
#           define OS_isMacOS 0
#           define OS_isIOS 1
#           define OS_isTVOS 0
#           define OS_isWatchOS 0
#       endif
#   else
#       define OS_isMacOS 1
#       define OS_isIOS 0
#       define OS_isTVOS 0
#       define OS_isWatchOS 0
#   endif
#else
#   define OS_isMacOS 0
#   define OS_isIOS 0
#   define OS_isTVOS 0
#   define OS_isWatchOS 0
#   define OS_isApple 0
#endif

// === Linux ===
#if defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
#   define OS_isLinux 1
#   define OS_isUnix 1
#   if defined(__ANDROID__) || defined(ANDROID)
#       define OS_isAndroid 1
#   else
#       define OS_isAndroid 0
#   endif
#else
#   define OS_isLinux 0
#   define OS_isAndroid 0
#endif

// === BSD family ===
#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
#   define OS_isFreeBSD 1
#   define OS_isUnix 1
#else
#   define OS_isFreeBSD 0
#endif

#if defined(__NetBSD__)
#   define OS_isNetBSD 1
#   define OS_isUnix 1
#else
#   define OS_isNetBSD 0
#endif

#if defined(__OpenBSD__)
#   define OS_isOpenBSD 1
#   define OS_isUnix 1
#else
#   define OS_isOpenBSD 0
#endif

#if defined(__DragonFly__)
#   define OS_isDragonFly 1
#   define OS_isUnix 1
#else
#   define OS_isDragonFly 0
#endif

#if OS_isFreeBSD || OS_isNetBSD || OS_isOpenBSD || OS_isDragonFly
#   define OS_isBSD 1
#else
#   define OS_isBSD 0
#endif

// === Other Unix-like ===
#if defined(__HAIKU__)
#   define OS_isHaiku 1
#else
#   define OS_isHaiku 0
#endif

// === Unix Fallback ===
// for any other Unix-like systems 
#if (defined(__unix__) || defined(__unix) || defined(unix)) \
        && (!defined(OS_isUnix) || !OS_isUnix)
#   define OS_isUnix 1
#elif !defined(OS_isUnix)
#   define OS_isUnix 0
#endif

#if defined(__sun) || defined(sun)
#   if defined(__SVR4) || defined(__svr4__)
#       define OS_isSolaris 0
#       define OS_isIllumos 1
#   else
#       define OS_isSolaris 1
#       define OS_isIllumos 0
#   endif
#else
#   define OS_isSolaris 0
#   define OS_isIllumos 0
#endif

#if defined(__hpux) || defined(__hpux__)
#   define OS_isHPUX 1
#else
#   define OS_isHPUX 0
#endif

#if defined(_AIX) || defined(__AIX__) || defined(__aix__)
#   define OS_isAIX 1
#else
#   define OS_isAIX 0
#endif

#if defined(sgi) || defined(__sgi)
#   define OS_isIRIX 1
#else
#   define OS_isIRIX 0
#endif

#if defined(__OS2__) || defined(__TOS_OS2__)
#   define OS_isOS2 1
#else
#   define OS_isOS2 0
#endif

// == OS Path --
#if OS_isWindows
#   define OS_newline       "\r\n"
#   define OS_newlineLen    2
#   define OS_pathSep       '\\'
#   define OS_pathAltSep    '/'
#   define OS_pathSepStr    "\\"
#   define OS_pathAltSepStr "/"
#   define OS_isPathSep(ch) ((ch) == '\\' || (ch) == '/')
#else
#   define OS_newline       "\n"
#   define OS_newlineLen    1
#   define OS_pathSep       '/'
#   define OS_pathSepStr    "/"
#   define OS_isPathSep(ch) ((ch) == '/')
#endif

// == Endianness --
#if defined(__BYTE_ORDER__)
#   if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#       define OS_isLittleEndian 1
#       define OS_isBigEndian    0
#   elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#       define OS_isLittleEndian 0
#       define OS_isBigEndian    1
#   else
#       error "Unknown byte order"
#   endif
#elif defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
    // MSVC / MinGW on x86/x64/ARM64 Windows - all little-endian
#   define OS_isLittleEndian 1
#   define OS_isBigEndian    0
#else
#   error "Cannot determine endianness"
#endif

/* ================================================================== */
/* Architecture Detection                                             */
/* ================================================================== */

// Defaults - all 0, then override the detected one
#define ARCH_isX86_64    0
#define ARCH_isX86_32    0
#define ARCH_isARM64     0
#define ARCH_isARM32     0
#define ARCH_isRISCV64   0
#define ARCH_isRISCV32   0
#define ARCH_isLoongArch64 0
#define ARCH_isMIPS64    0
#define ARCH_isMIPS32    0
#define ARCH_isPPC64     0
#define ARCH_isPPC32     0
#define ARCH_isS390X     0
#define ARCH_isS390      0
#define ARCH_isSPARC64   0
#define ARCH_isSPARC32   0
#define ARCH_isAlpha     0
#define ARCH_isHPPA      0
#define ARCH_isM68K      0
#define ARCH_isIA64      0

#define ARCH_is64Bit     0
#define ARCH_is32Bit     0

#define ARCH_isX86       0
#define ARCH_isARM       0
#define ARCH_isRISCV     0
#define ARCH_isLoongArch 0
#define ARCH_isMIPS      0
#define ARCH_isPPC       0
#define ARCH_isS390      0
#define ARCH_isSPARC     0
#define ARCH_isAlpha     0
#define ARCH_isHPPA      0
#define ARCH_isM68K      0
#define ARCH_isIA64      0

// Capability defaults
#define ARCH_hasMMX      0
#define ARCH_hasSSE      0
#define ARCH_hasSSE2     0
#define ARCH_hasSSE3     0
#define ARCH_hasSSSE3    0
#define ARCH_hasSSE4_1   0
#define ARCH_hasSSE4_2   0
#define ARCH_hasNEON     0
#define ARCH_hasAES      0
#define ARCH_hasCRC32    0
#define ARCH_hasVector   0
#define ARCH_hasBitManip 0

// == Detect Architecture --

#if defined(__x86_64__) || defined(_M_X64) || defined(__amd64__)
#   undef ARCH_isX86_64
#   undef ARCH_is64Bit
#   undef ARCH_isX86
#   define ARCH_isX86_64  1
#   define ARCH_is64Bit   1
#   define ARCH_isX86     1

#   undef ARCH_hasSSE
#   undef ARCH_hasSSE2
#   undef ARCH_hasSSE3
#   undef ARCH_hasSSSE3
#   undef ARCH_hasSSE4_1
#   undef ARCH_hasSSE4_2
#   define ARCH_hasSSE     1
#   define ARCH_hasSSE2    1
#   define ARCH_hasSSE3    1
#   define ARCH_hasSSSE3   1
#   define ARCH_hasSSE4_1  1
#   define ARCH_hasSSE4_2  1

#elif defined(__i386__) || defined(_M_IX86) || defined(__X86__)
#   undef ARCH_isX86_32
#   undef ARCH_is32Bit
#   undef ARCH_isX86
#   define ARCH_isX86_32  1
#   define ARCH_is32Bit   1
#   define ARCH_isX86     1

#   undef ARCH_hasMMX
#   undef ARCH_hasSSE
#   undef ARCH_hasSSE2
#   define ARCH_hasMMX    1
#   define ARCH_hasSSE    1
#   define ARCH_hasSSE2   1

#elif defined(__aarch64__) || defined(_M_ARM64)
#   undef ARCH_isARM64
#   undef ARCH_is64Bit
#   undef ARCH_isARM
#   define ARCH_isARM64   1
#   define ARCH_is64Bit   1
#   define ARCH_isARM     1

#   undef ARCH_hasNEON
#   undef ARCH_hasAES
#   undef ARCH_hasCRC32
#   define ARCH_hasNEON   1
#   define ARCH_hasAES    1
#   define ARCH_hasCRC32  1

#elif defined(__arm__) || defined(_M_ARM) || defined(__thumb__)
#   undef ARCH_isARM32
#   undef ARCH_is32Bit
#   undef ARCH_isARM
#   define ARCH_isARM32   1
#   define ARCH_is32Bit   1
#   define ARCH_isARM     1
#   if defined(__ARM_NEON) || defined(__ARM_NEON__)
#       undef ARCH_hasNEON
#       define ARCH_hasNEON  1
#   endif
#   if defined(__ARM_FEATURE_CRC32)
#       undef ARCH_hasCRC32
#       define ARCH_hasCRC32 1
#   endif

#elif defined(__riscv)
#   if __riscv_xlen == 64
#       undef ARCH_isRISCV64
#       undef ARCH_is64Bit
#       undef ARCH_isRISCV
#       define ARCH_isRISCV64 1
#       define ARCH_is64Bit   1
#       define ARCH_isRISCV   1
#   elif __riscv_xlen == 32
#       undef ARCH_isRISCV32
#       undef ARCH_is32Bit
#       undef ARCH_isRISCV
#       define ARCH_isRISCV32 1
#       define ARCH_is32Bit   1
#       define ARCH_isRISCV   1
#   else
#       error "Unsupported RISC-V XLEN"
#   endif
#   if defined(__riscv_vector)
#       undef ARCH_hasVector
#       define ARCH_hasVector   1
#   endif
#   if defined(__riscv_zba) || defined(__riscv_zbb) || defined(__riscv_zbc) || defined(__riscv_zbs)
#       undef ARCH_hasBitManip
#       define ARCH_hasBitManip 1
#   endif

#elif defined(__loongarch64)
#   undef ARCH_isLoongArch64
#   undef ARCH_is64Bit
#   undef ARCH_isLoongArch
#   define ARCH_isLoongArch64 1
#   define ARCH_is64Bit       1
#   define ARCH_isLoongArch   1

#elif defined(__mips__)
#   if defined(__mips64) && defined(_MIPS_SIM) && _MIPS_SIM == _ABI64
#       undef ARCH_isMIPS64
#       undef ARCH_is64Bit
#       undef ARCH_isMIPS
#       define ARCH_isMIPS64  1
#       define ARCH_is64Bit   1
#       define ARCH_isMIPS    1
#   else
#       undef ARCH_isMIPS32
#       undef ARCH_is32Bit
#       undef ARCH_isMIPS
#       define ARCH_isMIPS32  1
#       define ARCH_is32Bit   1
#       define ARCH_isMIPS    1
#   endif

#elif defined(__powerpc64__) || defined(__ppc64__) || defined(_ARCH_PPC64)
#   undef ARCH_isPPC64
#   undef ARCH_is64Bit
#   undef ARCH_isPPC
#   define ARCH_isPPC64   1
#   define ARCH_is64Bit   1
#   define ARCH_isPPC     1

#elif defined(__powerpc__) || defined(__ppc__) || defined(_ARCH_PPC)
#   undef ARCH_isPPC32
#   undef ARCH_is32Bit
#   undef ARCH_isPPC
#   define ARCH_isPPC32   1
#   define ARCH_is32Bit   1
#   define ARCH_isPPC     1

#elif defined(__s390x__)
#   undef ARCH_isS390X
#   undef ARCH_is64Bit
#   undef ARCH_isS390
#   define ARCH_isS390X   1
#   define ARCH_is64Bit   1
#   define ARCH_isS390    1

#elif defined(__s390__)
#   undef ARCH_isS390
#   undef ARCH_is32Bit
#   undef ARCH_isS390
#   define ARCH_isS390    1
#   define ARCH_is32Bit   1
#   define ARCH_isS390    1

#elif defined(__sparc__)
#   if defined(__arch64__)
#       undef ARCH_isSPARC64
#       undef ARCH_is64Bit
#       undef ARCH_isSPARC
#       define ARCH_isSPARC64 1
#       define ARCH_is64Bit   1
#       define ARCH_isSPARC   1
#   else
#       undef ARCH_isSPARC32
#       undef ARCH_is32Bit
#       undef ARCH_isSPARC
#       define ARCH_isSPARC32 1
#       define ARCH_is32Bit   1
#       define ARCH_isSPARC   1
#   endif

#elif defined(__alpha__)
#   undef ARCH_isAlpha
#   undef ARCH_is64Bit
#   define ARCH_isAlpha   1
#   define ARCH_is64Bit   1

#elif defined(__hppa__)
#   undef ARCH_isHPPA
#   undef ARCH_is32Bit
#   define ARCH_isHPPA    1
#   define ARCH_is32Bit   1

#elif defined(__m68k__)
#   undef ARCH_isM68K
#   undef ARCH_is32Bit
#   define ARCH_isM68K    1
#   define ARCH_is32Bit   1

#elif defined(__ia64__) || defined(_M_IA64)
#   undef ARCH_isIA64
#   undef ARCH_is64Bit
#   define ARCH_isIA64    1
#   define ARCH_is64Bit   1

#else
#   error "Unsupported or unknown architecture"
#endif

#if defined(__AVX2__)
#   define ARCH_hasAVX2 1
#else
#   define ARCH_hasAVX2 0
#endif

#if ARCH_is64Bit
#   define ARCH_bits 64
#else
#   define ARCH_bits 32
#endif

/* ================================================================== */
/* Compiler Detection                                                 */
/* ================================================================== */

#define COMPILER_isGCC       0
#define COMPILER_isClang     0
#define COMPILER_isMSVC      0
#define COMPILER_isICC       0
#define COMPILER_isICX       0
#define COMPILER_isMinGW     0
#define COMPILER_isCygwin    0
#define COMPILER_isTinyCC    0
#define COMPILER_isPGI       0
#define COMPILER_isSunPro    0
#define COMPILER_isIBMXL     0
#define COMPILER_isARMCC     0
#define COMPILER_isEmscripten 0
#define COMPILER_isWatcom    0
#define COMPILER_isBorland   0
#define COMPILER_isGHS       0

#define COMPILER_versionMajor 0
#define COMPILER_versionMinor 0
#define COMPILER_versionPatch 0

// === GCC (not Clang, not Intel) ===
#if defined(__GNUC__) && !defined(__clang__) && !defined(__INTEL_COMPILER) && !defined(__INTEL_LLVM_COMPILER)
#   undef COMPILER_isGCC
#   undef COMPILER_versionMajor
#   undef COMPILER_versionMinor
#   undef COMPILER_versionPatch
#   define COMPILER_isGCC 1
#   define COMPILER_versionMajor __GNUC__
#   define COMPILER_versionMinor __GNUC_MINOR__
#   define COMPILER_versionPatch __GNUC_PATCHLEVEL__
#endif

// === Clang (including Apple Clang) ===
#if defined(__clang__)
#   undef COMPILER_isClang
#   undef COMPILER_versionMajor
#   undef COMPILER_versionMinor
#   undef COMPILER_versionPatch
#   define COMPILER_isClang 1
#   define COMPILER_versionMajor __clang_major__
#   define COMPILER_versionMinor __clang_minor__
#   define COMPILER_versionPatch __clang_patchlevel__
#endif

// === MSVC ===
#if defined(_MSC_VER) && !defined(__clang__) && !defined(__GNUC__)
#   undef COMPILER_isMSVC
#   undef COMPILER_versionMajor
#   undef COMPILER_versionMinor
#   undef COMPILER_versionPatch
#   define COMPILER_isMSVC 1
#   define COMPILER_versionMajor (_MSC_VER / 100)
#   define COMPILER_versionMinor (_MSC_VER % 100)
#   define COMPILER_versionPatch 0
#endif

// === Intel Classic Compiler (ICC) ===
#if defined(__INTEL_COMPILER) && !defined(__INTEL_LLVM_COMPILER)
#   undef COMPILER_isICC
#   undef COMPILER_versionMajor
#   undef COMPILER_versionMinor
#   undef COMPILER_versionPatch
#   define COMPILER_isICC 1
#   define COMPILER_versionMajor (__INTEL_COMPILER / 100)
#   define COMPILER_versionMinor (__INTEL_COMPILER % 100)
#   define COMPILER_versionPatch 0
#endif

// === Intel LLVM-based Compiler (ICX/DPC++) ===
#if defined(__INTEL_LLVM_COMPILER)
#   undef COMPILER_isICX
#   undef COMPILER_versionMajor
#   undef COMPILER_versionMinor
#   undef COMPILER_versionPatch
#   define COMPILER_isICX 1
#   define COMPILER_versionMajor (__INTEL_LLVM_COMPILER / 100)
#   define COMPILER_versionMinor (__INTEL_LLVM_COMPILER % 100)
#   define COMPILER_versionPatch 0
#endif

// === MinGW (after GCC so GCC is detected first) ===
#if defined(__MINGW32__) || defined(__MINGW64__)
#   undef COMPILER_isMinGW
#   define COMPILER_isMinGW 1
#endif

// === Cygwin GCC ===
#if defined(__CYGWIN__) && defined(__GNUC__)
#   undef COMPILER_isCygwin
#   define COMPILER_isCygwin 1
#endif

// === TinyCC ===
#if defined(__TINYC__)
#   undef COMPILER_isTinyCC
#   define COMPILER_isTinyCC 1
#endif

// === PGI / NVIDIA HPC SDK ===
#if defined(__PGI) || defined(__PGIC__) || defined(__NVCOMPILER__)
#   undef COMPILER_isPGI
#   define COMPILER_isPGI 1
#endif

// === Oracle Solaris Studio ===
#if defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#   undef COMPILER_isSunPro
#   define COMPILER_isSunPro 1
#endif

// === IBM XL C/C++ ===
#if defined(__IBMC__) || defined(__IBMCPP__)
#   undef COMPILER_isIBMXL
#   define COMPILER_isIBMXL 1
#endif

// === ARM Compiler ===
#if defined(__ARMCC_VERSION)
#   undef COMPILER_isARMCC
#   define COMPILER_isARMCC 1
#endif

// === Emscripten ===
#if defined(__EMSCRIPTEN__)
#   undef COMPILER_isEmscripten
#   define COMPILER_isEmscripten 1
#endif

// === Watcom ===
#if defined(__WATCOMC__)
#   undef COMPILER_isWatcom
#   define COMPILER_isWatcom 1
#endif

// === Borland ===
#if defined(__BORLANDC__)
#   undef COMPILER_isBorland
#   define COMPILER_isBorland 1
#endif

// === Green Hills Software ===
#if defined(__ghs__)
#   undef COMPILER_isGHS
#   define COMPILER_isGHS 1
#endif

// === Composite compiler queries ===
#define COMPILER_isIntel (COMPILER_isICC || COMPILER_isICX)

#define COMPILER_isGNUCCompatible \
    (COMPILER_isGCC || COMPILER_isClang || COMPILER_isICC || COMPILER_isICX || \
     COMPILER_isMinGW || COMPILER_isCygwin)

#define COMPILER_isGNUC COMPILER_isGNUCCompatible

#define COMPILER_versionInteger \
    (COMPILER_versionMajor * 10000 + COMPILER_versionMinor * 100 + COMPILER_versionPatch)

/* ================================================================== */
/* Feature Detection Macros                                           */
/* ================================================================== */

// Provide fallbacks for compilers that don't define these
#ifndef __has_attribute
#   define __has_attribute(x) 0
#endif

#ifndef __has_builtin
#   define __has_builtin(x) 0
#endif

#ifndef __has_cpp_attribute
#   define __has_cpp_attribute(x) 0
#endif

#ifndef __has_feature
#   define __has_feature(x) 0
#endif

#ifndef __has_extension
#   define __has_extension(x) 0
#endif

/* ================================================================== */
/* Compiler Capability Macros                                         */
/* ================================================================== */

// Attribute support
#define COMPILER_hasGccAttribute(attr) __has_attribute(attr)
#define COMPILER_hasClangAttribute(attr) __has_attribute(attr)

// Built-in support
#define COMPILER_hasBuiltin(builtin) __has_builtin(builtin)

// C++ standard attributes
#define COMPILER_hasCppAttribute(attr) __has_cpp_attribute(attr)

// Clang features
#define COMPILER_hasFeature(feature) __has_feature(feature)

// MSVC declspec support (all MSVC versions support it)
#define COMPILER_hasDeclspec 1

/* ================================================================== */
/* Language Detection                                                 */
/* ================================================================== */

#if (defined(__STDC__) || defined (__STDC_VERSION__)) && !defined(__cplusplus) && !defined(__OBJC__)
#   define LANG_isC 1
#   define LANG_isCPP 0
#   define LANG_isObjectiveC 0
#elif defined(__cplusplus)
#   define LANG_isC 0
#   define LANG_isCPP 1
#   define LANG_isObjectiveC 0
#elif defined(__OBJC__)
#   define LANG_isC 0
#   define LANG_isCPP 0
#   define LANG_isObjectiveC 1
#else
#   define LANG_isC 0
#   define LANG_isCPP 0
#   define LANG_isObjectiveC 0
#endif

#if !LANG_isC
#   define DECL_BEGIN  extern "C" {
#   define DECL_END  }
#else
#   define DECL_BEGIN
#   define DECL_END
#endif

/* ================================================================== */
/* C Standard Version Detection                                       */
/* ================================================================== */

#define STD_cVersion     0
#define STD_cVersionName CXX
#define STD_cHas(n) __STDC_VERSION__ >= n
#define STD_cHasYear(n) __STDC_VERSION__ >= (n * 100L)

#if LANG_isC
#   if defined(__STDC_VERSION__)
#       undef STD_cVersion
#       undef STD_cVersionName
#       if __STDC_VERSION__ >= 202311L
#           define STD_cVersion     202311L
#           define STD_cVersionName C23
#       elif __STDC_VERSION__ >= 201710L
#           define STD_cVersion     201710L
#           define STD_cVersionName C17
#       elif __STDC_VERSION__ >= 201112L
#           define STD_cVersion     201112L
#           define STD_cVersionName C11
#       elif __STDC_VERSION__ >= 199901L
#           define STD_cVersion     199901L
#           define STD_cVersionName C99
#       elif __STDC_VERSION__ >= 199409L
#           define STD_cVersion     199409L
#           define STD_cVersionName C94
#       else
#           define STD_cVersion     199001L
#           define STD_cVersionName C90
#       endif
#   else
#       undef STD_cVersion
#       undef STD_cVersionName
#       define STD_cVersion 199001L
#       define STD_cVersionName C90
#   endif
#endif

#define STD_Name X

#define STD_hasC89 0
#define STD_hasC99 0
#define STD_hasC11 0
#define STD_hasC17 0
#define STD_hasC23 0

#if STD_cHasYear(1989)
#   undef STD_hasC89
#   undef STD_Name
#   define STD_hasC89 1
#   define STD_Name C89
#endif
#if STD_cHasYear(1999)
#   undef STD_hasC99
#   undef STD_Name
#   define STD_hasC99 1
#   define STD_Name C99
#endif
#if STD_cHasYear(2011)
#   undef STD_hasC11
#   undef STD_Name
#   define STD_hasC11 1
#   define STD_Name C11
#endif
#if STD_cHasYear(2017)
#   undef STD_hasC17
#   undef STD_Name
#   define STD_hasC17 1
#   define STD_Name C17
#endif
#if STD_cHasYear(2023)
#   undef STD_hasC23
#   undef STD_Name
#   define STD_hasC23 1
#   define STD_Name C23
#endif

/* ================================================================== */
/* Version Comparison Macros                                          */
/* ================================================================== */

#define STD_versionGen(year) ((year) * 10000)
#define STD_versionFull(year, month) ((year) * 10000 + (month) * 100)
#define STD_versionPatch(year, month, patch) ((year) * 10000 + (month) * 100 + (patch))

#define STD_versionYear(version)       ((version) / 10000)
#define STD_versionMonth(version)      (((version) / 100) % 100)
#define STD_versionPatchNum(version)   ((version) % 100)

// Returns 1 if v1 > v2, 0 if equal, -1 if v1 < v2
#define STD_versionCmp(v1, v2) M_cmp(v1, v2)

#define STD_versionCmpYear(v1, v2)      M_cmp((v1) / 10000, (v2) / 10000)
#define STD_versionCmpYearMonth(v1, v2) M_cmp((v1) / 100, (v2) / 100)
#define STD_versionMatchYear(v1, v2)    (((v1) / 10000) == ((v2) / 10000))
#define STD_versionMatchYearMonth(v1, v2) (((v1) / 100) == ((v2) / 100))

#define STD_versionGtYear(v1, v2)       (((v1) / 10000) >  ((v2) / 10000))
#define STD_versionGeYear(v1, v2)       (((v1) / 10000) >= ((v2) / 10000))
#define STD_versionLtYear(v1, v2)       (((v1) / 10000) <  ((v2) / 10000))
#define STD_versionLeYear(v1, v2)       (((v1) / 10000) <= ((v2) / 10000))
#define STD_versionGtYearMonth(v1, v2)  (((v1) / 100  ) >  ((v2) / 100)  )
#define STD_versionGeYearMonth(v1, v2)  (((v1) / 100  ) >= ((v2) / 100)  )
#define STD_versionLtYearMonth(v1, v2)  (((v1) / 100  ) <  ((v2) / 100)  )
#define STD_versionLeYearMonth(v1, v2)  (((v1) / 100  ) <= ((v2) / 100)  )

/* ================================================================== */
/* Storage Class Specifiers (STORAGE_)                                */
/* ================================================================== */

// === Thread-local storage ===
#if STD_cHas(202311L)
#   define STORAGE_threadLocal thread_local
#elif STD_cHas(201112L)
#   define STORAGE_threadLocal _Thread_local
#elif COMPILER_isGNUCCompatible && __has_attribute(tls_model)
#   define STORAGE_threadLocal __thread
#elif COMPILER_isMSVC
#   define STORAGE_threadLocal __declspec(thread)
#else
#   define STORAGE_threadLocal
#endif

// === Noreturn ===
#if STD_cHas(202311L)
#   define STORAGE_noRet [[noreturn]]
#elif STD_cHas(201112L)
#   define STORAGE_noRet _Noreturn
#elif COMPILER_isGNUCCompatible && __has_attribute(noreturn)
#   define STORAGE_noRet __attribute__((__noreturn__))
#elif COMPILER_isMSVC
#   define STORAGE_noRet __declspec(noreturn)
#else
#   define STORAGE_noRet
#endif

// === Alignas (alignment specifier) ===
#if STD_cHas(202311L)
#   define STORAGE_alignas(alignment) alignas(alignment)
#elif STD_cHas(201112L)
#   define STORAGE_alignas(alignment) _Alignas(alignment)
#elif COMPILER_isGNUCCompatible && __has_attribute(aligned)
#   define STORAGE_alignas(alignment) __attribute__((__aligned__(alignment)))
#elif COMPILER_isMSVC
#   define STORAGE_alignas(alignment) __declspec(align(alignment))
#else
#   define STORAGE_alignas(alignment)
#endif

// === Alignof (alignment query) ===
#if STD_cHas(202311L)
#   define STORAGE_alignof(type) alignof(type)
#elif STD_cHas(201112L)
#   define STORAGE_alignof(type) _Alignof(type)
#elif COMPILER_isGNUCCompatible
#   define STORAGE_alignof(type) __alignof__(type)
#elif COMPILER_isMSVC
#   define STORAGE_alignof(type) __alignof(type)
#else
#   define STORAGE_alignof(type) 0
#endif

/* ================================================================== */
/* Function & Variable Attributes (ATTR_)                             */
/* ================================================================== */

// --== Detection helpers for each attribute ----

// always_inline
#if __has_attribute(always_inline)
#   define ATTR_alwaysInline __attribute__((__always_inline__)) inline
#elif COMPILER_isMSVC
#   define ATTR_alwaysInline __forceinline
#else
#   define ATTR_alwaysInline inline
#endif

// noinline
#if __has_attribute(noinline)
#   define ATTR_noInline __attribute__((__noinline__))
#elif COMPILER_isMSVC
#   define ATTR_noInline __declspec(noinline)
#else
#   define ATTR_noInline
#endif

// pure
#if __has_attribute(pure)
#   define ATTR_pure __attribute__((__pure__))
#else
#   define ATTR_pure
#endif

// const
#if __has_attribute(const)
#   define ATTR_const __attribute__((__const__))
#else
#   define ATTR_const
#endif

// hot
#if __has_attribute(hot)
#   define ATTR_hot __attribute__((__hot__))
#else
#   define ATTR_hot
#endif

// cold
#if __has_attribute(cold)
#   define ATTR_cold __attribute__((__cold__))
#else
#   define ATTR_cold
#endif

// weak
#if __has_attribute(weak)
#   define ATTR_weak __attribute__((__weak__))
#elif COMPILER_isMSVC
#   define ATTR_weak __declspec(selectany)
#else
#   define ATTR_weak
#endif

// noreturn
#if __has_attribute(noreturn)
#   define ATTR_noReturn __attribute__((__noreturn__))
#elif COMPILER_isMSVC
#   define ATTR_noReturn __declspec(noreturn)
#else
#   define ATTR_noReturn
#endif

// returns_twice
#if __has_attribute(returns_twice)
#   define ATTR_returnTwice __attribute__((__returns_twice__))
#else
#   define ATTR_returnTwice
#endif

// malloc
#if __has_attribute(malloc)
#   define ATTR_malloc __attribute__((__malloc__))
#else
#   define ATTR_malloc
#endif

// alloc_size
#if __has_attribute(alloc_size)
#   define ATTR_alloc_size(n) __attribute__((__alloc_size__(n)))
#else
#   define ATTR_alloc_size(n)
#endif

// alloc_align
#if __has_attribute(alloc_align)
#   define ATTR_alloc_align(n) __attribute__((__alloc_align__(n)))
#else
#   define ATTR_alloc_align(n)
#endif

// returns_nonnull
#if __has_attribute(returns_nonnull)
#   define ATTR_returns_nonnull __attribute__((__returns_nonnull__))
#else
#   define ATTR_returns_nonnull
#endif

// nonnull
#if __has_attribute(nonnull)
#   define ATTR_nonnull(...) __attribute__((__nonnull__(__VA_ARGS__)))
#else
#   define ATTR_nonnull(...)
#endif

// nothrow
#if __has_attribute(nothrow)
#   define ATTR_nothrow __attribute__((__nothrow__))
#elif COMPILER_isMSVC
#   define ATTR_nothrow __declspec(nothrow)
#else
#   define ATTR_nothrow
#endif

// warn_unused_result
#if __has_attribute(warn_unused_result)
#   define ATTR_warnUnused __attribute__((__warn_unused_result__))
#elif COMPILER_isMSVC
#   define ATTR_warnUnused _Check_return_
#else
#   define ATTR_warnUnused
#endif

// unused
#if __has_attribute(unused)
#   define ATTR_unused __attribute__((__unused__))
#elif COMPILER_isMSVC
#   define ATTR_unused __pragma(warning(suppress: 4100 4189))
#else
#   define ATTR_unused
#endif

// used
#if __has_attribute(used)
#   define ATTR_used __attribute__((__used__))
#else
#   define ATTR_used
#endif

// packed
#if __has_attribute(packed)
#   define ATTR_packed __attribute__((__packed__))
#else
#   define ATTR_packed
#endif

// section
#if __has_attribute(section)
#   define ATTR_section(name) __attribute__((__section__(name)))
#elif COMPILER_isMSVC
#   define ATTR_section(name) __declspec(code_seg(name))
#else
#   define ATTR_section(name)
#endif

// abi_tag (C++ only)
#if defined(__cplusplus) && __has_attribute(abi_tag)
#   define ATTR_abiTag(tag) __attribute__((__abi_tag__(tag)))
#else
#   define ATTR_abiTag(tag)
#endif

// deprecated
#if __has_attribute(deprecated)
#   define ATTR_deprecated(msg) __attribute__((__deprecated__(msg)))
#elif COMPILER_isMSVC
#   define ATTR_deprecated(msg) __declspec(deprecated(msg))
#else
#   define ATTR_deprecated(msg)
#endif

// unavailable
#if __has_attribute(unavailable)
#   define ATTR_unavailable(msg) __attribute__((__unavailable__(msg)))
#else
#   define ATTR_unavailable(msg)
#endif

// aligned (alignment attribute)
#if __has_attribute(aligned)
#   define ATTR_aligned(bytes) __attribute__((__aligned__(bytes)))
#elif COMPILER_isMSVC
#   define ATTR_aligned(bytes) __declspec(align(bytes))
#else
#   define ATTR_aligned(bytes)
#endif

// no_sanitize
#if __has_attribute(no_sanitize)
#   define ATTR_noSanitize(san) __attribute__((__no_sanitize__(san)))
#elif COMPILER_isMSVC && _MSC_VER >= 1920
#   define ATTR_noSanitize(san) __declspec(no_sanitize_address)
#else
#   define ATTR_noSanitize(san)
#endif

// target (ISA specific)
#if __has_attribute(target)
#   define ATTR_target(isa) __attribute__((__target__(isa)))
#else
#   define ATTR_target(isa)
#endif

// optnone
#if __has_attribute(optnone)
#   define ATTR_optnone __attribute__((__optnone__))
#else
#   define ATTR_optnone
#endif

// --== Calling conventions (Windows) ----

// cdecl
#if COMPILER_isMSVC
#   define ATTR_cdecl __cdecl
#elif __has_attribute(cdecl)
#   define ATTR_cdecl __attribute__((__cdecl__))
#else
#   define ATTR_cdecl
#endif

// stdcall
#if COMPILER_isMSVC
#   define ATTR_stdcall __stdcall
#elif __has_attribute(stdcall)
#   define ATTR_stdcall __attribute__((__stdcall__))
#else
#   define ATTR_stdcall
#endif

// fastcall
#if COMPILER_isMSVC
#   define ATTR_fastcall __fastcall
#elif __has_attribute(fastcall)
#   define ATTR_fastcall __attribute__((__fastcall__))
#else
#   define ATTR_fastcall
#endif

// naked
#if COMPILER_isMSVC
#   define ATTR_naked __declspec(naked)
#elif __has_attribute(naked)
#   define ATTR_naked __attribute__((__naked__))
#else
#   define ATTR_naked
#endif

/* ================================================================== */
/* Compiler Built-ins (B_)                                            */
/* ================================================================== */

// --== Branch prediction ----
#if COMPILER_isGNUCCompatible && __has_builtin(__builtin_expect)
#   define B_likely(x)   __builtin_expect(!!(x), 1)
#   define B_unlikely(x) __builtin_expect(!!(x), 0)
#else
#   define B_likely(x)   (x)
#   define B_unlikely(x) (x)
#endif

// --== Unreachable ----
#if COMPILER_isGNUCCompatible && __has_builtin(__builtin_unreachable)
#   define B_unreachable() __builtin_unreachable()
#elif COMPILER_isMSVC
#   define B_unreachable() __assume(0)
#else
#   define B_unreachable() do { } while (1)
#endif

// --== Assumption ----
#if COMPILER_isClang && __has_builtin(__builtin_assume)
#   define B_assume(expr) __builtin_assume(expr)
#elif COMPILER_isMSVC
#   define B_assume(expr) __assume(expr)
#else
#   define B_assume(expr) do { if (!(expr)) B_unreachable(); } while (0)
#endif

// --== Compiler barrier ----
#if COMPILER_isGNUCCompatible
#   define B_compilerBarrier() __asm__ volatile("" ::: "memory")
#elif COMPILER_isMSVC
#   define B_compilerBarrier() __asm__ volatile("" ::: "memory")
#else
#   define B_compilerBarrier() do { } while (0)
#endif

// --== Memory prefetch ----
#if COMPILER_isGNUCCompatible && __has_builtin(__builtin_prefetch)
#   define B_prefetch(addr, rw, locality) __builtin_prefetch(addr, rw, locality)
#else
#   define B_prefetch(addr, rw, locality) ((void)0)
#endif

// --== Compile-time constant check ----
#if COMPILER_isGNUCCompatible && __has_builtin(__builtin_constant_p)
#   define B_constant_p(expr) __builtin_constant_p(expr)
#else
#   define B_constant_p(expr) 0
#endif

// --== Type compatibility (GCC only) ----
#if COMPILER_isGCC && __has_builtin(__builtin_types_compatible_p)
#   define B_typesCompatible_p(t1, t2) __builtin_types_compatible_p(t1, t2)
#else
#   define B_typesCompatible_p(t1, t2) 0
#endif

// --== Compile-time choice (GCC only) ----
#if COMPILER_isGCC && __has_builtin(__builtin_choose_expr)
#   define B_chooseExpr(c, e1, e2) __builtin_choose_expr(c, e1, e2)
#else
#   define B_chooseExpr(c, e1, e2) ((c) ? (e1) : (e2))
#endif

// --== Trap ----
#if COMPILER_isGNUCCompatible && __has_builtin(__builtin_trap)
#   define B_trap() __builtin_trap()
#elif COMPILER_isMSVC
#   define B_trap() __debugbreak()
#else
#   define B_trap() do { } while (1)
#endif

// --== Offsetof (built-in) ----
#if COMPILER_isGNUCCompatible && __has_builtin(__builtin_offsetof)
#   define B_offsetof(type, member) __builtin_offsetof(type, member)
#else
#   define B_offsetof(type, member) ((__size_t)&(((type*)0)->member))
#endif

/* ================================================================== */
/* General Utility Macros (M_)                                        */
/* ================================================================== */

// --== Alignment ----
#define M_alignUp(value, alignment)   (((value) + ((alignment) - 1)) & ~((alignment) - 1))
#define M_alignDown(value, alignment) ((value) & ~((alignment) - 1))
#define M_isAligned(value, alignment) (((value) & ((alignment) - 1)) == 0)

// --== Array size ----
#define M_arraySize(arr) (sizeof(arr) / sizeof((arr)[0]))

// --== Offsetof (fallback) ----
#if !defined(M_offsetOf)
#   define M_offsetOf(type, member) B_offsetof(type, member)
#endif

// --== Container_of ----
#define M_containerOf(ptr, type, member) \
    ((type*)((char*)(ptr) - M_offsetOf(type, member)))

// --== Comparison ----
#define M_cmp(a, b) \
    ((a) > (b) ?  1 : \
     (a) < (b) ? -1 : 0)

// --== Byte swap (using built-ins if available) ----
#if COMPILER_isGNUCCompatible && __has_builtin(__builtin_bswap16)
#   define M_swap16(x) __builtin_bswap16(x)
#elif defined(_MSC_VER)
#   define M_swap16(x) _byteswap_ushort(x)
#else
#   define M_swap16(x) ((unsigned short)(((x) >> 8) | ((x) << 8)))
#endif

#if COMPILER_isGNUCCompatible && __has_builtin(__builtin_bswap32)
#   define M_swap32(x) __builtin_bswap32(x)
#elif defined(_MSC_VER)
#   define M_swap32(x) _byteswap_ulong(x)
#else
#   define M_swap32(x) ((unsigned)( \
        (((x) & 0xFF000000U) >> 24) | \
        (((x) & 0x00FF0000U) >>  8) | \
        (((x) & 0x0000FF00U) <<  8) | \
        (((x) & 0x000000FFU) << 24)))
#endif

#if COMPILER_isGNUCCompatible && __has_builtin(__builtin_bswap64)
#   define M_swap64(x) __builtin_bswap64(x)
#elif defined(_MSC_VER)
#   define M_swap64(x) _byteswap_uint64(x)
#else
#   define M_swap64(x) /* fallback implementation if needed */
#endif

// --== Endian conversion ----
#if OS_isBigEndian
#   define M_hton16(x) (x)
#   define M_hton32(x) (x)
#   define M_ntoh16(x) (x)
#   define M_ntoh32(x) (x)
#else
#   define M_hton16(x) M_swap16(x)
#   define M_hton32(x) M_swap32(x)
#   define M_ntoh16(x) M_swap16(x)
#   define M_ntoh32(x) M_swap32(x)
#endif

// --== Preprocessor utilities ----
#define M_resolveMacro(sym) sym
#define M_toString(v) #v
#define M_toStringMacro(v) M_toString(v)
#define M_concatWord(a, b) a ## b
#define M_concatMacro(a, b) M_concatWord(a, b)

// --== Function name macros ----
#if COMPILER_isGNUCCompatible
#   define M_functionName __PRETTY_FUNCTION__
#elif COMPILER_isMSVC
#   define M_functionName __FUNCSIG__
#elif STD_hasC99
#   define M_functionName __func__
#else
#   define M_functionName ""
#endif

#if STD_hasC99
#   define M_funcNameStr __func__
#else
#   define M_funcNameStr ""
#endif

/* ================================================================== */
/* Sanity Checks                                                      */
/* ================================================================== */

#if !OS_isWindows && !OS_isApple && !OS_isLinux && !OS_isBSD && \
    !OS_isAndroid && !OS_isSolaris
#   if OS_isUnix
#       pragma message("Warning: Building for unknown Unix-like system")
#   else
#       error "Unsupported or unknown operating system"
#   endif
#endif

#if !ARCH_isX86 && !ARCH_isARM && !ARCH_isRISCV && !ARCH_isLoongArch && \
    !ARCH_isMIPS && !ARCH_isPPC && !ARCH_isS390 && !ARCH_isSPARC && \
    !ARCH_isAlpha && !ARCH_isHPPA && !ARCH_isM68K && !ARCH_isIA64
#   error "No architecture detected - this should not happen"
#endif

#endif /* PIASL_PLATFORM_H */
