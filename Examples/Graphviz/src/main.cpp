#include<cstdio>
#include<cstdlib>

#include "../../FLTK/Simple_window.h"
#include "../../FLTK/Graph.h"

#include "Graph.h"

using namespace std;



Graph_lib::Point tl(100,200);  // the top left corner of the window                 
Graph_lib::Window win(tl,1200,800,"Graphviz");      



void call_back( void *graph)
{
  /*
	Implement here the update of the drawing
  */
  
  Fl::check();
  Fl::redraw();
     
  Fl::repeat_timeout(1/48.0,call_back,graph);

}



int main (int argc, char **argv) {
  string inputfile;
  if (argc==2) {
	inputfile=argv[1];
	timeLimit = atoi(argv[2]);
  }
  else {
	cout<<"graph filename"<<endl;
	exit(EXIT_FAILURE);
  }

  /*
	Read the graph
   */
  /*
	Implement here the initial drawing of the graph
   */
  
  win.color(Graph_lib::Color::white); // we set the background color
  Fl::add_timeout(1,call_back,&g);
  win.end(); // we tell FLTK that we will not add Widgets 
  win.show();
  return Fl::run();

}


