.PHONY: all clean

# Build configuration (override on the command line if needed)
CC ?= gcc
WINDRES ?= windres
STRIP ?= strip

CFLAGS ?= -O3 -flto -std=gnu17 -Wall -Wextra
LDFLAGS ?= -flto -s -mwindows

OUTDIR := bin
OUT := $(OUTDIR)/KeySwap.exe

SRCS := clipboard.c keyboard.c main.c
# library sources (everything except main)
LIB_SRCS := clipboard.c keyboard.c
LIB_OBJS := $(patsubst %.c,$(OUTDIR)/%.o,$(LIB_SRCS))
# place all intermediate object files in OUTDIR
APP_OBJS := $(LIB_OBJS) $(OUTDIR)/main.o


TEST_OUT := $(OUTDIR)/test_runner.exe
TEST_SRCS := tests/test_runner.c
# put test object in OUTDIR as well
TEST_OBJ := $(OUTDIR)/test_runner.o
LDFLAGS_TEST := -flto -s

RESRC := resources/KeySwap.rc
RESOBJ :=

# point RESOBJ at the object in OUTDIR if the resource exists
ifneq ($(wildcard $(RESRC)),)
RESOBJ := $(OUTDIR)/KeySwap_res.o
else
RESOBJ :=
endif

all: $(OUT)


test: $(OUTDIR) $(TEST_OBJ) $(LIB_OBJS)
	@echo Building test runner
	$(CC) $(CFLAGS) $(TEST_OBJ) $(LIB_OBJS) -o $(TEST_OUT) $(LDFLAGS_TEST)



$(OUT): $(APP_OBJS) $(RESOBJ) | $(OUTDIR)
	@echo Building $@
	$(CC) $(LDFLAGS) $(APP_OBJS) $(RESOBJ) -o $@
	-@$(STRIP) --strip-all $@ 2>/dev/null || true

$(OUTDIR):
	@mkdir -p $(OUTDIR)

$(OUTDIR)/%.o: %.c | $(OUTDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJ): $(TEST_SRCS) | $(OUTDIR)
	$(CC) $(CFLAGS) -I. -c $(TEST_SRCS) -o $(TEST_OBJ)

$(OUTDIR)/KeySwap_res.o: $(RESRC) | $(OUTDIR)
	@echo Compiling resources: $<
	$(WINDRES) $< -O coff -o $@

clean:
	@rm -f $(OUT) $(APP_OBJS) $(RESOBJ) $(TEST_OBJ) $(TEST_OUT)
