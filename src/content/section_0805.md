# Section 805

```c << Set the glue in all the unset boxes of the current list >>=
q = link(head);
s = head;
while (q != null) {
    if (!is_char_node(q)) {
        if (type(q) == UNSET_NODE) {
            // << Set the unset box |q| and the unset boxes in it >>
        }
        else if (type(q) == RULE_NODE) {
            // << Make the running dimensions in rule |q| extend to the boundaries of the alignment >>
        }
    }
    s = q;
    q = link(q);
}
```
