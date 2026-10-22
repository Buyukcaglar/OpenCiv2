# Debug image: docker build -t civ2-dbg tools/docker-dbg
FROM civ2-dev
USER root
RUN apt-get update && apt-get install -y --no-install-recommends valgrind gdb libc6-dbg:i386 clang lld && rm -rf /var/lib/apt/lists/*
