# Section 56

Macro abbreviations for output to the terminal and to the log file are defined here for convenience.
Some systems need special conventions for terminal output, and it is possible to adhere to those conventions by changing *wterm*, *wterm_ln*, and *wterm_cr* in this section.

```c include/io.h
#define wterm(X, ...)       printf(X, ##__VA_ARGS__)
#define wterm_char(X)       printf("%c", (X))
#define wterm_ln(X, ...)    printf(X"\n", ##__VA_ARGS__)
#define wterm_cr            printf("\n")
#define wlog(X, ...)        fprintf(log_file, X, ##__VA_ARGS__)
#define wlog_char(X)        fprintf(log_file, "%c", (X))
#define wlog_ln(X, ...)     fprintf(log_file, X"\n", ##__VA_ARGS__)
#define wlog_cr             fprintf(log_file, "\n")

#define write_ln(F, X, ...) fprintf((F), X"\n", ##__VA_ARGS__)
#define write_char(F, X)    fprintf((F), "%c", (X))
#define write_byte(F, X)    fputc((X), (F))
```
