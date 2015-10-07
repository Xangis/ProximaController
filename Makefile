# Vorbital makefile.  Requires wxWidgets.
# by default, wx-config from the PATH is used
# Uses wxWidgets 2.8, not 2.9.
WX_CONFIG := /usr/bin/wx-config

# Main executable file
PROGRAM = ProximaController
INCLUDEDIR = rtmidi-1.0.11

# Object files
OBJECTS = wxOctaveCtrl.o wxkeyboardapp.o wxKeylessChoice.o wxKeylessSpinCtrl.o wxkeyboard.o wxBitmapSpinButton.o rtmidi-1.0.11/RtMidi.o

CXX = $(shell $(WX_CONFIG) --cxx)

.SUFFIXES:	.o .cpp

.cpp.o :
	$(CXX) -ggdb -c -Wall -D__LINUX_ALSASEQ__ -I$(INCLUDEDIR) `$(WX_CONFIG) --cxxflags` -o $@ $<

all:    $(PROGRAM)

$(PROGRAM):	$(OBJECTS)
	$(CXX) -o $(PROGRAM) $(OBJECTS) `$(WX_CONFIG) --libs` -lasound

clean: 
	rm -f *.o $(PROGRAM)
