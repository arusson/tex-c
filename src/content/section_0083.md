# Section 83

```c << Get user's advice and |return| >>=
while(true) {
    if (interaction != ERROR_STOP_MODE) {
        return;
    }
    clear_for_error_prompt();
    prompt_input("? ");
    if (last == first) {
        return;
    }
    c = buffer[first];
    if (c >= 'a') {
        c += 'A' - 'a'; // onvert to uppercase.
    }
    // << Interpret code |c| and |return| if done >>
}
```
