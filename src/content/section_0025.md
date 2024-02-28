# Section 25: Input and output

The bane of portability is the fact that different operating systems treat input and output quite differently, perhaps because computer scientists have not given sufficient attention to this problem.
People have felt somehow that input and output are not part of "real" programming.
Well, it is true that some kinds of programming are more fun than others.
With existing input/output conventions being so diverse and so messy, the only sources of
joy in such parts of the code are the rare occasions when one can find a way to make the program a little less bad than it might have been.
We have two choices, either to attack I/O now and get it over with, or to postpone I/O until near the end. Neither prospect is very attractive, so let's get it over with.

The basic operations we need to do are (1)&nbsp;inputting and outputting of text, to or from a file or the user's terminal; (2)&nbsp;inputting and outputting of eigh  bit bytes, to or from a file; (3)&nbsp; instructing the operating system to initiate ("open") or to terminate ("close") input or output from a specified file; (4)&nbsp;testing whether the end of an input file has been reached.

$\TeX$ needs to deal with two kinds of files.
We shall use the term *alpha_file* for a file that contains textual data, and the term *byte_file* for a file that contains eight-bit binary information.
These two types turn out to be the same on many computers, but sometimes there is a significant distinction, so we shall be careful to distinguish between them. Standard protocols for transferring such files from computer to computer, via high-speed networks, are now becoming available to more and more communities of users.

The program actually makes use also of a third kind of file, called a *word_file*, when dumping and reloading base information for its own initialization.
We shall define a word file later; but it will be possible for us to specify simple operations on word files before they are defined.

```c << Types in the outer block >>+=
typedef unsigned char eight_bits; // unsigned one-byte quantity
typedef FILE* alpha_file;         // files that contain textual data
typedef FILE* byte_file;          // files that contain binary data
```