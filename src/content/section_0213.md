# Section 213

```c include/datastructures.h
#define mode            cur_list.mode_field // current mode
#define head            cur_list.head_field // header node of current list
#define tail            cur_list.tail_field // final node on current list
#define prev_graf       cur_list.pg_field   // number of paragraph lines accumulated
#define aux             cur_list.aux_field  // auxiliary data about the current list
#define prev_depth      aux.sc              // the name of |aux| in vertical mode
#define space_factor    hh_lh(aux)          // part of |aux| in horizontal mode
#define clang           hh_rh(aux)          // the other part of |aux| in horizontal mode
#define incompleat_noad aux.integer         // the name of |aux| in math mode
#define mode_line       cur_list.ml_field   // source file line number at beginning of list
```

```c << Global variables >>+=
list_state_record nest[NEST_SIZE + 1];
int nest_ptr;               // first unused location of |nest|
int max_nest_stack;         // maximum of |nest_ptr| when pushing
list_state_record cur_list; // top "top" semantic nest
int shown_mode;             // most recent mode shown by \tracingcommands
```
