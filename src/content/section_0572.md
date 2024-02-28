# Section 572

```c << Replace |z| by |z'| and compute \alpha, \beta >>=
alpha = 16;
while (z >= 0x800000) {
    z /= 2;
    alpha += alpha;
}
beta = 256 / alpha;
alpha *= z;
```
