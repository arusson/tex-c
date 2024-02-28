# Section 601

A mild optimization of the output is performed by the *dvi_pop* routine, which issues a *POP* unless it is possible to cancel a *'PUSH* *POP'* pair.
The parameter to *dvi_pop* is the byte address following the old *PUSH* that matches the new *POP*.

```c dvi.c
void dvi_pop(int l) {
    if (l == dvi_offset + dvi_ptr && dvi_ptr > 0) {
        decr(dvi_ptr);
    }
    else {
        dvi_out(POP);
    }
}
```
