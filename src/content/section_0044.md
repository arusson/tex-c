# Section 44

To destroy the most recently made string, we say *flush_string*.

```c include/strings.h
#define flush_string decr(str_ptr); pool_ptr = str_start[str_ptr]
```