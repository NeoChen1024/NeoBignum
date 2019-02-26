CC	= cc
CFLAGS	= -O2 -g -Wall -Wextra -pipe -fPIE -fPIC -I.
OBJS	= bignum.o

.PHONY: all

all: fib

fib: $(OBJS) fib.o
	$(CC) $(CFLAGS) -o fib fib.o $(OBJS)

countline:
	wc -l *.c
clean:
	-rm -f ${EXE}
