# Section 1383

Finally, the makefile.

```makefile Makefile
CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lm
# -DSTAT and -DDEBUG can be added.
# For INIT or TRIP: use make rule initex or triptex
TEXFLAGS =

INCLDIR = include
BINDIR = bin

BINVIR = virtex
BININI = initex
BINTRIP = triptex
BINS = $(BINVIR) $(BININI)

SRC = $(wildcard *.c) $(wildcard */*.c)
OBJVIR = $(SRC:%.c=%.o)
OBJINI = $(SRC:%.c=%_init.o)
OBJTRIP = $(SRC:%.c=%_trip.o)

.PHONY: all clean

all: $(BINS)

$(BINVIR): $(OBJVIR)
$(BINVIR): OBJ = $(OBJVIR)

$(BININI): $(OBJINI)
$(BININI): OBJ = $(OBJINI)
$(BININI): TEXFLAGS += -DINIT

$(BINTRIP): $(OBJTRIP)
$(BINTRIP): OBJ = $(OBJTRIP)
$(BINTRIP): TEXFLAGS = -DINIT -DSTAT -DTRIP

$(BINS) $(BINTRIP): $(BINDIR) $(OBJ)
$(BINS) $(BINTRIP):
	$(CC) $(CFLAGS) $(TEXFLAGS) -o $(BINDIR)/$@ $(OBJ) $(LDFLAGS) -I$(INCLDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

%_init.o: %.c
	$(CC) $(CFLAGS) $(TEXFLAGS) -c $< -o $@ -I$(INCLDIR)

%_trip.o: %.c
	$(CC) $(CFLAGS) $(TEXFLAGS) -c $< -o $@ -I$(INCLDIR)

%.o: %.c
	$(CC) $(CFLAGS) $(TEXFLAGS) -c $< -o $@ -I$(INCLDIR)

clean:
	rm -f $(OBJVIR) $(OBJINI) $(OBJTRIP)
	rm -rf $(BINDIR)
```
