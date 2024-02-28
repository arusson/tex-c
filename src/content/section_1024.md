# Section 1024

```c << Explain that too many dead cycles have occurred in a row >>=
print_err("Output loop---");
print_int(dead_cycles);
print(" consecutive dead cycles");
help3("I've concluded that your \\output is awry; it never does a")
    ("\\shipout, so I'm shipping \\box255 out myself. Next time")
    ("increase \\maxdeadcycles if you want me to be more patient!");
error();
```
