CC=gcc
RM=rm
MAKE=make
CFLAGS=-std=c++11 -lz
all:
	$(MAKE) --no-print-directory ./bin/WGS

./bin/WGS: ./WGS/main.cpp
	mkdir -p bin
	$(CC) $(CFLAGS) ./WGS/main.cpp -o ./bin/WGS

test:

clean: ./bin/crisflash
	$(RM) ./bin/WGS