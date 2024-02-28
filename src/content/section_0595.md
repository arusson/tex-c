# Section 595

Some systems may find it more efficient to make *dvi_buf* a **packed** array, since output of four bytes at once may be facilitated.

```c << Global variables >>+=
eight_bits dvi_buf[DVI_BUF_SIZE + 1]; // buffer for `DVI` output
int half_buf;   // half of |DVI_BUF_SIZE|
int dvi_limit;  // end of the current half buffer
int dvi_ptr;    // the next available buffer address
int dvi_offset; // |DVI_BUF_SIZE| times the number of times the output buffer has been fully emptied
int dvi_gone;   // the number of bytes already output to |dvi_file|
```
