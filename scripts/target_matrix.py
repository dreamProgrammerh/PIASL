from sys import argv

"""
  each empty "" target-value mean, i didn't find a match
   for the target-key on llvm (if you found insert it).

  each non-defined target-key mean there is no os-arch
   combo supported (at least that's what i know, correct
   me if i were wrong).
"""

DEFAULT = "unknown"
MATRIX: dict[str, str] = {
    "linux-x86_32": "i386-pc-linux-gnu",
    "linux-x86_64": "x86_64-pc-linux-gnu",
    "linux-arm32": "armv7-unknown-linux-gnueabihf",
    "linux-arm64": "aarch64-unknown-linux-gnu",
    "linux-riscv32": "riscv32-unknown-linux-gnu",
    "linux-riscv64": "riscv64-unknown-linux-gnu",

    "android-x86_32": "i686-linux-android",
    "android-x86_64": "x86_64-linux-android",
    "android-arm32": "armv7-linux-androideabi",
    "android-arm64": "aarch64-linux-android",
    "android-riscv32": "riscv32-linux-android",
    "android-riscv64": "riscv64-linux-android",

    "freebsd-x86_32": "i386-unknown-freebsd",
    "freebsd-x86_64": "x86_64-unknown-freebsd",
    "freebsd-arm32": "armv7-unknown-freebsd",
    "freebsd-arm64": "aarch64-unknown-freebsd",
    "freebsd-riscv32": "",
    "freebsd-riscv64": "riscv64-unknown-freebsd",

    "netbsd-x86_32": "i386-unknown-netbsd",
    "netbsd-x86_64": "x86_64-unknown-netbsd",
    "netbsd-arm32": "armv7-unknown-netbsd-eabi",
    "netbsd-arm64": "aarch64-unknown-netbsd",
    "netbsd-riscv32": "riscv32-unknown-netbsd",
    "netbsd-riscv64": "riscv64-unknown-netbsd",

    "openbsd-x86_32": "i386-unknown-openbsd",
    "openbsd-x86_64": "x86_64-unknown-openbsd",
    "openbsd-arm32": "armv7-unknown-openbsd",
    "openbsd-arm64": "aarch64-unknown-openbsd",
    "openbsd-riscv32": "",
    "openbsd-riscv64": "riscv64-unknown-openbsd",

    "dragonflybsd-x86_32": "i386-unknown-dragonfly",
    "dragonflybsd-x86_64": "x86_64-unknown-dragonfly",

    "illumos-x86_32": "i386-pc-solaris",
    "illumos-x86_64": "x86_64-pc-solaris",
    "illumos-arm32": "",
    "illumos-arm64": "aarch64-pc-solaris",
    "illumos-riscv32": "",
    "illumos-riscv64": "",

    "macos-x86_32": "i386-apple-darwin",
    "macos-x86_64": "x86_64-apple-darwin",
    "macos-arm64": "aarch64-apple-darwin",

    "ios-arm32": "armv7-apple-ios",
    "ios-arm64": "aarch64-apple-ios",

    "windows-x86_32": "i686-w64-mingw32",
    "windows-x86_64": "x86_64-w64-mingw32",
    "windows-arm32": "armv7-w64-mingw32",
    "windows-arm64": "aarch64-w64-mingw32",

    "msvc-windows-x86_32": "i686-pc-windows-msvc",
    "msvc-windows-x86_64": "x86_64-pc-windows-msvc",
    "msvc-windows-arm32": "armv7-pc-windows-msvc",
    "msvc-windows-arm64": "aarch64-pc-windows-msvc",

    "cygnus-windows-x86_32": "i686-pc-windows-cygnus",
    "cygnus-windows-x86_64": "x86_64-pc-windows-cygnus",
    "cygnus-windows-arm32": "armv7-pc-windows-cygnus",
    "cygnus-windows-arm64": "aarch64-pc-windows-cygnus",
}

if __name__ == "__main__":
    target: str = ""

    if len(argv) > 1:
        target = argv[1]
    else:
        target = input()

    out: str | None = MATRIX.get(
        target.strip(' \t\v\r\n\0\"\'').lower())

    if out == None or len(out) == 0:
        print(DEFAULT)
    else:
        print(out)
