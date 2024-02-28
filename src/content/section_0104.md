# Section 104

Physical sizes that a $\TeX$ user specifies for portions of documents are represented internally as scaled points.
Thus, if we define an 'sp' (scaled point) as a unit equal to $2^{-16}$ printer's points, every dimension inside of $\TeX$ is an integer number of sp.
There are exactly 4,736,286.72 sp per inch.
Users are not allowed to specify dimensions larger than $2^{30} - 1$ sp, which is a distance of about 18.892 feet (5.7583 meters);
two such quantities can be added without overflow on a 32-bit computer.

The present implementation of $\TeX$ does not check for overflow when dimensions are added or subtracted.
This could be done by inserting a few dozen tests of the form '**if** *x* $\geq$ *0x40000000* **then** *report_overflow*', but the chance of overflow is so remote that such tests do not seem worthwhile.

$\TeX$ needs to do only a few arithmetic operations on scaled quantities, other than addition and subtraction, and the following subroutines do most of the work.
A single computation might use several subroutine calls, and it is desirable to avoid producing multiple error messages in case of arithmetic overflow;
so the routines set the global variable *arith_error* to *true* instead of reporting errors directly to the user.
Another global variable, *remainder*, holds the remainder after a division.

> ![NOTE]
> The global variable *remainder* has been renamed *remainder_* to avoid conflict with a function of the same name in math library.

```c << Global variables >>+=
bool arith_error;  // has arithmetic overflow occurred recently?
scaled remainder_; // amount subtracted to get an exact division
```
