/* tests/platform_macros.c
 *
 * Prints the value of every constant macro defined by platform.h, and ptypes.h
 * (OS_*, ARCH_*, COMPILER_*, LANG_*, STD_*, P_*). Function-like macros and pure text.
 */

#include <stdio.h>
#include <piasl/platform.h>
#include <piasl/ptypes.h>

#define P_BOOL(m)   printf("  \x1b[37m%-30s %s\x1b[0m\n", #m, (m) ? "\x1b[32mtrue" : "\x1b[31mfalse")
#define P_INT(m)    printf("  \x1b[37m%-30s \x1b[33m%+lld\x1b[0m\n", #m, (long long)(m))
#define P_UINT(m)   printf("  \x1b[37m%-30s \x1b[33m%llu\x1b[0m\n", #m, (unsigned long long)(m))
#define P_FLOAT(m)  printf("  \x1b[37m%-30s \x1b[33m%g\x1b[0m\n", #m, (double)(m))
#define P_CHAR(m)   printf("  \x1b[37m%-30s \x1b[34m'%c' \x1b[33m(%d)\x1b[0m\n", #m, (m), (int)(m))
#define P_STR(m)    printf("  \x1b[37m%-30s \x1b[34m\"%s\"\x1b[0m\n", #m, (m))
#define P_IDENT(m)  printf("  \x1b[37m%-30s \x1b[36m%s\x1b[0m\n", #m, M_toString(m))
#define P_SECT(m)   printf("  \n\x1b[35m== %s* ==\x1b[0m\n", #m);

