QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chess.cpp \
    ending.cpp \
    judgment.cpp \
    main.cpp \
    chessboard.cpp \
    singleplay.cpp \
    step.cpp

HEADERS += \
    chess.h \
    chessboard.h \
    ending.h \
    judgment.h \
    singleplay.h \
    step.h

FORMS += \
    chessboard.ui \
    ending.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc
