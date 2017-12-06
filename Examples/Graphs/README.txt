v0 is a basic version in which nodes have indices and edges are between indices. It implies that we can write the program almost pointerfree and without cary about memory management. Both nodes and edges are contained in vectors.

v1 is more complicated. Nodes are created and allocated once. Edges just refer to nodes. Nodes must be allocated directly. Allocating them in a vector would impliy that they are moved everytime the vector is expanded thus invalidating the pointers. It implies that we need to develop with pointers and memory management.
