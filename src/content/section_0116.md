# Section 116

The *mem* array is divided into two regions that are allocated separately, but the dividing line between these two regions is not fixed; they grow together until finding their "natural" size in a particular job.
Locations less than or equal to *lo_mem_max* are used for storing variable-length records consisting of two or more words each.
This region is maintained using an algorithm similar to the one described in exercise 2.5--19 of *The Art of Computer Programming*.
However, no size field appears in the allocated nodes; the program is responsible for knowing the relevant size when a node is freed.
Locations greater than or equal to *hi_mem_min* are used for storing one-word records; a conventional `AVAIL` stack is used for allocation in this region.

Locations of *mem* between *MEM_BOT* and *MEM_TOP* may be dumped as part of preloaded format files, by the `INITEX` preprocessor.
Production versions of $\TeX$ may extend the memory at both ends in order to provide more space; locations between *MEM_MIN* and *MEM_BOT* are always used for variable-size nodes, and locations between *MEM_TOP* and *MEM_MAX* are always used for single-word nodes.

The key pointers that govern *mem* allocation have a prescribed order:
$$
\begin{array}{l}
\v{null} \leq \v{MEM\_MIN} \leq \v{MEM\_BOT} < \v{lo\_mem\_max}\\
\hskip3cm < \v{hi\_mem\_min} < \v{MEM\_TOP} \leq \v{mem\_end} \leq \v{MEM\_MAX}
\end{array}
$$

Empirical tests show that the present implementation of $\TeX$ tends to spend about 9% of its running time allocating nodes, and about 6% deallocating them after their use.

> ![NOTE]
> *MEM_MIN* is 0, so it is not used in the declaration of `mem`.

```c << Global variables >>+=
memory_word mem[MEM_MAX + 1]; // the big dynamic storage area
pointer lo_mem_max;           // the largest location of variable-size memory in use
pointer hi_mem_min;           // the smallest location of one-word memory in use
```
