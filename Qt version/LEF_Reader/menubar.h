#ifndef MENUBAR_H
#define MENUBAR_H

#include <QWidget>
#include <QtWidgets>

class MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    QMenu* fileMenu;
    QAction* openAction;
    QAction* exitAction;
    explicit MenuBar(QWidget *parent = nullptr);
    void fill();

};

#endif // MENUBAR_H
