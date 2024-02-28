# Section 312

```c << Display the current context >>=
if (base_ptr == input_ptr
    || state != TOKEN_LIST
    || token_type != BACKED_UP
    || loc != null)
{
    // we omit backed-up token lists that have already been read
    tally = 0; // get ready to count characters
    old_setting = selector;
    if (state != TOKEN_LIST) {
        // << Print location of current line >>
        // << Pseudoprint the line >>
    }
    else {
        // << Print type of token list >>
        // << Pseudoprint the token list >>
    }
    selector = old_setting; // stop pseudoprinting
    // << Print two lines using the tricky pseudoprinted information >>
    incr(nn);
}
```
