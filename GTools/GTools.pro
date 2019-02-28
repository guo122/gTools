QT += quick sql
CONFIG += c++11

ios:QMAKE_INFO_PLIST += Info.plist
# amend Info.plist
# With Xcode:  Application supports iTunes file sharing
# With Text Ediotr:
#                   <key>UIFileSharingEnabled</key>
#                   <true/>

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

CONFIG(debug, debug|release){
    macx: LIBS += -L$$PWD/../build-GToolsM-Desktop_Qt_5_12_0_clang_64bit-Debug/ -lGToolsM
    macx: PRE_TARGETDEPS += $$PWD/../build-GToolsM-Desktop_Qt_5_12_0_clang_64bit-Debug/libGToolsM.a

    macx: LIBS += -L$$PWD/../build-GToolsP-Desktop_Qt_5_12_0_clang_64bit-Debug/ -lGToolsP
    macx: PRE_TARGETDEPS += $$PWD/../build-GToolsP-Desktop_Qt_5_12_0_clang_64bit-Debug/libGToolsP.a

    macx: LIBS += -L$$PWD/../build-GToolsV-Desktop_Qt_5_12_0_clang_64bit-Debug/ -lGToolsV
    macx: PRE_TARGETDEPS += $$PWD/../build-GToolsV-Desktop_Qt_5_12_0_clang_64bit-Debug/libGToolsV.a

    ios: LIBS += -L$$PWD/../build-GToolsM-Qt_5_12_0_for_iOS-Debug/ -lGToolsM
    ios: PRE_TARGETDEPS += $$PWD/../build-GToolsM-Qt_5_12_0_for_iOS-Debug/libGToolsM.a

    ios: LIBS += -L$$PWD/../build-GToolsP-Qt_5_12_0_for_iOS-Debug/ -lGToolsP
    ios: PRE_TARGETDEPS += $$PWD/../build-GToolsP-Qt_5_12_0_for_iOS-Debug/libGToolsP.a

    ios: LIBS += -L$$PWD/../build-GToolsV-Qt_5_12_0_for_iOS-Debug/ -lGToolsV
    ios: PRE_TARGETDEPS += $$PWD/../build-GToolsV-Qt_5_12_0_for_iOS-Debug/libGToolsV.a
} else {
    macx: LIBS += -L$$PWD/../build-GToolsM-Desktop_Qt_5_12_0_clang_64bit-Release/ -lGToolsM
    macx: PRE_TARGETDEPS += $$PWD/../build-GToolsM-Desktop_Qt_5_12_0_clang_64bit-Release/libGToolsM.a

    macx: LIBS += -L$$PWD/../build-GToolsP-Desktop_Qt_5_12_0_clang_64bit-Release/ -lGToolsP
    macx: PRE_TARGETDEPS += $$PWD/../build-GToolsP-Desktop_Qt_5_12_0_clang_64bit-Release/libGToolsP.a

    macx: LIBS += -L$$PWD/../build-GToolsV-Desktop_Qt_5_12_0_clang_64bit-Release/ -lGToolsV
    macx: PRE_TARGETDEPS += $$PWD/../build-GToolsV-Desktop_Qt_5_12_0_clang_64bit-Release/libGToolsV.a

    ios: LIBS += -L$$PWD/../build-GToolsM-Qt_5_12_0_for_iOS-Release/ -lGToolsM
    ios: PRE_TARGETDEPS += $$PWD/../build-GToolsM-Qt_5_12_0_for_iOS-Release/libGToolsM.a

    ios: LIBS += -L$$PWD/../build-GToolsP-Qt_5_12_0_for_iOS-Release/ -lGToolsP
    ios: PRE_TARGETDEPS += $$PWD/../build-GToolsP-Qt_5_12_0_for_iOS-Release/libGToolsP.a

    ios: LIBS += -L$$PWD/../build-GToolsV-Qt_5_12_0_for_iOS-Release/ -lGToolsV
    ios: PRE_TARGETDEPS += $$PWD/../build-GToolsV-Qt_5_12_0_for_iOS-Release/libGToolsV.a
}
