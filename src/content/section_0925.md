# Section 925

The exception table that is built by $\TeX$'s `\hyphenation` primitive is organized as an ordered hash table [cf. Amble and Knuth, *The Computer Journal* **17** (1974), 135--142] using linear probing.
If $\alpha$ and $\beta$ are words, we will say that $\alpha<\beta$ if $\vert\alpha\vert < \vert\beta\vert$ or if $\vert\alpha\vert = \vert\beta\vert$ and $\alpha$ is lexicographically smaller than $\beta$.
(The notation $\vert \alpha\vert$ stands for the length of $\alpha$.)
The idea of ordered hashing is to arrange the table so that a given word $\alpha$ can be sought by computing a hash address $h = h(\alpha)$ and then looking in table positions $h$, $h - 1$, $\dots$, until encountering the first word  $\leq\alpha$.
If this word is different from $\alpha$, we can conclude that $\alpha$ is not in the table.

The words in the table point to lists in *mem* that specify hyphen positions in their *info* fields.
The list for $c_1\ldots c_n$ contains the number *k* if the word $c_1\ldots c_n$ has a discretionary hyphen between $c_k$ and $c_{k + 1}$.
