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
CXXFLAGS     = $(shell $(FLTKCONFIG) --cxxflags) -Wall -Wfatal-errors
LINKFLTK     = $(shell $(FLTKCONFIG) --ldstaticflags)
LINKFLTK_GL  = $(shell $(FLTKCONFIG) --use-gl --ldstaticflags)
LINKFLTK_IMG = $(shell $(FLTKCONFIG) --use-images --ldstaticflags)
LINKFLTK_ALL = $(shell $(FLTKCONFIG) --use-images --use-gl --ldstaticflags)
.SUFFIXES: .cxx .h .fl .o $(EXEEXT)


OBJ = ../../FLTK/Graph.o ../../FLTK/GUI.o ../../FLTK/Window.o Graph.o main.o

# HOW TO COMPILE
%.o: %.cpp 
	@echo "*** Compile $<..."
	$(CXX) -I. $(CXXFLAGS) -c $< -o $@


graphviz: ${OBJ}
	@echo "*** Linking $@..."
	$(CXX) $^ $(LINKFLTK_ALL) -o $@			



clean:
	rm *.o *~
