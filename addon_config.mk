
meta:
	ADDON_NAME = np-miscela
	ADDON_DESCRIPTION = mix different scripts
	ADDON_AUTHOR = Nicola Pisanti
	ADDON_TAGS = "live coding" "VJ" "mixer"
	ADDON_URL = http://github.com/npisanti/np-miscela

common:
	ADDON_SOURCES_EXCLUDE += libs/ofxLua
	ADDON_INCLUDES_EXCLUDE += libs/ofxLua
	
	
linux64:
	ADDON_PKG_CONFIG_LIBRARIES += luajit
	
linux:
	ADDON_PKG_CONFIG_LIBRARIES += luajit
	
msys2:
	ADDON_CFLAGS += -DLUA_USE_WINDOWS
	
vs:
	ADDON_CFLAGS += -DLUA_USE_WINDOWS

linuxarmv6l:
	ADDON_PKG_CONFIG_LIBRARIES += luajit
	
linuxarmv7l:
	ADDON_PKG_CONFIG_LIBRARIES += luajit

android/armeabi:
	# not tested, probably works :)

android/armeabi-v7a:	
	# not tested, probably works :)

osx:
	ADDON_CFLAGS += -DLUA_USE_MACOSX

ios:


