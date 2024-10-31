CC=gcc-14
CFLAGS=-std=c99 -Wall -Werror -pedantic -O3
LDLIBS:=$(shell pkg-config --libs-only-l gmp)
LDFLAGS:=$(shell pkg-config --libs-only-L gmp)
CPPFLAGS:=$(shell pkg-config --cflags gmp)
OBJS=miller-rabin.o lucas-lehmer.o
PROG=lucas-lehmer

.PHONY: clean

$(PROG): $(OBJS)
	$(CC) main.c $(OBJS) $(CPPFLAGS) -o $@ $(LDLIBS) $(LDFLAGS)

clean:
	rm -f $(PROG) $(OBJS) >>/dev/null
