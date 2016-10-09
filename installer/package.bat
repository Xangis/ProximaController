echo This program runs the desktop app packager command to create a Windows 10 store package from an existing installer.
pause
DesktopAppConverter.exe -Installer "C:\Users\Xangis\code\ProximaController\installer\ProximaController1.11Setup.exe" -PackageName "ProximaController" -Version 1.1.1.0 -Makeappx -Destination "C:\Users\Xangis\code\ProximaController\installer" -InstallerArguments "/VERYSILENT" -Publisher "CN=Jason Champion" -Sign
Certutil -addStore TrustedPeople ProximaController\auto-generated.cer



