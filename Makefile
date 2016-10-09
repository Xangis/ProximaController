# Vorbital makefile.  Requires wxWidgets.
# by default, wx-config from the PATH is used
# Uses wxWidgets 3.1, but may work with 3.0.2
WX_CONFIG := wx-config

# Main executable file
PROGRAM = ProximaController
INCLUDEDIR = ../../lib/rtmidi-2.1.0

# Object files
OBJECTS = wxOctaveCtrl.o wxkeyboardapp.o wxKeylessChoice.o wxKeylessSpinCtrl.o wxkeyboard.o wxBitmapSpinButton.o $(INCLUDEDIR)/RtMidi.o

CXX = $(shell $(WX_CONFIG) --cxx)

.SUFFIXES:	.o .cpp

.cpp.o :
	$(CXX) -ggdb -c -Wall -D__LINUX_ALSASEQ__ -I$(INCLUDEDIR) `$(WX_CONFIG) --cxxflags` -o $@ $<

all:    $(PROGRAM)

$(PROGRAM):	$(OBJECTS)
	$(CXX) -o $(PROGRAM) $(OBJECTS) `$(WX_CONFIG) --libs` -lasound

clean: 
	rm -f *.o $(PROGRAM)
