# Section 100

Here is a routine that calculates half of an integer, using an unambiguous convention with respect to signed odd numbers.

```c arithmetic.c
// << Start file |arithmetic.c| >>

int half(int x) {
    int res;
    if (odd(x)) {
        res = (x + 1) / 2;
    }
    else {
        res = x / 2;
    }
    return res;
}
```
