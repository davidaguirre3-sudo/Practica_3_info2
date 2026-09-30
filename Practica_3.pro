TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ARCHIVOS.cpp \
        ENCRIPTACION.cpp \
        LZ78.cpp \
        RLE.cpp \
        main.cpp

HEADERS += \
    ARCHIVOS.h \
    ENCRIPTACION.h \
    LZ78.h \
    RLE.h
