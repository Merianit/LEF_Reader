#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QObject>
#include <QtWidgets>
#include "lef_graphic.h"
#include "tablewidget.h"
#include "treewidget.h"
#include "LEF.h"
#include "Macro.h"

class MainWidget : public QWidget
{
    Q_OBJECT
private:
    QScrollArea* scrollArea;
    QHBoxLayout* mainLayout;
    TableWidget* tableWidget;
    TreeWidget* treeWidget;
public:
    LEF_Graphic* graphicWidget;
    MainWidget(QWidget* parent = nullptr );
    void setScrollArea();
    void setMainLayout();
    void updateData(LEF::Macro & lefObject);
public slots:
    void statustoBarfromGraphic(QString message);
signals:
    void statusBarSignal(QString message);

};

#endif // MAINWIDGET_H
