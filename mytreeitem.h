#ifndef MYTREEITEM_H
#define MYTREEITEM_H

#include <QTreeWidgetItem>



class MyTreeWidgetItem : public QTreeWidgetItem {
    Q_OBJECT
  public:
  MyTreeWidgetItem(QTreeWidget* parent):QTreeWidgetItem(parent){}
  private:
  bool operator<(const MyTreeWidgetItem &other)const {
     int column = treeWidget()->sortColumn();
     return text(column).toLower() < other.text(column).toLower();
  }
};

#endif // MYTREEITEM_H
