# PIASL - Portable Inline Assembly System Layer

> Zero-libc, header-only, self-contained OS interface for custom runtimes.

PIASL provides the lowest-level system interface for building a C runtime 
and standard library from scratch - no `libc`, no `<windows.h>`, no `<unistd.h>`.
Every type is `p_` prefixed (`p_u64`/`p_iS`),
every syscall number is `PIASL_*CN_*`,
every dispatch is inline assembly at the call site.

## Philosophy

- **Self-contained:** each `piasl/sys/<os>/` has its own `types`, `numbers`,
  `dispatch`, `asm` and `master.h`-style master that only includes 
  `piasl/config.h` - no cross-`sys` deps.
- **p_ prefix:** `p_u64`/`p_iS`/`p_viw` never collide with user or libc.
- **Two layers (docs/support-matrix.md):** 
    - `Direct` (`syscall`/`svc`/`ecall`/`int $0x80` via `PIASL_ASMV` or manual `.S`) 
      for Linux/Android/FreeBSD/NetBSD/DragonFlyBSD,
    - `Gateway` (`kernel32`/`libSystem`/`libc.so` via PEB/`dlsym`/ELF walk)
      for Windows/macOS/iOS/OpenBSD/illumos.

## Simple

```c
#include <piasl/sys/master.h>

int main(void) {
    p_c8 msg[] = "hi\n";
    linux_write(PIASL_LC_STDOUT_FILENO, msg, 3);
    linux_exit(PIASL_LC_EXIT_SUCCESS);
}
```

Build:

```sh
# header-only inline
clang -o a.out -Iinclude -O2 -nostdlib main.c
# or external asm
clang -o a.out -Iinclude -O2 -nostdlib main.c -DPIASL_STATIC=1 piasl/sys/syscall.S
```

## Cross OS layer (cos)

`piasl/sys/cos.h` is the portable face of PIASL: one header, same calls
on every target - `cos_write`, `cos_read`, `cos_exit`, ... - plus the
`PIASL_COS_STDIN/STDOUT/STDERR` constants. Contract, error semantics
and target mapping: [docs/cos.md](docs/cos.md).

```c
#include <piasl/sys/cos.h>

void _start(void) {
    const p_c8 msg[] = "Hello PIASL\n";
    cos_write(PIASL_COS_STDOUT, msg, sizeof(msg) - 1);
    cos_exit(0);
}
```

Build:

```sh
# direct syscall targets (Linux) - header-only, no loader unit
clang -o a.out -std=c11 --target=x86_64-linux-gnu -Iinclude \
    -nostdlib -nostartfiles -Wl,--entry=_start \
    hello.c

# gateway targets (Windows) - link the loader unit
clang -o a.exe -std=c11 --target=x86_64-w64-mingw32 -Iinclude \
    -nostdlib -nostartfiles -Wl,--entry=_start -Wl,--subsystem=console \
    hello.c piasl/sys/gateloader.c
```

The cos matrix (all `os`x`arch` pairs compile) should run a 
runtime checks on Linux, Android, the three BSD VMs, macOS,
IOS, OpenBSD, Illumos and Windows CI jobs.

## Symbol Tables

The `symbols/` directory contains machine-readable symbol tables. These are
the canonical source of truth for code generation (a glad-style codegen
pipeline is planned). All files share one grammar:

- `a > b` - name mapping: the upstream / OS-side name becomes the PIASL name
- `a = v` - value assignment
- `a > b = v` - mapping with value
- `a > b = (x: t, ...): r` - full signature
- `@if COND` / `@elif` / `@else` / `@end` - conditional entries (see below)

Every file opens with the same fixed 5-line metadata header, so a parser
always knows exactly where the data begins - no comment counting, direct
seek:

```text
# piasl-symbols
# kind: syscalls | numbers | constants | types
# os: <os> | all
# arch: <arch> | all
# count: <entries>
```

After line 5 the file is pure data: no comments.

**Files:**

### symbols/`<os>`.txt:
---

one line per implemented syscall / OS API (the union across arches)
with its full signature: `getpid > getpid = (): iS`,
`ReadFile > read_file = (hFile: handle, lpBuffer: ptr, ...): i32`


### symbols/numbers_`<os>`_`<arch>`.txt:
---

per-arch syscall numbers (Linux/Android)


