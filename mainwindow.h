#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include "centralwidget.h"



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    CentralWidget *cw;
    QMenu *helpMenu;
    QAction *aboutAction;

    void showAbout();
};

#endif // MAINWINDOW_H
