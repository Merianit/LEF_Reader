#include "mainwindow.h"
#include <QtWidgets>
#include "lef_graphic.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    mainWidget = new MainWidget(this);
    menuBar = new MenuBar(this);
    statusBar = new QStatusBar(this);
    lefData = nullptr;
    setMenuBar(menuBar);
    setStatusBar(statusBar);
    setCentralWidget(mainWidget);
    menuBar->fill();
    QObject::connect(menuBar->openAction, &QAction::triggered, this, &MainWindow::openFile);
    QObject::connect(mainWidget, &MainWidget::statusBarSignal, this, &MainWindow::statusBarMessage);
    resize(1920, 990);
    statusBar->showMessage("Ready");
    qDebug() << this->objectName();
    dumpObjectTree();
}

void MainWindow::openFile()
{
    mainWidget->graphicWidget->lef_object = nullptr;
    if(lefData)
        delete lefData;
    lefData = new DataSet();
    lefData -> readMacro();
    mainWidget->updateData(lefData->macro);
}

 void MainWindow::statusBarMessage(QString message)
 {
    statusBar->showMessage(message);
 }

