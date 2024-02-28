# Section 960

Now let's go back to the easier problem, of building the linked trie.
When `INITEX` has scanned the '`\patterns`' control sequence, it calls on *new_patterns* to do the right thing.

```c << Declare procedures for preprocessing hyphenation patterns >>+=
// initializes the hyphenation pattern data
void new_patterns() {
    int k, l;          // indices into |hc| and |hyf|; not always in |small_number| range
    bool digit_sensed; // should the next digit be treated as a letter?
    quarterword v;     // trie op code
    int p, q;          // nodes of trie traversed during insertion
    bool first_child;  // is |p == trie_l[q]|?
    ASCII_code c;      // character being inserted
    
    if (trie_not_ready) {
        set_cur_lang;
        scan_left_brace(); // a left brace must follow \patterns
        // << Enter all of the patterns into a linked trie, until coming to a right brace >>
    }
    else {
        print_err("Too late for ");
        print_esc("patterns");
        help1("All patterns must be given before typesetting begins.");
        error();
        link(GARBAGE) = scan_toks(false, false);
        flush_list(def_ref);
    }
}
```
