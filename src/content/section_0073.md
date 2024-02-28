# Section 73

The global variable *interaction* has four settings, representing increasing amounts of user interaction:

```c include/constants.h
#define BATCH_MODE      0 // omits all stops and omits terminal output
#define NONSTOP_MODE    1 // omits all stops
#define SCROLL_MODE     2 // omits error stops
#define ERROR_STOP_MODE 3 // stops at every opportunity to interact
```

```c include/texerror.h
// << Start file |texerror.h| >>

#define print_err(X) print_nl("! "); print((X))
```

```c << Global variables >>+=
int interaction; // current level of interaction
```
