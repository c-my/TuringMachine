#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QListWidget>
#include <QTimer>
#include "turingmachine.h"
#include "papertape.h"

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = nullptr);
    ~CentralWidget();

signals:
    void setStatus(QString message);

public slots:
    void importJson();
    void loadTape();
    void stepCheck();
    void autoCheck();


private:
    QVBoxLayout *mainlayout, *vsublayout;
    QFormLayout *formlayout;
    QHBoxLayout *hlayout;
    QLineEdit   *nameEdit, *teststrEdit;
    QLineEdit   *allStatesEdit, *alphabetEdit, *inputEdit, *initialStateEdit, *blankEdit, *finialStatesEdit;
    QPushButton *importButton;
    QPushButton *loadButton, *checkByStep, *resetButton, *autoCheckButton;

    QListWidget *listWidget;

    QGraphicsScene  *scene;
    QGraphicsView   *view;
    PaperTape       *tape;

    QTimer *autoCheckTimer;

    TuringMachine *machine;
    bool machineReady = true;
};

#endif // CENTRALWIDGET_H
