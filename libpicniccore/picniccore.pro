TEMPLATE = lib
TARGET = picniccore

CONFIG  += dll

HEADERS += src/pmessage.h \
	   src/pmessage_p.h \
	   src/pcommunity.h \
	   src/picnicdefs.h \
	   src/pdeviceinfo.h \
	   src/pcommunitymanager.h \
	   src/pchannel.h \
	   src/pchannel_p.h \
	   src/pnetwork.h \
	   src/pencrypt.h \
	   src/pencmessage.h \
	   src/pencmessage_p.h
SOURCES += src/pmessage.cpp \
	   src/pmessage_p.cpp \
	   src/pcommunity.cpp \
	   src/picnicdefs.cpp \
	   src/pdeviceinfo.cpp \
	   src/pcommunitymanager.cpp \
	   src/pchannel.cpp \
	   src/pchannel_p.cpp \
	   src/pnetwork.cpp \
	   src/pencrypt.cpp \
	   src/pencmessage.cpp \
	   src/pencmessage_p.cpp

# This part is intended for Maemo packaging, hence
# the conditional which will be used in the package build script
maemo5 {
    #VARIABLES
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }
    
    INCLUDEPATH += /usr/include/awarenetcore
    LIBS +=  -lawarenetcore \
             -lawarenetmessages \
             -lawarenetcoreservices \
	     -lgcrypt \
	     -lgpg-error

    BINDIR = $$PREFIX/bin
    DATADIR =$$PREFIX/share

    DEFINES += DATADIR=\\\"$$DATADIR\\\" PKGDATADIR=\\\"$$PKGDATADIR\\\"

    # MAKE INSTALL target

    INSTALLS += target desktop iconxpm icon26 icon48 icon64

    target.path =$$BINDIR

    desktop.path = $$DATADIR/applications/hildon
    desktop.files += $${TARGET}.desktop
} else {
    # We want to enable building also outside scratchbox
    # but inside the awarenetcore source tree
    INCLUDEPATH += ../../api ../../common \
               ../../services/messaging
    LIBS += -L../../api -lawarenetcore \
    -L.././messages -lawarenetmessages \
    -L../../services -lawarenetcoreservices
}
