#include "Graph.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>

namespace Graph {


ostream& operator<<(ostream& os, const Node& v) {
   return os<<v.label<<" ("<<v.x<<","<<v.y<<")";   
}


ostream& operator<<(ostream& os, const Edge& e) {
   return os<<e.from->label<<" "<<e.to->label;
}


void Graph::readDIMACS(string filename) {
   ifstream infile {filename};
   int edge_count=0;
   int node_count=0;
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
         /*nodes.resize(n_nodes);
         for (int i=0;i<n_nodes; ++i)
         {
            Node v;
            v.label=to_string(i+1);
            double theta = M_PI/n_nodes*i;
            v.x=cos(theta);
            v.y=sin(theta);
            nodes[i]=v; // copy
            }*/
      }
      else if (c=='e')
      {
         string from,to;
         line>>from>>to;
         node_count += addNode(from, node_count);
         node_count += addNode(to, node_count);

         bool already_in=false;
         for (const Edge* pe: getEdges()) {
            if ((pe->from->label==from && pe->to->label==to) ||
               (pe->from->label==to && pe->to->label==from))
            {
               already_in=true;
               break;
            }
         }
         if (!already_in) {
            Edge* pe=new Edge;
            pe->index=edge_count;
            pe->from = getNode(from);
            pe->to = getNode(to);
            pe->label=to_string(edge_count++);            
            edges.push_back(pe);
         }
    
      }
      else if (c=='\0')
         cout<<"Empty line\n";
      else {
         cerr<<"line with undefined letter";
      }
   }
   assert(n_nodes==node_count);
   assert(n_edges==edge_count);
}


const Node& Graph::getNode(string lab) const
{
   for (const Node* pv : nodes) {
      if (pv->label==lab)
         return *pv;
   }
   cerr<<"node "+ lab+ "not found"<<endl;
   exit(EXIT_FAILURE);
}



Node* Graph::getNode(string lab)
{
   for (Node* v : nodes) {
      if (v->label==lab)
         return v;
   }
   cerr<<"node "+ lab+ "not found"<<endl;
   exit(EXIT_FAILURE);
}


   
int Graph::addNode(string lab, int index) {
   for (Node* pu : nodes) {
      if (pu->label==lab)
         return 0;
   }
   Node* pv=new Node;
   pv->index=index;
   pv->label=lab;
   double theta = 2*M_PI/n_nodes*index;
   pv->x=cos(theta);
   pv->y=sin(theta);
   nodes.push_back(pv);
   return 1;
}


ostream& operator<<(ostream& os, const Graph& g) {
   os<<g.getNodesN() <<" nodes; "<<g.getEdgesN()<<" edges\n";
   for (const Node* pv : g.getNodes()) {
      os<<*pv<<" ";
   }
   os<<"\n";
   for (const Edge* pe: g.getEdges()) {
      os<<*pe<<"\n";
   }
   return os;
}

}
