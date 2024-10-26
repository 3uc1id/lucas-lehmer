CC=gcc
CFLAGS=-std=c99 -Wall -Werror -pedantic -O2
LDLIBS=-lgmp
OBJS=miller-rabin.o lucas-lehmer.o
PROG=lucas-lehmer

.PHONY: clean

$(PROG): $(OBJS)
	$(CC) main.c $(OBJS) -o $@ $(LDLIBS)

clean:
	rm -f $(PROG) $(OBJS) >>/dev/null
