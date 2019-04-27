//====================================================================
//  TreeItem.h
//  created 6.7.18
//  written by odddd0
//
//  https://github.com/odddd0/ODWay
//====================================================================

#ifndef _TREEITEM_H_74E069809DFF059CEB8103FD170E113F_
#define _TREEITEM_H_74E069809DFF059CEB8103FD170E113F_

#include "ODMBase/ODBaseTypes.h"

#include <QList>
#include <QVariant>
#include <QStringList>
#include <QModelIndex>

class TreeItem
{
public:
    TreeItem();
    TreeItem(const StringList &data, TreeItem* parent);
    ~TreeItem();

    void appendChild(TreeItem *child);
    void deleteAllChild();

    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem *parent();
    void setParent(TreeItem *parent);

private:
    TreeItem *m_parentItem;
    QList<TreeItem*> m_childItems;
    StringList m_itemData;
};

#endif // _TREEITEM_H_74E069809DFF059CEB8103FD170E113F_
