#include "tablewidget.h"


TableWidget::TableWidget(QWidget *parent) : QTableWidget(parent)
{}


void TableWidget::fill(LEF::Macro & lefObject, LEF_Graphic* graphicWidget){
    setRowCount(lefObject.mapLayers.size() + 1);
    setColumnCount(2);
    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);
    setShowGrid(false);
    setStyleSheet("QTableWidget { background-color: transparent;}");
    qDebug() << lefObject.mapLayers;

    // Set item widgets for the table
    QTableWidgetItem* item0 = new QTableWidgetItem();
    QLabel* label0 = new QLabel("<H2>Layers: <H2> ");
    setCellWidget(0, 1, label0);

    auto it = lefObject.mapLayers.begin();
    for(int i = 1; i < lefObject.mapLayers.size()+1; i++)
    {
        QTableWidgetItem* item = new QTableWidgetItem();
        QCheckBox* checkBox = new QCheckBox(this);
        checkBox->setProperty("id", it.key());
        setCellWidget(i, 0, checkBox);
        connect(checkBox, &QCheckBox::stateChanged, graphicWidget, &LEF_Graphic::onCheckBoxStateChanged);
        ++it;
    }
    setColumnWidth(0, 50);

    int line = 1;
    it = lefObject.mapLayers.begin();
    for(; it != lefObject.mapLayers.end(); ++it)
    {

        QTableWidgetItem* item = new QTableWidgetItem();
        QLabel* label = new QLabel(it.key(), this);
        setCellWidget(line, 1, label);
        line++;
    }
    setColumnWidth(1, 100);

//    QList <QTableWidgetItem*> widgets;
//    auto iter = mapLayers.begin();
//    for(int i = 1; i < mapLayers.size()+1; i++)
//    {
//        widgets.append(new QTableWidgetItem());
//        QComboBox* comboBox = new QComboBox(tableWidget);
//        QStringList colorNames = QColor::colorNames();
//        for(const QString & colorName : colorNames)
//            comboBox->addItem(colorName, QColor(colorName));
//        //comboBox->setItemDelegate(new ColorizedComboBoxDelegate);
//        comboBox->setProperty("id", iter.key());
//        ++iter;
//        setCellWidget(i, 2, comboBox);
//        QObject::connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &LEF_Graphic::comboBoxIndexChanged);

//    }
    //setColumnWidth(2, 100);
    update();
}
