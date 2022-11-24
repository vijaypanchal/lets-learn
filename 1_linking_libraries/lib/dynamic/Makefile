CFLAGS := -Wall -g -fPIC -I../inc
OBJECTS := lib-src.o
 
all: libtest.so
	
# Build the dynamic/shared library
libtest.so: $(OBJECTS)
	$(CC) -shared -o libtest.so $(OBJECTS)

lib-src.o: ../lib-src.c
	$(CC) $(CFLAGS) -c ../lib-src.c

clean:
	rm -f $(OBJECTS)
	rm -f libtest.so
