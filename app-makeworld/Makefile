UNIKRAFT_ROOT?=$(shell realpath ../unikraft)
DEPS= \
    libs/musl \
    libs/libunwind \
    libs/compiler-rt \
    libs/libcxxabi \
    libs/libcxx \
    # this line intentionally left blank
BUILD_LIBS=$(subst $(eval) ,:,$(patsubst %,$(UNIKRAFT_ROOT)/%,$(DEPS)))
UNIKRAFT_VERBS=menuconfig nconfig fetch prepare preprocess properclean help

kernel=build/app-makeworld_kvm-x86_64

all: fetch prepare build

uk:
	@make -C $(UNIKRAFT_ROOT)/unikraft A=$(PWD) L=$(BUILD_LIBS) $(VERB)

$(UNIKRAFT_VERBS):
	@make -C $(UNIKRAFT_ROOT)/unikraft A=$(PWD) L=$(BUILD_LIBS) $@

build:
	@make -C $(UNIKRAFT_ROOT)/unikraft A=$(PWD) L=$(BUILD_LIBS) -j$(JOBS)

run:
	sudo qemu-system-x86_64 -nographic -device isa-debug-exit -smp 4 -m 1024M -machine pc,accel=kvm -cpu host,migratable=no,+invtsc -kernel $(kernel) -append "$(append)"

clean:
	@make -C $(UNIKRAFT_ROOT)/unikraft A=$(PWD) L=$(BUILD_LIBS) clean

.PHONY: all $(UNIKRAFT_VERBS) build run clean
