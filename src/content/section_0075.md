# Section 75

$\TeX$ is careful not to call *error* when the print *selector* setting might be unusual.
The only possible values of *selector* at the time of error messages are 

- *NO_PRINT* (when *interaction = BATCH_MODE* and *log_file* not yet open);
- *TERM_ONLY* (when *interaction > BATCH_MODE* and *log_file* not yet open);
- *LOG_ONLY* (when *interaction = BATCH_MODE* and *log_file* is open);
- *TERM_AND_LOG* (when *interaction > BATCH_MODE* and *log_file* is open).

```c << Initialize the print |selector| based on |interaction| >>=
if (interaction == BATCH_MODE) {
    selector = NO_PRINT;
}
else {
    selector = TERM_ONLY;
}
```
