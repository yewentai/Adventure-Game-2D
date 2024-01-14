QT       += core gui

TARGET = world
TEMPLATE = lib
CONFIG += c++20
DEFINES += WORLD_LIBRARY
DEFINES += "BUILDNUMBER=600"
SOURCES += world.cpp
QMAKE_CXXFLAGS += -std=c++20

HEADERS += world.h\
        world_global.h\
        pathfinder_function.h\
        pathfinder_class.h

#place where library will be put on deployment, replace this by your own operating system and map
#linux-g++ {
#  target.path = .
#  INSTALLS += target
#}

unix {
    target.path = .
}
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
