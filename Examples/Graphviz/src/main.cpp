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


   vector<Graph_lib::Circle> circles;

   for (Graph::Node* v : g.getNodes()) {
     circles.push_back( Graph_lib::Circle(Graph_lib::Point(100*v->x, 100*v->y),20) );
   }
   
   for (Graph_lib::Circle& c: circles) {
     win.attach(c);
   }
   
   win.wait_for_button();       // give control to the display engine

 
  
  exit(EXIT_SUCCESS);
}
