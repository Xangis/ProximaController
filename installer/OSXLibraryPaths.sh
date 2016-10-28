#!/bin/bash
install_name_tool -change librtmidi.2.1.0.dylib @executable_path/../Frameworks/librtmidi.2.1.0.dylib ProximaController.app/Contents/MacOS/ProximaController
# wxWidgets.
install_name_tool -change /usr/local/lib/libwx_osx_cocoau_xrc-3.1.dylib @executable_path/../Frameworks/libwx_osx_cocoau_xrc-3.1.dylib ProximaController.app/Contents/MacOS/ProximaController
install_name_tool -change /usr/local/lib/libwx_osx_cocoau_html-3.1.dylib @executable_path/../Frameworks/libwx_osx_cocoau_html-3.1.dylib ProximaController.app/Contents/MacOS/ProximaController
install_name_tool -change /usr/local/lib/libwx_osx_cocoau_qa-3.1.dylib @executable_path/../Frameworks/libwx_osx_cocoau_qa-3.1.dylib ProximaController.app/Contents/MacOS/ProximaController
install_name_tool -change /usr/local/lib/libwx_osx_cocoau_adv-3.1.dylib @executable_path/../Frameworks/libwx_osx_cocoau_adv-3.1.dylib ProximaController.app/Contents/MacOS/ProximaController
install_name_tool -change /usr/local/lib/libwx_osx_cocoau_core-3.1.dylib @executable_path/../Frameworks/libwx_osx_cocoau_core-3.1.dylib ProximaController.app/Contents/MacOS/ProximaController
install_name_tool -change /usr/local/lib/libwx_baseu_xml-3.1.dylib @executable_path/../Frameworks/libwx_baseu_xml-3.1.dylib ProximaController.app/Contents/MacOS/ProximaController
install_name_tool -change /usr/local/lib/libwx_baseu_net-3.1.dylib @executable_path/../Frameworks/libwx_baseu_net-3.1.dylib ProximaController.app/Contents/MacOS/ProximaController
install_name_tool -change /usr/local/lib/libwx_baseu-3.1.dylib @executable_path/../Frameworks/libwx_baseu-3.1.dylib ProximaController.app/Contents/MacOS/ProximaController
# wxWidget library references to other wxWidgets libraries.
# adv.txt		core.txt	html.txt	net.txt		qa.txt		xml.txt		xrc.txt
install_name_tool -change /usr/local/lib/libwx_osx_cocoau_core-3.1.0.0.0.dylib @executable_path/../Frameworks/libwx_osx_cocoau_core-3.1.dylib ProximaController.app/Contents/Frameworks/libwx_osx_cocoau_adv-3.1.dylib
install_name_tool -change /usr/local/lib/libwx_baseu-3.1.0.0.0.dylib @executable_path/../Frameworks/libwx_baseu-3.1.dylib ProximaController.app/Contents/Frameworks/libwx_osx_cocoau_adv-3.1.dylib
install_name_tool -change /usr/local/lib/libwx_baseu-3.1.0.0.0.dylib @executable_path/../Frameworks/libwx_baseu-3.1.dylib ProximaController.app/Contents/Frameworks/libwx_osx_cocoau_core-3.1.dylib
install_name_tool -change /usr/local/lib/libwx_osx_cocoau_core-3.1.0.0.0.dylib @executable_path/../Frameworks/libwx_osx_cocoau_core-3.1.dylib ProximaController.app/Contents/Frameworks/libwx_osx_cocoau_html-3.1.dylib
install_name_tool -change /usr/local/lib/libwx_baseu-3.1.0.0.0.dylib @executable_path/../Frameworks/libwx_baseu-3.1.dylib ProximaController.app/Contents/Frameworks/libwx_osx_cocoau_html-3.1.dylib
install_name_tool -change /usr/local/lib/libwx_baseu-3.1.0.0.0.dylib @executable_path/../Frameworks/libwx_baseu-3.1.dylib ProximaController.app/Contents/Frameworks/libwx_baseu_net-3.1.dylib
install_name_tool -change /usr/local/lib/libwx_osx_cocoau_core-3.1.0.0.0.dylib @executable_path/../Frameworks/libwx_osx_cocoau_core-3.1.dylib ProximaController.app/Contents/Frameworks/libwx_osx_cocoau_qa-3.1.dylib
install_name_tool -change /usr/local/lib/libwx_baseu-3.1.0.0.0.dylib @executable_path/../Frameworks/libwx_baseu-3.1.dylib ProximaController.app/Contents/Frameworks/libwx_osx_cocoau_qa-3.1.dylib
install_name_tool -change /usr/local/lib/libwx_baseu_xml-3.1.0.0.0.dylib @executable_path/../Frameworks/libwx_baseu_xml-3.1.dylib ProximaController.app/Contents/Frameworks/libwx_osx_cocoau_qa-3.1.dylib
install_name_tool -change /usr/local/lib/libwx_baseu-3.1.0.0.0.dylib @executable_path/../Frameworks/libwx_baseu-3.1.dylib ProximaController.app/Contents/Frameworks/libwx_baseu_xml-3.1.dylib
install_name_tool -change /usr/local/lib/libwx_osx_cocoau_core-3.1.0.0.0.dylib @executable_path/../Frameworks/libwx_osx_cocoau_core-3.1.dylib ProximaController.app/Contents/Frameworks/libwx_osx_cocoau_xrc-3.1.dylib
install_name_tool -change /usr/local/lib/libwx_baseu-3.1.0.0.0.dylib @executable_path/../Frameworks/libwx_baseu-3.1.dylib ProximaController.app/Contents/Frameworks/libwx_osx_cocoau_xrc-3.1.dylib
install_name_tool -change /usr/local/lib/libwx_baseu_xml-3.1.0.0.0.dylib @executable_path/../Frameworks/libwx_baseu_xml-3.1.dylib ProximaController.app/Contents/Frameworks/libwx_osx_cocoau_xrc-3.1.dylib
install_name_tool -change /usr/local/lib/libwx_osx_cocoau_html-3.1.0.0.0.dylib @executable_path/../Frameworks/libwx_osx_cocoau_html-3.1.dylib ProximaController.app/Contents/Frameworks/libwx_osx_cocoau_xrc-3.1.dylib
install_name_tool -change /usr/local/lib/libwx_osx_cocoau_adv-3.1.0.0.0.dylib @executable_path/../Frameworks/libwx_osx_cocoau_adv-3.1.dylib ProximaController.app/Contents/Frameworks/libwx_osx_cocoau_xrc-3.1.dylib
#install_name_tool -change  @executable_path/../Frameworks/ ProximaController.app/Contents/Frameworks/
otool -L ProximaController.app/Contents/MacOS/ProximaController
