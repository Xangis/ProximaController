# Vorbital makefile.  Requires wxWidgets.
# by default, wx-config from the PATH is used
# Uses wxWidgets 3.1, but may work with 3.0.2
WX_CONFIG := wx-config

# Main executable file
PROGRAM = installer/ProximaController.app/Contents/MacOS/ProximaController
INCLUDEDIR = ../../lib/rtmidi-2.1.0
LIBDIR = ../../lib/rtmidi-2.1.0

# Object files
OBJECTS = ../wxAudioControls/wxOctaveCtrl.o wxkeyboardapp.o ../wxAudioControls/wxKeylessChoice.o ../wxAudioControls/wxKeylessSpinCtrl.o wxkeyboard.o ../wxAudioControls/wxBitmapSpinButton.o $(INCLUDEDIR)/RtMidi.o ../wxAudioControls/wxMidiLogger.o ../wxAudioControls/wxVectorDlg.o

#CXX = $(shell $(WX_CONFIG) --cxx)
CXX = $(shell $(WX_CONFIG) --cxx) -g -ggdb

.SUFFIXES:	.o .cpp

.cpp.o :
	$(CXX)  -D__MACOSX_CORE__ -ggdb -c -Wall -I$(INCLUDEDIR) `$(WX_CONFIG) --cxxflags` -o $@ $<

all:    $(PROGRAM)

$(PROGRAM):	$(OBJECTS)
	$(CXX) -D__MACOSX_CORE__ -o $(PROGRAM) $(OBJECTS) `$(WX_CONFIG) --libs` -L$(LIBDIR) -lrtmidi -framework CoreMidi -framework CoreAudio

clean: 
	rm -f *.o ../wxAudioControls/*.o $(PROGRAM)
