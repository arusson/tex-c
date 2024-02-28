# Section 531

```c << Scan file name in the buffer >>=
begin_name();
k = first;
while (buffer[k] == ' ' && k < last) {
    incr(k);
}
while(true) {
    if (k == last || !more_name(buffer[k])) {
        break; // Goto done
    }
    incr(k);
}
// done:
end_name();
```
