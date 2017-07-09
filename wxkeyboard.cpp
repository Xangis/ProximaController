#include "wx/wx.h"
#include "wx/aboutdlg.h"
#include "wx/strconv.h"
#include "wxkeyboard.h"

#include "exclamation.xpm"
#include "help.xpm"
#include "info.xpm"
#include "log.xpm"
#include "vector.xpm"
#include "spin.xpm"

IMPLEMENT_DYNAMIC_CLASS( wxKeyboard, wxDialog )

BEGIN_EVENT_TABLE( wxKeyboard, wxDialog )
    EVT_CLOSE( wxKeyboard::OnCloseWindow )
    EVT_KEY_DOWN( wxKeyboard::OnKeyDown )
    EVT_KEY_UP( wxKeyboard::OnKeyUp )
	EVT_CHOICE( ID_MIDI_DEVICE, wxKeyboard::OnChangeMidiDevice )
	EVT_BUTTON( ID_PANICBUTTON, wxKeyboard::OnPanic )
	EVT_BUTTON( ID_INFOBUTTON, wxKeyboard::OnInfo )
	EVT_BUTTON( ID_HELPBUTTON, wxKeyboard::OnHelp )
	EVT_BUTTON( ID_LOGGERBUTTON, wxKeyboard::OnLogger )
	EVT_BUTTON( ID_VECTORBUTTON, wxKeyboard::OnVector )

    EVT_SPIN_UP( ID_BANKSPIN, wxKeyboard::OnBankSpinUp )
    EVT_SPIN_DOWN( ID_BANKSPIN, wxKeyboard::OnBankSpinDown )

    EVT_SPIN_UP( ID_PATCHSPIN, wxKeyboard::OnPatchSpinUp )
    EVT_SPIN_DOWN( ID_PATCHSPIN, wxKeyboard::OnPatchSpinDown )

    EVT_SPIN_UP( ID_CHANNELSPIN, wxKeyboard::OnChannelSpinUp )
    EVT_SPIN_DOWN( ID_CHANNELSPIN, wxKeyboard::OnChannelSpinDown )

	EVT_COMMAND_SCROLL( ID_MODWHEEL, wxKeyboard::OnModWheel )
	EVT_COMMAND_SCROLL( ID_PITCHWHEEL, wxKeyboard::OnPitchWheel )

    EVT_LEFT_UP(wxKeyboard::OnMouseRelease) // Catches note off outside of an octave control.
END_EVENT_TABLE()


wxKeyboard::wxKeyboard( )
{
}

wxKeyboard::wxKeyboard( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}


bool wxKeyboard::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    _bankSpin = NULL;
    _patchSpin = NULL;
    _channelSpin = NULL;
	_bankText = NULL;
	_channelText = NULL;
	_patchText = NULL;
    _device = NULL;
	_panicButton = NULL;
	_infoButton = NULL;
	_helpButton = NULL;
	_ichannel = 1;
	_ipatch = 1;
	_ibank = 1;
	_helpCtrl = NULL;
    _octave[0] = NULL;
    _octave[1] = NULL;
    _octave[2] = NULL;
    _octave[3] = NULL;
    _octave[4] = NULL;
	// Open default MIDI device
    _midiOutDevice = new RtMidiOut();
	_midiInDevice = new RtMidiIn();
	memset( _noteState, 0, (sizeof(bool) * 128 ) );
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();
    SetFocus();

	wxFileSystem::AddHandler(new wxZipFSHandler());
	_helpCtrl = new wxHtmlHelpController(wxHF_CONTENTS);
#ifdef __APPLE__
        wxString filename = wxString::Format(_("%s/%s"), wxStandardPaths::Get().GetResourcesDir(), _("proximacontrol.htb"));
        wxString iconFile = wxString::Format(_("%s/%s"), wxStandardPaths::Get().GetResourcesDir(), _("proxima.ico"));
#endif
#ifdef WIN32
	wxFileName filename = wxStandardPaths::Get().GetDataDir() + _("\\proximacontrol.htb");
    wxString iconFile = _("proxima.ico");
#endif
#ifdef linux
	wxFileName filename = wxString(_("./proximacontrol.htb"));
        wxString iconFIle = _("proxima.ico");
#endif
	if( !_helpCtrl->AddBook(filename))
	{
		wxMessageBox( _("Unable to load help file.  Please make sure that proximacontrol.htb is in the program directory." ));
	}
	// Create subwindows.
	_logger = new wxMidiLogger(this);
	_vector = new wxVectorDlg(this);
	// Load icon.
	if( _icon.LoadFile(iconFile, wxBITMAP_TYPE_ICO ))
	{
		_logger->SetIcon(_icon);
		_vector->SetIcon(_icon);
		SetIcon(_icon);
	}
    return true;
}

