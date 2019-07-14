#!/bin/bash
echo "--- CODE SIGNING ProximaController.app ---"
codesign -f --deep -s "3rd Party Mac Developer Application: Jason Champion (G6PFF85X2R)" ProximaController.app --entitlements ProximaController.app/Contents/Resources/Entitlements.plist
echo "--- CREATING AND SIGNING ProximaController.pkg ---"
productbuild --sign "3rd Party Mac Developer Installer: Jason Champion (G6PFF85X2R)" --component ProximaController.app /Applications ProximaController.pkg
