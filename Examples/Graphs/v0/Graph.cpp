#include "Graph.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>


ostream& operator<<(ostream& os, const Node& v) {
   return os<<v.label;   
}


ostream& operator<<(ostream& os, const Edge& e) {
  //return os<<e.from<<" "<<e.to;
  return os<<"edge "<<e.from<<" "<<e.to;
}


void Graph::readDIMACS(string filename) {
   ifstream infile {filename};
   int edge_count=0;
   while (!infile.eof()) {      
      string buf;
      getline(infile,buf);
      stringstream line{buf};
      char c='\0';
      line>>c;
      if (c=='p')
      {
         string trash;
         line>>trash;       
         line>>n_nodes>>n_edges;
         nodes.resize(n_nodes);
         for (int i=0;i<n_nodes; ++i)
         {
            Node v;
            v.label=to_string(i+1);
            double theta = M_PI/n_nodes*i;
            v.x=cos(theta);
            v.y=sin(theta);
            nodes[i]=v; // copy
         }
      }
      else if (c=='e')
      {
         int from,to;
         line>>from>>to;
         int index_from = from-1;
         int index_to = to-1;
         bool already_in=false;
         for (const Edge& e: getEdges()) {
           if ((e.from==index_from && e.to==index_to) ||
               (e.from==index_to && e.to==index_from))
            {
               already_in=true;
               break;
            }
         }
         if (!already_in) {
           Edge e;
           e.from = index_from;
           e.to = index_to;
           e.label=to_string(edge_count++);            
           edges.push_back(e);
         }
    
      }
      else if (c=='\0')
         cout<<"Empty line\n";
      else {
         cerr<<"line with undefined letter";
      }
   }
   assert(n_edges==edge_count);
}


const Node& Graph::getNode(string lab) const
{
   for (const Node &v : nodes) {
      if (v.label==lab)
         return v;
   }
   cerr<<"node "+ lab+ "not found"<<endl;
   exit(EXIT_FAILURE);
}




ostream& operator<<(ostream& os, const Graph& g) {
  os<<g.getNodesN() <<" nodes; "<<g.getEdgesN()<<" edges\n";
  for (const Edge& e: g.getEdges()) {
    os<<"edge "<<g.getNode(e.from).label<<" "<<g.getNode(e.to).label<<"\n";
  }
  return os;
}

