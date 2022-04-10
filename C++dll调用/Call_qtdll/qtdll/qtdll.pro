TEMPLATE     = lib
CONFIG	    += dll
SOURCES	     = main.cpp \
    QtDirDlg.cpp

TARGET	     = qtdialog
DLLDESTDIR   = $$[QT_INSTALL_PREFIX]/bin

include(./src/qtwinmigrate.pri)

FORMS += \
    QtDirDlg.ui

HEADERS += \
    QtDirDlg.h
