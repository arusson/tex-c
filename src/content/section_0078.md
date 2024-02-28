# Section 78

Since errors can be detected almost anywhere in $\TeX$, we want to declare the error procedures near the beginning of the program. But the error procedures in turn use some other procedures, which need to be declared *forward* before we get to *error* itself.

It is possible for *error* to be called recursively if some error arises when *get_token* is being used to delete a token, and/or if some fatal error occurs while $\TeX$ is trying to fix a non-fatal one. But such recursion is never more than two levels deep.

> ![NOTE]
> No need for forward declaration; they are in header files.
