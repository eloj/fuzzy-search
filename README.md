
# Fuzzy Search

Experiments in fuzzy-searching, edit distances and related fields. Copy from this
code at your own risk.

*NOTE:* Since this repo is meant for experiments, _I reserve the right to rebase it._

# Building

```bash
$ make
```

## levenshtein.c

Your basic edit distance, with the common optimization to only keep part of
the previous row (or column, depending on world-view) of the matrix,
and supporting a `max_k` to reduce the number of matrix entries that needs
to be calculated when you don't care about the true distance, only whether
it's at least `max_k` or not.

Only supports extended-ASCII (octet) alphabet.

### Prototype

```c
int levenshtein(const char *s1, int s1_len, const char *s2, int s2_len, int max_k);
```

If you specify `-1` for the string lengths, `strlen()` will be called internally.

Specify `-1` for `max_k` if you want the true distance returned in every case.

A buffer proportional to the length of the shortest input string is allocated on the stack,
i.e space is in `O(min(|s1|,|s2|))`.

The function contains a fair amount of pre-checks which sacrifice a little bit of
performance in the common case for robustness.

### Driver example runs

```bash
$ ./levenshtein 1 volvo volvvos
ed('volvo', 'volvvos', 1) at least 1
$ ./levenshtein 2 volvo volvvos
ed('volvo', 'volvvos', 2) at least 2
$ ./levenshtein 3 volvo volvvos
ed('volvo', 'volvvos', 3) = 2
```

## damerau.c

Bog-standard implementation, building the full matrix,
i.e space is in `O(|s1|*|s2|)+|Σ|`

Only supports extended-ASCII (octet) alphabet.

### Prototype

```c
static int damerau_ref(const char *s1, int s1_len, const char *s2, int s2_len);
```

### Driver example runs

```bash
$ ./damerau CA AC
damerau('CA', 'AC') = 1
$ ./damerau AC ABC
damerau('AC', 'ABC') = 1
$ ./damerau CA ABC
damerau('CA', 'ABC') = 2
```

# Build status #

N/A
