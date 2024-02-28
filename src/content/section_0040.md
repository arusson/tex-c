# Section 40

Several of the elementary string operations are performed using `WEB` macros instead of Pascal procedures, because many of the operations are done quite frequently and we want to avoid the overhead of procedure calls.
For example, here is a simple macro that computes the length of a string.

```c include/strings.h
// << Start file |strings.h| >>

#define length(X) (str_start[(X) + 1] - str_start[(X)]) // the number of characters in string number X
```