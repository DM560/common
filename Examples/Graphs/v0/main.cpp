#include<cstdio>
#include<cstdlib>

#include "Graph.h"

using namespace std;

int main (int argc, char **argv) {
  if (argc==2) {
    Graph g(argv[1]);
    cout<<g<<endl;
  }
  else {
    cout<<"graph filename"<<endl;
  }
  
  exit(EXIT_SUCCESS);
}
