#!/usr/bin/env python
import graphlab
import sys
import time

filename = sys.argv[1]
print(filename)

# from https://dato.com/products/create/docs/generated/graphlab.pagerank.create.html
g = graphlab.load_graph(filename, format='snap')
start = time.time()
pr = graphlab.pagerank.create(g, reset_probability=.5)
end = time.time()
pr_out = pr['pagerank']     # SFrame
g.vertices['pagerank'] = pr['graph'].vertices['pagerank']

print(pr_out)
print('time: ' + str(end - start))
