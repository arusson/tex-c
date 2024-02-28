# Section 1336

```c << Last-minute procedures >>+=
#ifdef INIT
// initialize all the primitives
void init_prim() {
    no_new_control_sequence = false;

    // << Put each of TeX's primitives into the hash table >>
    
    no_new_control_sequence = true;
}
#endif
```
