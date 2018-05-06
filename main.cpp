#include "mainwindow.h"
#include <QApplication>
#include "turingmachine.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setFont(QFont("Microsoft YaHei UI",9));
    MainWindow w;
    w.show();

    return a.exec();
}
