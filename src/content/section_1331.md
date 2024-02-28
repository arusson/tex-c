# Section 1331

We have noted that there are two versions of $\TeX82$.
One, called `INITEX`, has to be run first; it initializes everything from scratch, without reading a format file, and it has the capability of dumping a format file.
The other one is called '`VIRTEX`'; it is a "virgin" program that needs to input a format file in order to get started.
`VIRTEX` typically has more memory capacity than `INITEX`, because it does not need the space consumed by the auxiliary hyphenation tables and the numerous calls on *primitive*, etc.

The `VIRTEX` program cannot read a format file instantaneously, of course;
the best implementations therefore allow for production versions of $\TeX$ that not only avoid the loading routine for Pascal object code, they also have a format file pre-loaded.
This is impossible to do if we stick to standard Pascal;
but there is a simple way to fool many systems into avoiding the initialization, as follows:

1. We declare a global integer variable called *ready_already*.
   The probability is negligible that this variable holds any particular
   value like 314159 when `VIRTEX` is first loaded.

2. After we have read in a format file and initialized
   everything, we set *ready_already &larr; 314159*.

3. Soon `VIRTEX` will print '`*`', waiting for more input;
   and at this point we interrupt the program and save its core
   image in some form that the operating system can reload speedily.

4. When that core image is activated, the program starts again
   at the beginning; but now *ready_already = 314159* and all
   the other global variables have their initial values too.
   The former chastity has vanished!

In other words, if we allow ourselves to test the condition *ready_already = 314159*, before *ready_already* has been assigned a value, we can avoid the lengthy initialization.
Dirty tricks rarely pay off so handsomely.

On systems that allow such preloading, the standard program called `TeX` should be the one that has `plain` format preloaded, since that agrees with *The TeXbook*.
Other versions, e.g., `AmSTeX`, should also be provided for commonly used formats.

> ![NOTE]
> This implementation does not support this dirty trick.
>
> ```pas
>  ready_already: integer; { a sacrifice of purity for economy }
> ```
