# Section 555

The global variable *null_character* is set up to be a word of *char_info* for a character that doesn't exist.
Such a word provides a convenient way to deal with erroneous situations.

```c << Global variables >>+=
memory_word null_character; // nonexistent character information
```
