# Section 4

The program begins with a normal Pascal program heading, whose components will be filled in later, using the conventions of `WEB`.
For example, the portion of the program called '⟨&nbsp;Global variables, 13&nbsp;⟩' below will be replaced by a sequence of variable declarations that starts in [Section 13](./part01#section-13) of this documentation.
In this way, we are able to define each individual global variable when we are prepared to understand what it means; we do not have to define all of the globals at once.
Cross references in section [13](./part01.md#section-13), where it says "See also
sections 26, 30, $\dots$", also make it possible to look at the set of all global variables, if desired.
Similar remarks apply to the other portions of the program heading.

Actually the heading shown here is not quite normal:
The **program** line does not mention any *output* file, because Pascal-H would ask the $\TeX$ user to specify a file name if *output* were specified here.

> ![NOTE]
> A few named blocks are not needed:
> - ⟨ Compiler directives 9 ⟩;
> - ⟨ Label in the outer block 6 ⟩.
>
> Also, other named blocks are removed and replaced by a filename.
> Here, for example:
> - ⟨ Constants in the outer block 11 ⟩: in header file `constants.h`;
> - ⟨ Types in the outer block 18 ⟩: in `tex.h`;
> - ⟨ Global variables, 13 ⟩: in `global.c` (variables are declared `extern` in `tex.h`, see section [1380](./part54.md#section-1380));
> - ⟨ Basic printing procedures 57 ⟩: in `basic_printing.c`;
> - ⟨ Error handling procedures 78 ⟩: in `error.c`.
> 
> The same happens for others later.


```c include/tex.h
// << Start file |tex.h| >>

// << Types in the outer block >>
```

```c global.c
// << Start file |global.c| >>

// << Global variables >>
```

```c init_cleanup.c
// << Start file |init_cleanup.c| >>

void initialize() {
    // << Local variables for initialization >>
    // << Initialize whatever TeX might access >>
}
```