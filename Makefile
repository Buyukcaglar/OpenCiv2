# Civilization II reconstruction — common entry points.  Everything runs in
# Docker (tools/dk); see README.md.

DK      = tools/dk
SEED   ?= 7
SCRIPT ?= harness/scripts/newgame.txt
NAME   := $(basename $(notdir $(SCRIPT)))

.PHONY: images hook gen build wipe standalone suite abi analysis ref run compare bisect native port native-suite clean

images:                       ## build the Docker images (wine/mingw/python/SDL2/wasi-sdk; Ghidra)
	docker build -t civ2-dev-base tools/docker
	docker build -t civ2-dev tools/docker-ext
	docker build -t civ2-ghidra tools/ghidra-docker

native:                       ## build/civ2-linux32: the native SDL2 build (32-bit Linux, in Docker)
	$(DK) python3 tools/build_native.py --target linux32

port:                         ## build/civ2-port: the portable native build (in Docker; on a Mac run tools/build_port.py directly)
	$(DK) python3 tools/build_port.py

native-suite:                 ## run every scenario on a native build (EXE=civ2-port or civ2-linux32) against the Wine recordings
	$(DK) sh -c "EXE=$(or $(EXE),civ2-port) sh harness/native_suite.sh"

hook:                         ## proxy XDaemon.dll: seed control, rand trace, replay, crash log
	$(DK) make -C hook

gen:                          ## regenerate src/auto from the Ghidra export and build
	$(DK) sh tools/autoconvert.sh

build:                        ## compile src/ and graft it onto civ2.exe -> build/civ2_recon.exe
	$(DK) python3 tools/build_recon.py

wipe:                         ## like build, but overwrite all original code with int3 (proves none of it runs)
	$(DK) python3 tools/build_recon.py --patch-only --wipe

standalone: build             ## build/civ2.exe written from source + data/image only (no original civ2.exe)
	$(DK) python3 tools/build_standalone.py

suite:                        ## run every scenario and compare against the original (RECON_EXE=... to pick a build)
	$(DK) sh -c "RECON_EXE=$(RECON_EXE) sh harness/suite.sh"

abi:                          ## check every reconstructed function pops the same stack bytes
	$(DK) python3 tools/check_abi.py

analysis:                     ## full re-analysis: machine-code facts -> Ghidra -> export -> gen -> build
	tools/pipeline.sh

ref:                          ## record the original game on SCRIPT (deterministic replay)
	$(DK) python3 harness/run.py --build orig --seed $(SEED) --script $(SCRIPT) --out run/ref-$(NAME)

run:                          ## run the reconstruction on SCRIPT
	$(DK) python3 harness/run.py --build recon --seed $(SEED) --script $(SCRIPT) --out run/recon-$(NAME)

compare: run                  ## compare reconstruction against the reference, write an HTML report
	$(DK) python3 harness/compare.py run/ref-$(NAME) run/recon-$(NAME) --report run/report-$(NAME)

bisect:                       ## find reconstructed functions that make SCRIPT differ from the reference
	$(DK) python3 tools/bisect_recon.py --script $(SCRIPT) --seed $(SEED) --crash --ref run/ref-$(NAME)

clean:
	rm -rf build run
