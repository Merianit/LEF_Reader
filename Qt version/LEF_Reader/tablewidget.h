#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QtWidgets>
#include <QTableWidget>
#include <LEF.h>
#include "Macro.h"
#include "lef_graphic.h"

class TableWidget : public QTableWidget
{
    Q_OBJECT
public:
    void fill(LEF::Macro & lefObject, LEF_Graphic* graphicWidget);
    explicit TableWidget(QWidget *parent = nullptr);

};

#endif // TABLEWIDGET_H
