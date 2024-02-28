# Section 495

When we begin to process a new `\if`, we set *if_limit &larr; IF_CODE*;
then if `\or` or `\else` or `\fi` occurs before the current `\if` condition has been evaluated, `\relax` will be inserted.
For example, a sequence of commands like '`\ifvoid1\else...\fi`' would otherwise require something after the '`1`'.

```c << Push the condition stack >>=
p = get_node(IF_NODE_SIZE);
link(p) = cond_ptr;
type(p) = if_limit;
subtype(p) = cur_if;
if_line_field(p) = if_line;
cond_ptr = p;
cur_if = cur_chr;
if_limit = IF_CODE;
if_line = line;
```
