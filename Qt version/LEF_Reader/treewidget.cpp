#include "treewidget.h"

TreeWidget::TreeWidget(QWidget *parent) : QTreeWidget(parent)
{}

void TreeWidget::fill(LEF::Macro & lefObject){
    QString label("Project tree");
    setHeaderLabel(label);
    QString root_name(QString::fromStdString(lefObject.name));
    QTreeWidgetItem* root = new QTreeWidgetItem(this, QStringList(root_name));

    for(int i = 0; i < lefObject.pin_array.size(); i++){
        QString child_name(QString::fromStdString((lefObject.pin_array[i].name)));
        QTreeWidgetItem* child = new QTreeWidgetItem(root, QStringList(child_name));
    }
    // Установка элемента корневым элементом дерева
    addTopLevelItem(root);

}
