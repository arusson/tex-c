# Section 914

In this repeat loop we will insert another discretionary if *hyf[j − 1]* is odd, when both branches of the previous discretionary end at position *j − 1*.
Strictly speaking, we aren't justified in doing this, because we don't know that a hyphen after *j − 1* is truly independent of those branches.
But in almost all applications we would rather not lose a potentially valuable hyphenation
point.
(Consider the word 'difficult', where the letter 'c' is in position *j*.)

```c include/breaker.h
#define advance_major_tail major_tail = link(major_tail); incr(r_count)
```

```c << Create and append a discretionary node as an alternative to the unhyphenated word, and continue to develop both branches until they become equivalent >>=
do {
    r = get_node(SMALL_NODE_SIZE);
    link(r) = link(HOLD_HEAD);
    type(r) = DISC_NODE;
    major_tail = r;
    r_count = 0;
    while (link(major_tail) > null) {
        advance_major_tail;
    }
    i = hyphen_passed;
    hyf[i] = 0;
    // << Put the characters |hu[l..i]| and a hyphen into |pre_break(r)| >>
    // << Put the characters |hu[i + 1..]| into |post_break(r)|, appending to this list and to |major_tail| until synchronization has been achieved >>
    // << Move pointer |s| to the end of the current list, and set |replace_count(r)| appropriately >>
    hyphen_passed = j - 1;
    link(HOLD_HEAD) = null;
} while (odd(hyf[j - 1]));
```
