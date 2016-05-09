CPP=g++
CPPFLAGS=-std=c++11 -g

all: graph hmgraph

hmgraph: src/hmgraph.cpp
	$(CPP) $(CPPFLAGS) src/hmgraph.cpp -o bin/hmgraph

graph: src/graph.cpp
	$(CPP) $(CPPFLAGS) src/graph.cpp -o bin/graph

test: graph
	bin/graph

clean: 
	rm -rf bin/*
