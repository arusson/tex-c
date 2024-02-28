# Section 600

The *dvi_four* procedure outputs four bytes in two's complement notation, without risking arithmetic overflow.

```c dvi.c
void dvi_four(int x) {
    if (x >= 0) {
        dvi_out(x / 0x1000000);
    }
    else {
        x += 0x40000000;
        x += 0x40000000;
        dvi_out(x / 0x1000000 + 128);
    }
    x %= 0x1000000;
    dvi_out(x / 0x10000);
    x %= 0x10000;
    dvi_out(x / 256);
    dvi_out(x % 256);
}
```
