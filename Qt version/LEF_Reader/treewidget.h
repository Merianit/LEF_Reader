#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QtWidgets>
#include <QTreeWidget>
#include <LEF.h>
#include "Macro.h"

class TreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    void fill(LEF::Macro & lefObject);
    explicit TreeWidget(QWidget *parent = nullptr);
};

#endif // TREEWIDGET_H
