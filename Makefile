FLAGS = -ansi -Wall -pedantic
CC = gcc

OBJS = hexdump.o keys.o encryption.o utils.o main.o 

k128: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o k128 -lm

main.o: main.c
	$(CC) $(FLAGS) -c main.c

encryption.o: encryption.c
	$(CC) $(FLAGS) -c encryption.c

keys.o: keys.c
	$(CC) $(FLAGS) -c keys.c

utils.o: utils.c
	$(CC) $(FLAGS) -c utils.c

hexdump.o: hexdump.c
	$(CC) $(FLAGS) -c hexdump.c

clean:
	rm -rf *~ *.o k128
