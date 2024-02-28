# Section 81

The *jump_out* procedure just cuts across all active procedure levels and goes to *end_of_TEX*.
This is the only nontrivial **goto** statement in the whole program.
It is used when there is no recovery from a particular error.

Some Pascal compilers do not implement non-local **goto** statements.
In such cases the body of *jump_out* should simply be '*close_files_and_terminate*;' followed by a call on some system procedure that quietly terminates the program.

```c error.c
// << Start file |error.c| >>

void jump_out() {
    close_files_and_terminate();
    exit(0);
}
```
