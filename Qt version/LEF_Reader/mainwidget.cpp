#include "mainwidget.h"

MainWidget::MainWidget(QWidget* parent ) : QWidget(parent)
{
   mainLayout = new QHBoxLayout();
   graphicWidget = new LEF_Graphic(this);
   tableWidget = new TableWidget(this);
   treeWidget = new TreeWidget(this);
   scrollArea = new QScrollArea(this);
   QObject::connect(graphicWidget, &LEF_Graphic::statusBarSignaltoMainWgt, this, &MainWidget::statustoBarfromGraphic);
   tableWidget->setStyleSheet("background-color: transparent");

}

void MainWidget::setScrollArea()
{
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(graphicWidget);
    // Устанавливаем флаги виджетов прокрутки, чтобы они всегда отображались
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->resize(1200, 1000);
}

void MainWidget::setMainLayout()
{
    mainLayout->addWidget(treeWidget, 0, Qt::AlignLeft);
    mainLayout->addStretch();
    mainLayout->addWidget(scrollArea, 2);
    mainLayout->addStretch();
    mainLayout->addWidget(tableWidget, 0, Qt::AlignRight);
}

 void MainWidget::updateData(LEF::Macro & lefObject)
 {
    graphicWidget->fill(&lefObject);
    tableWidget->clear();
    tableWidget->fill(lefObject, graphicWidget);
    treeWidget->clear();
    treeWidget->fill(lefObject);
    setScrollArea();
    setMainLayout();
    setLayout(mainLayout);

 }

 void MainWidget::statustoBarfromGraphic(QString message)
 {
     emit statusBarSignal(message);
 }
