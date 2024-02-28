# Section 1378

```c << Finish the extensions >>=
for(k = 0; k <= 15; k++) {
    if (write_open[k]) {
        a_close(write_file[k]);
    }
}
```
