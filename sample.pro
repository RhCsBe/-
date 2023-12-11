QT       += core gui multimedia network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    beginning.cpp \
    chess.cpp \
    ending.cpp \
    forbidchess.cpp \
    judgment.cpp \
    main.cpp \
    chessboard.cpp \
    networkplay.cpp \
    rule.cpp \
    setting.cpp \
    singleplay.cpp \
    step.cpp \
    worker.cpp

HEADERS += \
    beginning.h \
    chess.h \
    chessboard.h \
    ending.h \
    forbidchess.h \
    judgment.h \
    networkplay.h \
    rule.h \
    setting.h \
    singleplay.h \
    step.h \
    worker.h

FORMS += \
    beginning.ui \
    chessboard.ui \
    ending.ui \
    forbidchess.ui \
    rule.ui \
    setting.ui \
    worker.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc
