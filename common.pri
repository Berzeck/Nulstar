# Avoid SDK version warning
CONFIG += sdk_no_version_check
CONFIG += unversioned_soname

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# Release with debug info
QMAKE_CFLAGS_RELEASE -= $$QMAKE_CFLAGS_RELEASE
QMAKE_CFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_CXXFLAGS_RELEASE -= $$QMAKE_CXXFLAGS_RELEASE
QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE -= $$QMAKE_LFLAGS_RELEASE
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

win32:CONFIG += skip_target_version_ext
!win32:CONFIG += unversioned_libname

# Qt 5.12 supports macOS: 10.12 10.13 10.14
# macos:QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.12

# Platform Settings
macos:CONFIG   -= app_bundle
win32:DEFINES  += WIN32

CONFIG(debug, debug|release) {
  isEmpty(CUSTOMDESTDIR){
    TOP_OUTDIR=$$shadowed($$PWD)/debug
  } else {
    TOP_OUTDIR=$$CUSTOMDESTDIR
  }
} else {
  isEmpty(CUSTOMDESTDIR){
    TOP_OUTDIR=$$shadowed($$PWD)/release
  } else {
    TOP_OUTDIR=$$CUSTOMDESTDIR
  }
  DEFINES += QT_NO_DEBUG_OUTPUT
}

APP_DOMAIN=Nulstar
APP_ROLE=Role_ServiceController
APP_ROLE_VERSION=0.1
APP_NAME=Nulstar Main Controller
APP_VERSION=0.1.0
APP_VERSION_NAME=OneEye Baby Ninja Egg

DESTDIR=$$TOP_OUTDIR
LIBRARIES_OUTDIR=$$TOP_OUTDIR/Libraries/CPP/Nulstar/$$NULSTAR_LIBRARIES_VERSION
QT_LIBRARIES_OUTDIR=$$TOP_OUTDIR/Libraries/CPP/Qt/$$[QT_VERSION]
MODULES_OUTDIR=$$TOP_OUTDIR/Modules
LIBS += -L$$LIBRARIES_OUTDIR
INCLUDEPATH += $$TOP_BUILDDIR

