# Section 334

```c << Put each of TeX's primitives into the hash table >>+=
primitive("par", PAR_END, 256); // cf. |scan_file_name|
par_loc = cur_val;
par_token = CS_TOKEN_FLAG + par_loc;
```
