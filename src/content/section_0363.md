# Section 363

If the user has set the *pausing* parameter to some positive value, and if nonstop mode has not been selected, each line of input is displayed on the terminal and the transcript file, followed by '`=>`'.
$\TeX$ waits for a response.
If the response is simply *CARRIAGE_RETURN*, the line is accepted as it stands, otherwise the line typed is used instead of the line in the file.

```c parser/get_next_token.c
void firm_up_the_line() {
    int k; // an index into |buffer|
    limit = last;
    if (pausing > 0 && interaction > NONSTOP_MODE) {
        print_ln();
        if (start < limit) {
            for(k = start; k < limit; k++) {
                print_strnumber(buffer[k]);
            }
        }
        first = limit;
        prompt_input("=>"); // wait for user response
        if (last > first) {
            for(k = first; k < last; k++) {
                // move line down in buffer
                buffer[k + start - first] = buffer[k];
            }
            limit = start + last - first;
        }
    }
}
```
