# Section 625

```c include/constants.h
#define BILLION 1000000000.0
```

```c include/dvi.h
#define vet_glue(X)                      \
    do {                                 \
        glue_temp = (X);                 \
        if (glue_temp > BILLION) {       \
            glue_temp = BILLION;         \
        }                                \
        else if (glue_temp < -BILLION) { \
            glue_temp = -BILLION;        \
        }                                \
    } while (0)
```

```c << Move right or output leaders >>=
g = glue_ptr(p);
rule_wd = width(g) - cur_g;
if (g_sign != NORMAL) {
    if (g_sign == STRETCHING) {
        if (stretch_order(g) == g_order) {
            cur_glue += stretch(g);
            vet_glue(glue_set(this_box)*cur_glue);
            cur_g = (scaled)round(glue_temp);
        }
    }
    else if (shrink_order(g) == g_order) {
        cur_glue -= shrink(g);
        vet_glue(glue_set(this_box)*cur_glue);
        cur_g = (scaled)round(glue_temp);
    }
}
rule_wd += cur_g;
if (subtype(p) >= A_LEADERS) {
    // << Output leaders in an hlist, |goto fin_rule| if a rule or to |next_p| if done >>
}
goto move_past;
```
