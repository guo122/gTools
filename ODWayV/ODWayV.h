//====================================================================
//  ODWayV.h
//  created 6.3.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODWAYV_H_9F433F37BF2CF3966F72117B88A35683_
#define _ODWAYV_H_9F433F37BF2CF3966F72117B88A35683_

#include <QObject>

class ODWayV : public QObject
{
    Q_OBJECT

public:
    explicit ODWayV(QObject *parent = nullptr);

public slots:
    QString getDescription(const QString &name_);

private:
};

#endif // _ODWAYV_H_9F433F37BF2CF3966F72117B88A35683_
