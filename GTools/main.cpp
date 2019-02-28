//====================================================================
//  main.cpp
//  created 2.20.19
//  written by gzy
//
//  https://github.com/guo122
//====================================================================

#include <QDir>
#include <QQuickView>
#include <QGuiApplication>

#include <GToolsM/GToolsM.h>
#include <GToolsV/GTVRandomList.h>

int main(int argc, char* argv[])
{
    /**
     * Init Model layer.
     */
    // get home path.
    QString dir = QDir::homePath();
#ifdef Q_OS_IOS
    dir += "/Documents/list.db";
#else
    dir += "/Documents/list.db";
#endif
    GToolsM::Instance()->Init(dir);
    GToolsM::Instance()->ReadDB();

    /**
     * Init View layer.
     */
    qmlRegisterType<GTVRandomList>("GTVRandomList", 1, 0, "GTVRandomListQML");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc,argv);

    QQuickView view;
    view.setFlags(Qt::MaximizeUsingFullscreenGeometryHint);
    view.setSource(QUrl("qrc:///main.qml"));

    if (view.status() == QQuickView::Error)
        return -1;

    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();

    return app.exec();
}
