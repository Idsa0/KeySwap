.PHONY: all clean bin_dir KeySwap

ifeq ($(OS),Windows_NT)
    RM = if exist bin\KeySwap.exe del /Q bin\KeySwap.exe
    MKDIR = if not exist bin mkdir bin
    SEP = \\
else
    RM = rm -f
    MKDIR = mkdir -p bin
    SEP = /
endif

all: bin_dir KeySwap

bin_dir:
	@$(MKDIR)

KeySwap: clipboard.c keyboard.c main.c
	@gcc -O3 clipboard.c keyboard.c main.c -o bin$(SEP)KeySwap.exe

clean:
	@$(RM)
