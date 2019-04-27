QT += quick
CONFIG += c++11

ios:QMAKE_INFO_PLIST += Info.plist
# amend Info.plist
# With Xcode:  Application supports iTunes file sharing
# With Text Ediotr:
#                   <key>UIFileSharingEnabled</key>
#                   <true/>

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
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

INCLUDEPATH += $$PWD/../3rd/ODBase
DEPENDPATH += $$PWD/../3rd/ODBase
INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

LIBS += -lsqlite3

CONFIG(debug, debug|release){
    macx: LIBS += -L$$PWD/../3rd/ODBase/lib/clang64-Debug/ -lODMBase
    macx: PRE_TARGETDEPS += $$PWD/../3rd/ODBase/lib/clang64-Debug/libODMBase.a

    macx: LIBS += -L$$PWD/../3rd/ODBase/lib/clang64-Debug/ -lODUtil
    macx: PRE_TARGETDEPS += $$PWD/../3rd/ODBase/lib/clang64-Debug/libODUtil.a

    macx: LIBS += -L$$PWD/../build-ODWayM-Desktop_Qt_5_12_0_clang_64bit-Debug/ -lODWayM
    macx: PRE_TARGETDEPS += $$PWD/../build-ODWayM-Desktop_Qt_5_12_0_clang_64bit-Debug/libODWayM.a

    macx: LIBS += -L$$PWD/../build-ODWayP-Desktop_Qt_5_12_0_clang_64bit-Debug/ -lODWayP
    macx: PRE_TARGETDEPS += $$PWD/../build-ODWayP-Desktop_Qt_5_12_0_clang_64bit-Debug/libODWayP.a

    macx: LIBS += -L$$PWD/../build-ODWayV-Desktop_Qt_5_12_0_clang_64bit-Debug/ -lODWayV
    macx: PRE_TARGETDEPS += $$PWD/../build-ODWayV-Desktop_Qt_5_12_0_clang_64bit-Debug/libODWayV.a

    ios: LIBS += -L$$PWD/../3rd/ODBase/lib/ios-Debug/ -lODMBase
    ios: PRE_TARGETDEPS += $$PWD/../3rd/ODBase/lib/ios-Debug/libODMBase.a

    ios: LIBS += -L$$PWD/../3rd/ODBase/lib/ios-Debug/ -lODUtil
    ios: PRE_TARGETDEPS += $$PWD/../3rd/ODBase/lib/ios-Debug/libODUtil.a

    ios: LIBS += -L$$PWD/../build-ODWayM-Qt_5_12_0_for_iOS-Debug/ -lODWayM
    ios: PRE_TARGETDEPS += $$PWD/../build-ODWayM-Qt_5_12_0_for_iOS-Debug/libODWayM.a

    ios: LIBS += -L$$PWD/../build-ODWayP-Qt_5_12_0_for_iOS-Debug/ -lODWayP
    ios: PRE_TARGETDEPS += $$PWD/../build-ODWayP-Qt_5_12_0_for_iOS-Debug/libODWayP.a

    ios: LIBS += -L$$PWD/../build-ODWayV-Qt_5_12_0_for_iOS-Debug/ -lODWayV
    ios: PRE_TARGETDEPS += $$PWD/../build-ODWayV-Qt_5_12_0_for_iOS-Debug/libODWayV.a
} else {
    macx: LIBS += -L$$PWD/../3rd/ODBase/lib/clang64-Release/ -lODMBase
    macx: PRE_TARGETDEPS += $$PWD/../3rd/ODBase/lib/clang64-Release/libODMBa    se.a

    macx: LIBS += -L$$PWD/../3rd/ODBase/lib/clang64-Release/ -lODUtil
    macx: PRE_TARGETDEPS += $$PWD/../3rd/ODBase/lib/clang64-Release/libODUtil.a

    macx: LIBS += -L$$PWD/../build-ODWayM-Desktop_Qt_5_12_0_clang_64bit-Release/ -lODWayM
    macx: PRE_TARGETDEPS += $$PWD/../build-ODWayM-Desktop_Qt_5_12_0_clang_64bit-Release/libODWayM.a

    macx: LIBS += -L$$PWD/../build-ODWayP-Desktop_Qt_5_12_0_clang_64bit-Release/ -lODWayP
    macx: PRE_TARGETDEPS += $$PWD/../build-ODWayP-Desktop_Qt_5_12_0_clang_64bit-Release/libODWayP.a

    macx: LIBS += -L$$PWD/../build-ODWayV-Desktop_Qt_5_12_0_clang_64bit-Release/ -lODWayV
    macx: PRE_TARGETDEPS += $$PWD/../build-ODWayV-Desktop_Qt_5_12_0_clang_64bit-Release/libODWayV.a

    ios: LIBS += -L$$PWD/../3rd/ODBase/lib/ios-Release/ -lODMBase
    ios: PRE_TARGETDEPS += $$PWD/../3rd/ODBase/lib/ios-Release/libODMBase.a

    ios: LIBS += -L$$PWD/../3rd/ODBase/lib/ios-Release/ -lODUtil
    ios: PRE_TARGETDEPS += $$PWD/../3rd/ODBase/lib/ios-Release/libODUtil.a

    ios: LIBS += -L$$PWD/../build-ODWayM-Qt_5_12_0_for_iOS-Release/ -lODWayM
    ios: PRE_TARGETDEPS += $$PWD/../build-ODWayM-Qt_5_12_0_for_iOS-Release/libODWayM.a

    ios: LIBS += -L$$PWD/../build-ODWayP-Qt_5_12_0_for_iOS-Release/ -lODWayP
    ios: PRE_TARGETDEPS += $$PWD/../build-ODWayP-Qt_5_12_0_for_iOS-Release/libODWayP.a

    ios: LIBS += -L$$PWD/../build-ODWayV-Qt_5_12_0_for_iOS-Release/ -lODWayV
    ios: PRE_TARGETDEPS += $$PWD/../build-ODWayV-Qt_5_12_0_for_iOS-Release/libODWayV.a
}


