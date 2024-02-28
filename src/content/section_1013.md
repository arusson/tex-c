# Section 1013

```c << Set the value of |output_penalty| >>=
if (type(best_page_break) == PENALTY_NODE) {
    geq_word_define(INT_BASE + OUTPUT_PENALTY_CODE, penalty(best_page_break));
    penalty(best_page_break) = INF_PENALTY;
}
else {
    geq_word_define(INT_BASE + OUTPUT_PENALTY_CODE, INF_PENALTY);
}
```
