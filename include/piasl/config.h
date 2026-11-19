#ifndef PIASL_CONFIG_H
#define PIASL_CONFIG_H 1
#include "cp/platform.h"
#include "cp/nonative.h"
#include "cp/ptypes.h"

#if ARCH_isX86_32
#   define PIASL_FC ATTR_stdcall
#   define PIASL_AC ATTR_stdcall
#else
#   define PIASL_FC
#   define PIASL_AC
#endif

#if !COMPILER_isGNUCCompatible && !defined(PIASL_STATIC)
#   define PIASL_STATIC 1
#endif

#if defined(PIASL_STATIC) && defined(PIASL_INLINE)
#   define PIASL_F ATTR_alwaysInline
#   define PIASL_A extern
#   define PIASL_B(...) ;
#   define PIASL_ASMV
#   define PIASL_ASM
#elif defined(PIASL_INLINE)
#   define PIASL_F ATTR_alwaysInline
#   define PIASL_A ATTR_alwaysInline
#   define PIASL_B(...) {__VA_ARGS__}
#   define PIASL_ASMV __asm__ volatile
#   define PIASL_ASM __asm__
#elif defined(PIASL_STATIC)
#   define PIASL_F static inline
#   define PIASL_A extern
#   define PIASL_B(...) ;
#   define PIASL_ASMV
#   define PIASL_ASM
#else
#   define PIASL_F static inline
#   define PIASL_A static inline
#   define PIASL_B(...) {__VA_ARGS__}
#   define PIASL_ASMV __asm__ volatile
#   define PIASL_ASM __asm__
#endif

#endif /* PIASL_CONFIG_H */
