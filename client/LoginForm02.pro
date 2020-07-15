QT += widgets gui

SOURCES += \
    main.cpp \
    mainform.cpp \
    loginform.cpp \
    registerform.cpp \
    panel.cpp \
    mainwindow.cpp \
    widget.cpp

HEADERS += \
    mainform.h \
    loginform.h \
    registerform.h \
    ../general.h \
    ../general.h \
    panel.h \
    mainwindow.h \
    widget.h

FORMS += \
    panel.ui \
    mainwindow.ui \
    widget.ui

RESOURCES += \
    TCPChatResource.qrc

DISTFILES += \
    TCPchat.pro.user \
    TCPchat.pro.user.3.2-pre1
