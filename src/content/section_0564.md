# Section 564

Note: A malformed `TFM` file might be shorter than it claims to be;
thus *eof(tfm_file)* might be true when *read_font_info* refers to *tfm_file↑* or when it says *get(tfm_file)*.
If such circumstances cause system error messages, you will have to defeat them somehow, for example by defining *fget* to be '**begin** *get(tfm_file)*; *if (eof(tfm_file))* **then** *abort*; **end**'.

> ![NOTE]
> *fget* is implemented with the *fgetc* function.
> An error occurs if the end of file is reached.

```c include/font_metric.h
#define fget(X)                \
    do {                       \
        (X) = fgetc(tfm_file); \
        if (feof(tfm_file)) {  \
            abort;             \
        }                      \
    } while (0)

#define read_sixteen(X) \
    fget(temp);         \
    if (temp > 127) {   \
        abort;          \
    }                   \
    fget((X));          \
    (X) += temp*256

#define store_four_quarters(X) \
    fget(a);                   \
    qqqq_b0(qw) = a;           \
    fget(b);                   \
    qqqq_b1(qw) = b;           \
    fget(c);                   \
    qqqq_b2(qw) = c;           \
    fget(d);                   \
    qqqq_b3(qw) = d;           \
    (X) = qw
```
