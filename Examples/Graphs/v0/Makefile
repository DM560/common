CXX=g++ -std=c++14 
# Wfatal-errors interrupts compilation after first error

# Falgs in Debug mode:
CXXFLAGS=-g -Wfatal-errors
#-fsanitize=address -fsanitize=undefined

#Falgs in Release mode:
#CXXFLAGS=-O3

INCLUDE_DIR=.
LIB_DIR=.

DEPS = Graph.h
OBJ = Graph.o main.o 

%.o: %.cpp $(DEPS)
	$(CXX) -I$(INCLUDE_DIR) $(CXXFLAGS) -c -o $@ $< 

graph: $(OBJ)
	$(CXX) -L$(LIB_DIR) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o *~ graph
