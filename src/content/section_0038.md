# Section 38: String handling

Control sequence names and diagnostic messages are variable-length strings of eight-bit characters.
Since Pascal does not have a well-developed string mechanism, $\TeX$ does all of its string processing by homegrown methods.

Elaborate facilities for dynamic strings are not needed, so all of the necessary operations can be handled with a simple data structure.
The array *str_pool* contains all of the (eight-bit) ASCII codes in all of the strings, and the array *str_start* contains indices of the starting points of each string.
Strings are referred to by integer numbers, so that string number *s* comprises the characters *str_pool[j]* for *str_start[s]* $\leq$ *j* $<$ *str_start[s + 1]*.
Additional integer variables *pool_ptr* and *str_ptr* indicate the number of entries used so far in *str_pool* and *str_start*, respectively;
locations *str_pool[pool_ptr]* and *str_start[str_ptr]* are ready for the next string to be allocated.

String numbers 0 to 255 are reserved for strings that correspond to single ASCII characters.
This is in accordance with the conventions of `WEB`, which converts single-character strings into the ASCII code number of the single character involved, while it converts other strings into integers and builds a string pool file.
Thus, when the string constant `"."` appears in the program below, `WEB` converts it into the integer 46, which is the ASCII code for a period, while `WEB` will convert a string like `"hello"` into some integer greater than&nbsp;255.
String number 46 will presumably be the single character '`.`';
but some ASCII codes have no standard visible representation, and $\TeX$ sometimes needs to be able to print an arbitrary ASCII character, so the first 256 strings are used to specify exactly what should be printed for each of the 256 possibilities.

Elements of the *str_pool* array must be ASCII codes that can actually be printed; i.e., they must have an *xchr* equivalent in the local character set.
(This restriction applies only to preloaded strings, not to those generated dynamically by the user.)

Some Pascal compilers won't pack integers into a single byte unless the integers lie in the range *−128 .. 127*.
To accommodate such systems we access the string pool only via macros that can easily be redefined.

> ![NOTE]
> Strings in the source code are mostly handled as `char *` and not how `WEB` used to do (using an external file to copy during preprocessing, and then loaded them in the string pool).
> 
> The *si* and *so* macros are not needed, and *packed_ASCII_code* is not introduced.

```c << Types in the outer block >>+=
typedef int pool_pointer; // for variables that point into |str_pool|
typedef int str_number;   // for variables that point into |str_start|
```