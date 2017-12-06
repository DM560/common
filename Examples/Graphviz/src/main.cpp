#include<cstdio>
#include<cstdlib>
#include "../../FLTK/Simple_window.h"
#include "../../FLTK/Graph.h"

#include "Graph.h"

using namespace std;
//using namespace Graph_lib;   // use our graphics interface library

int main (int argc, char **argv) {
  if (argc==2) {
  }
  else {
    cout<<"graph filename"<<endl;
  }

    Graph::Graph g(argv[1]);
    cout<<g<<endl;
  
   Graph_lib::Point tl(100,200);                   // a point 
   
   Simple_window win(tl,600,400,"Canvas");      // make a simple window


   vector<Graph_lib::Circle*> circles;
   vector<Graph_lib::Text*> labels;

   for (Graph::Node* v : g.getNodes()) {
     circles.push_back(new Graph_lib::Circle(Graph_lib::Point(200+100*v->x, 200-100*v->y),15) );
     labels.push_back(new Graph_lib::Text(Graph_lib::Point(200+100*v->x, 200-100*v->y),v->label) );

     win.attach(*circles[circles.size()-1]);    
     win.attach(*labels[labels.size()-1]);    

   }

   vector<Graph_lib::Line*> lines;
   for (Graph::Edge* pe : g.getEdges() ) {

    lines.push_back(new Graph_lib::Line(
     circles[pe->from->index]->center(),
     circles[pe->to->index]->center()
    ));
     win.attach(*lines[lines.size()-1]);
    
   }
   
   win.wait_for_button();       // give control to the display engine

 
  
  exit(EXIT_SUCCESS);
}
