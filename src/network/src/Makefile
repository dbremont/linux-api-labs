CC      := gcc
CFLAGS  := -Wall -O2
SRCS    := $(wildcard *.c)
TARGETS := $(SRCS:.c=)

.PHONY: all run clean

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

run: $(TARGETS)
	@for bin in $(TARGETS); do echo "Running $$bin..."; ./$$bin; echo; done

clean:
	rm -f $(TARGETS)
