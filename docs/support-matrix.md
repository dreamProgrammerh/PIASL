# PIASL Support Matrix

| OS                                       | Layer          | Wrappers | Syscall-number model                                      | Architectures in source                                    |
| ---------------------------------------- | -------------- | -------- | --------------------------------------------------------- | ---------------------------------------------------------- |
| [Linux](./linux/README.md)               | Direct syscall | 0        | Per-architecture syscall numbers                          | `x86_64`, `x86_32`, `arm64`, `arm32`, `riscv64`, `riscv32` |
| [Android](./android/README.md)           | Direct syscall | 0        | Per-architecture syscall numbers                          | `x86_64`, `arm64`, `arm32`, `riscv64`                      |
| [FreeBSD](./freebsd/README.md)           | Direct syscall | 0        | Unified syscall numbers                                   | `x86_64`, `x86_32`, `arm64`, `arm32`, `riscv64`, `riscv32` |
| [NetBSD](./netbsd/README.md)             | Direct syscall | 0        | Unified syscall numbers                                   | `x86_64`, `x86_32`, `arm64`, `arm32`, `riscv64`, `riscv32` |
| [DragonFlyBSD](./dragonflybsd/README.md) | Direct syscall | 0        | Unified syscall numbers                                   | `x86_64`                                                   |
| [Windows](./windows/README.md)           | Gateway        | 0        | Runtime API resolution (PEB walk)                         | `x86_32`, `x86_64`                                         |
| [MacOS](./macos/README.md)               | Gateway        | 0        | Runtime API resolution (Dynamic linker API)               | `arm64`, `x86_64`                                          |
| [IOS](./ios/README.md)                   | Gateway        | 0        | Runtime API resolution (Dynamic linker API)               | `arm64`, `x86_64`                                          |
| [OpenBSD](./openbsd/README.md)           | Gateway        | 0        | Runtime API resolution (zero-import ELF walk)             | `x86_64`, `arm64`                                          |
| [Illumos](./illumos/README.md)           | Gateway        | 0        | Runtime API resolution (zero-import ELF walk + r_ldsomap) | `x86_64`, `x86_32`, `arm64`                                |

## Number Table Patterns

### Architecture-specific

`linux/` and `android/` select `numbers/<arch>.h` through `numbers.h` 
using the architecture macros.

### Unified

`freebsd/`, `netbsd/`, and `dragonflybsd/` keep all PIASL syscall numbers
in one `numbers.h`.

## Documentation Links

- [Overall](./overall.md) Soon
- [PIASL Types](./piasl-types.md)
- [Linux](./linux/README.md)
- [Android](./android/README.md)
- [FreeBSD](./freebsd/README.md)
- [NetBSD](./netbsd/README.md)
- [DragonFlyBSD](./dragonflybsd/README.md)
- [Windows](./windows/README.md)
- [MacOS](./macos/README.md)
- [IOS](./ios/README.md)
- [OpenBSD](./openbsd/README.md)
- [Illumos](./illumos/README.md)

## Syscall targets

Linux, Android, FreeBSD, NetBSD, and DragonFlyBSD are PIASL's syscall based
backends.  Syscall targets uses syscall-number table with syscalls written
GNU inline assembly for `clang` / `gcc`, and `msvc` need one .S file unit
that contain the syscall assembly code directly.

```sh
clang main.c                    # gnu just works
cl main.c piasl/sys/syscall.S   # msvc require one extra assembly file
```

```text
piasl/sys/syscall.S
    -> selected OS asm.S
    -> syscall arch dispatch
    -> direct assembly
```

## Gateway Targets

Windows, macOS, iOS, OpenBSD, and illumos are PIASL's gateway reference
backends.  Gateway targets use a linked C loader unit rather than a
syscall-number table or assembly syscall.

```sh
clang main.c piasl/sys/gateloader.c # one c file
cl main.c piasl/sys/gateloader.c    # same here (always required)
```

```text
piasl/sys/gateloader.c
    -> selected OS loader.c
    -> gateway loader
```

### Bootstrap approaches

| Target  | Bootstrap            | Library imports | Description                                                  |
| ------- | -------------------- | --------------- | ------------------------------------------------------------ |
| Windows | PEB walk             | 0               | Walk PEB -> LDR -> kernel32.dll PE export table              |
| macOS   | Dynamic linker API   | 2               | `_dyld_image_count` + `_dyld_get_image_header` + export trie |
| iOS     | Dynamic linker API   | 2               | Same as macOS (shares Darwin/XNU kernel)                     |
| OpenBSD | ELF walk             | 0               | `_DYNAMIC` -> `DT_DEBUG` -> `r_debug` -> `link_map` -> ld.so |
| illumos | ELF walk + r_ldsomap | 0               | Same as OpenBSD + illumos `r_ldsomap` fast-path              |

Three gateway targets (Windows, OpenBSD, illumos) achieve true
zero-import bootstraps - walking in-memory OS data structures 
to resolve `dlopen`/`dlsym` without linking against any library.
