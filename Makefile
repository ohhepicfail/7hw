CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -Werror -Wno-return-local-addr -std=c++14 -g3 -Wswitch-default -Wmaybe-uninitialized -Wredundant-decls

all: compile run  clean

run:
	./kth

compile: kth_statistic.cpp
	$(CXX) $(CXXFLAGS) kth_statistic.cpp -o kth;

clean:
	rm -rf *.o
	
