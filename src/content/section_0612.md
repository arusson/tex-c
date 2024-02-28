# Section 612

We might find a valid hit in a *Y* or *Z* byte that is already gone from the buffer.
But we can't change bytes that are gone forever; "the moving finger writes, $\ldots$".

```c << Consider a node with matching width; |goto found| if it's a hit >>=
switch (mstate + info(p)) {
case NONE_SEEN + YZ_OK:
case NONE_SEEN + Y_OK:
case Z_SEEN + YZ_OK:
case Z_SEEN + Y_OK:
    if (location(p) < dvi_gone) {
        goto not_found;
    }
    else {
        // << Change buffered instruction to |y| or |w| and |goto found| >>
    }
    break;

case NONE_SEEN + Z_OK:
case Y_SEEN + YZ_OK:
case Y_SEEN + Z_OK:
    if (location(p) < dvi_gone) {
        goto not_found;
    }
    else {
        // << Change buffered instruction to |z| or |x| and |goto found| >>
    }
    break;

case NONE_SEEN + Y_HERE:
case NONE_SEEN + Z_HERE:
case Y_SEEN + Z_HERE:
case Z_SEEN + Y_HERE:
    goto found;

default:
    do_nothing;
}
```
