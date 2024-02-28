# Section 10

This $\TeX$ implementation conforms to the rules of the *Pascal User Manual* published by Jensen and Wirth in 1975, except where system-dependent code is necessary to make a useful system program, and except in another respect where such conformity would unnecessarily obscure the meaning and clutter up the code:
We assume that **case** statements may include a default case that applies if no matching label is found.
Thus, we shall use constructions like

<div align="center">
<div style="text-align: left; display: inline-block;">

**case** *x* **of**<br>
1: ⟨ code for *x* = 1 ⟩;<br>
3: ⟨ code for *x* = 3 ⟩;<br>
**othercases** ⟨ code for *x* $\ne$ 1 and *x* $\ne$ 3 ⟩<br>
**endcases**
</div>
</div>

since most Pascal compilers have plugged this hole in the language by incorporating some sort of default mechanism.
For example, the Pascal-H compiler allows *'others:'* as a default label, and other Pascals allow syntaxes like '**else**' or '**otherwise**' or *'otherwise:'*, etc.
The definitions of **othercases** and **endcases** should be changed to agree with local conventions.
Note that no semicolon appears before **endcases** in this program, so the definition of **endcases** should include a semicolon if the compiler wants one.
(Of course, if no default mechanism is available, the **case** statements of $\TeX$ will have to be laboriously extended by listing all remaining cases.
People who are stuck with such Pascals have, in fact, done this, successfully but not happily!)

> ![NOTE]
> In C, we use `switch`, with the *break* keyword to end a case.
> Multiple cases can be combined with subsequents `case something:`.
> The default case is `default:`.
