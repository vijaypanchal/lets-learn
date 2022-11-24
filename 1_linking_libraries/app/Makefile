CFLAGS := -c -Wall -I../lib/inc
PROGS := sample-app-static sample-app-dynamic

all: $(PROGS)

sample-app-dynamic.o: sample-app.c
	$(CC) $(CFLAGS) -o $@ $^

sample-app-static.o: sample-app.c
	$(CC) $(CFLAGS) -o $@ $^	

sample-app-dynamic: sample-app-dynamic.o
	$(CC) -o $@ $^ -L../lib/dynamic -ltest

sample-app-static: sample-app-static.o
	$(CC) -static -o $@ $^ -L../lib/static -ltest	

clean:
	rm -f *.o
	rm -f $(PROGS)

install:
	cp $(PROGS) $(TARGET_DIR)/usr/local/bin
