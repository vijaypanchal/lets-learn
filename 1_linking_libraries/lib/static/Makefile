CFLAGS = -Wall -g -I../inc
OBJECTS = lib-src.o
 
all: libtest.a

# Build the static library
libtest.a: $(OBJECTS)
	ar rc libtest.a $(OBJECTS)

lib-src.o: ../lib-src.c
	$(CC) $(CFLAGS) -c ../lib-src.c

clean:
	rm -f $(OBJECTS)
	rm -f libtest.a
