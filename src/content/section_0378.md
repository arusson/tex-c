# Section 378

```c << Initiate or terminate input from a file >>=
if (cur_chr > 0) {
    force_eof = true;
}
else if (name_in_progress) {
    insert_relax();
}
else {
    start_input();
}
```
