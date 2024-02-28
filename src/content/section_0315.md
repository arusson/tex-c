# Section 315

Here it is necessary to explain a little trick.
We don't want to store a long string that corresponds to a token list, because that string might take up lots of memory; and we are printing during a time when an error message is being given, so we dare not do anything that might overflow one of $\TeX$'s tables.
So 'pseudoprinting' is the answer:
We enter a mode of printing that stores characters into a buffer of length *ERROR_LINE*, where character *k + 1* is placed into *trick_buf[k* **mod** *ERROR_LINE]* if *k* $<$ *trick_count*, otherwise character *k* is dropped.
Initially we set *tally &larr; 0* and *trick_count &larr; 1000000*;
then when we reach the point where transition from line 1 to line 2 should occur, we set *first_count &larr; tally* and *trick_count &larr; max(ERROR_LINE, tally + 1 + ERROR_LINE − HALF_ERROR_LINE)*.
At the end of the pseudoprinting, the values of *first_count*, *tally*, and *trick_count* give us all the information we need to print the two lines, and all of the necessary text is in *trick_buf*.

Namely, let *l* be the length of the descriptive information that appears on the first line.
The length of the context information gathered for that line is *k = first_count*, and the length of the context information gathered for line&nbsp;2 is *m = min(tally, trick_count) − k*.
If *l + k* $\leq$ *h*, where *h = HALF_ERROR_LINE*, we print *trick_buf[0 .. k − 1]* after the descriptive information on line&nbsp;1, and set *n &larr; l + k*; here *n* is the length of line&nbsp;1.
If *l + k* $>$ *h*, some cropping is necessary, so we set *n &larr; h* and print '`...`' followed by 

<div align="center">

*trick_buf[(l + k − h + 3) .. k − 1]*
</div>

where subscripts of *trick_buf* are circular modulo *ERROR_LINE*.
The second line consists of *n*&nbsp;spaces followed by *trick_buf[k .. (k + m − 1)]*, unless *n + m* $>$ *ERROR_LINE*; in the latter case, further cropping is done.
This is easier to program than to explain.

```c << Local variables for formatting calculations >>=
int i;  // index into |buffer|
int j;  // end of current line in |buffer|
int l;  // length of descriptive information on line 1
int m;  // context information gathered for line 2
int n;  // length of line 1
int p;  // starting or ending place in |trick_buf|
int q;  // temporary index
```
