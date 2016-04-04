CPP=g++
CPPFLAGS=-std=c++11 -g

graph: graph.cpp
	$(CPP) $(CPPFLAGS) graph.cpp -o bin/graph

test: graph
	bin/graph

clean: 
	rm -rf bin/*
