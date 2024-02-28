# Section 944

It's tempting to remove the *overflow* stops in the following procedure;
*new_trie_op* could return *MIN_QUARTERWORD* (thereby simply ignoring part of a hyphenation pattern) instead of aborting the job.
However, that would lead to different hyphenation results on different installations of $\TeX$ using the same patterns.
The *overflow* stops are necessary for portability of patterns.

```c << Declare procedures for preprocessing hyphenation patterns >>=
quarterword new_trie_op(small_number d, small_number n, quarterword v) {
    int h;         // trial hash location
    quarterword u; // trial op code
    int l;         // pointer to stored data
    h = abs(n + 313*d + 361*v + 1009*cur_lang) % (TRIE_OP_SIZE + TRIE_OP_SIZE) - TRIE_OP_SIZE;
    while(true) {
        l = trie_op_hash[h];
        if (l == 0) {
            // empty position found for a new op
            if (trie_op_ptr == TRIE_OP_SIZE) {
                overflow("pattern memory ops", TRIE_OP_SIZE);
            }
            u = trie_used[cur_lang];
            if (u == MAX_QUARTERWORD) {
                overflow("pattern memory ops per language", MAX_QUARTERWORD - MIN_QUARTERWORD);
            }
            incr(trie_op_ptr);
            incr(u);
            trie_used[cur_lang] = u;
            hyf_distance[trie_op_ptr] = d;
            hyf_num[trie_op_ptr] = n;
            hyf_next[trie_op_ptr] = v;
            trie_op_lang[trie_op_ptr] = cur_lang;
            trie_op_hash[h] = trie_op_ptr;
            trie_op_val[trie_op_ptr] = u;
            return u;
        }
        if (hyf_distance[l] == d
            && hyf_num[l] == n
            && hyf_next[l] == v
            && trie_op_lang[l] == cur_lang)
        {
            return trie_op_val[l];
        }
        if (h > -TRIE_OP_SIZE) {
            decr(h);
        }
        else {
            h = TRIE_OP_SIZE;
        }
    }
}
```
