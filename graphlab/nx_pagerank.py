#!/usr/bin/env python
import sys
import time
import networkx as nx

filename = sys.argv[1]
print(filename)

g = nx.DiGraph()
edges = []
nodes = set()
with open(filename, 'r') as fp:
	for line in fp:
		t = tuple([int(x) for x in line.split()])
		edges.append(t)
		nodes.add(t[0])
		nodes.add(t[1])
#print(nodes)
#print(edges)
g.add_nodes_from(nodes)
g.add_edges_from(edges)

#print(g.nodes())
#print(g.adjacency_list())
start = time.time()
pr = nx.pagerank(g, alpha=.5, tol=.01, max_iter=10)
end = time.time()
print(pr)
print('Time: ' + str(end - start))
