#include "Simple_window.h"
#include "Graph.h"

int main()
{
   using namespace Graph_lib;	// use our graphics interface library
   
   Point tl(100,200);			// a point 
   
   Simple_window win(tl,600,400,"Canvas"); 	// make a simple window
   
   Polygon poly;		// make a shape (a polygon)
   
   poly.add(Point(300,200));	// add three points to the polygon
   poly.add(Point(350,100));
   poly.add(Point(400,200));
   
   poly.set_color(Color::red);	    // make the polygon red
   
   win.attach(poly);		// connect poly to the window
   
   win.wait_for_button();	// give control to the display engine
}
