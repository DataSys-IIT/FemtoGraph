CPP=g++
CPPFLAGS=-lpthread -pthread -std=c++11 -Wl,--no-as-needed -g 

all: graph hmgraph mtgraph

hmgraph: src/hmgraph.hpp
	$(CPP) $(CPPFLAGS) src/hmgraph.hpp src/hmgraph-main.cpp -o bin/hmgraph

graph: src/graph.hpp
	$(CPP) src/graph.hpp src/graph-main.cpp  -o bin/graph  $(CPPFLAGS)

mtgraph:  src/mtgraph.o src/queue.o src/mtmain.o
	$(CPP) $(CPPFLAGS) src/mtmain.cpp src/mtgraph.hpp src/queue.hpp  -o bin/mtgraph

queue-test: src/tqueue.cpp
	$(CPP) $(CPPFLAGS) src/tqueue.hpp -o bin/tqueue-test

test: graph
	bin/graph

clean: 
	rm -rf bin/*
