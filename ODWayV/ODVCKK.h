//====================================================================
//  ODVCKK.h
//  created 6.13.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _ODVCKK_H_963240FF4634998C509BD24ECCC8C303_
#define _ODVCKK_H_963240FF4634998C509BD24ECCC8C303_

#include <QObject>
#include <QVariant>
#include <ODUtil/ODCKK.h>

class ODVCKK : public QObject
{
    Q_OBJECT
public:
    explicit ODVCKK(QObject *parent = nullptr);

signals:

public slots:
    void setCKK(const QVariant &var_);

public slots:
    QStringList classifyList() const;
    QStringList kindFirstList(const QString &classify_ = "") const;
    QStringList kindSecondList(const QString &classify_ = "", const QString &kindFirst_ = "") const;

private:
    CKKPtr _ckk;
};

#endif // _ODVCKK_H_963240FF4634998C509BD24ECCC8C303_
