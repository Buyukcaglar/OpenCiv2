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
echo "toolchain ready in tools/toolchain"
