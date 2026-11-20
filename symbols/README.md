# PIASL Symbol Tables

This directory is the **canonical, machine-readable description of every
PIASL syscall/API layer**: signatures, per-arch syscall numbers, constants
and types. It is the input a generator needs to reproduce the platform
code - nothing about the syscall layer lives anywhere else. The files are
checked in as source of truth; they are NOT a build output.

Everything a consumer needs is in the data itself: the file formats below
are deliberately trivial to parse (fixed header, one entry per line, no
free-form comments), so a generator can be a few hundred lines of code in
any language.

## Files

| File                      | Kind      | Contents                                                                                                                                 |
| ------------------------- | --------- | ---------------------------------------------------------------------------------------------------------------------------------------- |
| `<os>.txt`                | syscalls  | one entry per syscall/OS API (union across arches) with its full signature; `!`-prefixed lines document symbols PIASL does not implement |
| `numbers_<os>_<arch>.txt` | numbers   | per-arch syscall number (Linux, Android)                                                                                                 |
| `numbers_<os>.txt`        | numbers   | unified syscall number (FreeBSD, NetBSD, DragonFly BSD)                                                                                  |
| `constants_<os>.txt`      | constants | OS constant `>` PIASL constant `=` value (all ten OSes)                                                                                  |
| `types_<os>.txt`          | types     | direct targets: every struct/union the OS layer defines; gateway targets: OS-type `>` PIASL-type normalization map                       |
| `types.txt`               | types     | shared base type aliases (all OSes)                                                                                                      |

Direct-syscall targets: linux, android, freebsd, netbsd, dragonflybsd.
Gateway targets: windows, macos, ios, openbsd, illumos.

## Fixed metadata header

Every file starts with EXACTLY 5 metadata lines, then pure data:

```text
# piasl-symbols 
# kind: syscalls | numbers | constants | types
# os: <os> | all
# arch: <arch> | all
# count: <entries>
```

The header is a constant size, so a parser skips exactly 5 lines and lands
on data - no comment counting, direct seek. `count` is the number of
logical entries (a conditional type with two layouts counts once). After
line 5 there are no comments and no blank lines.

## Entry grammar

```text
a > b                  mapping (OS name/type -> PIASL name/type)
a > b = v              mapping with value (constants, types)
a = v                  value assignment (numbers files)
a > b = (x: t, ...): r signature (see below)
a = struct {           type definition block
  attr: type
}
```

Signatures use the `(arg: type, ...): return` style - argument name first,
type last, return type after the closing parenthesis:

```text
getpid    > linux_getpid  = (): iS
read      > linux_read    = (fd: i32, buf: ptr, count: uS): iS
open      > macos_open    = (path: const c8*, flags: i32, ...): i32
ReadFile  > windows_read_file = (hFile: handle, lpBuffer: ptr, nNumberOfBytesToRead: u32, lpNumberOfBytesRead: u32*, lpOverlapped: ptr): i32
```

- `()` - no arguments (the C `(void)` placeholder is not repeated here)
- `...` - a C varargs tail, always last
- a bare type without a name means the source parameter was unnamed
- pointer stars stay on the type side: `lpNumberOfBytesRead: u32*`

## Conditional entries

Some types and constants depend on configuration (most commonly the
pointer width - the Linux `stat` layout differs between 32-bit and 64-bit
arches, and illumos' fcntl record-lock commands differ between the LP64
and ILP32 compilation environments).

Exactly four `@` keywords exist: `@if`, `@elif`, `@else`, `@end`.  There
is no `@ifdef` and no inline conditional form.  Conditions test the flag
VALUE directly - `@if ARCH_is64Bit` - never `@if defined(ARCH_is64Bit)`:
the `ARCH_*` flags are boolean macros defined to 1 or 0 on EVERY target,
so `defined(...)` would always be true.  A reader never has to guess
whether a bare word is a flag or not; only known flags may appear at all:

```text
@if ARCH_is32Bit
stat > linux_stat = struct {
  st_dev: u32
  ...
}
@else
stat > linux_stat = struct {
  st_dev: u64
  ...
}
@end
```

Conditioned branches chain with `@elif`; an unconditioned fallback (`@else`)
is optional and must come last.  A single-variant condition (no `@elif`,
no `@else`) is also valid, and the negated value form `@if !ARCH_is32Bit`
works too.  An `@if` without a matching `@end`, an `@else`/`@elif` without
a matching `@if`, a branch after `@else`, or an unknown flag must all be
errors, never silently false: a generator that does not know a flag cannot
produce correct code.

**One condition site, one block.**  When the same condition covers
several entries they share a single `@if` group instead of repeating the
condition per entry - the same style as `piasl/ptypes.h`, whose
width-dependent typedefs sit under one `#if ARCH_is64Bit /
#elif ARCH_is32Bit` group.  Real example from `types.txt`:

```text
@if ARCH_is64Bit
iP = i64
iS = i64
uP = u64
uS = u64
@elif ARCH_is32Bit
iP = i32
iS = i32
uP = u32
uS = u32
@end
```

Real example from `constants_illumos.txt` - the same fcntl command has
different numbers in the LP64 and ILP32 environments:

```text
@if ARCH_is64Bit
F_GETLK > PIASL_XC_F_GETLK=14
@else
F_GETLK > PIASL_XC_F_GETLK=33
@end
```

Condition flags use the same spelling as PIASL's own macros in
`piasl/platform.h`:

- `ARCH_is32Bit`, `ARCH_is64Bit` - pointer/long width
- (reserved for future use, same rule) `OS_is<Name>`, `ABI_is<...>`,
  `ENDIAN_is<...>`

