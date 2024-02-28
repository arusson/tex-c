# Section 597

The actual output of *dvi_buf[a .. b]* to *dvi_file* is performed by calling *write_dvi(a, b)*.
For best results, this procedure should be optimized to run as fast as possible on each particular system, since   is part of $\TeX$'s inner loop.
It is safe to assume that *a* and *b + 1* will both be multiples of 4 when *write_dvi(a, b)* is called; therefore it is possible on many machines to use efficient methods to pack four bytes per word and to output an array of words with one system call.

```c dvi.c
// << Start file |dvi.c| >>

void write_dvi(int a, int b) {
    int k;
    for(k = a; k <= b; k++) {
        write_byte(dvi_file, dvi_buf[k]);
    }
}
```
