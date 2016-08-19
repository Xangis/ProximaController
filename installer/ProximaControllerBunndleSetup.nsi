;Include Modern UI

  !include "MUI2.nsh"
  !include "FileAssociation.nsh"

Name "Proxima Controller 1.1"
OutFile "ProximaController1.1Setup.exe"
InstallDir "$PROGRAMFILES\Zeta Centauri\Proxima Controller"
InstallDirRegKey HKLM "Software\ProximaController" "Install_Dir"
RequestExecutionLevel admin
!define MUI_ICON "proxima.ico"
!define MUI_UNICON "proxima.ico"

;Version Information

  VIProductVersion "1.1.0.0"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "Proxima Controller"
;  VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments" "A test comment"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "Zeta Centauri"
;  VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" "Test Application is a trademark of Fake company"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "Copyright 2006-2012 Zeta Centauri"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "Proxima Controller Installer"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "1.1.0.0"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductVersion" "1.1.0.0"

;Interface Settings

  !define MUI_ABORTWARNING

;Pages

  !insertmacro MUI_PAGE_LICENSE "License.txt"
;  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
      !define MUI_FINISHPAGE_NOAUTOCLOSE
      !define MUI_FINISHPAGE_RUN
      !define MUI_FINISHPAGE_RUN_CHECKED
      !define MUI_FINISHPAGE_RUN_TEXT "Launch Proxima Controller"
      !define MUI_FINISHPAGE_RUN_FUNCTION "LaunchProgram"
      !define MUI_FINISHPAGE_SHOWREADME ""
      !define MUI_FINISHPAGE_SHOWREADME_NOTCHECKED
      !define MUI_FINISHPAGE_SHOWREADME_TEXT "Create Desktop Shortcut"
      !define MUI_FINISHPAGE_SHOWREADME_FUNCTION finishpageaction
  !insertmacro MUI_PAGE_FINISH
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES

;Languages
 
  !insertmacro MUI_LANGUAGE "English"


; The following file is reserved in memory so that we can make
; a copy later on for DLL registering purposes. This DLL contains
; COM interfaces that need to be registered with the operating
; system before they can be used.
ReserveFile "${NSISDIR}\Plugins\BunndleOfferManager.dll"


; The stuff to install
Section "Proxima Controller"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File "ProximaController.exe"
  File "License.txt"
  File "proxima.ico"
  File "exclamation.xpm"
  File "info.xpm"
  File "help.xpm"
  File "octave.bmp"
  File "spin.bmp"
  File "proximacontrol.htb"
  File "vcredist_x86.exe"

  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\ProximaController "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ProximaController" "DisplayName" "Proxima Controller"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ProximaController" "DisplayVersion" "1.1"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ProximaController" "Publisher" "Zeta Centauri"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ProximaController" "DisplayIcon" "$INSTDIR\proxima.ico"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ProximaController" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ProximaController" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ProximaController" "NoRepair" 1
  WriteUninstaller "uninstall.exe"

  ExecWait '"$INSTDIR\vcredist_x86.exe /q"' 

SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\Zeta Centauri\Proxima Controller"
  CreateShortCut "$SMPROGRAMS\Zeta Centauri\Proxima Controller\Proxima Controller.lnk" "$INSTDIR\ProximaController.exe" "" "" 0
  ;CreateShortCut "$SMPROGRAMS\Zeta Centauri\Proxima Controller\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  WriteINIStr "$SMPROGRAMS\Zeta Centauri\Proxima Controller\Proxima Controller Website.url" "InternetShortcut" "URL" "http://zetacentauri.com/software_proximacontrol.htm"
  
SectionEnd

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ProximaCController"
  DeleteRegKey HKLM SOFTWARE\ProximaController

  ; Remove files and uninstaller
  Delete $INSTDIR\ProximaController.exe
  Delete $INSTDIR\License.txt
  Delete $INSTDIR\proxima.ico
  Delete $INSTDIR\exclamation.xpm
  Delete $INSTDIR\info.xpm
  Delete $INSTDIR\help.xpm
  Delete $INSTDIR\octave.bmp
  Delete $INSTDIR\spin.bmp
  Delete $INSTDIR\proximacontrol.htb
  Delete $INSTDIR\uninstall.exe


  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\Zeta Centauri\Proxima Controller\*.*"
  Delete "$DESKTOP\Proxima Controller.lnk"
  Delete "$SMPROGRAMS\Zeta Centauri\Proxima Controller\Proxima Controller Website.url"
  ;DeleteINISec "$SMPROGRAMS\Zeta Centauri\Proxima Controller\Proxima Controller Website.url" "InternetShortcut"

  ; Remove directories used
  RMDir "$SMPROGRAMS\Zeta Centauri\Proxima Controller"
  RMDir "$SMPROGRAMS\Zeta Centauri"
  RMDir "$INSTDIR"


SectionEnd

; This function is automatically executed when the installer starts
Function .onInit
	; make sure that the plugins directory exists before we access it
	InitPluginsDir
	
	; Extract the reserved DLL file
	File /oname=$PLUGINSDIR\BunndleOfferManager.reg.dll "${NSISDIR}\Plugins\BunndleOfferManager.dll"
	
	; Register the DLL with the operating system so the COM interfaces are known.
	RegDLL $PLUGINSDIR\BunndleOfferManager.reg.dll
FunctionEnd

; This function is automatically executed when the installer finishes
Function .onGUIEnd
	; Un-register the offer manager plugin with the operating system
	UnRegDLL $PLUGINSDIR\BunndleOfferManager.reg.dll
        Delete $INSTDIR\vcredist_x86.exe
FunctionEnd

Section instfiles
	BunndleOfferManager::nsisShowAllOffers "4B18923C-B656-4BEA-B2E2-212FF1779A7B" 1 512 400 "Proxima Controller"
SectionEnd

Function LaunchProgram
  ExecShell "" "$SMPROGRAMS\Zeta Centauri\Proxima Controller\Proxima Controller.lnk"
FunctionEnd

Function finishpageaction
  ;CreateShortCut "$DESKTOP\Proxima Controller.lnk" "$INSTDIR\ProximaController.exe" "" "" 0
  CreateShortcut "$DESKTOP\Proxima Controller.lnk" "$INSTDIR\ProximaController.exe"
FunctionEnd