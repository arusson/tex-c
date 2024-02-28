# Section 1351

```c << Implement \openout >>=
new_write_whatsit(OPEN_NODE_SIZE);
scan_optional_equals();
scan_file_name();
open_name(tail) = cur_name;
open_area(tail) = cur_area;
open_ext(tail) = cur_ext;
```
