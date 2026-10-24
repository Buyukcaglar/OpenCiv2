# Civilization II reconstruction — common entry points.  Everything runs in
# Docker (tools/dk); see README.md.  (src/auto is edited directly: the
# Ghidra regeneration is retired; tools/gen_c.py refuses without
# CIV2_REGENERATE=1.  The Windows graft build is retired: tag pre-step5.)

DK      = tools/dk
SEED   ?= 7
SCRIPT ?= harness/scripts/newgame.txt
NAME   := $(basename $(notdir $(SCRIPT)))

.PHONY: images hook ref native port native-suite clean

images:                       ## build the Docker images (wine/mingw/python/SDL2/wasi-sdk; Ghidra)
	docker build -t civ2-dev-base tools/docker
	docker build -t civ2-dev tools/docker-ext
	docker build -t civ2-ghidra tools/ghidra-docker

native:                       ## build/civ2-linux32: the native SDL2 build (32-bit Linux, in Docker)
	$(DK) python3 tools/build_native.py --target linux32

port:                         ## build/OpenCiv2: the portable native build (in Docker; on a Mac run tools/build_port.py directly)
	$(DK) python3 tools/build_port.py

native-suite:                 ## run every scenario on a native build (EXE=OpenCiv2 or civ2-linux32) against the Wine recordings
	$(DK) sh -c "EXE=$(or $(EXE),OpenCiv2) sh harness/native_suite.sh"

hook:                         ## proxy XDaemon.dll: seed control, rand trace, replay, crash log
	$(DK) make -C hook






ref:                          ## record the original game on SCRIPT (deterministic replay)
	$(DK) python3 harness/run.py --build orig --seed $(SEED) --script $(SCRIPT) --out run/ref-$(NAME)




clean:
	rm -rf build run
