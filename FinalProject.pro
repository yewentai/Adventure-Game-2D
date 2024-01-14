QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
QMAKE_CXXFLAGS += -std=c++20
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    my_text_editor.cpp \
    controllers/protagonist_control.cpp \
    controllers/penemy_control.cpp \
    controllers/level_control.cpp \
    models/game.cpp \
    models/gate.cpp \
    models/penemy.cpp \
    models/xenemy.cpp \
    models/protagonist.cpp \
    views/graphic.cpp \
    views/graphic_protagonist.cpp \
    views/text.cpp \
    views/graphic_penemy.cpp

HEADERS += \
    mainwindow.h \
    models/gate.h \
    models/tileadapter.h \
    models/protagonist.h \
    my_text_editor.h \
    my_slider.h \
    controllers/protagonist_control.h \
    controllers/penemy_control.h \
    controllers/level_control.h \
    models/game.h \
    models/protagonist.h \
    models/healthpack.h \
    models/penemy.h \
    models/xenemy.h \
    models/tileadapter.h \
    views/graphic.h \
    views/graphic_enemy.h \
    views/graphic_gate.h \
    views/graphic_healthpack.h \
    views/graphic_markedtile.h \
    views/graphic_penemy.h \
    views/graphic_poison.h \
    views/graphic_protagonist.h \
    views/graphic_tile.h \
    views/graphic_xenemy.h \
    views/graphic_background_brick.h \
    views/graphic_background_grassbrick.h \
    views/graphic_background_grassflower.h \
    views/graphic_background_grassworld.h \
    views/graphic_background_greengrass.h \
    views/graphic_background_lightgrass.h \
    views/graphic_background_pool.h \
    views/graphic_background_road.h \
    views/graphic_background_yellowgrass.h \
    views/text.h \
    views/text_background.h \
    views/text_enemy.h \
    views/text_healthpack.h \
    views/text_markedtile.h \
    views/text_penemy.h \
    views/text_protagonist.h \
    views/text_tile.h \
    views/text_xenemy.h \
    views/game_over.h



FORMS +=

RESOURCES += \
    images.qrc


# # Default rules for deployment.
# qnx: target.path = /tmp/$${TARGET}/bin
# else: unix:!android: target.path = /opt/$${TARGET}/bin
# !isEmpty(target.path): INSTALLS += target

unix: LIBS += -L$$PWD/build-world-Desktop-Debug/ -lworld
macx: LIBS += -L$$PWD/lib/ -lworld.1.0.0


INCLUDEPATH += $$PWD/build-world-Desktop-Debug
DEPENDPATH += $$PWD/build-world-Desktop-Debug

win32: LIBS += -L$$PWD/lib/ -lworld
INCLUDEPATH += $$PWD/lib
DEPENDPATH += $$PWD/lib
