CPP=g++

graph: graph.cpp
	$(CPP) -g graph.cpp -o bin/graph

test: graph
	bin/graph

clean: 
	rm -rf bin/*