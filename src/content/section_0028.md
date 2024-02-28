# Section 28

Files can be closed with the Pascal-H routine *'close(f)'*, which should be used when all input or output with respect to *f* has been completed.
This makes *f* available to be opened again, if desired; and if *f* was used for output, the *close* operation makes the corresponding external file appear on the user's area, ready to be read.

These procedures should not generate error messages if a file is being closed before it has been successfully opened.

> ![NOTE]
> And *fclose* for all type of files.

```c io/files.c
// close a text file
void a_close(alpha_file f) {
    fclose(f);
}

// close a binary file
void b_close(byte_file f) {
    fclose(f);
}

// close a word file
void w_close(word_file f) {
    fclose(f);
}
```