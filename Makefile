CPP=g++
CPPFLAGS=-lpthread -lboost_thread  -lboost_system -DBOOST_SYSTEM_NO_DEPRECATED -std=c++11 -g

all: graph hmgraph mtgraph

hmgraph: src/hmgraph.hpp
	$(CPP)src/hmgraph.hpp src/hmgraph-main.cpp -o bin/hmgraph  $(CPPFLAGS) 

graph: src/graph.hpp
	$(CPP)  src/graph.hpp src/graph-main.cpp  -o bin/graph $(CPPFLAGS)  

mtgraph:  src/mtgraph.o src/queue.o src/mtmain.o
	$(CPP) $(CPPFLAGS) src/mtmain.cpp src/mtgraph.hpp src/queue.hpp  -o bin/mtgraph

queue-test: src/tqueue.cpp
	$(CPP) $(CPPFLAGS) src/tqueue.hpp -o bin/tqueue-test

test: graph
	bin/graph

clean: 
	rm -rf bin/*
