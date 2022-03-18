LIBS = -L. ../lib/libhypamas.a -lrt -lpthread -lm 
INC = -I ../include/ 
CC = gcc
CFLAGS = -c -O3
LFLAGS = 

all: benchmark

benchmark: benchmark.o
	$(CC) $(LFLAGS) -o benchmark benchmark.o $(LIBS)

benchmark.o: benchmark.c
	$(CC) $(CFLAGS) -o benchmark.o $(INC) benchmark.c 

clean:
	rm -f benchmark.o benchmark
