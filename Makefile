WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 

TESTFLAGS = -DTEST_COUNTWORD

SRCS = a5_main.c
OBJS = $(SRCS:%.c=%.o)


a5: $(OBJS) 
	$(GCC) $(TESTFLAGS) $(OBJS) -o a5

.c.o: 
	$(GCC) $(TESTFLAGS) -c $*.c 

clean:
	rm -f a5 *.o output* *~