QT -= gui

TEMPLATE = lib
DEFINES += PERFORMANCESUITE_LIBRARY

CONFIG += c++14

CONFIG(debug, debug|release) {
    DLLDESTDIR = "C:\Users\jan-r\projects\wikiClient\build-wikiClient-Desktop_Qt_5_15_0_MSVC2019_64bit-Debug\debug"
} else {
    DLLDESTDIR = "C:\Users\jan-r\projects\wikiClient\build-wikiClient-Desktop_Qt_5_15_0_MSVC2019_64bit-Release\release"
}

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    performancecontext.cpp \
    performancesuite.cpp

HEADERS += \
    PerformanceSuite_global.h \
    performancecontext.h \
    performancesuite.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
