CPP=g++
CPPFLAGS=-std=c++11 -g

all: graph hmgraph mtgraph

hmgraph: src/hmgraph.cpp
	$(CPP) $(CPPFLAGS) src/hmgraph.cpp -o bin/hmgraph

graph: src/graph.cpp
	$(CPP) $(CPPFLAGS) src/graph.cpp -o bin/graph

mtgraph: src/mtgraph.cpp
	$(CPP) $(CPPFLAGS) src/mtgraph.cpp -o bin/mtgraph

test: graph
	bin/graph

clean: 
	rm -rf bin/*
