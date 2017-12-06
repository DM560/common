#include <cstdlib>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

namespace Graph {

struct Node {
   string label;
   double x;
   double y;
   int index;
};

ostream& operator<<(ostream& os, const Node& v);

struct Edge {
   Node *from; // alternatively, put here the index of the node
   Node *to; // alternatively, put here the index of the node
   string label;
   Edge() {};
Edge(const Edge& e) : from{e.from}, to{e.to}, label{e.label} {cout<<"copied";};
};


ostream& operator<<(ostream& os, const Edge& e);
   
class Graph {
   vector<Node*> nodes;
   vector<Edge*> edges;
   int n_nodes;
   int n_edges;
   int addNode(string lab,int index);
   Node* getNode(string lab);
 public:
   int getNodesN() const {return n_nodes;}
   int getEdgesN() const {return n_edges;}
   const Node& getNode(int i) const { assert(i>=0 && i<n_nodes); return *nodes[i];}
   const Node& getNode(string lab) const;
   const vector<Edge*>& getEdges() const { return edges;}
   const vector<Node*>& getNodes() const { return nodes;}
   Graph() {};
   Graph(string filename) {readDIMACS(filename);}
   void readDIMACS(string filename);
   void drawGraph() {};
};


ostream& operator<<(ostream& os, const Graph& g);

}
