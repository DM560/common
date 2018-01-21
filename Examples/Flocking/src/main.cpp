#include<cstdio>
#include<cstdlib>

#include "../../Graph_lib/Simple_window.h"
#include "../../Graph_lib/Graph.h"

#include "Flock.h"
#include "Steering.h"


// This is the size of the world in both directions from 0 (i.e. from
  // -WORLD_SIZE to +WORLD_SIZE)
  #define WORLD_SIZE 600
  
  // This is the gap between grid lines
  #define GRID_SIZE 5
  
  // The number of boids in the simulation
  #define BOIDS 30
  
  // 
  #define MAX_SPEED 50.0
  #define MAX_ACCELERATION 50.0
  
  // The relative blend weights
  #define SEPARATION_WEIGHT ((double)2.0)
  #define COHESION_WEIGHT ((double)1.0)
  #define VMA_WEIGHT ((double)2.0)
  
  using namespace std;
  using namespace Flocking;
  using namespace Graph_lib;   // use our graphics interface library
  
  
  
  class FlockingAnimation {
  private:  
    vector<Graph_lib::Circle*> circles;
    vector<Graph_lib::Line*> links;
    
    // make a simple window
    Graph_lib::Window *win;
    
    void renderBoid(const Flocking::Location &at);
    void renderLink(const Flocking::Location &from, const Flocking::Location &to );
    void display();
    static void call_back( void *flock);
    
    /** Holds the steering behaviours. */
    Separation *separation;
    Cohesion *cohesion;
    VelocityMatch *vMA;
    BlendedSteering *steering;
    
    Flocking::Flock *pflock;  
  public:
    FlockingAnimation();
    
  };
  
  //BlendedSteering *FlockingAnimation::steering;
  
  FlockingAnimation::FlockingAnimation() {
    win = new Graph_lib::Window(Graph_lib::Point(100,200),WORLD_SIZE,WORLD_SIZE,"Canvas");
    
    
    const int xmax = win->x_max (); // window size (600 by 400)
    const int ymax = win->y_max ();
    const int x_orig = xmax /2;
    const int y_orig = ymax /2;
    
    pflock = new Flocking::Flock(BOIDS,xmax,MAX_SPEED);
    
    
    // Set up the steering behaviours (we use one for all)
		separation = new Separation;
		separation->maxAcceleration = MAX_ACCELERATION;
		separation->neighbourhoodRay = (double)20.0;
		separation->theFlock = pflock;
		
		cohesion = new Cohesion;
		cohesion->maxAcceleration = MAX_ACCELERATION;
		cohesion->neighbourhoodRay = (double)30.0;
		cohesion->theFlock = pflock;
		
		vMA = new VelocityMatch;
		vMA->maxAcceleration = MAX_ACCELERATION;
		vMA->neighbourhoodRay = (double)45.0;
		vMA->theFlock = pflock;
		
		steering = new BlendedSteering;
		steering->behaviours.push_back(BlendedSteering::BehaviourAndWeight(
			separation, SEPARATION_WEIGHT
		));
		steering->behaviours.push_back(BlendedSteering::BehaviourAndWeight(
			cohesion, COHESION_WEIGHT
		));
		steering->behaviours.push_back(BlendedSteering::BehaviourAndWeight(
			vMA, VMA_WEIGHT
		));
    
    
    cout<<*pflock<<endl;
    display();
    
    //  Fl::redraw();
    win->color(Graph_lib::Color::white);
    Fl::add_timeout(1,FlockingAnimation::call_back,(void*) this);
    //win->end();
    //Fl::visual(FL_DOUBLE|FL_INDEX);
    win->show();
    Fl::run();
    
  }
  
  
  
  void FlockingAnimation::renderBoid(const Flocking::Location &at) {
    
    
    Point center(static_cast<int> (at.x),
    static_cast<int> (at.y));
    Graph_lib::Circle* pc = new Graph_lib::Circle(center,5);
    pc->set_fill_color(Graph_lib::Color::blue);
    circles.push_back(pc);
    
    //      labels.push_back(new Graph_lib::Text(center,v->label) );
    
    win->attach(*circles[circles.size()-1]);    
    //win.attach(*labels[labels.size()-1]);   
    
  }
  
  void FlockingAnimation::renderLink(const Flocking::Location &from, const Flocking::Location &to ) {
    
    
    Graph_lib::Line* ln = new Graph_lib::Line(
      Graph_lib::Point(from.x,from.y),
      Graph_lib::Point(to.x,to.y)
    );
    ln->set_color(Graph_lib::Color::green);
    
    links.push_back(ln);
    win->attach(*links[links.size()-1]);
  }
  
  void FlockingAnimation::display() {
    for (auto c : circles)
    win->detach(*c);
    circles.clear();
    for (auto ln : links)
    win->detach(*ln);
    links.clear();
    for (unsigned i =0;i<pflock->getNBoids(); ++i) {
      try {
        renderBoid(pflock->getBoid(i).position);
      }
      catch (out_of_range e) {
        cerr<<"index out of range"<<e.what()<<endl;
        exit(1);
      }
      /*
      try {
        for (Flocking::Boid* pb : pflock->getNeighbors(i))
        {
          renderLink(pflock->getBoid(i).position, pb->position);
        }
      } catch (out_of_range e) {
        cerr<<"index out of range"<<e.what()<<endl;
        exit(1);
      }*/
    }
  }
  
  
  void FlockingAnimation::call_back( void *flocking)
  {
    FlockingAnimation *f = (FlockingAnimation*) flocking;
    
    double duration=(double)1/50.0;
    
    
    SteeringResult steer;
    SteeringResult temp;
    
    for (Boid *pb : f->pflock->getBoids())
    {
      // Get the steering output
      f->steering->pboid = pb;
      f->steering->getSteering(&steer);
      
      // Update the kinematic
      pb->integrate(duration, steer);
      //pb->kinematic[i].setOrientationFromVelocity();
      
      // Check for maximum speed
      pb->trimMaxSpeed();
      
      // Keep in bounds of the world
      pb->WrapWorld();
    }
    //cout<<*(f->pflock)<<endl;
    f->display();
    
    Fl::check();
    Fl::redraw();
    //char c;
    //cin>>c;
    
    Fl::repeat_timeout(duration,call_back,flocking);
    //  ++i;
    //}
  }
  
  
  
  int main () {
    FlockingAnimation();
    
    return 0;
  }
  
  
  
  /*
  Assign each node in the graph an initial location.
  While the layout is not yet finished:
  Have each node exert a repulsive force on each other node.
  Have each edge exert an attractive force on its endpoints.
  Move the nodes according to the net force acting on them.
  */
  
  /*
  time_t startTime = time(NULL);
  double elapsedTime = difftime(time(NULL), startTime);
  
  
  
  
  
  
  win.redraw();
  win.wait_for_button();       // give control to the display engine
  elapsedTime = difftime(time(NULL), startTime);
  
}
win.wait_for_button();       // give control to the display engine

exit(EXIT_SUCCESS);
}

*/
