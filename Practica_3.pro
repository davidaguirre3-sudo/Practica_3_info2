TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        LZ78.cpp \
        RLE.cpp \
        XOR.cpp \
        main.cpp

HEADERS += \
    LZ78.h \
    RLE.h \
    XOR.h
