# Section 338

```c << Tell the user what has run away and try to recover >>=
runaway(); // print a definition, argument, or preamble
if (cur_cs == 0) {
    print_err("File ended");
}
else {
    cur_cs = 0;
    print_err("Forbidden control sequence found");
}
print(" while scanning ");
// << Print either 'definition' or 'use' or 'preamble' or 'text', and insert tokens that should lead to recovery >>
print(" of ");
sprint_cs(warning_index);
help4("I suspect you have forgotten a `}', causing me")
    ("to read past where you wanted me to stop.")
    ("I'll try to recover; but if the error is serious,")
    ("you'd better type `E' or `X' now and fix your file.");
error();
```
