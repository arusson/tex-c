# Section 292

The procedure *show_token_list*, which prints a symbolic form of the token list that starts at a given node *p*, illustrates these conventions.
The token list being displayed should not begin with a reference count.
However, the procedure is intended to be robust, so that if the memory links are awry or if *p* is not really a pointer to a token list, nothing catastrophic will happen.

An additional parameter *q* is also given; this parameter is either null or it points to a node in the token list where a certain magic computation takes place that will be explained later.
(Basically, *q* is non-null when we are printing the two-line context information at the time of an error message; *q* marks the place corresponding to where the second line should begin.)

For example, if *p* points to the node containing the first `a` in the token list above, then *show_token_list* will print the string
<div align="center">

'`a#1#2 \b ->#1\-a ##1#2 #2`';
</div>

and if *q* points to the node containing the second `a`, the magic computation will be performed just before the second `a` is printed.

The generation will stop, and '`\ETC.`' will be printed, if the length of printing exceeds a given limit&nbsp;*l*.
Anomalous entries are printed in the form of control sequences that are not followed by a blank space, e.g., '`\BAD.`';
this cannot be confused with actual control sequences because a real control sequence named `BAD` would come out '`\BAD `'.

```c io/display_tokens.c
// << Start file |display_tokens.c| >>

void show_token_list(int p, int q, int l) {
    int m, c;             // pieces of a token
    ASCII_code match_chr; // character used in a '|MATCH|'
    ASCII_code n;         // the highest parameter number, as an ASCII digit}
    match_chr = '#';
    n = '0';
    tally = 0;
    while (p != null && tally < l) {
        if (p == q) {
            // << Do magic computation >>
        }
        // << Display token |p|, and |return| if there are problems >>
        p = link(p);
    }
    if (p != null) {
        print_esc("ETC.");
    }
}
```
