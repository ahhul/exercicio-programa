FLAGS = -ansi -Wall -pedantic
CC = gcc

OBJS = utils.o main.o hexdump.o

k128: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o k128 -lm

main.o: main.c
	$(CC) $(FLAGS) -c main.c

hexdump.o: hexdump.c
	$(CC) $(FLAGS) -c hexdump.c

utils.o: utils.c
	$(CC) $(FLAGS) -c utils.c

clean:
	rm -rf *~ *.o k128