### symbols/numbers_`<os>`.txt:
---

unified syscall numbers (FreeBSD/NetBSD/DragonFly)
Numbers files are **line-aligned** with `<os>.txt`: entry N is the same
syscall in every file of the OS family. A signature found at line L of
`linux.txt` has its x86_64 number at line L of `numbers_linux_x86_64.txt` -
jump straight to it, no scanning. An arch that does not implement a
syscall keeps the line with an empty value (`access=`), so offsets never
shift between files.


### symbols/constants_`<os>`.txt:
---

constants as `os_constant > piasl_constant=value`
(e.g. `O_RDONLY > PIASL_LC_O_RDONLY=0`, `INVALID_HANDLE_VALUE >
PIASL_WC_INVALID_HANDLE_VALUE=(-1)`). All ten targets have one: PIASL
never includes native headers, so every literal value the platform
layer and its users need is owned by PIASL. Gateway values were
researched from the native OS headers (xnu, openbsd/src,
illumos-gate, the Windows SDK).


### symbols/types_`<os>`.txt:
---

struct/union definitions for direct targets:

```text
timeval > linux_timeval = struct {
  tv_sec: isize
  tv_usec: isize
}
```

Arch-variant structs carry an explicit condition instead of a name
suffix; both variants share the same PIASL-side C name:

```text
@if ARCH_is32Bit
stat > linux_stat = struct { ... }
@else
stat > linux_stat = struct { ... }
@end
```

Gateway targets keep type normalization mappings (`DWORD > i32`).


### symbols/types.txt:
---

shared base type aliases (`u8 = unsigned char`); the four 
width-dependent aliases (`uS`, `iS`, `uP`, `iP`) share one
`@if ARCH_is64Bit` / `@elif ARCH_is32Bit` block, mirroring `piasl/ptypes.h`

Types are written as plain names (`i32`, `uS`, `ptr`, ...) with no `p_`
prefix anywhere in `symbols/`; the generator maps them to the platform's C
types at codegen time.

Ordering: every entry in every file - syscalls, numbers, constants, types -
is sorted byte-wise alphabetically by the main (OS-side) symbol, never by
syscall number. All arch files of an OS therefore share the exact same
sequence, and a cross-arch diff is a pure value diff.

##

> See [symbols/README.md](symbols/README.md) for the full format contract (grammar,
> conditionals, alignment invariant, condition flags).

## Bootstrap Architectures

| Target  | Bootstrap            | Imports | Description                                                  |
| ------- | -------------------- | ------- | ------------------------------------------------------------ |
| Windows | PEB walk             | 0       | Walk PEB -> LDR -> kernel32.dll PE export table              |
| macOS   | Dynamic linker API   | 2       | `_dyld_image_count` + `_dyld_get_image_header` + export trie |
| iOS     | Dynamic linker API   | 2       | Same as macOS (shares Darwin/XNU kernel)                     |
| OpenBSD | ELF walk             | 0       | `_DYNAMIC` -> `DT_DEBUG` -> `r_debug` -> `link_map` -> ld.so |
| illumos | ELF walk + r_ldsomap | 0       | Same as OpenBSD + illumos `r_ldsomap` fast-path              |

## Repository Structure

```
Soon
```

## Upstream Verification Anchors

- Linux: https://github.com/torvalds/linux/blob/master/arch/x86/entry/syscalls/syscall_64.tbl
- Android: https://android.googlesource.com/platform/bionic/+/refs/heads/main/libc/SYSCALLS.TXT
- FreeBSD: https://cgit.freebsd.org/src/tree/sys/kern/syscalls.master
- NetBSD: https://github.com/NetBSD/src/tree/trunk/sys/kern
- DragonFly BSD: https://gitweb.dragonflybsd.org/dragonfly.git/blob/HEAD:/sys/kern/syscalls.master
- Windows: https://github.com/microsoft/win32metadata/tree/main/generation/WinSDK/RecompiledIdlHeaders/um
- macOS/iOS: https://opensource.apple.com/source/dyld/ (dyld / mach-O export trie reference)
- OpenBSD: https://github.com/openbsd/src (ld.so source)
- illumos: https://illumos.org/man/ (illumos manpages, authoritative libc reference)

## Makefile

- `platform-%`: runs platform_macros.c test file.
