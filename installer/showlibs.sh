#!/bin/bash
otool -L ProximaController.app/Contents/Frameworks/*.dylib|grep -v executable_path|grep -v '/System/Library/Frameworks'|grep -v libSystem|grep -v libc++|grep -v libobjc|grep -v iconv|grep -v libz
