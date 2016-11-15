CPP=g++
CPPFLAGS=-lpthread -lboost_thread  -lboost_system -DBOOST_SYSTEM_NO_DEPRECATED -std=c++11 -g

all: graph


graph: src/graph.hpp
	$(CPP)  src/graph.hpp src/graph-main.cpp  -o bin/graph $(CPPFLAGS)  

test: graph
	bin/graph

clean: 
	rm -rf bin/*
