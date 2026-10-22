# The dev image: civ2-dev-base (tools/docker: wine, mingw, python) plus what the
# native builds need: 64-bit mingw, SDL2 (also 32-bit, for the -m32 build), gdb,
# and the portable build's toolchain: wasi-sdk (clang for wasm32 with
# wasi-libc) and wabt (wasm2c).
#   docker build -t civ2-dev-base tools/docker && docker build -t civ2-dev tools/docker-ext
FROM civ2-dev-base
USER root
RUN apt-get update && apt-get install -y --no-install-recommends gcc-mingw-w64-x86-64-win32 libsdl2-dev gdb gcc-multilib \
        libsdl2-dev:i386 curl ca-certificates \
    && rm -rf /var/lib/apt/lists/* /usr/share/doc
RUN curl -fsSL https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-25/wasi-sdk-25.0-x86_64-linux.tar.gz \
        | tar xz -C /opt && ln -s /opt/wasi-sdk-25.0-x86_64-linux /opt/wasi-sdk \
    && curl -fsSL https://github.com/WebAssembly/wabt/releases/download/1.0.41/wabt-1.0.41-linux-x64.tar.gz \
        | tar xz -C /opt && ln -s /opt/wabt-1.0.41 /opt/wabt
ENV PATH="/opt/wabt/bin:${PATH}"
USER dev
