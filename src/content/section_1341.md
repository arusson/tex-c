# Section 1341

First let's consider the format of whatsit nodes that are used to represent
the data associated with `\write` and its relatives.
Recall that a whatsit has *type = WHATSIT_NODE*, and the *subtype* is supposed to distinguish different kinds of whatsits.
Each node occupies two or more words; the exact number is immaterial, as long as it is readily determined from the *subtype* or other data.

We shall introduce five *subtype* values here, corresponding to the control sequences `\openout`, `\write`, `\closeout`, `\special`, and `\setlanguage`.
The second word of I/O whatsits has a *write_stream* field that identifies the write-stream number (0 to 15, or 16 for out-of-range and positive, or 17 for out-of-range and negative).
In the case of `\write` and `\special`, there is also a field that points to the reference count of a token list that should be sent.
In the case of `\openout`, we need three words and three auxiliary subfields to hold the string numbers for name, area, and extension.

```c include/constants.h
#define WRITE_NODE_SIZE 2 // number of words in a write/whatsit node
#define OPEN_NODE_SIZE  3 // number of words in an open/whatsit node
#define OPEN_NODE       0 // |subtype| in whatsits that represent files to \openout
#define WRITE_NODE      1 // |subtype| in whatsits that represent things to \write
#define CLOSE_NODE      2 // |subtype| in whatsits that represent streams to \closeout
#define SPECIAL_NODE    3 // |subtype| in whatsits that represent \special things
#define LANGUAGE_NODE   4 // |subtype| in whatsits that change the current language
```

```c include/extensions.h
// << Start file |extensions.h| >>

#define what_lang(X)    link((X) + 1)    // language number, in the range |0 .. 255|
#define what_lhm(X)     type((X) + 1)    // minimum left fragment, in the range |1 .. 63|
#define what_rhm(X)     subtype((X) + 1) // minimum right fragment, in the range |1 .. 63|
#define write_tokens(X) link((X) + 1)    // reference count of token list to write
#define write_stream(X) info((X) + 1)    // stream number (0 to 17)
#define open_name(X)    link((X) + 1)    // string number of file name to open
#define open_area(X)    info((X) + 2)    // string number of file area for |open_name|
#define open_ext(X)     link((X) + 2)    // string number of file extension for |open_name|
```
