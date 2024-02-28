# Section 946

Before we forget how to initialize the data structures that have been mentioned so far, let's write down the code that gets them started.

```c << Initialize table entries (done by INITEX only) >>+=
for(k = -TRIE_OP_SIZE; k <= TRIE_OP_SIZE; k++) {
    trie_op_hash[k] = 0;
}
for(k = 0; k <= 255; k++) {
    trie_used[k] = MIN_QUARTERWORD;
}
trie_op_ptr = 0;
```
