#include <cstdlib>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

struct Node {
   string label;
   double x;
   double y;
   int index;
};

ostream& operator<<(ostream& os, const Node& v);

struct Edge {
  int from;
  int to;
  string label;
};


ostream& operator<<(ostream& os, const Edge& e);
   
class Graph {
   vector<Node> nodes;
   vector<Edge> edges;
   int n_nodes;
   int n_edges;
 public:
   int getNodesN() const {return n_nodes;}
   int getEdgesN() const {return n_edges;}
   const Node& getNode(int i) const { assert(i>=0 && i<n_nodes); return nodes[i];}
   const Node& getNode(string lab) const;
   const vector<Edge>& getEdges() const { return edges;}
   Graph() {};
   Graph(string filename) {readDIMACS(filename);}
   void readDIMACS(string filename);
   void drawGraph() {};
};


ostream& operator<<(ostream& os, const Graph& g);
