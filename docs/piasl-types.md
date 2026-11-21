# PIASL Primitive Types

Source: `piasl/ptypes.h`

These aliases are shared by every OS-specific layer (direct syscall and
gateway). Their exact width and representation is controlled by the
declarations in the header and by the architecture selected in
`piasl/platform.h`.

The type tables are not duplicated here. The canonical table - one
`piasl_type = C definition` line per alias - lives in the symbol file:

-> [symbols/types.txt](../symbols/types.txt)

`=` is used (rather than the `>` of the wrappers/constants files) because
a typedef is a definitional alias within a single namespace, not a
cross-namespace mapping.

## Categories

- **Fixed-width integers** - `p_u8` .. `p_u64`, `p_i8` .. `p_i64`, plus the
  `long`-width `p_uL` / `p_iL` used by the LP64 BSD targets.
- **Booleans** - `p_b8` / `p_b16` / `p_b32`.
- **Characters and floats** - `p_c8` / `p_c16` / `p_c32` and
  `p_f32` / `p_f64` / `p_f128`.
- **Pointers and buffers** - `p_ptr`, `p_ref`, `p_buf`, `p_viw`.
- **Architecture-width** - `p_uS`, `p_iS`, `p_uP`, `p_iP`. These
  resolve to the 64-bit or 32-bit variant depending on the target; the
  symbol file lists both (`p_uS = p_u64 if 64bit else p_u32`).
- **Handles** - `p_handle`, an opaque pointer-sized handle type used by the
  gateway targets for OS handle values.

## Related Documents

- [Overall documentation](./overall.md)
- [Support matrix](./support-matrix.md)
- Per-OS type notes:
  - [linux](./linux/types.md) 
  - [android](./android/types.md) 
  - [freebsd](./freebsd/types.md)
  - [netbsd](./netbsd/types.md) 
  - [dragonflybsd](./dragonflybsd/types.md)
  - [windows](./windows/types.md) 
  - [macos](./macos/types.md) 
  - [ios](./ios/types.md) 
  - [openbsd](./openbsd/types.md) 
  - [illumos](./illumos/types.md)
