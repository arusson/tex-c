# Section 475

```c << Express shock at the missing left brace; |goto found| >>=
print_err("Missing { inserted");
incr(align_state);
help2("Where was the left brace? You said something like `\\def\\a}',")
    ("which I'm going to interpret as `\\def\\a{}'.");
error();
goto found;
```
