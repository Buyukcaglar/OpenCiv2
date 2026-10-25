#!/bin/sh
# Download what the portable build's first two steps need (tools/build_port.py
# module, c) into tools/toolchain/: wasi-sdk (clang for wasm32 with wasi-libc)
# and wabt (wasm2c).  macOS (Apple silicon), Linux (x86-64, arm64), Windows
# (x86-64, in an MSYS2 shell).  `fetch-toolchain.sh windows` also fetches
# SDL2's MinGW release, to cross-compile the Windows executable.
set -e
cd "$(dirname "$0")"
mkdir -p toolchain && cd toolchain
os=$(uname -s); arch=$(uname -m)
case "$os-$arch" in
    Darwin-arm64) sdk=arm64-macos; wabt=macos-arm64 ;;
    Darwin-x86_64) sdk=x86_64-macos; wabt= ;;
    Linux-x86_64) sdk=x86_64-linux; wabt=linux-x64 ;;
    Linux-aarch64|Linux-arm64) sdk=arm64-linux; wabt=linux-arm64 ;;
    MINGW64*-x86_64|MSYS*-x86_64|CYGWIN*-x86_64) sdk=x86_64-windows; wabt=windows-x64 ;;
    *) echo "no prebuilt toolchain for $os $arch" >&2; exit 1 ;;
esac
if [ ! -d wasi-sdk ]; then
    curl -fL# https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-25/wasi-sdk-25.0-$sdk.tar.gz | tar xz
    mv wasi-sdk-25.0-$sdk wasi-sdk
fi
if [ ! -d wabt ]; then
    if [ -z "$wabt" ]; then
        echo "wabt: no prebuilt release for this system; install it (brew install wabt) and set WABT=\$(brew --prefix wabt)" >&2
        exit 1
    fi
    curl -fL# https://github.com/WebAssembly/wabt/releases/download/1.0.41/wabt-1.0.41-$wabt.tar.gz | tar xz
    mv wabt-1.0.41 wabt
fi
if [ "$1" = windows ] && [ ! -d SDL2-mingw ]; then
    curl -fL# https://github.com/libsdl-org/SDL/releases/download/release-2.30.9/SDL2-devel-2.30.9-mingw.tar.gz | tar xz
    mv SDL2-2.30.9 SDL2-mingw
fi
# The Windows set-up's readers of the game's CD (src/host/setup_win.c):
# unshield (its InstallShield cabinet) and zlib, as sources, built into the
# program by tools/build_port.py.
fetch_src() {   # url sha256 top-level-folder name
    if [ ! -d "$4" ]; then
        curl -fL# "$1" -o "$4.tar.gz"
        sum=$( (sha256sum "$4.tar.gz" 2>/dev/null || shasum -a 256 "$4.tar.gz") | cut -d' ' -f1)
        if [ "$sum" != "$2" ]; then
            echo "$4.tar.gz: not the expected file (SHA-256 $sum)" >&2
            exit 1
        fi
        tar xzf "$4.tar.gz" && rm "$4.tar.gz" && mv "$3" "$4"
    fi
}
if [ "$1" = windows ]; then
    fetch_src https://github.com/twogood/unshield/archive/refs/tags/1.6.2.tar.gz \
        a937ef596ad94d16e7ed2c8553ad7be305798dcdcfd65ae60210b1e54ab51a2f unshield-1.6.2 unshield
    fetch_src https://github.com/madler/zlib/releases/download/v1.3.1/zlib-1.3.1.tar.gz \
        9a93b2b7dfdac77ceba5a558a580e74667dd6fede4585b91eefb60f03b72df23 zlib-1.3.1 zlib
    # (what unshield's cmake would configure)
    cat > unshield/lib/unshield_config.h <<'EOF2'
#define HAVE_INTTYPES_H 1
#define HAVE_STDBOOL_H 1
#define HAVE_STDINT_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRING_H 1
#define HAVE_SYS_STAT_H 1
#define HAVE_SYS_TYPES_H 1
#define SIZE_FORMAT "zu"
#define USE_OUR_OWN_MD5 1
EOF2
fi
echo "toolchain ready in tools/toolchain"
