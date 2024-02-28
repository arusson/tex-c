# Section 291

A token list is a singly linked list of one-word nodes in *mem*, where each word contains a token and a link.
Macro definitions, output-routine definitions, marks, `\write` texts, and a few other things
are remembered by $\TeX$ in the form of token lists, usually preceded by a node with a reference count in its *token_ref_count* field.
The token stored in location *p* is called *info(p)*.

Three special commands appear in the token lists of macro definitions.
When *m = MATCH*, it means that $\TeX$ should scan a parameter for the current macro;
when *m = END_MATCH*, it means that parameter matching should end and $\TeX$ should start reading the macro text;
and when *m = OUT_PARAM*, it means that $\TeX$ should insert parameter number *c* into the text at this point.

The enclosing `{` and `}` characters of a macro definition are omitted, but an output routine will be enclosed in braces.

Here is an example macro definition that illustrates these conventions.
After $\TeX$ processes the text

<div align="center">

`\def\mac a#1#2 \b {#1\-a ##1#2 #2}`
</div>

the definition of `\mac` is represented as a token list containing

<div align="center">

(reference count), *LETTER* `a`, *MATCH* `#`, *MATCH* `#`, *SPACER* `␣`, `\b`, *END_MATCH*, <br>
*OUT_PARAM* `1`, `\-`, *LETTER* `a`, *SPACER* `␣`, *MAC_PARAM* `#`, *OTHER_CHAR* `1`, <br>
*OUT_PARAM* `2`, *SPACER* `␣`, *OUT\_PARAM* `2`.
</div>

The procedure *scan_toks* builds such token lists, and *macro_call* does the parameter matching.

Examples such as
<div align="center">

`\def\m{\def\m{a} b}`
</div>

explain why reference counts would be needed even if $\TeX$ had no `\let` operation:
When the token list for `\m` is being read, the redefinition of `\m` changes the *eqtb* entry before the token list has been fully consumed, so we dare not simply destroy a token list when its control sequence is being redefined.

If the parameter-matching part of a definition ends with '`#{`', the corresponding token list will have '`{`' just before the *'END_MATCH'* and also at the very end.
The first '`{`' is used to delimit the parameter; the second one keeps the first from disappearing.
