# Growl — OWL 2 RL Reasoner
# Build from transpiled C sources — no SLOP toolchain required.

CC      ?= cc
GROWL_VERSION ?= 0.1.0
CFLAGS  ?= -O2 -Wall -Wno-unused-function -Wno-unused-variable \
           -Wno-return-type -Wno-pointer-sign \
           -DSLOP_ARENA_NO_CAP \
           -DGROWL_VERSION=\"$(GROWL_VERSION)\"
LDFLAGS ?= -lpthread
AR      ?= ar

CSRC    = csrc/src
RUNTIME = csrc/runtime
BIN     = build
OBJ     = $(BIN)/obj

ALL_SRCS    := $(wildcard $(CSRC)/*.c)
SHARED_SRCS := $(filter-out $(CSRC)/slop_main.c $(CSRC)/slop_test_cli.c, $(ALL_SRCS))
SHARED_OBJS := $(patsubst $(CSRC)/%.c,$(OBJ)/%.o,$(SHARED_SRCS))

.PHONY: all cli lib test benchmark conformance reference clean release dist csrc slop-build \
       crate-vendor crate-build crate-test crate-publish

PLATFORM ?= unknown

all: cli

$(BIN):
	mkdir -p $(BIN)

$(OBJ):
	mkdir -p $(OBJ)

$(OBJ)/%.o: $(CSRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -I$(RUNTIME) -I$(CSRC) -c $< -o $@

lib: $(BIN)/libgrowl.a

$(BIN)/libgrowl.a: $(SHARED_OBJS) | $(BIN)
	$(AR) rcs $@ $^
	@echo "  -> $@"

cli: $(BIN)
	@echo "Building growl..."
	$(CC) $(CFLAGS) -I$(RUNTIME) -I$(CSRC) $(SHARED_SRCS) $(CSRC)/slop_main.c $(LDFLAGS) -o $(BIN)/growl
	@echo "  -> $(BIN)/growl"

test: $(BIN)
	@echo "Building tests..."
	$(CC) $(CFLAGS) -I$(RUNTIME) -I$(CSRC) $(SHARED_SRCS) $(CSRC)/slop_test_cli.c $(LDFLAGS) -o $(BIN)/growl-test
	@echo "Running tests..."
	cd cli/tests && ../../$(BIN)/growl-test

benchmark: cli
	@echo "Running benchmarks..."
	cd cli/tests && GROWL=../../$(BIN)/growl ./benchmark.sh

conformance: release
	cd cli/tests && uv run --with pytest --with rdflib pytest test_conformance.py test_interactions.py -v

reference: release
	cd cli/tests && uv run --with pytest --with rdflib --with owlrl pytest test_reference.py -v

clean:
	rm -rf $(BIN) dist

release: CFLAGS = -O3 -Wall -Wno-unused-function -Wno-unused-variable \
                  -Wno-return-type -Wno-pointer-sign -DNDEBUG \
                  -DSLOP_ARENA_NO_CAP \
                  -DGROWL_VERSION=\"$(GROWL_VERSION)\"
release: clean cli
	@echo "Release binary built: $(BIN)/growl"

slop-build:
	slop build
	@mkdir -p include
	cp build/growl.h include/growl.h
	@echo "  -> include/growl.h updated"

csrc:
	./csrc/update_bootstrap.sh

dist:
	rm -rf dist
	mkdir -p dist/include dist/lib
	cp include/growl.h dist/include/
	cp csrc/runtime/slop_runtime.h dist/include/
	cp $(BIN)/libgrowl.a dist/lib/
	cd dist && zip -r ../libgrowl-$(PLATFORM).zip include/ lib/
	@echo "  -> libgrowl-$(PLATFORM).zip"

# --- Rust crate targets ---

crate-vendor:
	@mkdir -p rust/csrc/src rust/csrc/runtime
	cp csrc/src/*.c csrc/src/*.h rust/csrc/src/
	cp csrc/runtime/slop_runtime.h rust/csrc/runtime/
	cp LICENSE rust/LICENSE
	@echo "  -> rust/csrc/ vendored"

crate-build: crate-vendor
	cd rust && cargo build

crate-test: crate-vendor
	cd rust && cargo test

crate-publish: crate-vendor
	cd rust && cargo publish --dry-run --allow-dirty
