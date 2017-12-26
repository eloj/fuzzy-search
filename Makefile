OPT:=-O3 -std=c11 -fomit-frame-pointer -fstrict-aliasing -march=native -mtune=native
CFLAGS:=-g -Wall $(OPT)

all: levenshtein damerau

levenshtein: levenshtein.c

damerau: damerau.c

clean:
	rm -f levenshtein core.*
