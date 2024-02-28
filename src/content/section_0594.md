# Section 594

The `DVI` bytes are output to a buffer instead of being written directly to the output file.
This makes it possible to reduce the overhead of subroutine calls, thereby measurably speeding up the computation, since output of `DVI` bytes is part of $\TeX$'s inner loop.
And it has another advantage as well, since we can change instructions in the buffer in order to make the output more compact.
For example, a *'DOWN2'* command can be changed to a *'Y2'*, thereby making a subsequent *'Y0'* command possible, saving two bytes.

The output buffer is divided into two parts of equal size; the bytes found in *dvi_buf[0 .. half_buf − 1]* constitute the first half, and those in *dvi_buf[half_buf .. DVI_BUF_SIZE − 1]* constitute the second.
The global variable *dvi_ptr* points to the position that will receive the next output byte.
When *dvi_ptr* reaches *dvi_limit*, which is always equal to one of the two values *half_buf* or *DVI_BUF_SIZE*, the half buffer that is about to be invaded next is sent to the output and *dvi_limit* is changed to its other value.
Thus, there is always at least a half buffer's worth of information present, except at the very beginning of the job.

Bytes of the `DVI` file are numbered sequentially starting with 0;
the next byte to be generated will be number *dvi_offset + dvi_ptr*.
A byte is present in the buffer only if its number is  $\geq$ *dvi_gone*.
