.PHONY: all
all: generator primeCounter

generator:  generator.c
	gcc -o randomGenerator generator.c

primeCounter:	primeCounter.cpp
	gcc -o primeCounter primeCounter.cpp

.PHONY: clean
clean:
	-rm randomGenerator primeCounter 2>/dev/null
