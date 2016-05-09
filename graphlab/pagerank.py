#!/usr/bin/env python
import graphlab
import sys
import time

if (len(sys.argv) < 5):
	print "Usage: %s <edge list filename> <epsilon> <damping factor> <max iterations>" % sys.argv[0]
	sys.exit(1)

filename = sys.argv[1]
print(filename)

# from https://dato.com/products/create/docs/generated/graphlab.pagerank.create.html
epsilon = float(sys.argv[2])
damping = float(sys.argv[3])
maxIterations = int(sys.argv[4])
g = graphlab.load_graph(filename, format='snap')
start = time.time()
pr = graphlab.pagerank.create(g, reset_probability=damping, max_iterations=maxIterations, _distributed=False, threshold=epsilon)
end = time.time()
pr_out = pr['pagerank']     # SFrame
g.vertices['pagerank'] = pr['graph'].vertices['pagerank']

print(pr_out)
print('time: ' + str(end - start))
