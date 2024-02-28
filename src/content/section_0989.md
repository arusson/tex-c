# Section 989

The global variable *output_active* is true during the time the user's output routine is driving $\TeX$.

```c << Global variables >>+=
bool output_active; // are we in the midst of an output routine?
```
