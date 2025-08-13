CC = gcc
CFLAGS = -Wall
OBJ = main.o tasks.o

.PHONY: all clean

all: todo

todo: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o todo

main.o: main.c tasks.h colors.h
	$(CC) $(CFLAGS) -c main.c

tasks.o: tasks.c tasks.h colors.h
	$(CC) $(CFLAGS) -c tasks.c

clean:
	rm -f *.o todo


