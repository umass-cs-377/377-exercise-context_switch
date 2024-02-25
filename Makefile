CC  = g++
CXX = g++

CFLAGS   = -g -Wall
CXXFLAGS = -g -Wall -std=c++14 -fno-elide-constructors

executables = context_switch

.PHONY: default
default: $(executables)

context_switch: context_switch.o

.PHONY: clean
clean:
	rm -f *~ a.out core *.o $(executables)

.PHONY: all
all: clean default
