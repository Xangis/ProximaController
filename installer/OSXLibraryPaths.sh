#!/bin/bash
install_name_tool -change librtmidi.2.1.0.dylib @executable_path/../Frameworks/librtmidi.2.1.0.dylib ProximaController.app/Contents/MacOS/ProximaController
install_name_tool -change /usr/local/lib/libwx_osx_cocoau_xrc-3.1.dylib @executable_path/../Frameworks/libwx_osx_cocoau_xrc-3.1.dylib ProximaController.app/Contents/MacOS/ProximaController
install_name_tool -change /usr/local/lib/libwx_osx_cocoau_html-3.1.dylib @executable_path/../Frameworks/libwx_osx_cocoau_html-3.1.dylib ProximaController.app/Contents/MacOS/ProximaController
install_name_tool -change /usr/local/lib/libwx_osx_cocoau_qa-3.1.dylib @executable_path/../Frameworks/libwx_osx_cocoau_qa-3.1.dylib ProximaController.app/Contents/MacOS/ProximaController
install_name_tool -change /usr/local/lib/libwx_osx_cocoau_adv-3.1.dylib @executable_path/../Frameworks/libwx_osx_cocoau_adv-3.1.dylib ProximaController.app/Contents/MacOS/ProximaController
install_name_tool -change /usr/local/lib/libwx_osx_cocoau_core-3.1.dylib @executable_path/../Frameworks/libwx_osx_cocoau_core-3.1.dylib ProximaController.app/Contents/MacOS/ProximaController
install_name_tool -change /usr/local/lib/libwx_baseu_xml-3.1.dylib @executable_path/../Frameworks/libwx_baseu_xml-3.1.dylib ProximaController.app/Contents/MacOS/ProximaController
install_name_tool -change /usr/local/lib/libwx_baseu_net-3.1.dylib @executable_path/../Frameworks/libwx_baseu_net-3.1.dylib ProximaController.app/Contents/MacOS/ProximaController
install_name_tool -change /usr/local/lib/libwx_baseu-3.1.dylib @executable_path/../Frameworks/libwx_baseu-3.1.dylib ProximaController.app/Contents/MacOS/ProximaController
otool -L ProximaController.app/Contents/MacOS/ProximaController
