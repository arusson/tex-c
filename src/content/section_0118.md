# Section 118

Let's consider the one-word memory region first, since it's the simplest.
The pointer variable *mem_end* holds the highest-numbered location of *mem* that has ever been used.
The free locations of *mem* that occur between *hi_mem_min* and *mem_end*, inclusive, are of type
*two_halves*, and we write *info(p)* and *link(p)* for the *lh* and *rh* fields of *mem[p]* when it is of this type.
The single-word free locations form a linked list

<div align="center">

*avail*, *link(avail)*, *link(link(avail))*, $\dots$
</div>

terminated by *null*.

```c include/datastructures.h
#define link(X) hh_rh(mem[(X)]) // the |link| field of a memory word
#define info(X) hh_lh(mem[(X)]) // the |info| field of a memory word
```

```c << Global variables >>+=
pointer avail;   // head of the list of available one-word nodes
pointer mem_end; // the last one-word node used in |mem|
```
