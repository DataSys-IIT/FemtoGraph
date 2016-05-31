CPP=g++
CPPFLAGS=-std=c++11 -g -lpthread

all: graph hmgraph mtgraph

hmgraph: src/hmgraph.cpp
	$(CPP) $(CPPFLAGS) src/hmgraph.cpp -o bin/hmgraph

graph: src/graph.cpp
	$(CPP) $(CPPFLAGS) src/graph.cpp -o bin/graph

mtgraph:  src/mtgraph.o src/tqueue.o
	$(CPP) $(CPPFLAGS) src/mtgraph.cpp src/tqueue.cpp  -o bin/mtgraph

queue-test: src/tqueue.cpp
	$(CPP) $(CPPFLAGS) src/tqueue.cpp -o bin/tqueue-test

test: graph
	bin/graph

clean: 
	rm -rf bin/*
