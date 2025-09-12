flags=-O2 -Wall -std=c2x

all: clean inmemdb

tree: tree.o
	cc $(flags) $^ -o $@ $(ldflags)

tree.o: tree.c
	cc $(flags) -c $^

inmemdb: inmemdb.o
	cc ${flags} $^ -o $@ ${ldflags}

inmemdb.o: inmemdb.c
	cc ${flags} -c $^

clean:
	rm -rf *.o inmemdb