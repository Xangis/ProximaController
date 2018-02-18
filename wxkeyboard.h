#ifndef _WXKEYBOARD_H_
#define _WXKEYBOARD_H_

/*!
 * Includes
 */
#include "wx/filesys.h"
#include "wx/fs_zip.h"
#include "wx/html/helpctrl.h"
#include "../wxAudioControls/wxOctaveCtrl.h"
#include "OctaveCallback.h"
#include "wx/stdpaths.h"
#include "../wxAudioControls/wxBitmapSpinButton.h"
//typedef wxSpinButton wxBitmapSpinButton;
#include "../wxAudioControls/wxKeylessChoice.h"
#include "../wxAudioControls/wxMidiLogger.h"
#include "../wxAudioControls/wxVectorDlg.h"
#include "RtMidi.h"

/*!
 * Forward declarations
 */
class wxSpinCtrl;

#define MAX_OCTAVES 5

/*!
 * Control identifiers
 */
#define ID_KEYBOARD_DLG 10000
#define SYMBOL_WXKEYBOARD_STYLE wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|wxWANTS_CHARS|wxMINIMIZE_BOX
#define SYMBOL_WXKEYBOARD_TITLE _("Proxima Controller")
#define SYMBOL_WXKEYBOARD_IDNAME ID_KEYBOARD_DLG
#define SYMBOL_WXKEYBOARD_SIZE wxSize(400, 300)
#define SYMBOL_WXKEYBOARD_POSITION wxDefaultPosition
#define ID_BANKSPIN 10001
#define ID_PATCHSPIN 10003
#define ID_CHANNELSPIN 10005
#define ID_KEYBOARD1 10006
#define ID_KEYBOARD2 10007
#define ID_KEYBOARD3 10008
#define ID_KEYBOARD4 10009
#define ID_KEYBOARD5 10010
#define ID_MIDI_DEVICE 10011
#define ID_BANKTEXT 10012
#define ID_PATCHTEXT 10013
#define ID_CHANNELTEXT 10014
#define ID_PITCHWHEEL 10015
#define ID_MODWHEEL 10016
#define ID_PANICBUTTON 10017
#define ID_INFOBUTTON 10018
#define ID_HELPBUTTON 10019
#define ID_LOGGERBUTTON 10020
#define ID_VECTORBUTTON 10021

/*!
 * Compatibility
 */
#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif

/*!
 * wxKeyboard class declaration
 */
#ifdef __APPLE__
class wxKeyboard: public wxFrame, public OctaveCallback
#else
class wxKeyboard: public wxDialog, public OctaveCallback
#endif
{
    DECLARE_DYNAMIC_CLASS( wxKeyboard )
    DECLARE_EVENT_TABLE()
public:
    /// Constructors
    wxKeyboard( );
    wxKeyboard( wxWindow* parent, wxWindowID id = SYMBOL_WXKEYBOARD_IDNAME, const wxString& caption = SYMBOL_WXKEYBOARD_TITLE, const wxPoint& pos = SYMBOL_WXKEYBOARD_POSITION, const wxSize& size = SYMBOL_WXKEYBOARD_SIZE, long style = SYMBOL_WXKEYBOARD_STYLE );
	virtual ~wxKeyboard() { };
    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_WXKEYBOARD_IDNAME, const wxString& caption = SYMBOL_WXKEYBOARD_TITLE, const wxPoint& pos = SYMBOL_WXKEYBOARD_POSITION, const wxSize& size = SYMBOL_WXKEYBOARD_SIZE, long style = SYMBOL_WXKEYBOARD_STYLE );
    void CreateControls();
    void OnCloseWindow( wxCloseEvent& event );
    void OnKeyDown( wxKeyEvent& event );
    void OnKeyUp( wxKeyEvent& event );
    void OnBankSpinUp( wxSpinEvent& event );
    void OnBankSpinDown( wxSpinEvent& event );
    void OnPatchSpinUp( wxSpinEvent& event );
    void OnPatchSpinDown( wxSpinEvent& event );
    void OnChannelSpinUp( wxSpinEvent& event );
    void OnChannelSpinDown( wxSpinEvent& event );
	void OnChangeMidiDevice( wxCommandEvent& event );
	void OnPitchWheel( wxScrollEvent& event );
	void OnModWheel( wxScrollEvent& event );
	void OnPanic( wxCommandEvent& event );
	void OnInfo( wxCommandEvent& event );
	void OnHelp( wxCommandEvent& event );
	void OnLogger( wxCommandEvent& event );
	void OnVector( wxCommandEvent& event );
        void OnExit( wxCommandEvent& event );
	int GetNoteValue( int value );
	void SoundNote( int note );
	void NoteOff( int note );
	void AllControllersOff( void );
	void AllSoundOff( void );
	void SetPatch( int patch );
	void SetBank( int bank );
    void OnMouseRelease( wxMouseEvent &event );
    wxBitmap GetBitmapResource( const wxString& name );
    wxIcon GetIconResource( const wxString& name );
	void LogMidiInMessage( wxString& message );
    static bool ShowToolTips();
	int GetOctaveByNote( int note );
	// OctaveCallback members.
	void PlayNote( int note, bool receivedFromMidi = false );
	void StopNote( int note, bool receivedFromMidi = false );
	void AllNotesOff( bool receivedFromMidi = false );
	void OnRightClick( int note );
	// End OctaveCallback members.
    void SendMidiMessage( unsigned char byte1, unsigned char byte2, unsigned char byte3, unsigned char byte4, bool shortmsg=false );
private:
	wxIcon _icon;
	wxStaticText* _bankText;
	wxStaticText* _patchText;
	wxStaticText* _channelText;
	wxBitmapSpinButton* _bankSpin;
	wxBitmapSpinButton* _patchSpin;
	wxBitmapSpinButton* _channelSpin;
	wxBitmapButton* _panicButton;
	wxBitmapButton* _infoButton;
	wxBitmapButton* _helpButton;
	//wxBitmapButton* _loggerButton;
	//wxBitmapButton* _vectorButton;
	wxSlider* _modWheel;
	wxSlider* _pitchWheel;
	wxHtmlHelpController* _helpCtrl;
    int _ichannel;
    int _ipatch;
    int _ibank;
	bool _noteState[128];
    wxKeylessChoice* _device;
    wxOctaveCtrl* _octave[MAX_OCTAVES];
    RtMidiOut* _midiOutDevice;
	RtMidiIn* _midiInDevice;
	wxMidiLogger* _logger;
	wxVectorDlg* _vector;
};

void MidiMessageHandler( double deltatime, std::vector< unsigned char > *message, void *userData );

#endif
    // _WXKEYBOARD_H_
