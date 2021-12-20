QT       += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    finddialog.cpp \
    godialog.cpp \
    main.cpp \
    spreadsheet.cpp

HEADERS += \
    finddialog.h \
    godialog.h \
    spreadsheet.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../Desktop/icons/cut_icon.png \
    ../../Desktop/icons/new_file.png \
    ../../Desktop/icons/quit_icon.png \
    ../../Desktop/icons/save_file.png \
    ../../Desktop/icons/search_icon.png

RESOURCES += \
    icons.qrc

FORMS += \
    finddialog.ui \
    godialog.ui
