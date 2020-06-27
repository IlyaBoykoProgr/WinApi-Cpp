system(taskkill /f /im test.exe);
TEMPLATE = app
CONFIG += c++17
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -fexceptions -static -static-libgcc -static-libstdc++ -g -static-libgcc -static-libstdc++

SOURCES += main.cpp

HEADERS += \
    count.h
LIBS+= -lgdi32
