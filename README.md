
# Fuzzy Search

Experiments in fuzzy-searching, edit distances and related fields.

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

### Prototype

```c
int levenshtein(const char *s1, int s1_len, const char *s2, int s2_len, int max_k);
```

If you specify `-1` for the string lengths, `strlen()` will be called internally.

Specify `-1` for `max_k` if you want the true distance returned in every case.

A buffer the length of the longest input string is allocated on the stack.

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

# Build status #

N/A
