//====================================================================
//  ODVCKK.cpp
//  created 6.13.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================


#include "ODVCKK.h"

Q_DECLARE_METATYPE(CKKPtr);

ODVCKK::ODVCKK(QObject *parent)
    : QObject(parent)
    , _ckk(NULL)
{

}

void ODVCKK::setCKK(const QVariant &var_)
{
    _ckk = var_.value<CKKPtr>();
}

QStringList ODVCKK::classifyList() const
{
    QStringList Result;
    if (_ckk)
    {
        StringList tmpList;
        _ckk->classifyList(tmpList);
        std::for_each(tmpList.begin(), tmpList.end(), [&Result](std::string &x){
            Result.push_back(QString::fromStdString(x));
        });
    }
    return Result;
}

QStringList ODVCKK::kindFirstList(const QString &classify_) const
{
    QStringList Result;
    if (_ckk)
    {
        StringList tmpList;
        _ckk->kindFirstList(tmpList, classify_.toStdString());
        std::for_each(tmpList.begin(), tmpList.end(), [&Result](std::string &x){
            Result.push_back(QString::fromStdString(x));
        });
    }
    return Result;
}

QStringList ODVCKK::kindSecondList(const QString &classify_, const QString &kindFirst_) const
{
    QStringList Result;
    if (_ckk)
    {
        StringList tmpList;
        _ckk->kindSecondList(tmpList, classify_.toStdString(), kindFirst_.toStdString());
        std::for_each(tmpList.begin(), tmpList.end(), [&Result](std::string &x){
            Result.push_back(QString::fromStdString(x));
        });
    }
    return Result;
}
