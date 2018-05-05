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

//    TuringMachine tm;
//    tm.setGrammar("0n1n.json");
//    tm.setTestStr("");
//    if(tm.run())
//        qDebug()<<"OK";
//    else
//        qDebug()<<"not ok";
    return a.exec();
}
