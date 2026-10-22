CC = i686-w64-mingw32-gcc
CFLAGS = -O1 -Wall -Wno-unused -fno-omit-frame-pointer
OBJS = main.o maplog.o crash.o replay.o compat.o xdaemon_proxy.o determinism.o recon.o gditrace.o apitrace.o proctrace.o stackprobe.o

XDaemon.dll: $(OBJS) xdaemon.def
	$(CC) -shared -o $@ $(OBJS) xdaemon.def -static-libgcc -Wl,--enable-stdcall-fixup -lwinmm -lgdi32 -luser32 -lcomdlg32

clean:
	rm -f *.o XDaemon.dll