void wxKeyboard::OnMouseRelease( wxMouseEvent& event )
{
	AllNotesOff();
	event.Skip();
}

void wxKeyboard::CreateControls()
{
    wxKeyboard* itemDialog1 = this;

	wxColour foregroundColour = wxColour( 0, 160, 80 );
	wxColour backgroundColour = wxColour( 2, 30, 2 );

    this->SetBackgroundColour(backgroundColour);
    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("Bank"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText4->SetForegroundColour(foregroundColour);
	itemStaticText4->Connect(wxID_STATIC, wxEVT_LEFT_UP, wxMouseEventHandler(wxKeyboard::OnMouseRelease), NULL, this);
    itemBoxSizer3->Add(itemStaticText4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    _bankText = new wxStaticText( itemDialog1, ID_BANKTEXT, _T("1"), wxDefaultPosition, wxSize( 22, -1 ), 0 );
    _bankText->SetForegroundColour(foregroundColour);
	_bankText->Connect(ID_BANKTEXT, wxEVT_LEFT_UP, wxMouseEventHandler(wxKeyboard::OnMouseRelease), NULL, this);
    itemBoxSizer3->Add(_bankText, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	_bankSpin = new wxBitmapSpinButton( itemDialog1, ID_BANKSPIN, wxDefaultPosition, wxSize( 16, 22 ), wxSP_ARROW_KEYS|wxSP_VERTICAL );
    _bankSpin->SetRange(1, 127);
    _bankSpin->SetXpmBitmap(spin_xpm);
	_bankSpin->Connect(ID_BANKSPIN, wxEVT_LEFT_UP, wxMouseEventHandler(wxKeyboard::OnMouseRelease), NULL, this);
	_bankSpin->SetToolTip( _("Change patch bank" ));
	itemBoxSizer3->Add(_bankSpin, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText* itemStaticText8 = new wxStaticText( itemDialog1, wxID_STATIC, _("Patch"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText8->SetForegroundColour(foregroundColour);
	itemStaticText8->Connect(wxID_STATIC, wxEVT_LEFT_UP, wxMouseEventHandler(wxKeyboard::OnMouseRelease), NULL, this);
    itemBoxSizer3->Add(itemStaticText8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    _patchText = new wxStaticText( itemDialog1, ID_PATCHTEXT, _T("1"), wxDefaultPosition, wxSize( 22, -1 ), 0 );
    _patchText->SetForegroundColour(foregroundColour);
	_patchText->Connect(ID_PATCHTEXT, wxEVT_LEFT_UP, wxMouseEventHandler(wxKeyboard::OnMouseRelease), NULL, this);
    itemBoxSizer3->Add(_patchText, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    _patchSpin = new wxBitmapSpinButton( itemDialog1, ID_PATCHSPIN, wxDefaultPosition, wxSize( 16, 22 ), wxSP_ARROW_KEYS|wxSP_VERTICAL );
    _patchSpin->SetRange(1, 128);
    _patchSpin->SetXpmBitmap(spin_xpm);
    _patchSpin->Connect(ID_PATCHSPIN, wxEVT_LEFT_UP, wxMouseEventHandler(wxKeyboard::OnMouseRelease), NULL, this);
    _patchSpin->SetToolTip( _("Change patch number") );
    itemBoxSizer3->Add(_patchSpin, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText* itemStaticText10 = new wxStaticText( itemDialog1, wxID_STATIC, _("MIDI Channel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText10->SetForegroundColour(foregroundColour);
    itemBoxSizer3->Add(itemStaticText10, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    _channelText = new wxStaticText( itemDialog1, ID_CHANNELTEXT, _T("1"), wxDefaultPosition, wxDefaultSize, 0 );
    _channelText->SetForegroundColour(foregroundColour);
    itemBoxSizer3->Add(_channelText, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    _channelSpin = new wxBitmapSpinButton( itemDialog1, ID_CHANNELSPIN, wxDefaultPosition, wxSize( 16, 22 ), wxSP_ARROW_KEYS|wxSP_VERTICAL );
    _channelSpin->SetRange(1, 16);
    _channelSpin->SetXpmBitmap(spin_xpm);
    itemBoxSizer3->Add(_channelSpin, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    wxStaticText* itemStaticText11 = new wxStaticText( itemDialog1, wxID_STATIC, _("MIDI Device"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText11->SetForegroundColour(foregroundColour);
    itemBoxSizer3->Add(itemStaticText11, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    // Look for MIDI output devices before creating choice box.
    wxArrayString deviceList;
    unsigned int nPorts = _midiOutDevice->getPortCount();
    std::string portName;
    std::cout << "\nThere are " << nPorts << " MIDI output ports available.\n";
    for ( unsigned int i=0; i < nPorts; i++ )
    {
        try
        {
          portName = _midiOutDevice->getPortName(i);
          wxString port(portName.c_str(), wxConvUTF8, portName.length());
          deviceList.Add( port );
        }
        catch (RtMidiError &error)
        {
          error.printMessage();
        }
        std::cout << "  Output Port #" << i+1 << ": " << portName << '\n';
    }
    std::cout << '\n';

    try
    {
        _midiOutDevice->openPort(0);
    }
    catch( RtMidiError &error )
    {
        // I don't know why trying to get a std::string into a wxString is so fucking hard.
        wxString message(error.getMessage().c_str(), wxConvUTF8, error.getMessage().length());
        wxMessageBox(message, _("Error Opening MIDI Out"));
    }

    try
    {
        _midiInDevice->openPort(0);
        _midiInDevice->setCallback(MidiMessageHandler, this);
    }
    catch( RtMidiError &error )
    {
        // I don't know why trying to get a std::string into a wxString is so fucking hard.
        /* No warning messages for lack of MIDI in. This is a MIDI out app.
        wxString message(error.getMessage().c_str(), wxConvUTF8, error.getMessage().length());
        wxMessageBox(message, _("Error Opening MIDI In"));
        */
    }

    _device = new wxKeylessChoice( itemDialog1, ID_MIDI_DEVICE, wxDefaultPosition, wxDefaultSize, deviceList );
	_device->SetSelection(0);
	_device->SetForegroundColour(foregroundColour);
	_device->SetBackgroundColour(backgroundColour);
    itemBoxSizer3->Add(_device, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	wxBitmap panicBitmap( exclamation_xpm, wxBITMAP_TYPE_XPM );
	_panicButton = new wxBitmapButton( itemDialog1, ID_PANICBUTTON, panicBitmap, wxDefaultPosition, wxSize( 26, 26 ) );
	itemBoxSizer3->Add(_panicButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	_panicButton->Connect(ID_PANICBUTTON, wxEVT_KEY_DOWN, wxKeyEventHandler(wxKeyboard::OnKeyDown), NULL, this);
	_panicButton->Connect(ID_PANICBUTTON, wxEVT_KEY_UP, wxKeyEventHandler(wxKeyboard::OnKeyUp), NULL, this);
	_panicButton->Connect(ID_PANICBUTTON, wxEVT_LEFT_UP, wxMouseEventHandler(wxKeyboard::OnMouseRelease), NULL, this);
    _panicButton->SetToolTip(_("Panic: Send all notes off MIDI message"));

	wxBitmap infoBitmap( info_xpm, wxBITMAP_TYPE_XPM );
	_infoButton = new wxBitmapButton( itemDialog1, ID_INFOBUTTON, infoBitmap, wxDefaultPosition, wxSize( 26, 26 ) );
	itemBoxSizer3->Add(_infoButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	_infoButton->Connect(ID_INFOBUTTON, wxEVT_KEY_DOWN, wxKeyEventHandler(wxKeyboard::OnKeyDown), NULL, this);
	_infoButton->Connect(ID_INFOBUTTON, wxEVT_KEY_UP, wxKeyEventHandler(wxKeyboard::OnKeyUp), NULL, this);
	_infoButton->Connect(ID_INFOBUTTON, wxEVT_LEFT_UP, wxMouseEventHandler(wxKeyboard::OnMouseRelease), NULL, this);

	wxBitmap helpBitmap( help_xpm, wxBITMAP_TYPE_XPM );
	_helpButton = new wxBitmapButton( itemDialog1, ID_HELPBUTTON, helpBitmap, wxDefaultPosition, wxSize( 26, 26 ) );
	itemBoxSizer3->Add(_helpButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	_helpButton->Connect(ID_HELPBUTTON, wxEVT_KEY_DOWN, wxKeyEventHandler(wxKeyboard::OnKeyDown), NULL, this);
	_helpButton->Connect(ID_HELPBUTTON, wxEVT_KEY_UP, wxKeyEventHandler(wxKeyboard::OnKeyUp), NULL, this);
	_helpButton->Connect(ID_HELPBUTTON, wxEVT_LEFT_UP, wxMouseEventHandler(wxKeyboard::OnMouseRelease), NULL, this);
    _helpButton->SetToolTip(_("Help"));

#ifndef DEMOVERSION
#ifndef __APPLE__
	wxBitmap logBitmap( log_xpm, wxBITMAP_TYPE_XPM );
	_loggerButton = new wxBitmapButton( itemDialog1, ID_LOGGERBUTTON, logBitmap, wxDefaultPosition, wxSize( 26, 26 ) );
	itemBoxSizer3->Add(_loggerButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	_loggerButton->Connect(ID_INFOBUTTON, wxEVT_KEY_DOWN, wxKeyEventHandler(wxKeyboard::OnKeyDown), NULL, this);
	_loggerButton->Connect(ID_INFOBUTTON, wxEVT_KEY_UP, wxKeyEventHandler(wxKeyboard::OnKeyUp), NULL, this);
	_loggerButton->Connect(ID_INFOBUTTON, wxEVT_LEFT_UP, wxMouseEventHandler(wxKeyboard::OnMouseRelease), NULL, this);
    _loggerButton->SetToolTip(_("Show the MIDI message logger"));

	wxBitmap vectorBitmap( vector_xpm, wxBITMAP_TYPE_XPM );
	_vectorButton = new wxBitmapButton( itemDialog1, ID_VECTORBUTTON, vectorBitmap, wxDefaultPosition, wxSize( 26, 26 ) );
	itemBoxSizer3->Add(_vectorButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	_vectorButton->Connect(ID_VECTORBUTTON, wxEVT_KEY_DOWN, wxKeyEventHandler(wxKeyboard::OnKeyDown), NULL, this);
	_vectorButton->Connect(ID_VECTORBUTTON, wxEVT_KEY_UP, wxKeyEventHandler(wxKeyboard::OnKeyUp), NULL, this);
	_vectorButton->Connect(ID_VECTORBUTTON, wxEVT_LEFT_UP, wxMouseEventHandler(wxKeyboard::OnMouseRelease), NULL, this);
    _vectorButton->SetToolTip(_("Show the Vector Control Pad"));
#endif
#endif

    wxBoxSizer* itemBoxSizer12 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer12, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	_pitchWheel = new wxSlider( itemDialog1, ID_PITCHWHEEL, 8192, 0, 16383, wxDefaultPosition, wxSize( 30, 108 ), wxSL_VERTICAL|wxSL_INVERSE );
	itemBoxSizer12->Add( _pitchWheel, 0, wxALL, 5 );
	_pitchWheel->Connect(ID_PITCHWHEEL, wxEVT_KEY_DOWN, wxKeyEventHandler(wxKeyboard::OnKeyDown), NULL, this);
	_pitchWheel->Connect(ID_PITCHWHEEL, wxEVT_KEY_UP, wxKeyEventHandler(wxKeyboard::OnKeyUp), NULL, this);

	_modWheel = new wxSlider( itemDialog1, ID_MODWHEEL, 0, 0, 16383, wxDefaultPosition, wxSize( 30, 108 ), wxSL_VERTICAL|wxSL_INVERSE );
	itemBoxSizer12->Add( _modWheel, 0, wxALL, 5 );
	_modWheel->Connect(ID_MODWHEEL, wxEVT_KEY_DOWN, wxKeyEventHandler(wxKeyboard::OnKeyDown), NULL, this);
	_modWheel->Connect(ID_MODWHEEL, wxEVT_KEY_UP, wxKeyEventHandler(wxKeyboard::OnKeyUp), NULL, this);

#ifndef __APPLE__
    wxString octavePath = _("octave.bmp");
#else
    wxString octavePath = wxString::Format(_("%s//%s"), wxStandardPaths::Get().GetResourcesDir(), _("octave.bmp"));
#endif
    wxBitmap _octaveBitmap;
    _octaveBitmap.LoadFile(octavePath, wxBITMAP_TYPE_BMP);
    _octave[0] = new wxOctaveCtrl( itemDialog1, ID_KEYBOARD1, _octaveBitmap, 36, this, wxDefaultPosition, wxSize(137, 99), wxNO_BORDER );
    itemBoxSizer12->Add(_octave[0], 0, wxALIGN_CENTER_VERTICAL|wxALL, 0);
	_octave[0]->Connect(ID_KEYBOARD1, wxEVT_KEY_DOWN, wxKeyEventHandler(wxKeyboard::OnKeyDown), NULL, this);
	_octave[0]->Connect(ID_KEYBOARD1, wxEVT_KEY_UP, wxKeyEventHandler(wxKeyboard::OnKeyUp), NULL, this);

    _octave[1] = new wxOctaveCtrl( itemDialog1, ID_KEYBOARD2, _octaveBitmap, 48, this, wxDefaultPosition, wxSize(137, 99), wxNO_BORDER );
    itemBoxSizer12->Add(_octave[1], 0, wxALIGN_CENTER_VERTICAL|wxALL, 0);
	_octave[1]->Connect(ID_KEYBOARD2, wxEVT_KEY_DOWN, wxKeyEventHandler(wxKeyboard::OnKeyDown), NULL, this);
	_octave[1]->Connect(ID_KEYBOARD2, wxEVT_KEY_UP, wxKeyEventHandler(wxKeyboard::OnKeyUp), NULL, this);

    _octave[2] = new wxOctaveCtrl( itemDialog1, ID_KEYBOARD3, _octaveBitmap, 60, this, wxDefaultPosition, wxSize(137, 99), wxNO_BORDER );
    itemBoxSizer12->Add(_octave[2], 0, wxALIGN_CENTER_VERTICAL|wxALL, 0);
	_octave[2]->Connect(ID_KEYBOARD3, wxEVT_KEY_DOWN, wxKeyEventHandler(wxKeyboard::OnKeyDown), NULL, this);
	_octave[2]->Connect(ID_KEYBOARD3, wxEVT_KEY_UP, wxKeyEventHandler(wxKeyboard::OnKeyUp), NULL, this);

    _octave[3] = new wxOctaveCtrl( itemDialog1, ID_KEYBOARD4, _octaveBitmap, 72, this, wxDefaultPosition, wxSize(137, 99), wxNO_BORDER );
    itemBoxSizer12->Add(_octave[3], 0, wxALIGN_CENTER_VERTICAL|wxALL, 0);
	_octave[3]->Connect(ID_KEYBOARD4, wxEVT_KEY_DOWN, wxKeyEventHandler(wxKeyboard::OnKeyDown), NULL, this);
	_octave[3]->Connect(ID_KEYBOARD4, wxEVT_KEY_UP, wxKeyEventHandler(wxKeyboard::OnKeyUp), NULL, this);

    _octave[4] = new wxOctaveCtrl( itemDialog1, ID_KEYBOARD5, _octaveBitmap, 84, this, wxDefaultPosition, wxSize(137, 99), wxNO_BORDER );
    itemBoxSizer12->Add(_octave[4], 0, wxALIGN_CENTER_VERTICAL|wxALL, 0);
	_octave[4]->Connect(ID_KEYBOARD5, wxEVT_KEY_DOWN, wxKeyEventHandler(wxKeyboard::OnKeyDown), NULL, this);
	_octave[4]->Connect(ID_KEYBOARD5, wxEVT_KEY_UP, wxKeyEventHandler(wxKeyboard::OnKeyUp), NULL, this);
}

bool wxKeyboard::ShowToolTips()
{
    return true;
}

void wxKeyboard::OnRightClick( int note )
{
	return;
}

void wxKeyboard::PlayNote( int note, bool receivedFromMidi )
{
	SoundNote( note );
}

wxBitmap wxKeyboard::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
    wxUnusedVar(name);
    if (name == _T("octave.bmp"))
    {
        wxBitmap bitmap(_T("octave.bmp"), wxBITMAP_TYPE_BMP);
        return bitmap;
    }
    return wxNullBitmap;
}

wxIcon wxKeyboard::GetIconResource( const wxString& name )
{
    wxUnusedVar(name);
    return wxNullIcon;
}

void wxKeyboard::OnChannelSpinUp( wxSpinEvent& event )
{
    // Set MIDI Channel
    int value = atoi(_channelText->GetLabel().ToAscii());
	++value;
	if( value > 16 )
	{
		value = 1;
	}
	_channelText->SetLabel( wxString::Format( _("%d"), value ) );
	// Turn off all notes before changing channel.
	// Send "all notes off" message.
	AllNotesOff();
	_ichannel = value;
    event.Skip(false);
}

void wxKeyboard::OnChannelSpinDown( wxSpinEvent& event )
{
    // Set MIDI Channel
    int value = atoi(_channelText->GetLabel().ToAscii());
	--value;
	if( value < 1 )
	{
		value = 16;
	}
	_channelText->SetLabel( wxString::Format( _("%d"), value ) );
	// Turn off all notes before changing channel.
	// Send "all notes off" message.
	AllNotesOff();
    _ichannel = value;
    event.Skip(false);
}

/**
* Handles bank up spinner events.
*/
void wxKeyboard::OnBankSpinUp( wxSpinEvent& event )
{
    // Set Bank
    int value = atoi(_bankText->GetLabel().ToAscii());
	++value;
	if( value > 128 )
	{
		value = 1;
	}
	SetBank( value );
	SetPatch( _ipatch );
	event.Skip(false);
}

/**
* Handles bank down spinner events.
*/
void wxKeyboard::OnBankSpinDown( wxSpinEvent& event )
{
    // Set Bank
    int value = atoi(_bankText->GetLabel().ToAscii());
	--value;
	if( value < 1 )
	{
		value = 128;
	}
	SetBank( value );
	SetPatch( _ipatch );
    event.Skip(false);
}

/**
* Changes patch banks, sending MIDI bank change messages.
*/
void wxKeyboard::SetBank( int bank )
{
	_bankText->SetLabel( wxString::Format( _("%d"), bank ));
    _ibank = bank;
    //std::cout << "Setting bank to " << bank << " on channel " << _ichannel << std::endl;
	// Always send MSB as bank 1.
    SendMidiMessage( 0, 0, 0, (_ichannel + 175), false );
    SendMidiMessage( 0, bank-1, 32, (_ichannel + 175), false );
}

/**
* Handles patch spinner up events.
*/
void wxKeyboard::OnPatchSpinUp( wxSpinEvent& event )
{
    // Set Patch
    int value = atoi(_patchText->GetLabel().ToAscii());
	++value;
	if( value > 128 )
	{
		value = 1;
	}
    // Send MIDI message
	// Patch change: 0xC[channel] + byte for patch change.
	SetPatch( value );
    event.Skip(true);
}

/**
* Handles patch spinner down events.
*/
void wxKeyboard::OnPatchSpinDown( wxSpinEvent& event )
{
    // Set Patch
    int value = atoi(_patchText->GetLabel().ToAscii());
	--value;
	if( value < 1 )
	{
		value = 128;
	}
	SetPatch( value );
	event.Skip(true);
}

/**
* Handles patch changes, sends MIDI patch change message.
*/
void wxKeyboard::SetPatch( int value )
{
    // Send MIDI message
	// Patch change: 0xC[channel] + byte for patch change.
    //std::cout << "Setting patch to " << value << " on channel " << _ichannel << std::endl;
	_patchText->SetLabel( wxString::Format( _("%d"), value ));
    _ipatch = value;
    SendMidiMessage( 0, 0, (value-1), (_ichannel + 191), true );
}

/**
* Handles window close events.
*/
void wxKeyboard::OnCloseWindow( wxCloseEvent& event )
{
    Destroy();
    event.Skip();
}

/**
* Handles key down events.
*/
void wxKeyboard::OnKeyDown( wxKeyEvent& event )
{
    int key = event.GetKeyCode();
    int note = GetNoteValue( key );
	if( note == 0 )
	{
		event.Skip();
		return;
	}
	// Find out which octave control we're using so we can light the not on light.
	int octavenum = ((note - 36 ) / 12 );
	if( octavenum >= 0 && octavenum <= 4 )
	{
		// Turn on one of the 12 available notes in the octave.
		PlayNote(note);
	}
    SoundNote( note );
	event.Skip();
}

/**
* Handles key up events, turns off a playing note.
*/
void wxKeyboard::OnKeyUp( wxKeyEvent& event )
{
	int key = event.GetKeyCode();
	int note = GetNoteValue( key );
	if( note == 0 )
	{
		event.Skip();
		return;
	}
	StopNote( note );
    event.Skip();
}

/**
* Gets the MIDI note number from a keyboard code.
*/
int wxKeyboard::GetNoteValue( int value )
{
	int note = 0;
    switch( value )
    {
    case WXK_F1:
        note = 36;
        break;
    case WXK_F2:
        note = 37;
        break;
    case WXK_F3:
        note = 38;
        break;
    case WXK_F4:
        note = 39;
        break;
    case WXK_F5:
        note = 40;
        break;
    case WXK_F6:
        note = 41;
        break;
    case WXK_F7:
        note = 42;
        break;
    case WXK_F8:
        note = 43;
        break;
    case WXK_F9:
        note = 44;
        break;
    case WXK_F10:
        note = 45;
        break;
    case WXK_F11:
        note = 46;
        break;
    case WXK_F12:
        note = 47;
        break;
    case '1':
        note = 48;
        break;
    case '2':
        note = 49;
        break;
    case '3':
        note = 50;
        break;
    case '4':
        note = 51;
        break;
    case '5':
        note = 52;
        break;
    case '6':
        note = 53;
        break;
    case '7':
        note = 54;
        break;
    case '8':
        note = 55;
        break;
    case '9':
        note = 56;
        break;
    case '0':
        note = 57;
        break;
    case '-':
        note = 58;
        break;
	case 43:
        note = 59;
        break;
    case 81: // q
        note = 60;
        break;
    case 87: // w
        note = 61;
        break;
    case 69: // e
        note = 62;
        break;
    case 82: // r
        note = 63;
        break;
    case 84: // t
        note = 64;
        break;
    case 89: // y
        note = 65;
        break;
    case 85: //
        note = 66;
        break;
    case 73: // i
        note = 67;
        break;
    case 79: // o
        note = 68;
        break;
    case 80: // p
        note = 69;
        break;
    case '[':
        note = 70;
        break;
    case ']':
        note = 71;
        break;
    case 65: // a
        note = 72;
        break;
    case 83: // s
        note = 73;
        break;
    case 68: // d
        note = 74;
        break;
    case 70: // f
        note = 75;
        break;
    case 71: // g
        note = 76;
        break;
    case 72: // h
        note = 77;
        break;
    case 74: // j
        note = 78;
        break;
    case 75: // k
        note = 79;
        break;
    case 76: // l
        note = 80;
        break;
    case ';':
        note = 81;
        break;
    case '\'':
        note = 82;
        break;
    case '\r':
        note = 83;
        break;
	case 90: // z
        note = 84;
        break;
    case 88: // x
        note = 85;
        break;
    case 67: // c
        note = 86;
        break;
    case 86: // v
        note = 87;
        break;
    case 66: // b
        note = 88;
        break;
    case 78: // n
        note = 89;
        break;
    case 77: // m
        note = 90;
        break;
    case ',':
        note = 91;
        break;
    case '.':
        note = 92;
        break;
    case '/':
        note = 93;
        break;
	case 306: // (right) shift
		note = 94;
		break;
	case 92: // backslash
		note = 95;
		break;
    default:
		note = 0;
        break;
    }
	return note;
}

/**
* Takes the note number and figures out which octave object it refers to.
*/
int wxKeyboard::GetOctaveByNote( int note )
{
	// Minimum octave and below is translated to minimum octave.
	if( note < 36 )
	{
		return 0;
	}
	// Maximum octave and above is translated to maximum octave.
	else if( note >= 96 )
	{
		return 6;
	}
	else
	{
		return (note - 36) / 12;
	}
}

void wxKeyboard::StopNote( int note, bool receivedFromMidi )
{
	NoteOff( note );
}

void wxKeyboard::SoundNote( int note )
{
	if( _noteState[note] == false )
	{
		// Find out which octave control we're using so we can light the note on light.
		int octavenum = GetOctaveByNote(note);
		if( octavenum >= 0 && octavenum <= 4 )
		{
			// Turn on one of the 12 available notes in the octave.
			_octave[octavenum]->NoteIndicatorOn((note % 12));
		}

		// 0x00 (not used), 0x7F [127] (velocity), 0x2B (note number), 0x90 [144] (note on)+channel
        //std::cout << "Turning on note " << note << " on channel " << _ichannel << std::endl;
        SendMidiMessage( 0, 127, note, (143 + _ichannel) );
		_noteState[note] = true;
	}
}

void wxKeyboard::NoteOff( int note )
{
	int octavenum = GetOctaveByNote(note);
	if( octavenum >= 0 && octavenum < MAX_OCTAVES )
	{
		// Turn off one of the 12 available notes in the octave.
		_octave[octavenum]->NoteIndicatorOff((note % 12 ));
	}

	// We send the note off regardless of whether it's actually on or not - we may
	// have had a mistriggered event.
	// 0x00 (not used), 0x00 (velocity), 0x2B (note number), 0x80 [128] (note off)+channel
    //std::cout << "Turning off note " << note << " on channel " << _ichannel << std::endl;
    SendMidiMessage( 0, 0, note, (127 + _ichannel) );
	_noteState[note] = false;
}

/**
* Processes MIDI output device selection changes.
*/
void wxKeyboard::OnChangeMidiDevice( wxCommandEvent& event )
{
    AllNotesOff();
    try
    {
        // Close the old device
        std::cout << "Closing port: " << _midiOutDevice->getPortName() << std::endl;
        _midiOutDevice->closePort();
	    // Subtract 1 because the first device is -1 (MIDI Mapper).
	    int selection = _device->GetCurrentSelection( );
        std::cout << "Opening port: " << _midiOutDevice->getPortName(selection) << std::endl;
	    _midiOutDevice->openPort(selection);
    }
    catch( RtMidiError &error )
    {
        // I don't know why trying to get a std::string into a wxString is so fucking hard.
        //wxMessageBox(wxString(error.getMessage()), _("Error Opening MIDI Out"));
    }
}

/**
* Handles pitch wheel messages, sends MIDI controller data.
*/
void wxKeyboard::OnPitchWheel( wxScrollEvent& event )
{
	int value;
	if( event.GetEventType() == wxEVT_SCROLL_THUMBRELEASE )
	{
		value = 8192;
		_pitchWheel->SetValue(8192);
		Refresh();
	}
	else
	{
		value = _pitchWheel->GetValue();
	}
	// We may just want to use the fine value for this - coarse might be what hoses us.
	int coarse = value / 128;
	int fine = value % 128;
	// 00 (not used), XX (coarse), XX (fine), 0xEx (message + channel)
	SendMidiMessage( 0, coarse, fine, (223 + _ichannel) );
	event.Skip();
}

/**
* Handles mod wheel messages, sends MIDI controller data.
*/
void wxKeyboard::OnModWheel( wxScrollEvent& event )
{
	int value = _modWheel->GetValue();
	int coarse = value / 128;
	int fine = value % 128;
	// Modwheel message is two parts - coarse and fine.
	// 00 (not used), 0xXX (value:coarse), 0x01 (controller), 0xBX (175 + channel)
	SendMidiMessage( 0, coarse, 1, (175 + _ichannel) );
	// 00 (not used), 0xXX (value:fine), 0x21 [33] (controller), 0xBX (175 + channel)
	SendMidiMessage( 0, fine, 33, (175 + _ichannel) );
	event.Skip();
}

/**
* Handles panic button, turns everything off.
*/
void wxKeyboard::OnPanic( wxCommandEvent& event )
{
	AllNotesOff();
	AllControllersOff();
	AllSoundOff();
	event.Skip();
}

/**
* Sends MIDI all sounds off message.
*/
void wxKeyboard::AllSoundOff( void )
{
	// 00 (not used), 0x00, 120, 0xBX (message + channel)
	SendMidiMessage( 0, 0, 120, (175 + _ichannel) );
}

/**
* Turns off all notes and indicators.
*/
void wxKeyboard::AllNotesOff( bool receivedFromMidi )
{
    //std::cout << "All notes off." << std::endl;
	for(int i = 0; i < MAX_OCTAVES; i++ )
	{
		_octave[i]->TurnOffAll();
	}
    for( int i = 0; i < 128; i++ )
    {
        if( _noteState[i] != 0 )
        {
            NoteOff(i);
        }
    }
	memset( _noteState, 0, (sizeof(bool) * 128 ) );
	// 00 (not used), 0x00, 123, 0xBX (message + channel)
	SendMidiMessage( 0, 0, 123, (175 + _ichannel) );
	// Turn off any red dots.
	Refresh();
}

/**
* Turns off all MIDI controllers.
*/
void wxKeyboard::AllControllersOff( void )
{
	// 00 (not used), 0x00, 121, 0xBX (message + channel)
	SendMidiMessage( 0, 0, 121, (175 + _ichannel) );
	// Reset modwheel position
	_modWheel->SetValue(0);
	_pitchWheel->SetValue(8192);
	Refresh();
}

/**
* Shows help file.
*/
void wxKeyboard::OnHelp( wxCommandEvent& event )
{
	// Show help file.
	_helpCtrl->DisplayContents();
	event.Skip();
}

/**
* Shows logger.
*/
void wxKeyboard::OnLogger( wxCommandEvent& event )
{
	// Show logger.
        if( _logger != NULL )
        {
	    _logger->Show();
        }
	event.Skip();
}

/**
* Shows logger.
*/
void wxKeyboard::OnVector( wxCommandEvent& event )
{
	// Show vector pad.
	_vector->Show();
	event.Skip();
}


/**
* Shows about box.
*/
void wxKeyboard::OnInfo( wxCommandEvent& event )
{
    // Show about box.
    wxAboutDialogInfo info;
    info.SetName(_("Proxima Controller"));
    info.SetVersion(_("1.12"));
    info.SetCopyright(_("(c) 2006-2017 Jason Champion"));
    info.AddDeveloper(_("Jason Champion"));
    info.SetIcon(_icon);
    info.SetLicense(_("Proxima Controller is freeware and may be distributed freely under the terms of the MIT license."));
    info.SetWebSite(_("https://github.com/Xangis/ProximaController"));
    info.SetDescription(_("Proxima Controller uses the wxWidgets and RtMidi libraries."));

    wxAboutBox(info);

    event.Skip();
}

void wxKeyboard::SendMidiMessage(unsigned char byte1, unsigned char byte2, unsigned char byte3, unsigned char byte4, bool shortmsg)
{
    std::vector<unsigned char> msg;
    msg.push_back(byte4);
    msg.push_back(byte3);
    if( !shortmsg )
    {
      msg.push_back(byte2);
      if( byte1 != 0 )
      {
        msg.push_back(byte1);
      }
    }
    _midiOutDevice->sendMessage(&msg);
    if( _logger != NULL )
    {
        wxString logMessage = wxString::Format(_("%02x %02x %02x %02x"), byte1, byte2, byte3, byte4);
        _logger->AddOutMessage(logMessage);
    }
}

void wxKeyboard::LogMidiInMessage( wxString& message )
{
    if( _logger != NULL )
    {
        _logger->AddInMessage(message);
    }
}

/**
* Callback for MIDI message data.
*/
void MidiMessageHandler( double deltatime, std::vector< unsigned char > *message, void *userData )
{
	wxKeyboard* key = (wxKeyboard*)userData;

    unsigned char a = 0;
    unsigned char b = 0;
    unsigned char c = 0;
    unsigned char d = 0;
    if( message->size() == 4 )
    {
        a = (*message)[3];
        b = (*message)[2];
        c = (*message)[1];
        d = (*message)[0];
    }
    else if( message->size() == 3 )
    {
        b = (*message)[2];
        c = (*message)[1];
        d = (*message)[0];
    }
    else if( message->size() == 2 )
    {
        c = (*message)[1];
        d = (*message)[0];
    }
    else if( message->size() == 1 )
    {
        d = (*message)[0];
    }
	wxString logMessage = wxString::Format(_("%02x %02x %02x %02x"), a, b, c, d);
	key->LogMidiInMessage(logMessage);
}
