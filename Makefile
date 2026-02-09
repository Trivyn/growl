# Growl — OWL 2 RL Reasoner
# Build from transpiled C sources — no SLOP toolchain required.

CC      ?= cc
CFLAGS  ?= -O2 -Wall -Wno-unused-function -Wno-unused-variable \
           -Wno-return-type -Wno-pointer-sign \
           -DSLOP_ARENA_NO_CAP
LDFLAGS ?= -lpthread
AR      ?= ar

CSRC    = csrc/src
RUNTIME = csrc/runtime
BIN     = build
OBJ     = $(BIN)/obj

ALL_SRCS    := $(wildcard $(CSRC)/*.c)
SHARED_SRCS := $(filter-out $(CSRC)/slop_main.c $(CSRC)/slop_test_cli.c, $(ALL_SRCS))
SHARED_OBJS := $(patsubst $(CSRC)/%.c,$(OBJ)/%.o,$(SHARED_SRCS))

.PHONY: all cli lib test benchmark clean release

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

clean:
	rm -rf $(BIN)

release: CFLAGS = -O3 -Wall -Wno-unused-function -Wno-unused-variable \
                  -Wno-return-type -Wno-pointer-sign -DNDEBUG \
                  -DSLOP_ARENA_NO_CAP
release: clean cli
	@echo "Release binary built: $(BIN)/growl"
