#include "wx/wx.h"
#include "wxkeyboardapp.h"

/*!
 * Application instance implementation
 */

IMPLEMENT_APP( wxKeyboardApp )

/*!
 * wxKeyboardApp type definition
 */

IMPLEMENT_CLASS( wxKeyboardApp, wxApp )

/*!
 * wxKeyboardApp event table definition
 */

BEGIN_EVENT_TABLE( wxKeyboardApp, wxApp )
END_EVENT_TABLE()

/*!
 * Constructor for wxKeyboardApp
 */
wxKeyboardApp::wxKeyboardApp()
{
}

wxKeyboardApp::~wxKeyboardApp()
{
}

/*!
 * Initialisation for wxKeyboardApp
 */
bool wxKeyboardApp::OnInit()
{
    // Remove the comment markers above and below this block
    // to make permanent changes to the code.
    wxInitAllImageHandlers();
    wxKeyboard* mainWindow = new wxKeyboard(NULL, ID_KEYBOARD_DLG );
    mainWindow->Show(true);

    return true;
}

/*!
 * Cleanup for wxKeyboardApp
 */
int wxKeyboardApp::OnExit()
{
    return wxApp::OnExit();
}

