# Section 515

Here now is the first of the system-dependent routines for file name scanning.

```c parser/filenames.c
// << Start file |filenames.c| >>

void begin_name() {
    area_delimiter = 0;
    ext_delimiter = 0;
}
```
