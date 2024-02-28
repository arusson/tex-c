# Section 502

```c << Display the value of |b| >>=
begin_diagnostic();
if (b) {
    print("{true}");
}
else {
    print("{false}");
}
end_diagnostic(false);
```
