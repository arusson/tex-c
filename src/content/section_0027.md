# Section 27

The Pascal-H compiler with which the present version of $\TeX$ was prepared has extended the rules of Pascal in a very convenient way.
To open file&nbsp;*f*, we can write

<div align="center">
<div style="text-align: left; display:inline-block;">

*reset*(*f*, *name*, `'/O'`) for input;<br>
*rewrite*(*f*, *name*, `'/O'`) for output.
</div>
</div>

The *'name'* parameter, which is of type '**packed array**[$\langle$*any*$\rangle$] **of** *char*', stands for the name of the external file that is being opened for input or output.
Blank spaces that might appear in *'name'* are ignored.

The '`/O`' parameter tells the operating system not to issue its own error messages if something goes wrong.
If a file of the specified name cannot be found, or if such a file cannot be opened for some other reason (e.g., someone may already be trying to write the same file), we will have *erstat(f)* $\ne$ *0* after an unsuccessful *reset* or *rewrite*.
This allows $\TeX$ to undertake appropriate corrective action.

$\TeX$'s file-opening procedures return *false* if no file identified by *name_of_file* could be opened.

> ![NOTE]
> *fopen* is used with the different arguments *r*, *w*, *rb* and *wb* depending the type of file manipulated.

```c io/files.c
// << Start file |files.c| >>

// open a text file for input
int a_open_in(alpha_file *f) {
    *f = fopen(name_of_file, "r");
    return *f != NULL;
}

// open a text file for output
int a_open_out(alpha_file *f) {
    *f = fopen(name_of_file, "w");
    return *f != NULL;
}

// open a binary file for input
int b_open_in(byte_file *f) {
    *f = fopen(name_of_file, "rb");
    return *f != NULL;
}

// open a binary file for output
int b_open_out(byte_file *f) {
    *f = fopen(name_of_file, "wb");
    return *f != NULL;
}

// open a word file for input
int w_open_in(word_file *f) {
    *f = fopen(name_of_file, "rb");
    return *f != NULL;
}

// open a word file for output
int w_open_out(word_file *f) {
    *f = fopen(name_of_file, "wb");
    return *f != NULL;
}
```