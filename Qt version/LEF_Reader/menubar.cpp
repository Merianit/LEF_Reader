#include "menubar.h"
#include "mainwindow.h"

MenuBar::MenuBar(QWidget *parent) : QMenuBar(parent)
{}

void MenuBar::fill(){
    fileMenu = new QMenu("File");
    openAction = new QAction("Open", this);
    exitAction = new QAction("Exit", this);
    fileMenu->addAction(openAction);
    fileMenu->addAction(exitAction);
    QObject::connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);
    addMenu(fileMenu);
}
