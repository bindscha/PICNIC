TEMPLATE = app
TARGET = testsender

HEADERS += src/testsender.h
SOURCES += src/testsender.cpp \
	   src/main.cpp

# This part is intended for Maemo packaging, hence
# the conditional which will be used in the package build script
maemo5 {
    #VARIABLES
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }
    
    INCLUDEPATH += /usr/include/awarenetcore \
    		   /usr/include/picniccore
    LIBS +=  -lawarenetcore \
             -lawarenetmessages \
             -lawarenetcoreservices \
	     -lpicniccore

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
