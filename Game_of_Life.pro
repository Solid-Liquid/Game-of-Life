TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    gameoflife.cpp

LIBS += -L"../../SFML/lib/"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += ../../SFML/include
DEPENDPATH += ../../SFML/include

HEADERS += \
    gameoflife.h \
    notes.h
