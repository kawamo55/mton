#
OBJECTS = main.o mton.o
CFLAGS  = -Wall

all:$(OBJECTS)
	cc $(CFLAGS) $(OBJECTS) -o mton

main.o:main.c mton.h
	cc -c main.c

mton.o:mton.c mton.h
	cc -c mton.c

clean:
	rm $(OBJECTS) mton

