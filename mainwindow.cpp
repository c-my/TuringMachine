#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
//    ui(new Ui::MainWindow)
{
//    ui->setupUi(this);
    cw = new CentralWidget(this);
    helpMenu = new QMenu(this);
    aboutAction = new QAction(tr("关于"), this);
    connect(aboutAction, QAction::triggered, this, showAbout);
    helpMenu->setTitle(tr("帮助(&H)"));
    helpMenu->addAction(aboutAction);
    setCentralWidget(cw);
    menuBar()->addMenu(helpMenu);
    statusBar()->showMessage("欢迎使用环保图灵机！");
    connect(cw, CentralWidget::setStatus, this,[this](QString message)
    {
        statusBar()->showMessage(message, 0);
    });

}

MainWindow::~MainWindow()
{
    delete cw;
}

void MainWindow::showAbout()
{
    QMessageBox *aboutWindow = new QMessageBox(this);
   aboutWindow->setStandardButtons(QMessageBox::Ok);
   aboutWindow->setText(tr("<h1>TuringMachine</h1>"
                            "<p>Based on Qt 5.10.1 (MinGW 5.3.0, 32bit)</p>"
                            "Source Code: <a href=\"https://github.com/c-my/TuringMachine\">https://github.com/c-my/TuringMachine</a><br/>"
                           "Email: "
                           "<address><a href=\"mailto:cmy1113@outlook.com?subject=TuringMachine Feedback\">cmy1113@outlook.com</a>"
                           "</address>"));
   aboutWindow->show();
}
