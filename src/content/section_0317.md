# Section 317

And the following code uses the information after it has been gathered.

```c << Print two lines using the tricky pseudoprinted information >>= 
if (trick_count == 1000000) {
    // |set_trick_count| must be performed
    set_trick_count;
}
if (tally < trick_count) {
    m = tally - first_count;
}
else {
    // context on line 2
    m = trick_count - first_count;
}
if (l + first_count <= HALF_ERROR_LINE) {
    p = 0;
    n = l + first_count;
}
else {
    print("...");
    p = l + first_count - HALF_ERROR_LINE + 3;
    n = HALF_ERROR_LINE;
}
for(q = p; q < first_count; q++) {
    print_char(trick_buf[q % ERROR_LINE]);
}
print_ln();
for(q = 1; q <= n; q++) {
    print_char(' '); // print |n| spaces to begin line 2
}
if (m + n <= ERROR_LINE) {
    p = first_count + m;
}
else {
    p = first_count + (ERROR_LINE - n - 3);
}
for(q = first_count; q < p; q++) {
    print_char(trick_buf[q % ERROR_LINE]);
}
if (m + n > ERROR_LINE) {
    print("...");
}
```
