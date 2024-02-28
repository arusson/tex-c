# Section 8

This program has two important variations:
(1) There is a long and slow version called `INITEX`, which does the extra calculations needed to initialize $\TeX$'s internal tables;
and (2)&nbsp;there is a shorter and faster production version, which cuts the initialization to a bare minimum.
Parts of the program that are needed in (1) but not in (2) are delimited by the codewords '**init** $\ldots$ **tini**'.

> ![NOTE]
> The specific code for `INITEX` is inside block `#ifdef INIT`.

```c << Initialize whatever TeX might access >>=
// << Set initial values of key variables >>
#ifdef INIT
// << Initialize table entries (done by INITEX only) >>
#endif
``` 
