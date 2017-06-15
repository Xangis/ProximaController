# ProximaController

A MIDI controller application for Windows and Linux. This program was originally
published on http://zetacentauri.com and via the Ubuntu Software Center

![Proxima Controller Screenshot](https://github.com/Xangis/ProximaController/blob/master/images/proximacontroller1.gif)

The Proxima Controller is an application that allows you to use the mouse and computer keyboard 
to play external MIDI devices such as synthesizers and tone generators. It is also possible to 
play internal devices if they are designed to respond to MIDI messages (for example, the 
Microsoft GS Wavetable SW Synth). This application makes no sounds of its own and instead relies
on the MIDI devices it is controlling to produce sound.

It supports bank and patch changes, transmits on MIDI channels 1-16, includes pitch and 
modulation sliders, and has five octaves of control.

This project depends on my wxAudioControls library, a wxWidgets control library designed for
use with audio applications:
https://github.com/Xangis/wxAudioControls

The wxAudioControls should be checked out in a directory next to the Proxima Controller
directory (they should both have the same parent directory).

The GUI for this application was developed using wxWidgets:
http://www.wxwidgets.org

This program uses the RtMidi library by Gary P. Scavone.
http://www.music.mcgill.ca/~gary/rtmidi/

A prebuilt Windows installer and Linux binaries are available in the installer directory.
