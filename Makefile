INCS = 
LIBS = 
CFLAGS = -O -g -std=c11 -pedantic -Wall ${INCS}
LDFLAGS = ${LIBS}

all: run_tests test kimaris

run_tests: run_tests.o kimaris.o
	strip -N main kimaris.o -o _kimaris.o
	${CC} -o $@ run_tests.o _kimaris.o ${LDFLAGS}

test:
	./run_tests

clean:
	rm *.o run_tests kimaris
