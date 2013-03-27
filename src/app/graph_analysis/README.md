Graph Analysis Algorithms
========================================================

##Connected Component

**Strongly Connected**: A directed graph is called a strongly connected *if there is a path from each vertex in the graph to every other vertex*(paths in each direction).
**Strongly Connected Components** of a directed graph G are its maximal strongly connected subgraphs.

##K-Core

###Definition:

Let $G=(V,E)$ be a graph, A subgraph $H_k=(W,E|W)$ induced by the set W is *k-core* or a *core of order k* iff $\forall{v} \in W: deg_H(v) \geq k$, and $H_k$ is the maximum subgraph with this property.

The core of maximum order is also called the *main core*.

The *core number* of vertex $v$ is the highest order of a core that contains this vertex.

The degree $deg(v)$ can be in-degree, out-degree or in-degree $+$ out-degree, determining different types of cores.

2 properties of cores:
1. The cores are nested: $i < j \Rightarrow H_j \in H_i$.
2. Cores are not necessarily connected subgraphs.
