# Section 904

We must now face the fact that the battle is not over, even though the hyphens have been found:
The process of reconstituting a word can be nontrivial because ligatures might change when a hyphen is present.
*The TeXbook* discusses the difficulties of the word "difficult", and the discretionary material surrounding a hyphen can be considerably more complex than that.
Suppose $\tt abcdef$ is a word in a font for which the only ligatures are $\tt b\!c$, $\tt c\!d$, $\tt d\!e$, and $\tt e\!f$.
If this word permits hyphenation between $\tt b$ and $\tt c$, the two patterns with and without hyphenation are $\tt a\,b\, - c\!d\,e\!f$ and $\tt a\,b\!c\,d\!e\,f$.
Thus the insertion of a hyphen might cause effects to ripple arbitrarily far into the rest of the word.
A further complication arises if additional hyphens appear together with such rippling, e.g., if the word in the example just given could also be hyphenated between $\tt c$ and $\tt d$; $\TeX$ avoids this by simply ignoring the additional hyphens in such weird cases.

Still further complications arise in the presence of ligatures that do not delete the original characters.
When punctuation precedes the word being hyphenated, $\TeX$'s method is not perfect under all possible scenarios, because punctuation marks and letters can propagate information back and forth.
For example, suppose the original pre-hyphenation pair $\tt*a$ changes to $\tt*y$ via a `|=:` ligature, which changes to $\tt xy$ via a `=:|` ligature;
if $p_{a - 1} = \tt x$ and $p_a = \tt y$, the reconstitution procedure isn't smart enough to obtain $\tt xy$ again.
In such cases the font designer should include a ligature that goes from $\tt xa$ to $\tt xy$.
