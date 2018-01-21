#
# Stuff every FLTK application might need
#
#    If you take this for use in your own project, be sure to change
#    the 'FLTKCONFIG' setting to point to where it's installed
#    on your system. Common examples:
#
#	FLTKCONFIG = /usr/local/bin/fltk-config
#       FLTKCONFIG = /usr/local/src/fltk-1.3.x-svn/fltk-config
#
#    Set .SILENT in your Makefile if you want 'quieter' builds.
#

ifeq '$(OS)' "Windows_NT"
EXEEXT = .exe
endif

FLTKCONFIG   = /usr/local/bin/fltk-config
CXX          = $(shell $(FLTKCONFIG) --cxx) --std=c++14
CXXFLAGS     = $(shell $(FLTKCONFIG) --cxxflags) -Wall -Wfatal-errors -g
LINKFLTK     = $(shell $(FLTKCONFIG) --ldstaticflags)
LINKFLTK_GL  = $(shell $(FLTKCONFIG) --use-gl --ldstaticflags)
LINKFLTK_IMG = $(shell $(FLTKCONFIG) --use-images --ldstaticflags)
LINKFLTK_ALL = $(shell $(FLTKCONFIG) --use-images --use-gl --ldstaticflags)
.SUFFIXES: .cxx .h .fl .o $(EXEEXT)


OBJ = ../../Graph_lib/Graph.o ../../Graph_lib/GUI.o ../../Graph_lib/Window.o Vector2D.o Flock.o Steering.o main.o

# HOW TO COMPILE
%.o: %.cpp 
	@echo "*** Compile $<..."
	$(CXX) -I. $(CXXFLAGS) -c $< -o $@


flocking: ${OBJ}
	@echo "*** Linking $@..."
	$(CXX) $^ $(LINKFLTK_ALL) -o $@			



clean:
	rm *.o *~ flocking
