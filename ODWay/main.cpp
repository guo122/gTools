//====================================================================
//  main.cpp
//  created 6.3.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#include <QDir>
#include <QQuickView>
#include <QGuiApplication>

#include <ODWayM/ODWayM.h>

#include <ODWayV/ODWayV.h>
#include <ODWayV/ODVCKK.h>
#include <ODWayV/ODVTime.h>
#include <ODWayV/TreeModel.h>
#include <ODWayV/ODVGoblin.h>
#include <ODWayV/ODVEfg.h>

int main(int argc, char* argv[])
{
    /**
     * Init Model layer.
     */
    // get home path.
    std::string dir = QDir::homePath().toStdString();
#ifdef Q_OS_IOS
    dir += "/Documents/list.db";
#else
    dir += "/brick/List/list.db";
#endif
    ODWayM::Instance(dir)->ReadDB();

    /**
     * Init View layer.
     */
    qmlRegisterType<ODWayV>("ODVWay", 1, 0, "ODVMain");
    qmlRegisterType<ODVTime>("ODVTime", 1, 0, "ODVTimeList");
    qmlRegisterType<TreeModel>("ODVTime", 1, 0, "ODTreeModel");
    qmlRegisterType<ODVCKK>("ODVCKK", 1, 0, "VCKK");
    qmlRegisterType<ODVGoblin>("ODVGoblin", 1, 0, "ODVGoblinList");
    qmlRegisterType<ODVEfg>("ODVEfg", 1, 0, "ODVEfgList");

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
