# Section 15

Labels are given symbolic names by the following definitions, so that occasional **goto** statements will be meaningful.
We insert the label *'exit'* just before the '**end**' of a procedure in which we have used the '**return**' statement defined below;
the label *'restart'* is occasionally used at the very beginning of a procedure;
and the label *'reswitch'* is occasionally used just prior to a **case** statement in which some cases change the conditions and we wish to branch to the newly applicable case.
Loops that are set up with the **loop** construction defined below are commonly exited by going to *'done'* or to *'found'* or to *'not_found'*, and they are sometimes repeated by going to *'continue'*.
If two or more parts of a subroutine start differently but end up the same, the shared code may be gathered together at *'common_ending'*.

Incidentally, this program never declares a label that isn't actually used, because some fussy Pascal compilers will complain about redundant labels.

> ![NOTE]
> The use of label *'exit'* is replaced directly by a `return`, except in at least one case.
> 
> Sometimes, the label *'done'* is replaced by a `break` when possible.
> The position of the label is still given in a comment for information.
>
> The '**loop**' is replaced by `while(true)`.
>
> Finally, the label *'continue'* is called *'continue_lbl'* because it is a C keyword, except when it can be used directly as the keyword `continue`.
