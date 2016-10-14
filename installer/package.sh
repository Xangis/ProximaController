#!/bin/bash
codesign -f --deep -s "3rd Party Mac Developer Application: Jason Champion (G6PFF85X2R)" ProximaController.app --entitlements ProximaController.app/Contents/Resources/Entitlements.plist
productbuild --sign "3rd Party Mac Developer Installer: Jason Champion (G6PFF85X2R)" --component ProximaController.app /Applications ProximaController.pkg
