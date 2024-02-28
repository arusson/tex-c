# Section 26

Most of what we need to do with respect to input and output can be handled by the I/O facilities that are standard in Pascal, i.e., the routines called *get*, *put*, *eof*, and so on.
But standard Pascal does not allow file variables to be associated with file names that are determined at run time, so it cannot be used to implement $\TeX$; some sort of extension to Pascal's ordinary *reset* and *rewrite* is crucial for our purposes.
We shall assume that *name_of_file* is a variable of an appropriate type such that the Pascal run-time system being used to implement $\TeX$ can open a file whose external name is specified by
*name_of_file*.

> ![NOTE]
> Compared to the original code, *name_of_file* is indexed from 0.

```c << Global variables >>+=
char name_of_file[FILE_NAME_SIZE + 1]; // extra byte for null byte
int name_length; // this many characters are actually relevant in |name_of_file| (the rest are blank)
```