# Section 341

Now we're ready to take the plunge into *get_next* itself.
Parts of this routine are executed more often than any other instructions of $\TeX$.

```c parser/get_next_token.c
// sets |cur_cmd|, |cur_chr|, |cur_cs| to next token
void get_next() {
   // restart:  go here to get the next input token
   // switch:   go here to eat the next character from a file
   // reswitch: go here to digest it again
   // start_cs: go here to start looking for a control sequence
   // found:    go here when a control sequence has been found
   // return    go here when the next input token has been got
    int k;            // an index into |buffer|
    halfword t;       // a token
    int cat;          // |cat_code(cur_chr)|, usually
    ASCII_code c, cc; // constituents of a possible expanded code
    int d;            // number of excess characters in an expanded code
restart:
    cur_cs = 0;
    if (state != TOKEN_LIST) {
        // << Input from external file, |goto restart| if no input found >>
    }
    else {
        // << Input from token list, |goto restart| if end of list or if a parameter needs to be expanded >>=
    }
    // << If an alignment entry has just ended, take appropriate action >>
}
```
