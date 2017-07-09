# ProximaController

A MIDI controller application for Windows and Linux. 

![Proxima Controller Screenshot](https://github.com/Xangis/ProximaController/blob/master/images/ProximaController1.11.png)

The Proxima Controller is an application that allows you to use the mouse and 
computer keyboard to play external MIDI devices such as synthesizers and tone 
generators. It is also possible to play internal devices if they are designed 
to respond to MIDI messages (for example, the Microsoft GS Wavetable SW Synth). 
This application makes no sounds of its own and instead relies on the MIDI 
devices it is controlling to produce sound.

Each row of keys on a standard computer keyboard controls a different octave 
of notes on the virtual keyboard.

This program was originally published on http://zetacentauri.com and via the 
Ubuntu Software Center and was downloaded more than 70,000 times before being 
open-sourced.

It is released under the terms of the MIT license. See the LICENSE file for 
details.

A prebuilt Windows installer is available in the installer directory here:

https://github.com/Xangis/ProximaController/blob/master/installer/ProximaController1.11Setup.exe

Linux binaries are also in the installer/linux_binaries directory, but you are
better off building from source on Linux.

### Features

- Supports bank and patch changes
- Transmits on any MIDI channel from 1-16
- Includes pitch and modulation sliders
- Has five octaves of control
- Can select any MIDI device detected by your operating system

# Building

The GUI for this application was developed using wxWidgets. You can download
wxWidgets here:

http://www.wxwidgets.org

This program also uses the RtMidi library by Gary P. Scavone, which is
available here:

http://www.music.mcgill.ca/~gary/rtmidi/

This project depends on my wxAudioControls library, a wxWidgets control library 
designed for use with audio applications: https://github.com/Xangis/wxAudioControls

### Windows

Use the included Visual Studio project. You'll have to change the include and
library paths to match where wxWidgets and RtMidi are on your system.

There is an InnoSetup installer script in the installer directory. You'll
need to update paths in that file to match where things are on your system
in order to build an installer.

### Linux

You can get probably get wxWidgets using your operating system's package 
manager. On Debian-based systems, you can run:

sudo apt-get install libwxgtk3.0-dev

Build with this command line:

make -f Makefile.linux

### OSX

This application has been built on OSX, but it may need a bit more work. To
build, you'll need the command-line compiler tools installed.

Just type "make" to build the program. You may need to change file maths in 
the Makefile to point to your library locations.

Once the binary is built, you can run installer/OSXLibraryPaths.sh to change
library paths in the application bundle.

At one point a build was submitted to the app store, but it was not approved.

# Changelog

### Version 1.11:

- Switched to RtMidi for MIDI control.
- Updated to wxWidgets 3.0 (from 2.8) for a cleaner/smoother UI

### Version 1.1:

- Fixed an issue that would cause a note to fail to release if you clicked on 
  one octave, dragged your mouse to another, and then released the mouse button.
- Minor adjustments to user interface aesthetics.

# Development Status

I consider this application complete and no new features are being developed 
for it. However, I do still maintain it and will update it as needed.

On some platforms, especially Windows and OSX, build and installer paths are 
specific to my development environment and more work could be done to make 
things a bit more portable.

I am willing to accept pull requests if you have improvements to contribute.
