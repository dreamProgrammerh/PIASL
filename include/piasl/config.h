#ifndef PIASL_CONFIG_H
#define PIASL_CONFIG_H 1

#include "platform.h"
#include "nonative.h"
#include "ptypes.h"

// silence warnings
#if !(PIASL_PLATFORM_H || PIASL_NONATIVE_H || PIASL_PTYPES_H)
#   error "piasl require platform.h, nonative.h, and ptypes.h to be included."
#endif

#define PIASL_EMPTY
#define PIASL_ATTR

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

#define PIASL_RET_(call) return call
#define PIASL_RET_RET(call) return call
#define PIASL_RET_NORET(call) do { call; B_unreachable(); } while (0)
#define PIASL_RET_VOID(call) do { call; } while (0)
#define PIASL_ETR_
#define PIASL_ETR_RET
#define PIASL_ETR_NORET STORAGE_noRet
#define PIASL_ETR_VOID

#endif /* PIASL_CONFIG_H */
