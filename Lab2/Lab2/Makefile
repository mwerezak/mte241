# Makefile, ECE254 lab1
# Irene Huang, 2012/09/20

CC=gcc
CFLAGS=-Wall -g
LD=gcc
LDFLAGS=-g -lrt -lm


OBJS=producer.o consumer.o main.o

all: main.out

main.out: $(OBJS) 
	$(LD) $(LDFLAGS) -o $@ $(OBJS) 

main.o: main.c globals.h producer.h consumer.h 
	$(CC) $(CFLAGS) -c main.c 
    
producer.o: producer.c producer.h globals.h
	$(CC) $(CFLAGS) -c producer.c 
    
consumer.o: consumer.c consumer.h globals.h
	$(CC) $(CFLAGS) -c consumer.c 
    
.PHONY: clean
clean:
	rm -f *.o *.out 