Conditionals may appear in constants and types files. They do NOT appear
in `<os>.txt` or numbers files - those stay one plain line per entry so
the line-alignment invariant below holds unconditionally.

## Not-implemented marker (`!`)

A line of `<os>.txt` may start with `!`:

```text
! SetConsoleWindowState >  = (hConsoleOutput: handle, dwState: u32): i32
```

`!` means *this OS symbol exists but PIASL does not implement it*.  It
lets the signature files grow towards covering the whole OS surface
without every entry needing a PIASL wrapper or a numbers row:

- only valid in signature files (`<os>.txt`) - never in 
  numbers/constant/types files;
- a generator skips `!` lines completely, as if they were not there;
- they are not counted in the `count` header;
- they live in a trailing block after the implemented entries so the
  line-alignment invariant stays intact;
- the piasl name may be left empty on a `!` line, since PIASL does not
  export it.

## Ordering invariant

All entries in ALL files (syscalls, numbers, constants, types) are sorted
**byte-wise alphabetically by the main (os-side) symbol** - never by
syscall number. 

Reasons:
- every arch file of an OS shares the exact same sequence, so a diff
  between two arches is a pure value diff (insertions never ripple);
- one sort rule for signatures, numbers, constants and types - no tiers,
  no "which number is the reference" question;
- syscall numbers differ per arch, so any number-based sort would order
  each file differently and break cross-arch comparability.

## Line alignment (`<os>.txt` <-> numbers files)

`<os>.txt` and every numbers file of the same OS list the same syscalls in
the same order: **entry N is the same syscall in every file of the OS
family**. Finding a signature at line L of `linux.txt` means the x86_64
number is at line L of `numbers_linux_x86_64.txt` - jump straight to it, no
scanning:

```sh
$ sed -n '53p' linux.txt             # ->  getpid > linux_getpid = (): iS
$ sed -n '53p' linux_x86_64.numbers  # ->  getpid=39
$ sed -n '53p' linux_arm64.numbers   # ->  getpid=172
```

An arch that does not implement a syscall keeps its line with an empty
value (`open=`), so offsets never shift between files of the family.

An `!`-prefixed signature line in `<os>.txt` file will can be empty
on the matching numbers file, yet most of the times it should not.

## Types

Types are written as **plain names with no `p_` prefix** everywhere -
`i32`, `u64`, `uS`, `iS`, `uP`, `iP`, `ptr`, `ref`, `buf`,
`viw`, `handle`, `c8`/`c16`/`c32`, `b8`/`b16`/`b32`, `f32`/`f64`/`f128`,
`vd`, `uL`, `iL`.  `symbols/types.txt` is the complete alias list and the
mapping source; the four width-dependent aliases (`uS`, `iS`, `uP`, `iP`)
sit together in ONE `@if ARCH_is64Bit` / `@elif ARCH_is32Bit` block,
mirroring `piasl/ptypes.h`.  The generator resolves the plain names
to the platform's C types (`p_i32`/`int`, `p_uS`/`size_t`, ...) at
code-generation time. Nothing in this directory is allowed to reference
a `p_*` name.

## Constants on gateway targets

All ten targets have `constants_<os>.txt`.  PIASL never includes native
headers - "all is ours" - so every literal value the platform layer (and
its users) needs is owned by PIASL and carried in the symbol tables.

Direct-syscall and Gateway targets define their constants in
`piasl/sys/<os>/constants.h` next to the wrappers that use them. 
those values were researched from the native OS headers (xnu, 
the macOS SDK, openbsd/src, illumos-gate, and the Windows SDK,
etc.) so the tables match what the real kernel/libc exposes -
not just what a wrapper happens to use today.

PIASL constant prefixes:

| OS           | prefix      | notes                                 |
| ------------ | ----------- | ------------------------------------- |
| linux        | `PIASL_LC_` |                                       |
| android      | `PIASL_AC_` |                                       |
| freebsd      | `PIASL_FC_` |                                       |
| netbsd       | `PIASL_NC_` |                                       |
| dragonflybsd | `PIASL_DC_` |                                       |
| windows      | `PIASL_WC_` |                                       |
| macos        | `PIASL_MC_` |                                       |
| ios          | `PIASL_IC_` | same Darwin/libSystem values as macOS |
| openbsd      | `PIASL_OC_` |                                       |
| illumos      | `PIASL_XC_` | `X` because `I` is taken by iOS       |

The per-OS families mirror each other: full native errno list, `O_*`,
`AT_*`, `F_*` commands and lock types, `FD_*`, `SEEK_*`, `F_OK` family,
`STD*_FILENO`, `PROT_*`/`MAP_*` (+`MAP_FAILED`), `CLOCK_*`, wait flags,
file mode bits, the full native signal list, and the socket core
(`AF_*`/`SOCK_*`/`SOL_SOCKET`/`SO_*`/`MSG_*`/`SHUT_*`).  Windows covers
access rights, share modes, creation dispositions, file attributes,
seek origins, `PAGE_*`/`MEM_*`, wait results, std handles, `MAX_PATH`,
`INVALID_HANDLE_VALUE`, a curated `ERROR_*` set, console modes,
`FORMAT_MESSAGE_*` and the winsock core.

Note that "same name, different OS" really means different values:
illumos numbers `SOCK_DGRAM=1`/`SOCK_STREAM=2` (SysV order) where the
BSDs use 1/2 swapped, illumos `CLOCK_REALTIME` is 3 while OpenBSD's is
0, and `MSG_NOSIGNAL` is `0x400` on OpenBSD, `0x80000` on Darwin and
`0x200` on illumos.  Never copy values across targets.

## Scripts

```sh
# soon :)
```
