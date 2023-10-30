#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <menubar.h>
#include <dataset.h>
#include <mainwidget.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
private:
    MainWidget *mainWidget;
    MenuBar* menuBar;
    QStatusBar* statusBar;
    DataSet* lefData;
public slots:
    void openFile();
    void statusBarMessage(QString message);
signals:

};

#endif // MAINWINDOW_H
