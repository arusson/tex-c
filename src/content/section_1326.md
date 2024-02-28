# Section 1326

We have already printed a lot of statistics, so we set *tracing_stats &larr; 0* to prevent them from appearing again.

```c << Dump a couple more things and the closing check word >>=
dump_int(interaction);
dump_int(format_ident);
dump_int(69069);
tracing_stats = 0;
```
