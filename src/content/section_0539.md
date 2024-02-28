# Section 539: Font metric data

TeX gets its knowledge about fonts from font metric files, also called `TFM` files; the '`T`' in '`TFM`' stands for $\TeX$, but other programs know about them too.

The information in a `TFM` file appears in a sequence of 8-bit bytes.
Since the number of bytes is always a multiple of 4, we could also regard the file as a sequence of 32-bit words, but $\TeX$ uses the byte interpretation.
The format of `TFM` files was designed by Lyle Ramshaw in 1980.
The intent is to convey a lot of different kinds of information in a compact but useful form.

```c << Global variables >>+=
byte_file tfm_file;
```
