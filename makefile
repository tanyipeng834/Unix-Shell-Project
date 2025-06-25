CC = gcc
TARG = wish
OPTS = -Wall -O -g -Werror
SRC = wish.c builtin.c user.c


OBJS = $(SRC:.c=.o)
$(TARG).o: $(TARG).c
	$(CC) $(OPTS) -c $(TARG).c 
$(TARG): $(OBJS) 
	$(CC) -o $(TARG) $(OPTS) $(OBJS)
$(TARG).o : $(TARG).c 
	$(CC) $(OPTS) -c $(TARG).c
all: $(TARG)
clean:
	rm -f *.o *.txt $(TARG)