//====================================================================
//  TreeModel.h
//  created 6.7.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _TREEMODEL_H_15B5DCB0C305E16CAAF0D86C4FD23BFE_
#define _TREEMODEL_H_15B5DCB0C305E16CAAF0D86C4FD23BFE_

#include <QAbstractItemModel>

#include "TreeItem.h"

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(QString daySum READ daySum WRITE setDaySum NOTIFY daySumChanged)
    enum ItemRoles {
        NAME = Qt::UserRole + 1,
        SIMPLIFY,
        OD_CLASSIFY,
        OD_KINDFIRST,
        OD_KINDSECOND
    };
public:
    TreeModel(QObject *parent = NULL);
    ~TreeModel();

    void appendChild(const QModelIndex& index);
    bool removeRows(int row, int count, QModelIndex parent);

    QModelIndex parent(const QModelIndex &index) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    QString daySum() const;

public slots:
    void setDaySum(QString daySum);
    void clearCKK();
    bool isSelectHighlight(const QString &classify_, const QString &kindFirst_, const QString &kindSecond_);

public slots:
    void updateSum(const bool &allSum_ = false);
    QStringList setSelectIndex(const QModelIndex &index_);
    QModelIndex getFirstExpand();
    QModelIndex getSecondExpand();
    bool isFirstExpand();
    bool isSecondExpand();

signals:
    void daySumChanged(QString daySum);

private:
    TreeItem *m_rootItem;
    std::vector<StringList> _classifyList;
    std::vector<std::vector<StringList>> _kindFirstList;
    std::vector<std::vector<std::vector<StringList>>> _kindSecondList;
    QString m_daySum;
    StringList _CKKCur;
    QModelIndex _firstExpand;
    QModelIndex _secondExpand;
    bool _isFirstExpand;
    bool _isSecondExpand;
};
#endif // _TREEMODEL_H_15B5DCB0C305E16CAAF0D86C4FD23BFE_
