# Section 205

```c << Make a copy of node |p| in node |r| >>=
words = 1; // this setting occurs in more branches than any other
if (is_char_node(p)) {
    r = get_avail();
}
else {
    // << Case statement to copy different types and set |words| to the number of initial words not yet copied >>
}
while (words > 0) {
  decr(words);
  mem[r + words] = mem[p + words];
}
```
