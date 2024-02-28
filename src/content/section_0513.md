# Section 513

The file names we shall deal with for illustrative purposes have the following structure:
If the name contains '`>`' or '`:`', the file area consists of all characters up to and including the final such character;
otherwise the file area is null.
If the remaining file name contains '`.`', the file extension consists of all such characters from the first remaining '`.`' to the end, otherwise the file extension is null.

We can scan such file names easily by using two global variables that keep track of the occurrences of area and extension delimiters:

> ![NOTE]
> This C implementation of $\TeX$ uses only '`/`' as the area delimiter.

```c << Global variables >>+=
pool_pointer area_delimiter; // the most recent '>' or ':', if any
pool_pointer ext_delimiter;  // the relevant '.', if any
```
