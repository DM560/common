CXX=g++ -std=c++14 -Wfatal-errors
# Wfatal-errors interrupts compilation after first error
CXXFLAGS=-I. -g
DEPS = Graph.h
OBJ = Graph.o main.o 

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

graph: $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS)


clean:
	rm -f *.o *~ graph
