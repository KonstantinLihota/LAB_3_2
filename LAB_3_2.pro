QT       += core gui
QT += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MainWindow_FileBrowser.cpp \
    adapter.cpp \
    byfile.cpp \
    bytype.cpp \
    filestrateg.cpp \
    filetablemodel.cpp \
    main.cpp \
    observer.cpp

HEADERS += \
    MainWindow_FileBrowser.h \
    adapter.h \
    byfile.h \
    bytype.h \
    filestrateg.h \
    filetablemodel.h \
    observer.h

FORMS += \
    MainWindow_FileBrowse.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
