# $\bf\TeX$ the program in C and Markdown

$\rm\TeX$ is a program written by Donald E. Knuth.
It has been written in [`WEB`](https://ctan.gutenberg-asso.fr/info/knuth/webman.pdf) which is at a higher level of the Pascal language and allows the programmer to write the documentation and code together.
This methodology is called [literate programming](https://www-cs-faculty.stanford.edu/~knuth/lp.html), where the idea is to write the programs for humans instead of a computer.

On one hand the source code can be extracted in a compilable form for a Pascal compiler, and on the other hand the documentation is extracted in a $\rm\TeX$ file from which a beautiful document (a [pdf](https://mirrors.ctan.org/info/knuth-pdf/tex/tex.pdf) or a [printed book](https://www.informit.com/store/computers-typesetting-volume-b-tex-the-program-9780137494194)) can be generated that makes the source code readable for humans.

This project is a conversion of $\rm\TeX$ into the C language mostly based on the conversion obtained from the [WEB to cweb](https://hint.userweb.mwn.de/hint/web2w.html) tool by Martin Ruckert with custom adjustments (mainly the format).
Then, it has been translated as Markdown files where code blocks are used to contain the pieces of code described in the 1300＋ sections of the documentation.

Thanks to [mdBook](https://rust-lang.github.io/mdBook/), the Markdown files are rendered as web pages where you can browse the source code as you would the pages of the original documentation, but this time with C as the base language:

<div align="center">

https://arusson.github.io/tex-c
</div>

Of course, the program can be compiled and used.

**Summary**:
- [How to read](#how-to-read)
- [Tangling](#tangling)
- [Weaving](#weaving)
- [Compilation](#compilation)
- [TRIP test](#trip-test)
- [Usage](#usage)
- [Preloaded format](#preloaded-format)
- [License](#license)

## How to read

The source code can be browsed on the [web pages](https://arusson.github.io/tex-c) of this project.

The principle is the same as `WEB`.
Each section can contain:
- informal commentary;
- a note about changes made for this conversion in C;
- blocks of C code.

Some parts may not be present all the time:
some sections have only a commentary, others a single code block.

Each code block is either *named*, or its destination file is indicated.
A named block begins with *"⟨ Name of section ⟩≡"* in angle brackets.
For example, the first named block is *"⟨ Initialize whatever TeX might access 8 ⟩≡"*, where the number 8 is the section where the block is defined.
Under this block is *"This code is used in section 4."*, so it means that this block is referenced in another block in section 4, given below for illustration:

```c
void initialize() {
    // << Local variables for initialization, 19 >>
    // << Initialize whatever TeX might access, 8 >>
}
```

The block name is given between `<<` and `>>` as a comment.
The meaning is that this comment `// << Name of section >>` has a replacement text that should be inserted at this place (the block code with the corresponding name).

The name of the block provides a short description of what the section does without going into details to avoid distraction for the reader.
But for further details, the section number makes it easy to go see what those details are.

It's possible for a named block to be the continuation of another.
In this case, there is a suffix `+≡`, such as in *"⟨&nbsp;Global variables 13&nbsp;⟩+≡"*.
For such cases there is a sentence like *"See also sections 26, 30, 39..."* below the first occurence, to indicate where the continuation blocks are defined.

Unnamed blocks are appended to the file indicated on top of the block, such as `line_break.c`.

If there is neither a name or a filename, then it is verbatim text that does not contribute the compilable source code, and is only part of the documentation.

## Tangling

The `WEB` version of $\rm\TeX$ is converted in compilable code with `tangle` into a single Pascal file.

For this implementation, a Python script `tangling.py` plays the same role, but an effort was made to make the compilable source readable and separated in several files.
The source code is extracted from the Markdown code blocks and rearranged according to the description given above.

This repository already contains the compilable source code in the `code/` folder.
To regenerate the code, the Makefile can be used:

```
make tangling
```

## Weaving

The `WEB` version of $\rm\TeX$ is converted into a beautiful documentation in $\rm\TeX$ itself using `weave`.

For this implementation, [mdBook](https://rust-lang.github.io/mdBook/) is used with a preprocessor written in Python scripts (`preprocessor.py` and `weaving.py`).
mdBook is a nice tool written in Rust to generate web pages from Markdown.
If you have Cargo already installed:

```
cargo install mdbook
```

For math rendering, the preprocessor [mdbook-katex](https://github.com/lzanini/mdbook-katex) is used.

```
cargo install mdbook-katex
```

Then, the pages of the [documentation](https://arusson.github.io/tex-c) can be regenerated with the following command:

```
mdbook build
```

> If you want it to be served on https://localhost:3000, the command `mdbook serve` can be used.

All the files are in the [book branch](https://github.com/arusson/tex-c/tree/book) of this repository.

## Compilation

The C code can be compiled using *gcc*.
There are three versions of the program:
- `initex`: the special version to produce formats;
- `virtex`: the production version of $\rm\TeX$;
- `triptex`: the special version for the TRIP test.

The main Makefile can be used to compile any of them:

```
make initex virtex triptex
```

## TRIP test

The torture test for $\rm\TeX$ has been tested on this implementation.

To run the TRIP test, it is necessary that the tool `dvitype` is present on your system (it can be installed through TeXlive).

Make sure the source code in `code/` is available (because `triptex` will be compiled), then:

```
make trip
```

This will generate three diff files:

- `tripin_log.diff`;
- `trip_log.diff`;
- `trip_typ.diff`.

Those files are compared with the expected results that are present in `trip/master/`.
According to the manual of the TRIP test, a few rounding errors are permissible in some cases only.
For instance, the rounding errors for `glue set` are the only divergences in `trip_log.diff`:

```
This is TeX, Version 3.141592653 (preloaded format=trip 2024. | This is TeX, Version 3.141592653 (preloaded format=trip 1776.
\vbox(16383.99998+0.0)x1000.0, glue set 16341.99998fil        | \vbox(16383.99998+0.0)x1000.0, glue set 16342.0fil
\vbox(16383.99998+1.0)x100.0, glue set 16238.99998fil         | \vbox(16383.99998+1.0)x100.0, glue set 16239.0fil
\vbox(16383.99998+0.0)x20.0, glue set 16330.99998fil          | \vbox(16383.99998+0.0)x20.0, glue set 16331.0fil
\vbox(10000.0+2.0)x28.0, glue set 9737.58742fil               | \vbox(10000.0+2.0)x28.0, glue set 9737.58789fil
\vbox(16383.99998+2.0)x100.0, glue set 16317.99997fil         | \vbox(16383.99998+2.0)x100.0, glue set 16318.0fil
\vbox(16383.99998+0.0)x8236.0, glue set 16343.99998fil        | \vbox(16383.99998+0.0)x8236.0, glue set 16344.0fil
\vbox(16383.99998+0.0)x100.0, glue set 16331.99998fil         | \vbox(16383.99998+0.0)x100.0, glue set 16332.0fil
\vbox(16383.99998+0.0)x205.12613, glue set 16343.99998fil     | \vbox(16383.99998+0.0)x205.12613, glue set 16344.0fil
 47 strings out of 2381                                       |  47 strings out of 1674
 253 string characters out of 28295                           |  253 string characters out of 8367
 7i,7n,9p,112b,38s stack positions out of 200i,40n,60p,200000 |  7i,7n,9p,113b,38s stack positions out of 200i,40n,60p,500b,6
 ```

## Usage

The programs `virtex` and `initex` can be used to produce DVI files as explained in the *TeXbook*.

The `example` folder contains the following subdirectories:
- `TeXfonts/`: fonts needed for the *plain* format (Computer Modern in various styles and sizes, and *manfnt*);
- `TeXinputs/`: `plain.tex` and `hyphen.tex` (both needed to generate the *plain* format).

The arguments to the binaries are essentially treated as the first line of input.

### Dumping a format file

To dump a format, the `initex` version of the program must be used.
The most classic way to used it is to write the name of the input file:

```
./initex TEXNAME
```

The input file must include the command `\dump`, otherwise a prompt will appear where you can add lines, until you type `\dump`.

Example for the *plain* format (place the binaries in the example folder to run these commands):

```
./initex 'plain \dump'
```

The command above acts as `\input plain` followed by `\dump`, and the file `plain.fmt` will be generated.
(The presence of single quotes `'` is to prevent the interpretation of the backslash by the terminal.)

An alternative using the terminal interaction:
- Run `./initex`;
- On the prompt `**` type `plain` (the `**` prompt asks for an input file, so it is an implicit "`\input`");
- On the prompt `*` type `\dump` (`*` is a regular prompt for a line of input).

A mix of both methods is possible:
- Run `./initex plain`;
- Then you can add new lines of input on prompts `*`, until you type `\dump`.

> The font metric files used by the format must be available while dumping.
> Those must be in the folder `TeXfonts/`.
> The fonts needed for the plain format (mainly Computer Modern in several sizes and styles) are already present.
> Any missing font will produce an error.
> Once a format is produced, all necessary data for $\rm\TeX$ are included, so the font metric files won't be necessary to create DVI files.
> 
> If the format needs auxiliary input files (for instance, the plain format needs the file `hyphen.tex`), make sure those are available:
> put them in the folder `TeXinputs/` and the program will know to look there.

### Generating a DVI file

To create a DVI document, the `virtex` version of the program is used.

A format file is necessary.
There are two cases:
- You provide the format filename preceded by `&` at the start of the command line or on the prompt `**`;
- No format is provided, then `virtex` tries to load `plain.fmt` from the folder `TeXformats/`: an error is returned if not found.

The character '`&`' tells $\rm\TeX$ to read the file `plain.fmt` and replace its internal memory from the content of the binary file (it contains all definition of macros from `plain.tex` and hyphenation patterns for english, both ready to be used).

An examples with *plain* and the file `formulas.tex`:

```
./virtex '&plain formulas'
```

The single quotes `'` is also to prevent the terminal to interpret it.

Again, there is an alternative with the command line interaction:
- Run `./virtex`
- On the prompt `**`, type `&plain`;
- On the prompt `*`, type `\input example`;
- The output will be the file `texput.dvi`.

If the file `plain.fmt` is in the folder `TeXformats/`, then you can type your input directly:

```
./virtex formulas
```

In all examples, the extension has been ommited, but it is not forbidden to use it.

> In case you don't have an input file, then type `\relax` on the prompt `**`.
> 
> If your input uses a font that is not included in the format (for example with `\font\libertine=LinLibertineT-tosf-t1`), make sure that it is present in `TeXfonts/`.
> 
> A DVI file can be converted in PDF with the program `dvipdf`, available with TeXlive.

## Preloaded format

There is no support for preloaded format as explained in section [1331](https://arusson.github.io/tex-c/part51.html#section-1331). 

To my understanding, such a trick is not used anymore for TeXlive binaries.
Instead, the name of the program you run is used to determine the format, then the file is found and loaded.
For example, `optex` is a symlink to the `luatex` binary, and the file `optex.fmt` (which is somewhere on the installation directory) is loaded.

This [Rust implementation](https://github.com/arusson/tex-rust) makes it possible to embed the format file in the binary, so it is loaded at the start of the execution without having to read an external file.
This is done using the macro `include_bytes!` to include a file inside the binary at compilation time.
The new preprocessor macro `#embed` of C23 could achieve the same thing for this C implementation, and could be added later.

## License

This work is released under the [MIT license](LICENSE).

The original $\rm\TeX$ program was created by Donald E. Knuth and released under his usual license: https://ctan.org/license/knuth.

Font metric files, input files `plain.tex` and `hyphen.tex`, and trip files were copied from CTAN and have not been modified:
[Computer Modern](https://ctan.org/tex-archive/fonts/cm/tfm), [manfnt](https://ctan.org/tex-archive/fonts/manual/tfm), [knuth-lib](https://ctan.org/tex-archive/systems/knuth/dist/lib), [knuth-tex](https://ctan.org/tex-archive/systems/knuth/dist/tex/).
These files are also under the Knuth license.

$\rm\TeX$ is a trademark of the American Mathematical Society.