int main(void) {
    P_SECT(OS_);
    P_BOOL(OS_isWindows);
    P_BOOL(OS_isWindows64);
    P_BOOL(OS_isWindows32);
    P_BOOL(OS_isMinGW);
    P_BOOL(OS_isCygwin);
    P_BOOL(OS_isApple);
    P_BOOL(OS_isUnix);
    P_BOOL(OS_isMacOS);
    P_BOOL(OS_isIOS);
    P_BOOL(OS_isTVOS);
    P_BOOL(OS_isWatchOS);
    P_BOOL(OS_isLinux);
    P_BOOL(OS_isAndroid);
    P_BOOL(OS_isFreeBSD);
    P_BOOL(OS_isNetBSD);
    P_BOOL(OS_isOpenBSD);
    P_BOOL(OS_isDragonFly);
    P_BOOL(OS_isBSD);
    P_BOOL(OS_isHaiku);
    P_BOOL(OS_isSolaris);
    P_BOOL(OS_isIllumos);
    P_BOOL(OS_isHPUX);
    P_BOOL(OS_isAIX);
    P_BOOL(OS_isIRIX);
    P_BOOL(OS_isOS2);
    P_BOOL(OS_isLittleEndian);
    P_BOOL(OS_isBigEndian);
    P_IDENT(OS_olf);
    P_UINT(OS_newlineLen);
    P_CHAR(OS_pathSep);
    P_CHAR(OS_pathAltSep);
    P_STR(OS_newline);
    P_STR(OS_pathSepStr);
    P_STR(OS_pathAltSepStr);

    P_SECT(ARCH_);
    P_BOOL(ARCH_isX86_64);
    P_BOOL(ARCH_isX86_32);
    P_BOOL(ARCH_isARM64);
    P_BOOL(ARCH_isARM32);
    P_BOOL(ARCH_isRISCV64);
    P_BOOL(ARCH_isRISCV32);
    P_BOOL(ARCH_isLoongArch64);
    P_BOOL(ARCH_isMIPS64);
    P_BOOL(ARCH_isMIPS32);
    P_BOOL(ARCH_isPPC64);
    P_BOOL(ARCH_isPPC32);
    P_BOOL(ARCH_isS390X);
    P_BOOL(ARCH_isS390);
    P_BOOL(ARCH_isSPARC64);
    P_BOOL(ARCH_isSPARC32);
    P_BOOL(ARCH_isAlpha);
    P_BOOL(ARCH_isHPPA);
    P_BOOL(ARCH_isM68K);
    P_BOOL(ARCH_isIA64);
    P_BOOL(ARCH_is64Bit);
    P_BOOL(ARCH_is32Bit);
    P_BOOL(ARCH_isX86);
    P_BOOL(ARCH_isARM);
    P_BOOL(ARCH_isRISCV);
    P_BOOL(ARCH_isLoongArch);
    P_BOOL(ARCH_isMIPS);
    P_BOOL(ARCH_isPPC);
    P_BOOL(ARCH_isS390);
    P_BOOL(ARCH_isSPARC);
    P_BOOL(ARCH_isAlpha);
    P_BOOL(ARCH_isHPPA);
    P_BOOL(ARCH_isM68K);
    P_BOOL(ARCH_isIA64);
    P_BOOL(ARCH_hasMMX);
    P_BOOL(ARCH_hasSSE);
    P_BOOL(ARCH_hasSSE2);
    P_BOOL(ARCH_hasSSE3);
    P_BOOL(ARCH_hasSSSE3);
    P_BOOL(ARCH_hasSSE4_1);
    P_BOOL(ARCH_hasSSE4_2);
    P_BOOL(ARCH_hasNEON);
    P_BOOL(ARCH_hasAES);
    P_BOOL(ARCH_hasCRC32);
    P_BOOL(ARCH_hasVector);
    P_BOOL(ARCH_hasBitManip);
    P_BOOL(ARCH_hasAVX2);
    P_UINT(ARCH_bits);

    P_SECT(COMPILER_);
    P_BOOL(COMPILER_isGCC);
    P_BOOL(COMPILER_isClang);
    P_BOOL(COMPILER_isMSVC);
    P_BOOL(COMPILER_isICC);
    P_BOOL(COMPILER_isICX);
    P_BOOL(COMPILER_isMinGW);
    P_BOOL(COMPILER_isCygwin);
    P_BOOL(COMPILER_isTinyCC);
    P_BOOL(COMPILER_isPGI);
    P_BOOL(COMPILER_isSunPro);
    P_BOOL(COMPILER_isIBMXL);
    P_BOOL(COMPILER_isARMCC);
    P_BOOL(COMPILER_isEmscripten);
    P_BOOL(COMPILER_isWatcom);
    P_BOOL(COMPILER_isBorland);
    P_BOOL(COMPILER_isGHS);
    P_BOOL(COMPILER_isIntel);
    P_BOOL(COMPILER_isGNUCCompatible);
    P_BOOL(COMPILER_isGNUC);
    P_BOOL(COMPILER_hasDeclspec);
    P_UINT(COMPILER_versionInteger);
    P_UINT(COMPILER_versionMajor);
    P_UINT(COMPILER_versionMinor);
    P_UINT(COMPILER_versionPatch);

    P_SECT(LANG_);
    P_BOOL(LANG_isC);
    P_BOOL(LANG_isCPP);
    P_BOOL(LANG_isObjectiveC);

    P_SECT(STD_);
    P_UINT(STD_cVersion);
    P_IDENT(STD_cVersionName);
    P_IDENT(STD_Name);
    P_BOOL(STD_hasC89);
    P_BOOL(STD_hasC99);
    P_BOOL(STD_hasC11);
    P_BOOL(STD_hasC17);
    P_BOOL(STD_hasC23);

    P_SECT(P_);
    P_UINT(P_U8_MIN);
    P_UINT(P_U16_MIN);
    P_UINT(P_U32_MIN);
    P_UINT(P_U64_MIN);
    P_UINT(P_UL_MIN);
    P_UINT(P_US_MIN);
    P_INT(P_I8_MIN);
    P_INT(P_I16_MIN);
    P_INT(P_I32_MIN);
    P_INT(P_I64_MIN);
    P_INT(P_IL_MIN);
    P_INT(P_IS_MIN);
    P_UINT(P_U8_MAX);
    P_UINT(P_U16_MAX);
    P_UINT(P_U32_MAX);
    P_UINT(P_U64_MAX);
    P_UINT(P_UL_MAX);
    P_UINT(P_US_MAX);
    P_INT(P_I8_MAX);
    P_INT(P_I16_MAX);
    P_INT(P_I32_MAX);
    P_INT(P_I64_MAX);
    P_INT(P_IL_MAX);
    P_INT(P_IS_MAX);
    P_UINT(P_PTR_SIZE);
    P_FLOAT(P_F64_NAN);
    P_FLOAT(P_F64_INF);
    P_FLOAT(P_F64_NINF);

    return 0;
}
