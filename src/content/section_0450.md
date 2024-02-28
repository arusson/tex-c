# Section 450

```c << Local variables for dimension calculations >>=
int num, denom;   // conversion ratio for the scanned units
int k, kk;        // number of digits in a decimal fraction
pointer p, q;     // top of decimal digit stack
scaled v;         // an internal dimension
int save_cur_val; // temporary storage of |cur_val|
```
